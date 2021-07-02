# FOSSEE Scilab Octave Toolbox

This is a scilab toolbox to call octave functions. It requires octave to be installed on the system. 

## This toolbox has been built and tested using 
1. `OS - Linux Debian 10, Ubuntu 18.10 and 19.10 (64-bit), Windows 10 (64-bit)`
2. `Octave - Version 4.4.1, 5.1.0`
3. `Scilab - Version 6.0.x`

---

## Software prerequisites
## Linux
Run the following commands in the linux terminal
1. `sudo apt-get install build-essential (~117 MB download)`
2. `sudo apt-get install liboctave-dev (~103 MB download)`
3. `sudo apt-get install octave`
4. `sudo apt-get install scilab`

Install the required octave packages using the below command in linux terminal
1. `sudo apt-get install octave-<pkg name>` For example, to install signal package in octave, do `sudo apt-get install octave-signal`


## Windows
1. Download and Install Scilab 6.0.1 x64 from [Scilab.org](https://www.scilab.org/) 
2. Download and Install Octave 4.4.1 x64. (If you use a custom installation path different from the default see troubleshooting section below.)
3. Install Mingw Tollbox for Scilab (https://atoms.scilab.org/toolboxes/mingw/0.10.5).
4. Create an user variable called `'OCTAVE_HOME'` with value equal to the installation directory of Octave (default being: `"C:\Octave\Octave-4.4.1\"`). 

---

## Running the Toolbox

## Linux
Launch Scilab and run the following commands inside the scilab console
1. `cd <path to fossee-scilab-octave-toolbox directory>`
2. `exec builder.sce`
3. `exec loader.sce`
4. `help octave_fun` (then execute the examples appearing on the help page to test the toolbox)

## Windows
Launch Scilab and run the following commands inside the scilab console
1. `cd <path to fossee-scilab-octave-toolbox directory>`
2. `exec builder.sce` (If you see erros executing this step, see troubleshooting section.)
3. Add "C:\Octave\Octave-4.4.1\bin" or wherever you installaed Octave to Environment PATH. (You need to follow this step only when you are building the toolbox for the first time).
4. `exec loader.sce`
5. `help octave_fun` (then execute the examples appearing on the help page to test the toolbox)
   
---

## Building the source

## Linux
In case if executing the builder and loader files in scilab throw an error regarding .so files, you probably need to build the toolbox from source. Do the following on the linux terminal
1. Download the fossee-scilab-octave-toolbox source from [`atoms.scilab.org`](https://atoms.scilab.org)
2. Close scilab, if running
3. `cd <path to fossee-scilab-octave-toolbox/src/ directory>`
4. `make clean`
5. `make`
6. `make install`

## Windows
1. `cd <path to fossee-scilab-octave-toolbox/src/ directory>`
2. Run the commands in `src/window_compile.txt` in a cmd prompt.
3. Copy `fun.h` to `thirdparty/windows/include`.
4. Copy and Overwrite `libfun.a` & `libfun.dll` to `thirdparty/windows/lib`

---

## Troubleshooting
## Windows
**1. Custom Octave install path**

If you have a custom Octave installtion path then change the path in `tollbox_root/sci_gateway/cpp/builder_gateway_cpp.sce` for `octave_lib_dir` at Line 43.

**2. library_name.a not found error on running "exec builder.sce".**

This usually happens when you build the toolbox on Windows for the first time or from scratch. Simply comment the commands  
> octave_lib_dir + "liboctave-6";
> 
> octave_lib_dir + "liboctinterp-6";

in `tollbox_root/sci_gateway/cpp/builder_gateway_cpp.sce`. Run `exec builder.sce` to get a sucessful build. Uncomment the commands you just commented and run the builder command once again. This time the toolbox will build sucessfully.

**3. Mingw gcc file not found/ path errors when running "exec builder.sce".**

This usually happens when you build the toolbox on Windows for the first time or from scratch and have the octave/bin folder in your PATH, causing conflicts with the gcc version required by Mingw Toolbox.

Remove "C:\Octave\Octave-4.4.1\bin" (or your Octave installation equivalent) from Environment Variable PATH, build the toolbox and add octave/bin back to your PATH as it is required by loader.sce.

**4. Some Octave Functions Not Found**

You are missing the OCTAVE_HOME user variable. See Windows software prerequisites section.

 

