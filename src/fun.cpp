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

#include <iostream>
#include <stdlib.h>
#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/interpreter.h>
#include <math.h>
#include <string>
#include <cstring>
#include "fun.h"

extern "C"
{
	/*!
	* \brief Function to Interact with Octave's API.
	*
	* This Function will be communicating with Octave to access it's function.
	*/
	int fun(FUNCARGS *inp, FUNCCALL *funcall)
	{

		static octave::interpreter interpreter;															
		bool status = interpreter.initialized();
		// Check octave interpreter loaded
		if (status == false)
		{
			interpreter.initialize();
			int status_exec = interpreter.execute();

			if (status_exec != 0)
			{
				std::cerr << "creating embedded Octave interpreter failed!"
						  << std::endl;
			}
		}

		try
		{
			octave_value_list in;
			unsigned int k;
			int l;
			int str_count = 0;
			char str_fun[20];
			char str_pkg[20];
			int pkg = 0;
			int nouts;
			// Format the input data values into data type acceptable by Octave
			for (l = 0; l < funcall->n_in_arguments; l++)
			{
				//check if Input type is Double
				if (inp[l].type == TYPE_DOUBLE)
				{
					if (inp[l].is_in_cmplx == 1)
					{
						ComplexMatrix matr = ComplexMatrix(inp[l].n_in_rows, inp[l].n_in_cols);
						double *id_real = (double *)inp[l].in_data_real;
						double *id_img = (double *)inp[l].in_data_img;
						k = 0;
						for (int r = 0; r < inp[l].n_in_rows; r++)
						{
							for (int c = 0; c < inp[l].n_in_cols; c++)
							{
								Complex cc(id_real[k], id_img[k]);
								matr(r, c) = cc;
								k++;
							}
						}
						in(l - str_count) = octave_value(matr);
					}
					else
					{
						Matrix inMatrix_x(inp[l].n_in_rows, inp[l].n_in_cols);
						double *id = (double *)inp[l].in_data_real;
						k = 0;
						for (unsigned int i = 0; i < inp[l].n_in_rows; i++)
						{
							for (unsigned int j = 0; j < inp[l].n_in_cols; j++)
							{
								inMatrix_x(i, j) = id[k];
								k++;
							}
						}
						in(l - str_count) = inMatrix_x;
					}
				}
				//check if Input type is string
				else if (inp[l].type == TYPE_STRING)
				{
					//std::cout << "In fun string. l is : " << l << '\n';

					char *c = (char *)inp[l].in_data_real;
					//std::cout << "String is: " << c << '\n';
					if (l == 0){
						strcpy(str_fun, c);
						str_count++;
					}
					else if (l == 1)
					{
						strcpy(str_pkg, c);
						pkg = 1;
						str_count++;
					}
					else
						in(l - str_count) = c;

					//std::cout << "String is: " << c << '\n';
				}
				//check if Input type is struct
				else if (inp[l].type == TYPE_STRUCT){
					FUNCSTRUCT* inStruct = inp[l].in_struct;

					octave_scalar_map inOctaveStruct;

					// populate the octave structure
					for (int j = 0; j < inp[l].n_in_struct_len; j++){
						std::string currKey;
						octave_value currValue;

						// converting wchar_t* to string for octave
						std::wstring currKeyWStr((wchar_t *) inStruct[j].key);
						currKey = std::string(currKeyWStr.begin(), currKeyWStr.end());


						// get Value 
						if (inStruct[j].type == TYPE_COMPLEX){
							ComplexMatrix currValueMatrix = ComplexMatrix(inStruct[j].rows, inStruct[j].cols);
							double* dReal = (double *)inStruct[j].dataReal;
							double* dImg = (double *)inStruct[j].dataImg;
							k = 0;
							for (int r = 0; r < inStruct[j].rows; r++)
							{
								for (int c = 0; c < inStruct[j].cols; c++)
								{
									Complex currItem(dReal[k], dImg[k]);
									currValueMatrix(r, c) = currItem;
									k++;
								}
							}
							currValue = currValueMatrix;
						}
						else if(inStruct[j].type == TYPE_DOUBLE){
							Matrix currValueMatrix = Matrix(inStruct[j].rows, inStruct[j].cols);
							double* dReal = (double *)inStruct[j].dataReal;
							k = 0;
							for (int r = 0; r < inStruct[j].rows; r++)
							{
								for (int c = 0; c < inStruct[j].cols; c++)
								{
									currValueMatrix(r, c) = dReal[k];
									k++;
								}
							}
							currValue = currValueMatrix;
						}
						else if (inStruct[j].type == TYPE_STRING){
							std::wstring currValueWStr((wchar_t *) inStruct[j].str);
							std::string currValueStr(currValueWStr.begin(), currValueWStr.end());
							currValue = octave_value(currValueStr);
						}
						inOctaveStruct.assign(currKey, currValue);
					}

					// insert struct to input octave list
					in(l - str_count) = inOctaveStruct;
				}
			}

			if (pkg == 1)
			{
				//std::cout << "loading package " << str_pkg << '\n';
				octave::feval("pkg", ovl("load", str_pkg), 0);
			}
			// Use feval to compute the required values
			octave_value_list out = octave::feval(str_fun, in, funcall->n_out_user);

			int row = 0;
			int col = 0;
			nouts = out.length();
			funcall->n_out_arguments = nouts;
			// DEBUG // std::cout << "funcall->n_out_arguments is: " << funcall->n_out_arguments << '\n';
			// Format and set the output data values from Octave into the FUNCARGS
			for (unsigned int ii = 0; ii < nouts; ii++)
			{
				//Format complex data
				if (out(ii).iscomplex() == 1)
				{
					inp[ii].is_out_cmplx = 1;
					//std::cout << "out "<< ii<< " is complex" << '\n';
					ComplexMatrix cmOut(out(ii).complex_matrix_value());
					//std::cout << "cmOut "<< cmOut << '\n';
					//std::cout << "Out(ii) "<< out(ii).complex_matrix_value() << '\n';
					//std::cout << "out(ii) "<< out(ii) << '\n';
					row = cmOut.rows();
					col = cmOut.columns();
					inp[ii].n_out_rows = row;
					inp[ii].n_out_cols = col;
					k = 0;
					inp[ii].out_data_real = malloc(sizeof(double) * (row * col));
					inp[ii].out_data_img = malloc(sizeof(double) * (row * col));
					double *rd = (double *)inp[ii].out_data_real;
					double *cd = (double *)inp[ii].out_data_img;
					for (unsigned int i = 0; i < row; i++)
					{
						for (unsigned int j = 0; j < col; j++)
						{
							rd[k] = real(cmOut(k));
							cd[k] = imag(cmOut(k));
							//std::cout << "out img "<< k << " is :" << (double)imag(cmOut(k)) << '\n';
							k++;
						}
					}
				}
				//Format Struct data
				else if(out(ii).isstruct()){
					inp[ii].is_out_struct = 1;
					
					octave_scalar_map outOctaveStruct = out(ii).scalar_map_value();
					
					int structLen = outOctaveStruct.nfields();
					inp[ii].n_out_struct_len = structLen;
					
					inp[ii].out_struct = (FUNCSTRUCT *) malloc(sizeof(FUNCSTRUCT) * structLen);
					FUNCSTRUCT* outStruct = inp[ii].out_struct;
					
					octave_scalar_map::iterator idx = outOctaveStruct.begin();
					int j = 0;

					// std::cout << "data in fun.cpp\n";
					// populating structure
					while (idx != outOctaveStruct.end()){
						std::string currKey = outOctaveStruct.key(idx);
						octave_value currValue = outOctaveStruct.contents(idx);

						// storing key by converting string to wchar_t* for scilab
						outStruct[j].key = malloc(sizeof(wchar_t) * (currKey.length() + 1));
						mbstowcs((wchar_t *) outStruct[j].key, currKey.c_str(), currKey.length() + 1);
						
						// storing value
						if (currValue.iscomplex()){
							outStruct[j].type = TYPE_COMPLEX;	

							ComplexMatrix currValueComplexMatrix(currValue.complex_matrix_value());
							
							row = currValueComplexMatrix.rows();
							col = currValueComplexMatrix.columns();
							outStruct[j].rows = row;
							outStruct[j].cols = col;
							
							outStruct[j].dataReal = malloc(sizeof(double) * (row * col));
							outStruct[j].dataImg = malloc(sizeof(double) * (row * col));
							
							double* dReal = (double *) outStruct[j].dataReal;
							double* dImg = (double *) outStruct[j].dataImg;
							
							k = 0;
							for (int r = 0; r < row; r++)
							{
								for (int c = 0; c < col; c++)
								{
									dReal[k] = real(currValueComplexMatrix(k));
									dImg[k] = imag(currValueComplexMatrix(k));
									k++;
								}
							}

						}
						else if (currValue.is_string()){
							outStruct[j].type = TYPE_STRING;
							std::string currValueStr = currValue.string_value();
							outStruct[j].str = malloc(sizeof(wchar_t) * (currValueStr.length() + 1));
							mbstowcs((wchar_t*) outStruct[j].str, currValueStr.c_str(), currValueStr.length() + 1);
						}
						else {
							outStruct[j].type = TYPE_DOUBLE;
							
							Matrix currValueMatrix(currValue.matrix_value());

							row = currValueMatrix.rows();
							col = currValueMatrix.columns();
							outStruct[j].rows = row;
							outStruct[j].cols = col;

							outStruct[j].dataReal = malloc(sizeof(double) * (row * col));
							double* dReal = (double *) outStruct[j].dataReal;

							k = 0;
							for (int r = 0; r < row; r++)
							{
								for (int c = 0; c < col; c++)
								{
									dReal[k] = currValueMatrix(k);
									k++;
								}
							}
						}

						j++;
						idx++;
					}
				}
				else if(out(ii).is_string()){
					inp[ii].is_out_string = 1;

					octave_value currOut = out(ii);
					std::string currOutStr = currOut.string_value(); 

					inp[ii].out_data_real = malloc(sizeof(wchar_t) * (currOutStr.length() + 1));
					mbstowcs((wchar_t *) inp[ii].out_data_real, currOutStr.c_str(), currOutStr.length() + 1);
				}
				else
				{
					//std::cout << "out "<< ii<< " is NOT complex" << '\n';
					inp[ii].is_out_cmplx = 0;
					Matrix mOut(out(ii).matrix_value());
					row = mOut.rows();
					col = mOut.columns();
					inp[ii].n_out_rows = row;
					inp[ii].n_out_cols = col;
					k = 0;
					inp[ii].out_data_real = malloc(sizeof(double) * (row * col));
					double *dd = (double *)inp[ii].out_data_real;
					for (unsigned int i = 0; i < row; i++)
					{
						for (unsigned int j = 0; j < col; j++)
						{
							dd[k] = mOut(k);
							k++;
						}
					}
				}
			}
		}
		// Exception handling Octave
		catch (const octave::exit_exception &ex)
		{
			std::cerr << "Octave interpreter exited with status = "
					  << ex.exit_status() << std::endl;
			return 1;
		}
		catch (const octave::execution_exception &)
		{
			//DEBUG//std::cerr << "error encountered in Octave evaluator!" << std::endl;
			return 1;
		}
		return 0;
	}
}
