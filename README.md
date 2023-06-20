# About this project
This project is an attempt at (currently) decoding PAF images to be seen in Windows using .NET C++ CLR.

This code only works properly with all types of PAF files. 1bpp and 2bpp to ARGB conversion with padding handling should be worked on.

This project also uses a DLL for manipulating PAF files (AniPAF.dll). This DLL is a reverse-engineer of the PDK Animation Format library used on certain LG phone firmwares along with fixes for proper results (includes those from https://github.com/Crawlerop/paftools), and is included in the project.
# Building
Currently, this project is compilable with Visual Studio 2017 and up (projects are targeted to VS2010).
# License
The owner of this project can't decide what license should be used here. Part of this code is based off of https://github.com/Crawlerop/paftools, under MIT license, whilst the reverse engineered part is originally covered by BNSoft (the maker of PDK)'s own license.
