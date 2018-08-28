#!/usr/bin/env python

#                 _ _                          _            _            
#          ______| (_)_ __ ___   ___ _ __  ___(_) ___  _ __( )__         
#         |_  / _` | | '_ ` _ \ / _ \ '_ \/ __| |/ _ \| '_ \/ __|        
#          / / (_| | | | | | | |  __/ | | \__ \ | (_) | | | \__ \        
#         /___\__,_|_|_| |_| |_|\___|_| |_|___/_|\___/|_| |_|___/        
#  _                                                       _             
# (_)___ ___ _   _  ___     __ _  ___ _ __   ___ _ __ __ _| |_ ___  _ __ 
# | / __/ __| | | |/ _ \   / _` |/ _ \ '_ \ / _ \ '__/ _` | __/ _ \| '__|
# | \__ \__ \ |_| |  __/  | (_| |  __/ | | |  __/ | | (_| | || (_) | |   
# |_|___/___/\__,_|\___|   \__, |\___|_| |_|\___|_|  \__,_|\__\___/|_|   
#                          |___/                                         
#
#                     it really whips the llama's ass
#
# You may have noticed that there is an issue (currently #46) on the GitHub,
# containing a list of functions. This is the list of (almost) all functions
# in the project, grouped by platform and file. We use this to keep track
# of how much functions we have decompiled so far. Of course, it's hard to
# keep up the list in sync with the code. Thus, I wrote this /little/ tool
# that basically reads through every code file and searches for the string
# "(F)". This is a "checkmark" we put in front of a function (in the code)
# when it's fully decompiled *and* working. So, for every file, it gets a 
# list of the decompiled functions and cuts out the function name.
# Next (actually before, but anyways), it "downloads" the issue using GitHub
# API. It actually downloads the Markdown source code of the issue, and parses
# it into a list. Then, it compares the current list (on GitHub) and the
# list it has generated from the source file, and checks if there are 
# functions that are marked (F) in the code and not in the list. It also works
# in the opposite way, if the function is checked in the list but not marked
# (F) in the code. It also checks if a function marked (F) is missing from
# the list, and adds it automagically (if AUTO_ADD_MISSING is True).
# It dynamically updates that list, and when finished, generates a brand new
# Markdown file that is either written down to stdout or copied to the 
# clipboard (if USE_CLIPBOARD is True). Note that the latter requires
# pyperclip, which can be installed using pip.

# Command-line usage:
# $ python issue_generator.py [arg1] [arg2] ...
# or you can chmod +x it and do
# $ ./issue_generator.py [arg1] [arg2] ...
# where [argN] is + or - an option (see below)
# example:
# $ ./issue_generator.py +warn -hint -clipboard
# = force show warnings, hide hints and don't use clipboard
# you can also use short args
# $ ./issue_generator.py +w -h -c

# increment this plz
# rev 11
# 2018-01-21


from urllib.request import urlopen
import json
import os.path
import sys
import itertools

def Warn(msg):
	if SHOW_WARN:
		print("[WARN--------] " + str(msg))

def Hint(msg):
	if SHOW_HINT:
		print("[----HINT----] " + str(msg))

def Status(msg):
	if SHOW_STATUS:
		print("[--------STAT] " + str(msg))

# STEP
#  _ 
# / |
# | |
# | |
# |_|
# 
# Global settings

def isarg(arg, short, default):
	if any(x for x in sys.argv if x.strip().lower() in ["+" + arg, "+" + short]):
		return True
	elif any(x for x in sys.argv if x.strip().lower() in ["-" + arg, "-" + short]):
		return False
	else:
		return default

