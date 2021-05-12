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

	/**
	 * 
	 * @brief Enumeration for the data types suported by the fun() 
	 * 
	 */
	typedef enum {
		TYPE_DOUBLE,	/**similar to scilab double*/
		TYPE_COMPLEX,	/**similar to scilab complex*/
		TYPE_STRING,	/**similar to scilab string*/
		TYPE_STRUCT,	/**similar to scilab struct*/
	}FUNCTYPE;

	/**
	 * @struct FUNCSTRUCT
	 * @brief Struct used to pass structs to Octave from the fun library
	 * @var type
	 * 
	 */

	typedef struct {
		FUNCTYPE type;		/// Type of value in struct's field 
		void* key;			/// key of struct field
		int rows;			/// rows dimension of struct field's value
		int cols;			/// cols dimension of struct fields' value
		void* dataReal;		/// Real data if struct field's value is real
		void* dataImg;		/// Img data if struct field's value is complex
		void* str;			/// String data if struct field's value is string
	} FUNCSTRUCT;

	/**
	 * @brief Struct used to send/receive Scilab data to/from the gateway to fun.cpp API
	 * 
	 */

	typedef struct {
		FUNCTYPE type;			/// Type of data  
		int n_in_rows;			/// Input rows dimension of data
		int n_in_cols;			/// Input cols dimension of data
		int n_in_struct_len; 	/// input struct length
		int n_out_rows;			/// Ouput rows dimension of data
		int n_out_cols;			/// Output cold dimension of data
		int n_out_struct_len;	/// Output struct length
		int is_in_cmplx;		/// Input is a Complex data type
		int is_out_cmplx;		/// Output is a Complex data type
		int is_out_struct;		/// Output is a Struct data type
		void* in_data_real;		/// Input real part (complex) array
		void* in_data_img;		/// Input imaginary part (complex) array
		void* out_data_real;	/// Output real part (complex) array
		void* out_data_img;		/// Output imaginary part (complex) array
		FUNCSTRUCT* in_struct;  /// Input struct 
		FUNCSTRUCT* out_struct;	/// Output struct
	} FUNCARGS;
	/**
	 * @brief Struct used to call and pass the data to fun.cpp API
	 * 
	 */
	typedef struct {
		int n_in_arguments;		/// Number of input arguments
		int n_out_arguments;	/// Number of output arguments
		int n_out_user;			/// Number of output arguments
		char *err; 				/// Return errors
		//char *package; 		//Name of octave package to be loaded
		FUNCARGS *argument;		/// Struct defining and containing the data
	} FUNCCALL;
	/**
	 * @brief API Function to call/receive and pass the data to fun API  
	 * 
	 * 
	 * @param arr Input data FUNCARGS
	 * @param call Input Arguments  FUNCCALL
	 * @return int 
	 */
	int fun(FUNCARGS *arr, FUNCCALL *call);
}
