# Overview

This project uses the SFML CMake GitHub template. Please view the original template for the full instructions.

## Purpose

The purpose of this repository is to store code and resources from my entry to the [GTMK Game Jam 2023](https://itch.io/jam/gmtk-2023).
This respository contains everything necessary to run the game by using CMake. No other installations should be necessary.

## How to run

For this particular project, CMake is used from the command line.
This project is intended for Windows systems. The commands to build are as follows:

    cmake -S . -B build
    cmake --build build --config Release

Navigate to the build directory, then to the Release directory. 
Move the openal32.dll and resource folders into this directory.

Then, you can run the executable to view the project.
