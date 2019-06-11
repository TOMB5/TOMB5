## Contributing

Pull requests which drastically alter the structure or architecture of the code will not be accepted. This is to maintain "sanity" whilst going back through code, comparing to the original MIPS disassembled output.

If you're able to program in C or C++ please feel free to contact me. I can assign you tasks to prevent collisions with my local code which is not pushed yet. I'm typically looking for pull requests which resolve bugs, finish existing decompiled methods, improve readability, introduce new decompiled methods and improve code documentation.

## Code Formatting
```C
int main()//10064(<), 10064(<) (F) (*) (D) (ND)
```
Methods are organised as follows:
- The address on the left is the address of the function in the PSX internal beta version.
- The address on the right is the address of the function in the PSX final version.
- The arrows "(<)" pointing to the address specify whether the code for this method belongs to that specific version
- Then follows some markers.

Markers are as follows:
- ** - This method when compiled, produces identical code to the original.
- F - This method is final, meaning it has been fully decompiled.
- D - This method has been debugged and is now functionally the same as the original.
- ND - This method has not been debugged and may not be functionally the same as the original.

## Current Positions

- MIPS r3000a Programmer/Interpreter - Translate TR5 PSX MIPS disassembled output back to C.
- PSX HLE Emulator Programmer - Help improve the PSX emulator for PSXPC_N code path.
- x86 Programmer/Interpreter - Translate TR5 PC x86 asm back to C. 
- SH4 Programmer/Interpreter - Translate TR5 Dreamcast SH4 asm back to C. 
- PPC Programmer/Interpreter - Translate TR5 Mac PPC asm back to C. 
- Platform Programmer (Mac) - (Maintain and ensure that PSXPC_N code compiles under Mac OSX).
- Platform Programmer (Linux) - (Maintain and ensure that PSXPC_N code compiles under Linux).
- Code Analyser (ASM - PSX) - Compare compiled code to the original to help detect any possible errors in exising code.
- Debugger - Debug existing code issues/crashes, propose a solution by basing the patch off the original disassembly.
- General Programmer - Clean existing code to improve readability without changing the structure, improve code documentation.
- Build Engineer - Manage and maintain existing Travis/Appveyor build automation systems. Improve code distribution/publishing methods by implmenting a system to support all platforms and possible release versions.

## Folder Structure
- CMAKE - Default CMake module folder. 
- GAME - Contains all Tomb Raider: Chronicles shared game logic code.
- SPEC_PC - Platform specific code for PC version. ***DEPRECATED!***
- SPEC_PC_N - New Platform specific code for PC version.
- SPEC_PSX - Platform specific code for PSX version.
- SPEC_PSXPC - Platform specific code for PSX version that runs on PC for debugging purposes (all psx sdk calls stripped). ***DEPRECATED!***
- SPEC_PSXPC_N - Platform specific code for PSX version that runs on PC emulated for debugging purposes.
- TOOLS - Game tools folder, contains various tools to work with the game files.
- DISC - Contains PSX specific disc project generation files.
- RESOURCE - Contains useful resources for decompiling the code.

## Base Versions (PSX)
- PSX NTSC v1.0 SLUS_013.11 MD5: (4EF523E708D7A7D6571F39C6E47784F9)
- PSX Internal Beta MAIN.EXE MD5: (238F15B1C6260F80DB79E31A94508354)

## Compiling
1. Dependencies:
    - CMake 3.0+
    - SDL 2.0.9.
    - GLEW 2.1.0+

2. PSXPC_N   
    - Windows (VS 2015-2019) (**recommended**)
        - Download SDL2-devel-2.0.9-VC.zip extract to project root EXTERNAL/ rename folder "SDL2-2.0.9" to  "SDL2".
        - Download glew-2.1.0-win32.zip extract to project root EXTERNAL/ 
        - Generate CMake project files for VS2015, 2017 or 2019, x86 ONLY! (x64 is currently unsupported so don't try it.)
    - Windows (CB MinGW32)       
        - Download SDL2-devel-2.0.9-mingw.tar.gz extract to project root EXTERNAL/ rename folder "SDL2-2.0.9" to "SDL2".
        - Download glew-2.1.0-mingw.zip ((link)[http://www.grhmedia.com/glew/glew-2.1.0-mingw.zip]) extract to project root EXTERNAL/ 
        - Generate CMake project files for CodeBlocks MinGW Makefiles, x86 ONLY! (x64 is currently unsupported so don't try it.)
    - Linux 
Note: On x64 distributions GCC must be configured to build 32-bit binaries.
Note: Some later versions of GCC are currently unsupported.
         - Open terminal and type in the following commands:
	 - sudo apt-get update -qq
	 - sudo apt-get install -y cmake
         - sudo apt-get install -y libegl1-mesa-dev
         - sudo apt-get install -y libgles2-mesa-dev
         - sudo apt-get install -y libsdl2-dev
         - sudo apt-get install -y libglew-dev
Open a new terminal window in the root directory where TOMB5 is cloned.
	 - Type in the following commands.
         - mkdir BUILD
         - cd BUILD
         - cmake ..
         - make
  
    - Open solution
    - In the project settings, set the `DISC_VERSION` to 1
    - Build
    - Download TR5 retail version for PSX (NTSC, USA), you should get two files, a .BIN and a .CUE; put the .BIN file in the the same folder as the .EXE file and rename it to TOMB5.BIN
3. Windows PSX:
    - Download PSX PsyQ SDK 4.6 or 4.6 + 4.7 update, extract to c:/psyq
    - Download and install TDM-GCC.
    - Run psxdev's pspath.reg file to update registry environment variables.
    - Compile all the TOOLS in the tool folder of the solution.
	- Create a /DATA/ folder in BUILD\TOOLS\GAMEWAD_Unpack\Release
	- Extract GAMEWAD.OBJ using GAMEWAD_Unpack tool (drag and drop onto GAMEWAD_Unpack.exe).
	- Copy the /DATA/ FOLDER to BUILD\TOOLS\GAMEWAD_Pack\Release
	- Create a /GAME/ folder in BUILD\TOOLS\CODEWAD_Unpack\Release
	- Extract CODE.WAD using CODEWAD_Unpack tool (drag and drop onto CODEWAD_Unpack.exe).
	- Copy the /GAME/ FOLDER to BUILD\TOOLS\CODEWAD_Pack\Release
	- Copy DEL2FAB.EXE (from leaked TR4&5 PSX SDK) to root clone directory.
    - Go to root clone directory in commandline type PSX_BUILD and enter the command.
    - Go to root clone directory /DISC/ and run MAKEISO.bat (note: mkpsxiso required)
4. Windows PC_N:
    - Install the DirectX 7 SDK ([link](https://mega.nz/#!nFgAhQpS!RIM-lDf7-3bedzYGFxYZHxsRGqg1ybKvTYka_kpFP4A)) to a simple path, such as `C:\dx7sdk`
    - Open project settings, in VC++ directories change the following:
      - Include dirs: add `C:\dx7sdk\Include` and then `$(WindowsSDK_IncludePath)` (make sure that one is **above** the DX one, otherwise you'll get compile errors)
      - Lib dirs: add `C:\dx7sdk\lib\x86`
    
Feel free to contact us on this: [Discord server](https://discord.gg/KYSx8Q7) channel #TOMB5-decompile