ISSUE_ID = 			46 								# ID of the issue on GitHub (for the API request)
SHOW_WARN = 		isarg("warn", 		"w", True) 	# Show warnings (error messages)
SHOW_HINT = 		isarg("hint", 		"h", True) 	# Show hints (e.g. function checked in list but not (F) in file)
SHOW_STATUS = 		isarg("status", 	"s", False)	# Show status messages (function added successfully yay)
AUTO_ADD_MISSING = 	isarg("addmissing", "m", True) 	# If a function is marked (F) in file but is missing in the list, add it to the list
USE_CLIPBOARD = 	isarg("clipboard", 	"c", True) 	# Copy output into clipboard instead of outputting it to the console
SHOW_UNIMPL =		isarg("showunimpl", "u", False)	# At the end, output a list of unimplemented (unchecked) functions
USE_REPR =			isarg("userepr", 	"r", False)	# Debugging purposes. When outputting a list (e.g. SHOW_UNIMPL), use repr()
SHOW_ADDED =		isarg("showadded", 	"a", False)	# Show a plain list of added functions
SHOW_FILES_STATS =	isarg("showfiles",	"f", False) # Show number of implemented functions by file
UNIMPL_NEUTRAL =	isarg("uneutral", 	"n", False) # for showunimp, show only GAME functions
UNIMPL_PC		 =	isarg("upc", 		"p", False) # for showunimp, show only SPEC_PC_N functions
SHOW_DUPL =			isarg("showdupl",	"d", True)  # show duplicate functions among each platform
AUTOREMOVE_DUPL =	isarg("remdupl",	"e", False) # automatically remove duplicates

if not os.path.isfile("README.md"):
	os.chdir("..")

if not os.path.isfile("README.md"):
	Warn("cannot find README.md in current or parent directory, are you in the correct folder?")

# STEP
#  ____  
# |___ \ 
#   __) |
#  / __/ 
# |_____|
# 
# Download the current list

body = urlopen("https://api.github.com/repos/TOMB5/TOMB5/issues/46").read().decode("utf8")
issue = json.loads(body)["body"] # loads the Markdown source of the issue

# STEP
#  _____ 
# |___ / 
#   |_ \ 
#  ___) |
# |____/ 
# 
# Parsing the issue source (Markdown)

issue = [x for x in issue.replace("\r\n", "\n").split("\n") if x] # get a clean line array without empty ones
platforms = {}
curplat = ""
curfile = ""
comments = {} # dictionary for when there is content after the function name in the list, i.e. comments, so that it's not erased
for idx, x in enumerate(issue):
	if not x.strip():
		continue

	if "#### " in x: 		# level 2 header - file
		curfile = x[5:]
		if curfile not in platforms[curplat]:
			platforms[curplat][curfile] = {}
		continue
	elif "### " in x:		# level 1 header - platform
		curplat = x[4:]
		if curplat not in platforms:
			platforms[curplat] = {}
		continue

	if len([c for c in x if c == "`"]) != 2:
		Warn("syntax error at line %d, function name is not correctly surrounded by ` -- ignoring : %s" % (idx, x))
		continue

	fname = x[7:x.rfind("`")]

	if len(x) - x.rfind("`") > 1:
		comment = x[x.rfind("`") + 1:]
		if comment:
			comments[fname] = comment

	if fname in platforms[curplat][curfile]:
		Warn("duplicate function '%s'" % fname)

	platforms[curplat][curfile][fname] = "[x]" in x

# STEP
#  _  _   
# | || |  
# | || |_ 
# |__   _|
#    |_|  
#
# Let the actual shit be done

Status("working for platforms: " + ", ".join(sorted(platforms.keys())))

added = []
addedFiles = []
unimplwarn = {p: {f: [] for f in platforms[p]} for p in platforms}
missing = {p: [] for p in platforms}
def getfline(path):
	with open(path, 'r') as fp:
		return [x.replace("\t", "    ") for x in fp.read().replace("\r\n", "\n").split('\n') if x]

