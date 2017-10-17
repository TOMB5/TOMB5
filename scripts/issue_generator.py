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

# increment this plz
# rev 1
# 2017-10-16                                                      


from urllib.request import urlopen
import json
import os.path
import sys

# STEP
#  _ 
# / |
# | |
# | |
# |_|
# 
# Global settings

def isarg(arg, default):
	if any(x for x in sys.argv if x.strip().lower() == "+%s" % arg):
		return True
	elif any(x for x in sys.argv if x.strip().lower() == "-%s" % arg):
		return False
	else:
		return default

ISSUE_ID = 			46 							# ID of the issue on GitHub (for the API request)
PLATFORMS = 		["GAME", "SPEC_PSX"] 		# Which folders/platforms to use
SHOW_WARN = 		isarg("warn", True) 		# Show warnings (error messages)
SHOW_HINT = 		isarg("hint", True) 		# Show hints (e.g. function checked in list but not (F) in file)
SHOW_STATUS = 		isarg("status", False)		# Show status messages (function added successfully yay)
AUTO_ADD_MISSING = 	isarg("addmissing", True) 	# If a function is marked (F) in file but is missing in the list, add it to the list
USE_CLIPBOARD = 	isarg("clipboard", True) 	# Copy output into clipboard instead of outputting it to the console
SHOW_UNIMPL =		isarg("showunimpl", False)	# At the end, output a list of unimplemented (unchecked) functions
USE_REPR =			isarg("userepr", False)		# Debugging purposes. When outputting a list (e.g. SHOW_UNIMPL), use repr()

if not os.path.isfile("README.md"):
	os.chdir("..")

if SHOW_WARN and not os.path.isfile("README.md"):
	print("[WARN--------] cannot find README.md in current or parent directory, are you in the correct folder?")

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
for x in issue:
	if "#### " in x: 		# level 2 header - file
		curfile = x[5:]
		continue
	elif "### " in x:		# level 1 header - platform
		curplat = x[4:]
		continue

	if curplat not in platforms:
		platforms[curplat] = {}

	if curfile not in platforms[curplat]:
		platforms[curplat][curfile] = {}

	fname = x[7:x.rfind("`")]

	if len(x) - x.rfind("`") > 1:
		comment = x[x.rfind("`") + 1:]
		if comment:
			comments[fname] = comment

	if fname in platforms[curplat][curfile]:
		print("[WARN--------] duplicate function '%s'" % fname)

	platforms[curplat][curfile][fname] = "[x]" in x

# STEP
#  _  _   
# | || |  
# | || |_ 
# |__   _|
#    |_|  
#
# Let the actual shit be done

if SHOW_STATUS:
	print("[--------STAT] working for platforms: " + ", ".join(platforms.keys()))

added = []

def getfline(path):
	with open(path, 'r') as fp:
		return [x for x in fp.read().replace("\r\n", "\n").split('\n') if x]

for plat in sorted(platforms.keys()):
	for file in sorted(platforms[plat].keys()):
		path = os.path.join(plat, file)
		if not os.path.isfile(path):
			if SHOW_WARN:
				print("[WARN--------] file does not exist - skipping -- '%s'" % path)
			continue

		funcs = [l for l in getfline(path) if "(F)" in l]

		for i in range(len(funcs)):
			a = funcs[i][:funcs[i].index("(")] # take everything until first parenthesis
			a = a[a.rfind(" ")+1:] # remove everything before last whitespace
			funcs[i] = a

		for func in sorted(platforms[plat][file].keys(), key=str.lower):
			if platforms[plat][file][func] and func not in funcs:
				if SHOW_HINT:
					print("[----HINT----] function marked as implemented in list, not in file -- %s // '%s'" % (path, func))

		for l in sorted(funcs):
			# function is present and (F) in file, but not present in list
			if l not in platforms[plat][file]:
				if AUTO_ADD_MISSING:
					platforms[plat][file][l] = True

					if SHOW_HINT:
						print("[----HINT----] function was not in list - has been added to list -- %s // '%s'" % (path, l))
				else:
					if SHOW_WARN:
						print("[WARN--------] function in file but not in list - skipping -- %s // '%s'" % (path, l))
				continue

			# function is (F) in file but not checked in list -> check it
			if not platforms[plat][file][l]:
				if SHOW_STATUS:
					print("[--------STAT] adding implemented function -- %s // '%s'" % (path, l))
				added.append(l)
				platforms[plat][file][l] = True

# STEP
#  ____  
# | ___| 
# |___ \ 
#  ___) |
# |____/ 
# 
# Output the results

lines = []
unimpl = []

for plat in sorted(platforms.keys()):
	lines.append("### " + plat)

	for file in sorted(platforms[plat].keys()):
		lines.append("#### " + file)

		for func in sorted(platforms[plat][file].keys(), key=str.lower):
			lines.append("- [%s] `%s`%s" %("x" if platforms[plat][file][func] else " ", func, comments[func] if func in comments else ""))
			if SHOW_UNIMPL and not platforms[plat][file][func]:
				unimpl.append("%s\\%s // %s" % (plat, file, func))

output = "\n".join(lines)

if USE_CLIPBOARD:
	import pyperclip
	pyperclip.copy(output)
else:
	print(output)

if SHOW_UNIMPL:
	if USE_REPR:
		print(repr([x.split(" // ")[1] for x in unimpl]))
	else:
		print("\n".join(unimpl))