# Project: Decompile Tomb Raider: Chronicles (TOMB5)

| Platform  | Build State |
| ------------- | ------------- |
| Windows  | [![Build status](https://ci.appveyor.com/api/projects/status/u5ery22l7cl587dq/branch/master?svg=true)](https://ci.appveyor.com/project/Gh0stBlade/tomb5/branch/master)  |
| Linux  | [![Build Status](https://travis-ci.org/Gh0stBlade/TOMB5.svg?branch=master)](https://travis-ci.org/Gh0stBlade/TOMB5)

## Disclaimer
This project may be abandoned at any time, use this product at your own risk.

## What is this?

This repository contains decompiled code for the game Tomb Raider: Chronicles. All decompiled code is based off the PlayStation version. The goal is to decompile as much as possible since the original source code is reportedly lost. It is not expected for code to be 1:1 to the original game. Debugging the original PlayStation version at a later phase will help map out any existing bugs.

## What are the current goals?

Current goals include decompiling all code up until the title screen sequence, ensuring it's fully correct then proceeding to decompiling in-game code. At this point in time the most critically required parts of code reside within the "GAME" folder.

## How long will this take?

Depending on the amount of contributors it could take years.

## Contributing

I will not accept pull requests which drastically alter the structure/architecture of the code. This is to maintain "santiy" whilst going back through code, comparing to the original MIPS disassembled output.

If you're able to code in C/C++ please feel free to contact me. I can assign you tasks to prevent collisions with my local code which is not pushed yet. I'm typically looking for pull requests which resolve bugs, finish existing decompiled methods, improve readability or introduce new decompiled methods.

Feel free to contact me on this * [Discord channel](https://discord.gg/KYSx8Q7)
