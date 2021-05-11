// Copyright (C) 2019 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Rupak Rokade
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

#define fun_h__
//extern "C" int fun (double* answ, double* in1, int in1_row, std::string name, std::string opt);

extern "C"
{

	typedef enum {
		TYPE_DOUBLE,
		TYPE_COMPLEX,
		TYPE_STRING,
		TYPE_STRUCT,
	}FUNCTYPE;

	typedef struct {
		FUNCTYPE type;		// type of value in struct's field
		void* key;			// key of struct field
		int rows;			// rows dimension of struct field's value
		int cols;			// cols dimension of struct fields' value
		void* dataReal;		// Real data if struct field's value is real
		void* dataImg;		// Img data if struct field's value is complex
		void* str;			// string data if struct field's value is string
	} FUNCSTRUCT;

	typedef struct {
		FUNCTYPE type;
		int n_in_rows;
		int n_in_cols;
		int n_in_struct_len; 	// ip struct length
		int n_out_rows;
		int n_out_cols;
		int n_out_struct_len;	// op struct length
		int is_in_cmplx;
		int is_out_cmplx;
		int is_out_struct;
		void* in_data_real;
		void* in_data_img;
		void* out_data_real;
		void* out_data_img;
		FUNCSTRUCT* in_struct;
		FUNCSTRUCT* out_struct;
	} FUNCARGS;

	typedef struct {
		int n_in_arguments;		// number of input arguments
		int n_out_arguments;	// number of output arguments
		int n_out_user;			// number of output arguments
		char *err; 				// Name
		//char *package; 		//Name of octave package to be loaded
		FUNCARGS *argument;
	} FUNCCALL;

	int fun(FUNCARGS *arr, FUNCCALL *call);
}
