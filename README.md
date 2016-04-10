# SphereServer
Game server for UO

[![Build status](https://ci.appveyor.com/api/projects/status/ylox4u925cs260v9?svg=true)](https://ci.appveyor.com/project/coruja747/source)
[![Join the chat at https://gitter.im/Sphereserver/Source](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Sphereserver/Source)

## Project details
[Automatic builds](http://nightly.prerelease.sphere.torfo.org/)

## Building
Project files can be build with CMake for both Linux (GCC) and Windows (MSVC and MinGW), old project files are still present in the source for now.

### Ubuntu
Install mysql library
* sudo apt-get install libmysqld-dev
* sudo apt-get install libmysql++ libmysql++-dev
* sudo apt-get install libmysqlclient-dev:i386

### Windows
Create a .sln file (If the project was not generated by CMake)
* Open 'GraySvr.vcxproj' file using Visual Studio, press Ctrl + S to save the solution and choose a name for the .sln file, use this file from now.

## Coding notes for new contributors
* Make sure you can compile and run the program before pushing a commit.
* Rebasing instead of pulling the project is a better practice to avoid unnecessary "merge branch master" commits.
* Removing/Changing/Adding anything that was working in one way for years should be followed by an ini setting if the changes cannot be replicated from script to keep some backwards compatibility.

## Licensing
Copyright 2016 SphereServer development team

Licensed under the Apache License, Version 2.0 (the "License").<br>
You may not use any file of this project except in compliance with the License.<br>
You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
