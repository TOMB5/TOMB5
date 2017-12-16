#---------------------------------------------------------------------------------
# Lameguy's general-purpose makefile for PSX development
# (for official PlayStation SDK)
# 2017 Meido-Tek Productions
#
# Use mingw32-make (included with MinGW GCC compiler) to run this makefile. You may
# also need to setup msys and assign it to your PATH environment to get the clean
# and cleanall rules to work as make cannot execute del and rm is used instead.
#
# Download msys here:
# https://sourceforge.net/projects/devkitpro/files/tools/msys%201.0.17/msys-1.0.17-1.exe/download
#
# NOTE: Do not use msys' make program! Its bugged in Win9x and may delete your souce
# files when you clean and some programs such as asmpsx cannot read the arguments
# when run by it.
#
# For ISO build to work, you will need mkpsxiso and Orion's Win32 version of cpe2x.
# mkpsxiso: https://github.com/Lameguy64/mkpsxiso
# cpe2x: http://onorisoft.free.fr/rdl.php?url=psx/cpe2x.zip
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# TARGET   - Name of the output
# PROGADDR   - Program load address (0x80010000 is the default)
# SOURCES   - Source directories (. for current directory)
# INCLUDES   - Include search directories
# ISOXML   - Name of mkpsxiso ISO project script
#---------------------------------------------------------------------------------
TARGET		= MAIN
PROGADDR	= 0x00010000
SOURCES		= SPEC_PSX/ GAME/
INCLUDES	= -ISPEC_PSX/ -IGAME/
DEFS		= -DPSX_VERSION -DDISC_VERSION
ISOXML		=

#---------------------------------------------------------------------------------
# LIBDIRS   - Library search directories
# LIBS      - Libraries to link during linking stage
#---------------------------------------------------------------------------------
LIBDIRS		=
LIBS		= LIBSPU.LIB LIBMCRD.LIB LIBPAD.LIB

#---------------------------------------------------------------------------------
# CFLAGS   - Base C compiler options
# AFLAGS   - Base assembler options
#---------------------------------------------------------------------------------
CFLAGS		= -Xm -Wall
AFLAGS		= /q /l

#---------------------------------------------------------------------------------
# Specific options to debug capable environments (debug options are only usable with
# SN Debugger and a DTL-H2000, 2500 or the Parallel Port based PsyQ/SN Blue Dongle)
# (you must set an H2000 environment variable with TRUE to compile with debug options)
#---------------------------------------------------------------------------------
#ifeq "$(H2000)" "TRUE"
#CFLAGS      += -g -DH2000
#AFLAGS      += /zd
#SYMFILE      = $(TARGET).sym
#else
CFLAGS      += -O2
SYMFILE      = $(TARGET).sym
#endif

#---------------------------------------------------------------------------------
## CC      - C compiler (usually ccpsx)
## AS      - Assembler (usually asmpsx)
#---------------------------------------------------------------------------------
CC         = ccpsx
AS         = asmpsx

#---------------------------------------------------------------------------------
# Parse source directories for source files
#---------------------------------------------------------------------------------
CFILES      = $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.C))
#CFILES      = SPEC_PSX/PSXMAIN.C GAME/GAMEFLOW.C GAME/CONTROL.C GAME/TEXT.C GAME/LARA.C GAME/DELSTUFF.C GAME/DELTAPAK.C GAME/DOOR.C GAME/DRAW.C GAME/BOX.C GAME/CAMERA.C GAME/COLLIDE.C GAME/ITEMS.C GAME/DEBRIS.C GAME/SPOTCAM.C GAME/EFFECT2.C GAME/TOMB4FX.C GAME/EFFECTS.C GAME/FLMTORCH.C GAME/HAIR.C GAME/HEALTH.C GAME/NEWINV2.C GAME/LARAFIRE.C GAME/LARAFLAR.C GAME/LARA1GUN.C GAME/LARA2GUN.C GAME/LARACLMB.C GAME/LARASWIM.C GAME/LARASURF.C GAME/LOT.C GAME/LARAMISC.C GAME/MISSILE.C GAME/OBJECTS.C GAME/PEOPLE.C GAME/SAVEGAME.C GAME/SOUND.C GAME/SPHERE.C GAME/SWITCH.C GAME/PICKUP.C GAME/OBJLIGHT.C SPEC_PSX/3D_GEN.C SPEC_PSX/CD.C GAME/TRAPS.C SPEC_PSX/GPU.C SPEC_PSX/FILE.C SPEC_PSX/MALLOC.C SPEC_PSX/3D_OBJ.C SPEC_PSX/PSXINPUT.C SPEC_PSX/ROOMLOAD.C SPEC_PSX/LOAD_LEV.C SPEC_PSX/DRAWSPKS.C SPEC_PSX/PSOUTPUT.C SPEC_PSX/SPECIFIC.C SPEC_PSX/PROFILE.C SPEC_PSX/MEMCARD.C SPEC_PSX/SPUSOUND.C SPEC_PSX/LOADSAVE.C SPEC_PSX/REQUEST.C SPEC_PSX/DRAWPHAS.C SPEC_PSX/SETUP.C
AFILES      = $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))

