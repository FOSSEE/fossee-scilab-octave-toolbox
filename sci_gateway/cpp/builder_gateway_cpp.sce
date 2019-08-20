// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Harpreet Singh, Yash Kataria, Adarsh Shah
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

mode(-1)
lines(0)

toolbox_title = "scilab_toolbox";

Build_64Bits = %t;

path_builder = get_absolute_file_path('builder_gateway_cpp.sce');

Function_Names = [
        
        //fun function
        "octave_fun","sci_octave_fun", "csci6";
    ];

//Name of all the files to be compiled
Files = [
        "sci_matrix.cpp"    
    ]



[a, opt] = getversion();
Version = opt(2);

//Build_64Bits = %f;

if getos()=="Windows" then
    third_dir = path_builder+filesep()+'..'+filesep()+'..'+filesep()+'thirdparty';
    lib_base_dir = third_dir + filesep() + 'windows' + filesep() + 'lib' + filesep() + Version + filesep();
    //inc_base_dir = third_dir + filesep() + 'windows' + filesep() + 'include' + filesep() + 'coin';
    inc_base_dir = third_dir + filesep() + 'linux' + filesep() + 'include' + filesep() + 'coin';
    threads_dir=third_dir + filesep() + 'linux' + filesep() + 'include' + filesep() + 'pthreads-win32';
    C_Flags=['-D__USE_DEPRECATED_STACK_FUNCTIONS__  -I -w '+path_builder+' '+ '-I '+inc_base_dir+' '+'-I '+threads_dir+' ']   
    Linker_Flag  = [lib_base_dir+"libcoinblas.lib "+lib_base_dir+"libcoinlapack.lib "+lib_base_dir+"libcoinmumps.lib "+lib_base_dir+"libClp.lib "+lib_base_dir+"libipopt.lib "+lib_base_dir+"libOsi.lib "+lib_base_dir+"libOsiClp.lib "+lib_base_dir+"libCoinUtils.lib "+lib_base_dir+"libCgl.lib "+lib_base_dir+"libOsiSym.lib "+lib_base_dir+"libSym.lib "+lib_base_dir+"libCbcSolver.lib "+lib_base_dir+"libCbc.lib "+lib_base_dir+"libbonmin.lib "+lib_base_dir+"pthreadVC2.lib " ]

elseif getos()=="Darwin" then 
	third_dir = path_builder+filesep()+'..'+filesep()+'..'+filesep()+'thirdparty';
    	lib_base_dir = third_dir + filesep() + 'Mac' + filesep() + 'lib' + filesep() + Version + filesep();
    	inc_base_dir = third_dir + filesep() + 'Mac' + filesep() + 'include' + filesep() + 'coin';
    	C_Flags=["-D__USE_DEPRECATED_STACK_FUNCTIONS__ -w -fpermissive -I"+path_builder+" -I"+inc_base_dir+" -Wl,-rpath "+lib_base_dir+" "]
    	Linker_Flag = ["-L"+lib_base_dir+"libSym"+" "+"-L"+lib_base_dir+"libipopt"+" "+"-L"+lib_base_dir+"libClp"+" "+"-L"+lib_base_dir+"libOsiClp"+" "+"-L"+lib_base_dir+"libCoinUtils" + " "+"-L"+lib_base_dir+"libbonmin" ]

else//LINUX

    third_dir = path_builder+filesep()+'..'+filesep()+'..'+filesep()+'thirdparty';
    lib_base_dir = third_dir + filesep() + 'linux' + filesep() + 'lib' + filesep() + Version + filesep();
    inc_base_dir = third_dir + filesep() + 'linux' + filesep() + 'include';
    

    //C_Flags=["-w -fpermissive -I"+path_builder+" -I"+inc_base_dir+" -Wl,-rpath="+lib_base_dir+" "+"-std=gnu++11"]

		//C_Flags = ["-D_GLIBCXX_USE_CXX11_ABI=0"+" "+"-Wall -L"+lib_base_dir+" "+ "-Wl,-rpath="+lib_base_dir+" -I"+inc_base_dir+" "+"-I/usr/include/octave-4.4.1/octave/"]
    C_Flags = ["-I"+inc_base_dir];
//disp(inc_base_dir)
    //Linker_Flag = ["-loctave"+" "+"-loctinterp"+" "+"-L/usr/lib/x86_64-linux-gnu/libqrupdate.so.1"+" "+"-L/usr/lib/x86_64-linux-gnu/libamd.so.2"+" "+"-L/usr/lib/x86_64-linux-gnu/libccolamd.so.2"+" "+"-L/usr/lib/x86_64-linux-gnu/libcolamd.so.2"+" "+"-L/usr/lib/x86_64-linux-gnu/libcholmod.so.3"+" "+"-L/usr/lib/x86_64-linux-gnu/libcolamd.so.2"+" "+"-L/usr/lib/x86_64-linux-gnu/libumfpack.so.5"+" "+"-L/usr/lib/x86_64-linux-gnu/libcxsparse.so.3"+" "+"-L/usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so"+" "+"-Wl,-rpath="+lib_base_dir]

//		Linker_Flag = ["-loctave"+" "+"-loctinterp"+" "+"#-L/usr/lib/x86_64-linux-gnu/libfftw3_threads.so.3"+" "+"-Wl,-rpath="+lib_base_dir]
		Linker_Flag = ["-loctave -loctinterp -L" + lib_base_dir + " -lfun -Wl,-rpath="+lib_base_dir]

    //Linker_Flag = ["-lutil -g -Wall"+" "+"-L"+lib_base_dir+" " + "-loctave"+" "+ "-loctinterp"]
    disp(C_Flags);
    disp(Linker_Flag);
    
end

tbx_build_gateway(toolbox_title,Function_Names,Files,get_absolute_file_path("builder_gateway_cpp.sce"), [], Linker_Flag, C_Flags,[]);

clear toolbox_title Function_Names Files Linker_Flag C_Flags;
