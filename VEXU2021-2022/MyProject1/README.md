# Overview

There are two folders that we care a lot about in  this project, the src and include folders. Because VEX runs its robots in C++, it's necessary fo us to have header files and cpp files. The header files will all be stored in the include folder (with some exceptions) and the rest of the files wil be in the src forlder. Any class that is designed to be used in multiple robots will likely have its header file in its class folder in src to keep it contained.

# File Structure

### include - Contains header files

RobotConfig.h   - declares vex-specific stuff like motors

vex.h           - contains most of the #include decralations

globals.h      - contains declarations for our stuff that we will need everywhere like motor vectors

*other header files as needed*

### src - Contains source files

main.cpp        - using the competition template contains autonomous, user control, and a few other important functions

robot-config.cpp - contains pre-built code defining the motors and things

globals.cpp     - contains the definitions for the stuff we will need everywhere, like motor vectors

*other .cpp files as needed*

### src/straightDriveBase - reusable code for the drivebase of the robot

drive.h         - contains the class declaration for the straight drive class

drive.cpp       - contains the meat of the drive functionality

debugging.cpp   - contains some prebuilt functions for debugging sensors and behaviors

calibrate.cpp   - contains experimental code for automaticaly calibrating the drive

helper.cpp      - contains support code to make the math and algorithms easier