#---------------------------------------------------------------------------------
# Generate file names for object binaries
#---------------------------------------------------------------------------------
OFILES      = $(CFILES:.c=.obj) $(AFILES:.s=.obj)
#OFILES = SPEC_PSX/PSXMAIN.obj GAME/GAMEFLOW.obj GAME/CONTROL.obj GAME/TEXT.obj GAME/LARA.obj GAME/DELSTUFF.obj GAME/DELTAPAK.obj GAME/DOOR.obj GAME/DRAW.obj GAME/BOX.obj GAME/CAMERA.obj GAME/COLLIDE.obj GAME/ITEMS.obj GAME/DEBRIS.obj GAME/SPOTCAM.obj GAME/EFFECT2.obj GAME/TOMB4FX.obj GAME/EFFECTS.obj GAME/FLMTORCH.obj GAME/HAIR.obj GAME/HEALTH.obj GAME/NEWINV2.obj GAME/LARAFIRE.obj GAME/LARAFLAR.obj GAME/LARA1GUN.obj GAME/LARA2GUN.obj GAME/LARACLMB.obj GAME/LARASWIM.obj GAME/LARASURF.obj GAME/LOT.obj GAME/LARAMISC.obj GAME/MISSILE.obj GAME/OBJECTS.obj GAME/PEOPLE.obj GAME/SAVEGAME.obj GAME/SOUND.obj GAME/SPHERE.obj GAME/SWITCH.obj GAME/PICKUP.obj GAME/OBJLIGHT.obj SPEC_PSX/3D_GEN.obj SPEC_PSX/CD.obj GAME/TRAPS.obj SPEC_PSX/GPU.obj SPEC_PSX/FILE.obj SPEC_PSX/MALLOC.obj SPEC_PSX/3D_OBJ.obj SPEC_PSX/PSXINPUT.obj SPEC_PSX/ROOMLOAD.obj SPEC_PSX/LOAD_LEV.obj SPEC_PSX/DRAWSPKS.obj SPEC_PSX/PSOUTPUT.obj SPEC_PSX/SPECIFIC.obj SPEC_PSX/PROFILE.obj SPEC_PSX/MEMCARD.obj SPEC_PSX/SPUSOUND.obj SPEC_PSX/LOADSAVE.obj SPEC_PSX/REQUEST.obj SPEC_PSX/DRAWPHAS.obj SPEC_PSX/SETUP.obj

#---------------------------------------------------------------------------------
# Default rule, compiles all source files
#---------------------------------------------------------------------------------
all: $(OFILES)
	$(CC) -Xo$(PROGADDR) $(INCLUDES) $(DEFS) $(CFLAGS) $(addprefix -L,$(LIBDIRS)) $(addprefix -l,$(LIBS)) $(OFILES) -o $(TARGET).cpe,$(TARGET).sym,$(TARGET).map

#---------------------------------------------------------------------------------
# Clean-up rule
#---------------------------------------------------------------------------------
#cleanall:
#	rm -f $(OFILES) $(TARGET).cpe $(TARGET).sym $(TARGET).map

#clean: cleanall

#---------------------------------------------------------------------------------
# ISO build rule (requires MKPSXISO)
#---------------------------------------------------------------------------------
#iso:
	cpe2x $(TARGET).cpe
	#mkpsxiso -q -y $(ISOXML)

#---------------------------------------------------------------------------------
# Rule for compiling C source
#---------------------------------------------------------------------------------
%.obj: %.c
	$(CC) $(CFLAGS) $(addprefix -I,$(INCLUDES)) -c $< -o $@

#---------------------------------------------------------------------------------
# Rule for assembling assembly source
#---------------------------------------------------------------------------------
%.obj: %.s
	$(AS) $(AFLAGS) $<,$@