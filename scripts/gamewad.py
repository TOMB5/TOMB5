#!/usr/bin/env python

#                   _ _                          _            _            
#            ______| (_)_ __ ___   ___ _ __  ___(_) ___  _ __( )__         
#           |_  / _` | | '_ ` _ \ / _ \ '_ \/ __| |/ _ \| '_ \/ __|        
#            / / (_| | | | | | | |  __/ | | \__ \ | (_) | | | \__ \        
#           /___\__,_|_|_| |_| |_|\___|_| |_|___/_|\___/|_| |_|___/        
#                                               _         _   _ _ _ _         
#   __ _  __ _ _ __ ___   _____      ____ _  __| |  _   _| |_(_) (_) |_ _   _ 
#  / _` |/ _` | '_ ` _ \ / _ \ \ /\ / / _` |/ _` | | | | | __| | | | __| | | |
# | (_| | (_| | | | | | |  __/\ V  V / (_| | (_| | | |_| | |_| | | | |_| |_| |
#  \__, |\__,_|_| |_| |_|\___| \_/\_/ \__,_|\__,_|  \__,_|\__|_|_|_|\__|\__, |
#  |___/                                                                |___/ 

# Command-line usage:
# $ python gamewad.py <mode> <input> <output> [args]
# if mode is "unpack" or "u" then input is either a file or - meaning stdio, and output is a directory
# if mode is "repack" or "r" then input is a directory and output is either a file or - meaning stdout

# increment this plz
# rev 1
# 2017-11-05

import os.path
import sys
import struct
import shutil
import io

def Warn(msg):
	if SHOW_WARN:
		print("[WARN--------] " + str(msg))

def Hint(msg):
	if SHOW_HINT:
		print("[----HINT----] " + str(msg))

def Status(msg):
	if SHOW_STATUS:
		print("[--------STAT] " + str(msg))

NUM_ENTRIES = 51

gw_files = [
	"SETUP.MOD",
	"CUTSEQ.JIZ",
	"TITLE.PSX",
	"ANDREA1.PSX",
	"ANDREA2.PSX",
	"ANDREA3.PSX",
	"JOBY2.PSX",
	"JOBY3.PSX",
	"JOBY4.PSX",
	"JOBY5.PSX",
	"ANDY1.PSX",
	"ANDY2.PSX",
	"ANDY3.PSX",
	"RICH1.PSX",
	"RICH2.PSX",
	"RICHCUT2.PSX",
	"RICH3.PSX",
	"RESERVED_17",
	"RESERVED_18",
	"RESERVED_19",
	"RESERVED_20",
	"RESERVED_21",
	"RESERVED_22",
	"RESERVED_23",
	"RESERVED_24",
	"RESERVED_25",
	"RESERVED_26",
	"RESERVED_27",
	"RESERVED_28",
	"RESERVED_29",
	"EXTRAS1.RAW",
	"EXTRAS2.RAW",
	"EXTRAS3.RAW",
	"RESERVED_33",
	"RESERVED_34",
	"RESERVED_35",
	"RESERVED_36",
	"RESERVED_37",
	"RESERVED_38",
	"RESERVED_39",
	"RESERVED_40",
	"TR5LEGAL_EN.RAW",
	"TR4LEGAL_FR.RAW",
	"TR4LEGAL_US.RAW",
	"TR4LEGAL_EN.RAW",
	"TR4LEGAL_EN.RAW",
	"TR5LEGAL_EN.RAW",
	"TR4LEGAL_US.RAW",
	"TR4LEGAL_EN.RAW",
	"TR4LOGO_FR.RAW",
	"TR4LOGO_EN.RAW"
]

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

SHOW_WARN = 		isarg("warn", 		"w", True) 	# Show warnings (error messages)
SHOW_HINT = 		isarg("hint", 		"h", True) 	# Show hints (messages that are useful, but not important)
SHOW_STATUS = 		isarg("status", 	"s", False)	# Show status messages
AUTO_DELETE =		isarg("deloutput",	"d", False) # If output already exists, delete it

if len(sys.argv) < 4:
	Warn("Not enough arguments provided -- exiting.")
	exit()

WORK_MODE =	sys.argv[1].strip().lower()
INPUT = 	sys.argv[2].strip()
OUTPUT = 	sys.argv[3].strip()

if WORK_MODE not in ["unpack", "u", "repack", "r"]:
	Warn("Incorrect mode specified: %s -- exiting." % WORK_MODE)
	exit()

# STEP
#  ____          
# |___ \    __ _ 
#   __) |  / _` |
#  / __/  | (_| |
# |_____|  \__,_|
#                
# Unpack GAMEWAD
if WORK_MODE in ["unpack", "u"]:
	if os.path.exists(OUTPUT):
		if AUTO_DELETE:
			Warn("Output folder already exists -- deleting")
			shutil.rmtree(OUTPUT)
		else:
			Warn("Output folder already exists -- exiting")
			exit()
	
	os.makedirs(OUTPUT)

	if INPUT == "-":
		istream = sys.stdin
	else:
		if not os.path.isfile(INPUT):
			Warn("The specified input file doesn't exist: %s -- exiting" % INPUT)
			exit()
		istream = open(INPUT, "rb")

	ibytes = io.BytesIO(istream.read())
	istream.close()

	entries = []

	# Read entries
	for i in range(NUM_ENTRIES):
		offset = struct.unpack('i', ibytes.read(4))[0]
		size = struct.unpack('i', ibytes.read(4))[0]

		Status("Read entry #%d ; offset = %d ; size = %d" % (i, offset, size))

		entries.append((offset, size))

		if offset % 2048 != 0:
			Hint("The offset (%d) of the entry #%d is not aligned to 2048" % (offset, i))

		if size == 0:
			Hint("Entry #%d has size 0" % i)


	for i in range(NUM_ENTRIES):
		Status("Writing entry #%d to file '%s'" % (i, gw_files[i]))
		with open(os.path.join(OUTPUT, gw_files[i]), "wb") as ostream:
			ibytes.seek(entries[i][0])
			ostream.write(ibytes.read(entries[i][1]))

	ibytes.close()

elif WORK_MODE in ["repack", "r"]:
	if not os.path.exists(INPUT):
		Warn("The specified input folder doesn't exist: %s -- exiting" % INPUT)
		exit()

	