for plat in sorted(platforms.keys()):
	for file in sorted(platforms[plat].keys()):
		path = os.path.join(plat, file)
		if not os.path.isfile(path):
			Warn("file does not exist - skipping -- '%s'" % path)
			continue

		file_lines = getfline(path)
		un_funcs = [l for l in file_lines if "] - Unimpl" in l]
		unm_funcs = [(i, l) for i, l in enumerate(file_lines) if "Unimpl();" in l]

		for i in range(len(un_funcs)):
			a = un_funcs[i]
			a = a[a.index("[")+1:a.index("]")]
			unimplwarn[plat][file].append(a)

		for i, l in unm_funcs:
			if file_lines[i - 1].strip() == "{" and file_lines[i + 1].strip() == "}":
				a = file_lines[i - 2]
				if "(" in a and ")" in a:
					a = a[:a.index("(")]
					b = a[a.rfind(" ")+1:].strip()
					if not b:
						b = a[a[:-1].rfind(" ")+1:].strip()
					if not b:
						Warn("Unable to determine function name -- %s // '%s'" % (path, file_lines[i - 2]))
					else:
						if b not in ["if", "else"]:
							unimplwarn[plat][file].append(b)

		funcs = [l for l in file_lines if "(F)" in l]

		for i in range(len(funcs)):
			a = funcs[i][:funcs[i].index("(")] # take everything until first parenthesis
			b = a[a.rfind(" ")+1:] # remove everything before last whitespace
			if not b:
				b = a[a[:-1].rfind(" ")+1:].strip()
			funcs[i] = b

		for l in sorted(funcs):
			if l in unimplwarn[plat][file]:
				Warn("function marked as (F) but still has unimplemented warning -- %s // '%s'" % (path, l))

		for l in sorted(unimplwarn[plat][file]):
			if l not in platforms[plat][file]:
				if AUTO_ADD_MISSING:
					platforms[plat][file][l] = False
					Hint("function (unimplemented) was not in list - has been added to list -- %s // '%s'" % (path, l))
				else:
					Warn("function (unimplemented) in file but not in list - skipping -- %s // '%s'" % (path, l))
				continue

		for func in sorted(platforms[plat][file].keys(), key=str.lower):
			if not any(l for l in file_lines if func in l and not "  " + func in l and not "/" + func in l):
				Warn("function in list missing completely from file - %s // '%s'" % (path, func))
				missing[plat].append((file, func))
			elif platforms[plat][file][func] and func not in funcs:
				Hint("function marked as implemented in list, not in file -- %s // '%s'" % (path, func))

		for l in sorted(funcs):
			# function is present and (F) in file, but not present in list
			if l not in platforms[plat][file]:
				if AUTO_ADD_MISSING:
					platforms[plat][file][l] = True
					Hint("function was not in list - has been added to list -- %s // '%s'" % (path, l))
				else:
					Warn("function in file but not in list - skipping -- %s // '%s'" % (path, l))
				continue

			# function is (F) in file but not checked in list -> check it
			if not platforms[plat][file][l]:
				Status("adding implemented function -- %s // '%s'" % (path, l))
				added.append((plat, file, l))
				platforms[plat][file][l] = True
				if all(platforms[plat][file].values()):
					addedFiles.append((plat, file))

# STEP
#  ____  
# | ___| 
# |___ \ 
#  ___) |
# |____/ 
# 
# Output the results

def getPlatStats(plat):
	return (
		sum([list(platforms[plat][f].values()).count(True) for f in platforms[plat]]), 
		len([x for x in added if x[0] == plat]),
		sum(len(platforms[plat][f]) for f in platforms[plat]), 
		plat
	)

def getFileStats(plat, file):
	return (
		list(platforms[plat][file].values()).count(True), 
		len([x for x in added if x[0] == plat and x[1] == file]),
		len(platforms[plat][file]), 
		os.path.join(plat, file)
	)

