# FOSSEE Scilab Octave Toolbox

This is a scilab toolbox to call octave functions. It requires octave to be installed on the system. 

## This toolbox has been built and tested using 
1. `OS - Linux Debian 10, Ubuntu 18.10 (64-bit)`
2. `Octave - Version 4.4.1, 5.1.0`
3. `Scilab - Version 6.0.1`

## Software prerequisites:
Run the following commands in the linux terminal
1. `sudo apt-get install build-essential (~117 MB download)`
2. `sudo apt-get install liboctave-dev (~103 MB download)`
3. `sudo apt-get install octave`
4. `sudo apt-get install scilab`

## Install the required octave packages using the below command in linux terminal
1. `sudo apt-get install octave-<pkg name>`
For example, to install signal package in octave, do
1. `sudo apt-get install octave-signal`

## Launch Scilab and run the following commands inside the scilab console
1. `cd <path to fossee-scilab-octave-toolbox directory>`
2. `exec builder.sce`
3. `exec loader.sce`
4. `help octave_fun` (then execute the examples appearing on the help page to test the toolbox)

## Building the source
In case if executing the builder and loader files in scilab throw an error regarding .so files, you probably need to build the toolbox from source. Do the following on the linux terminal
1. Download the fossee-scilab-octave-toolbox source from [`atoms.scilab.org`](https://atoms.scilab.org)
2. Close scilab, if running
3. `cd <path to fossee-scilab-octave-toolbox/src/ directory>`
4. `make clean`
5. `make`
6. `make install`


