## Contributing

Pull requests which drastically alter the structure/architecture of the code will not be accepted. This is to maintain "santiy" whilst going back through code, comparing to the original MIPS disassembled output.

If you're able to code in C/C++ please feel free to contact me. I can assign you tasks to prevent collisions with my local code which is not pushed yet. I'm typically looking for pull requests which resolve bugs, finish existing decompiled methods, improve readability or introduce new decompiled methods.

## Current Positions

- MIPS R3000 Programmer/Interpreter - Translate TR5 PSX MIPS Disassembled output back to C.
- x86 Programmer/Interpreter - Translate TR5 PC x86 asm back to C. 
- SH4 Programmer/Interpreter - Translate TR5 Dreamcast SH4 asm back to C. 
- PPC Programmer/Interpreter - Translate TR5 Mac PPC asm back to C. 
- Platform Programmer (Mac) - (Maintain and ensure that PSXPC code compiles under Mac OSX).
- Platform Programmer (Linux) - (Maintain and ensure that PSXPC code compiles under Linux).
- Code Analyser (ASM - PSX) - Compare compiled code to the original to help detect any possible errors in exising code.
- Debugger - Debug existing code issues/crashes, propose a solution by basing the patch off the original disassembly.
- General Programmer - Clean existing code to improve readability without changing the structure, improve code documentation.
- Build Engineer - Manage and maintain existing Travis/Appveyor build automation systems. Improve code distribution/publishing methods by implmenting a system to support all platforms and possible release versions.

## Folder Structure
- CMAKE - Default CMake module folder. 
- GAME - Contains all Tomb Raider 5 game specific code.
- SPEC_PC - Platform specific code for PC version.
- SPEC_PSX - Platform specific code for PSX version.
- SPEC_PSXPC - Platform specific code for PSX version that runs on PC for debugging purposes (all psx sdk calls stripped).
- TOOLS - Game tools folder, contains various tools to work with the game files.
- DISC - Contains PSX specific disc project generation files.

## Base Version (PSX)
- PSX NTSC v1.0 SLUS_013.11 MD5: (4EF523E708D7A7D6571F39C6E47784F9)

## Compiling
1. Dependencies:
    - CMake 3.0+
    - SDL 2.0.7.

2. Windows (VS 2015-2017) PSXPC:
    - Download SDL2-devel-2.0.7-VC.zip extract to project root EXTERNAL/ rename folder "SDL2-2.0.7" to "SDL2".
    - Generate CMake project files for VS2015 or 2017, x86 ONLY! (x64 is currently unsupported so don't try it.)
    - Open solution and build.

3. Windows (CB MinGW32) PSXPC:
    - Download SDL2-devel-2.0.7-mingw.tar.gz extract to project root EXTERNAL/ rename folder "SDL2-2.0.7" to "SDL2".
    - Generate CMake project files for CodeBlocks MinGW Makefiles, x86 ONLY! (x64 is currently unsupported so don't try it.)
    - Open solution and build.
4. Windows PSX:
    - Download PSX PsyQ SDK 4.6 or 4.7, extract to c:/psyq
    - Download and install TDM-GCC.
    - Run psxdev's pspath.reg file to update registry environment variables.
    - Compile all the TOOLS in the tool folder of the solution.
	- Create a /DATA/ folder in BUILD\TOOLS\GAMEWAD_Unpack\Release
	- Extract GAMEWAD.OBJ using GAMEWAD_Unpack tool (drag and drop onto exe).
	- Copy the /DATA/ FOLDER to BUILD\TOOLS\GAMEWAD_Pack\Release
	- Copy DEL2FAB.EXE (from leaked TR4&5 PSX SDK) to root clone directory.
    - Go to root clone directory in commandline type PSX_BUILD and enter the command.
    - Go to root clone directory /DISC/ and run MAKEISO.bat (note: mkpsxiso required)
    
Feel free to contact us on this: [Discord server](https://discord.gg/KYSx8Q7) channel #TOMB5
