# Project: Decompile Tomb Raider: Chronicles (TOMB5)

Start Date: 12th July 2017.

PSX:
<p align="center">
<a href="https://streamable.com/17ilj"><img src="https://i.imgur.com/YzFDlbRl.png"/><a>
 </p>

PSXPC_N:
<p align="center">
<a href="https://streamable.com/ip8lx"><img src="https://i.imgur.com/CkmdIzs.png"/><a>
 </p>

| Platform  | Build State |
| ------------- | ------------- |
| Windows (PSXPC_N)  | [![Build status](https://ci.appveyor.com/api/projects/status/wbfndh3l1j605tow/branch/master?svg=true)](https://ci.appveyor.com/project/Gh0stBlade/tomb5/branch/master) |
| Linux (PSXPC_N)  | [![Build status](https://ci.appveyor.com/api/projects/status/wbfndh3l1j605tow/branch/appveyor-ubuntu?svg=true)](https://ci.appveyor.com/project/Gh0stBlade/tomb5/branch/appveyor-ubuntu) |
| Linux (PSXPC_N) | [![Build Status](https://travis-ci.org/TOMB5/TOMB5.svg?branch=master)](https://travis-ci.org/TOMB5/TOMB5) |
| PSX  | [![Build status](https://ci.appveyor.com/api/projects/status/wbfndh3l1j605tow/branch/appveyor-psx?svg=true)](https://ci.appveyor.com/project/Gh0stBlade/tomb5/branch/appveyor-psx)
## Disclaimer
This project may be abandoned at any time, use this product at your own risk.

## What is this?

This repository contains decompiled code for the game Tomb Raider: Chronicles. All decompiled code is based off the final PlayStation and PC version. The goal is to decompile as much as possible since the original source code is reportedly lost. It is not expected for decompiled code to be 1:1 with the original source code. However, functionality wise it will be the same. Further debugging of the original PlayStation version at a later phase will help map out any existing bugs. All information (variable, file names, method names and data structures) have been obtained from debugging symbols (.SYM, .MAP), TRosettastone 3.0 and GAMEWAD.OBJ.

## What are the current goals?

Current goals include decompiling all code up until the title screen sequence, ensuring it's fully correct then proceeding to decompiling in-game code. At this point in time the most critically required parts of code reside within the "GAME" folder.

## Usage

Assuming you have compiled the most recent code or downloaded the latest binaries from appveyor (artifacts). Simply put your Tomb Raider: Chronicles PlayStation disc into your PC. At this point you'll need to copy all the files from the root of the CD to the same folder as MAIN.EXE. The codebase is currently based off the final NTSC version of Tomb Raider: Chronicles and final PC version. This means that other localised versions may not be supported.

## How long will this take?

Depending on the amount of contributors it could take years.

Feel free to contact me on this: [Discord server](https://discord.gg/KYSx8Q7) channel #TOMB5-decompile

## Credits

- Gh0stBlade: Lead Programmer (PSX/PSXPC_N).
- zdimension: Programmer (PSX/PSXPC_N,PC).
- Stohrendorf: Symdump tool creator.
- [You?](CONTRIBUTING.md)
