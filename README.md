# Project: Decompile Tomb Raider: Chronicles (TOMB5)

| Platform  | Build State |
| ------------- | ------------- |
| Windows  | [![Build status](https://ci.appveyor.com/api/projects/status/u5ery22l7cl587dq/branch/master?svg=true)](https://ci.appveyor.com/project/Gh0stBlade/tomb5/branch/master)  |
| Linux  | [![Build Status](https://travis-ci.org/Gh0stBlade/TOMB5.svg?branch=master)](https://travis-ci.org/Gh0stBlade/TOMB5)

## Disclaimer
This project may be abandoned at any time, use this product at your own risk.

## What is this?

This repository contains decompiled code for the game Tomb Raider: Chronicles. All decompiled code is based off the PlayStation version. The goal is to decompile as much as possible since the original source code is reportedly lost. It is not expected for code to be 1:1 to the original game. Debugging the original PlayStation version at a later phase will help map out any existing bugs. All information (variable and method names) have been obtained from debugging symbols (.SYM, .MAP).

## What are the current goals?

Current goals include decompiling all code up until the title screen sequence, ensuring it's fully correct then proceeding to decompiling in-game code. At this point in time the most critically required parts of code reside within the "GAME" folder.

## Usage

Assuming you have compiled the most recent code or downloaded the latest binaries from appveyor (artifacts). Simply put your Tomb Raider: Chronicles PlayStation disc into your PC. At this point you'll need to copy all the files from the root to the same folder as MAIN.EXE. The codebase is currently based off the final NTSC version of Tomb Raider: Chronicles. This means that other localised versions may not be supported.

## How long will this take?

Depending on the amount of contributors it could take years.

Feel free to contact me on this: [Discord channel](https://discord.gg/KYSx8Q7)