if SHOW_DUPL:
	print("Duplicates :")
	remove = {p: {f: [] for f in platforms[p]} for p in platforms}
	for plat in sorted(platforms.keys()):
		flatfuncs = [(file, func) for file in sorted(platforms[plat].keys()) for func in sorted(platforms[plat][file].keys(), key=str.lower)]
		#import pdb;pdb.set_trace()
		flatfuncs = [x for x in flatfuncs if sum(1 for f in flatfuncs if f[1] == x[1]) > 1]
		dfuncs = {tup[1]: [t[0] for t in flatfuncs if t[1] == tup[1]] for tup in flatfuncs}
		print("- %s : %d" % (plat, len(dfuncs.keys())))
		for func in sorted(dfuncs.keys(), key=str.lower):
			correctfiles = [x for x in dfuncs[func] if not any(m for m in missing[plat] if m[0] == x and m[1] == func)]
			print("  - '%s' : [%s] / [%s]" % (func, ", ".join(dfuncs[func]), ", ".join(correctfiles)))
			if len(correctfiles) == 1:
				for file in dfuncs[func]:
					if file != correctfiles[0]:
						remove[plat][file].append(func)
	print("Remove:")
	for plat in sorted(platforms.keys()):
		print("- %s" % plat)
		for file in sorted(remove[plat].keys()):
			if remove[plat][file]:
				print("  - %s : [%s]" % (file, ", ".join(sorted(remove[plat][file], key=str.lower))))
				if AUTOREMOVE_DUPL:
					for func in remove[plat][file]:
						del platforms[plat][file][func]

Status("statistics:")
for p in sorted(platforms.keys()):
	Status("- %4d [%2d added] / %4d in %s" % getPlatStats(p))
	if SHOW_FILES_STATS:
		for f in sorted(platforms[p].keys()):
			Status("- %4d [%2d added] / %4d in %s" % getFileStats(p, f))

globStats = [getPlatStats(p) for p in platforms]
Status("- %4d [%2d added] / %4d total" % (sum(c for c,_,__,___ in globStats), len(added), sum(t for _,__,t,___ in globStats)))

if len(addedFiles) > 0:
	Status("%d file%s ha%s been finished:" % (len(addedFiles), "s" if len(addedFiles) != 1 else "", "ve" if len(addedFiles) != 1 else "s"))
	for x in addedFiles:
		Status("- %s" % os.path.join(*x))

lines = []
unimpl = []

for plat in sorted(platforms.keys()):
	lines.append("### " + plat)

	for file in sorted(platforms[plat].keys()):
		lines.append("#### " + file)

		for func in sorted(platforms[plat][file].keys(), key=str.lower):
			lines.append("- [%s] `%s`%s" %("x" if platforms[plat][file][func] else " ", func, comments[func] if func in comments else ""))
			if SHOW_UNIMPL and not platforms[plat][file][func]:
				unimpl.append((plat, file, func))

output = "\n".join(lines)

if SHOW_UNIMPL:
	print("Unimplemented :")
	if USE_REPR:
		print(repr([x[2] for x in unimpl if ((not UNIMPL_PC) and ((not UNIMPL_NEUTRAL) or x[0] == "GAME")) or x[0] == "SPEC_PC_N"]))
	else:
		print("\n".join(["%s // %s" % (os.path.join(x[0], x[1]), x[2]) for x in unimpl]))

if SHOW_ADDED:
	print("Added :")
	if USE_REPR:
		print(repr(added))
	else:
		print("\n".join(["%s // '%s'" % (os.path.join(x[0], x[1]), x[2]) for x in added]))


# STEP
#   __   
#  / /_  
# | '_ \ 
# | (_) |
#  \___/ 
#        
# Display motivational messages for the poor developers

motivational_messages = [
	"Keep up the good work!",
	"Awesome!",
	"You're working very fast!"
]
import random
print("[MOTIVATIONAL] " + random.choice(motivational_messages))

if USE_CLIPBOARD:
	import pyperclip
	pyperclip.copy(output)
else:
	print(output)