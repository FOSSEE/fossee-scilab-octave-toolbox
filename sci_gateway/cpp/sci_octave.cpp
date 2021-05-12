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
#include <string>
#include "wchar.h"
#include <cstdlib>
#include <sstream>

extern "C"
{
#include <Scierror.h>
#include <sciprint.h>
#include <api_scilab.h>
#include "localization.h"
#include "fun.h"
#include <cstdio>
#include <math.h>
#include <stdio.h>
#include "os_string.h"
#include <stdlib.h>

	static const char fname[] = "octave_fun";

	/**
	 * @brief Function to connect to Scilab's API.
	 * 
	 *	This function will get Data from Scilab, proccess the data
	 *	in Octave then return the output back to Scilab using the 
	 *	API.
	 * 
	 * @param env Scialb env
	 * @param nin[in] Number of input arguments
	 * @param in[in] Input Parameters
	 * @param nopt[in] Number of optional parameters
	 * @param opt[in] Optional parameters
	 * @param nout[out] Number of expected output parametets
	 * @param out[out] Array for output data
	 * @return int 
	 */
	int sci_octave_fun(scilabEnv env, int nin, scilabVar *in, int nopt, scilabOpt *opt, int nout, scilabVar *out)

	{
		//DEBUG//printf("nin: %d\n", nin);
		// Check number of inputs
		if (nin < 1)
		{
			Scierror(999, _("%s: Wrong number of input arguments. Atleast %d expected.\n"), fname, 2);
			return STATUS_ERROR;
		}

		// Declare and initialize the API variables
		FUNCCALL funcall;
		FUNCCALL *funptr = &funcall;
		funcall.n_in_arguments = nin;
		funcall.n_out_user = nout;
		FUNCARGS ins[funcall.n_in_arguments * nout];
		FUNCARGS *argptr = ins;

		int i, j;
		double *d;
		double *rd = NULL;
		double *cd = NULL;
		int size;
		char str[20];
		char *c;
		double *n = NULL;
		int row = 0;
		int col = 0;
		double *in_real;
		double *in_img;



		// Check the data type of input variables and format them into the FUNNCALL
		for (i = 0; i < nin; i++)
		{
			// Check if [in] of type Sci:matrix
			if (scilab_getType(env, in[i]) == 1)
			{
				ins[i].type = TYPE_DOUBLE;

				// Check if [in] is of type Sci:complex
				if (scilab_isComplex(env, in[i]) == 1)
				{
					//DEBUG//printf("input %d is complex \n", i);
					ins[i].is_in_cmplx = 1;
					size = scilab_getDim2d(env, in[i], &row, &col);
					ins[i].n_in_rows = row;
					ins[i].n_in_cols = col;
					scilab_getDoubleComplexArray(env, in[i], &in_real, &in_img);

					ins[i].in_data_real = malloc(sizeof(double) * size);
					ins[i].in_data_img = malloc(sizeof(double) * size);
					rd = (double *)ins[i].in_data_real;
					cd = (double *)ins[i].in_data_img;

					////This code snippet is to flatten matrix row wise and then store it
					int p, q, k = 0;
					for (p = 0; p < row; p++)
					{
						for (q = 0; q < col; q++)
						{
							rd[k] = in_real[p + q * row];
							cd[k] = in_img[p + q * row];
							k++;
							//printf("%d\n",in_real[k]);
							//printf("%d\n",in_img[k]);
						}
					}
				}
				// [in] is not of type Sci:complex
				else
				{
					//DEBUG//printf("input %d is NOT complex \n", i);
					ins[i].is_in_cmplx = 0;
					size = scilab_getDim2d(env, in[i], &row, &col);
					ins[i].n_in_rows = row;
					ins[i].n_in_cols = col;
					scilab_getDoubleArray(env, in[i], &n);

					ins[i].in_data_real = malloc(sizeof(double) * size);
					d = (double *)ins[i].in_data_real;

					//DEBUG//This code snippet is to flatten matrix row wise and then store it
					int p, q, k = 0;
					for (p = 0; p < row; p++)
					{
						for (q = 0; q < col; q++)
						{
							d[k] = n[p + q * row];
							k++;
							//printf("%f\n",d[j]);
						}
					}
				}
				/////////////////////////////////////////
			}
			// Check if [in] of type SCI:Matrix of strings
			else if (scilab_getType(env, in[i]) == 10)
			{
				ins[i].is_in_cmplx = 0;
				wchar_t *in1 = 0;

				scilab_getString(env, in[i], &in1);
				//printf("%S\n", in1);

				wcstombs(str, in1, sizeof(str));
				//printf("%s\n", str);
				if (str)
				{
					//printf("lenght of string input: %d\n", strlen(str));
					ins[i].type = TYPE_STRING;
					ins[i].n_in_rows = 1;
					ins[i].n_in_cols = strlen(str);
					size = (ins[i].n_in_rows) * (ins[i].n_in_cols);
					ins[i].in_data_real = malloc(sizeof(char) * (size + 1));
					c = (char *)ins[i].in_data_real;
					int ci;

					strcpy(c, str);
					ins[i].n_in_cols = strlen(c);
					//printf("in scilab strin is: %s\n", c);
				}
			}
			else if (scilab_getType(env, in[i]) == 18) //Checking for Struct input
            {
				ins[i].type = TYPE_STRUCT;
                wchar_t** keys = NULL;
                scilabVar struct_out;       
				int dims = 0;      
                                
                dims = scilab_getFields(env, in[i], &keys); // Retrieving Struct Keys
				ins[i].n_in_struct_len = dims;
				//std::cout<<dims<<std::endl;
				
				// allocating memory for keys and values
				ins[i].in_struct = (FUNCSTRUCT*) malloc(sizeof(FUNCSTRUCT) * dims);
				FUNCSTRUCT* inStruct = ins[i].in_struct;
				                 
                for (j = 0; j < dims; j++)
                {
					// storing the key
                    inStruct[j].key = malloc(sizeof(wchar_t) * (wcslen(keys[j]) + 1));
					wcpcpy((wchar_t*) inStruct[j].key, keys[j]);

                    struct_out = scilab_getStructMatrix2dData(env, in[i], keys[j], 0, 0); // Retrieving Curr Value

                    // Checking Type of value in struct
					if (scilab_getType(env,struct_out) == 1) 
					{
						// Double Value
						if (scilab_isComplex(env,struct_out) == 1)
						{
							// Complex Value
							//printf("input %d is complex \n", i)
							inStruct[j].type = TYPE_COMPLEX;
							size = scilab_getDim2d(env, struct_out, &row, &col);
							inStruct[j].rows = row;
							inStruct[j].cols = col;
							scilab_getDoubleComplexArray(env, struct_out, &in_real, &in_img);

							inStruct[j].dataReal = malloc(sizeof(double) * size);
							inStruct[j].dataImg = malloc(sizeof(double) * size);
							rd = (double *) inStruct[j].dataReal;
							cd = (double *) inStruct[j].dataImg;

							////This code snippet is to flatten matrix row wise and then store it
							int p, q, k = 0;
							for (p = 0; p < row; p++)
							{
								for (q = 0; q < col; q++)
								{
									// printf("%d\n",in_real[p + q * row]);
									// printf("%d\n",in_img[p + q * row]);
									rd[k] = in_real[p + q * row];
									cd[k] = in_img[p + q * row];
									k++;
								}
							}
						}
						else
						{
							// Real Values Only
							inStruct[j].type = TYPE_DOUBLE;
							//printf("input %d is NOT complex \n", i);
							size = scilab_getDim2d(env, struct_out, &row, &col);
							scilab_getDoubleArray(env, struct_out, &n);

							inStruct[j].rows = row;
							inStruct[j].cols = col;

							inStruct[j].dataReal = malloc(sizeof(double) * size);
							d = (double *) inStruct[j].dataReal;

							////This code snippet is to flatten matrix row wise and then store it
							int p, q, k = 0;
							for (p = 0; p < row; p++)
							{
								for (q = 0; q < col; q++)
								{
									// printf("%f\n",n[k]);
									d[k] = n[k];
									k++;	
								}
							}
						}
					}
					else if (scilab_getType(env,struct_out) == 10)
					{
						inStruct[j].type = TYPE_STRING;
						wchar_t *in1 = NULL;

						scilab_getString(env, struct_out, &in1);
						//printf("%S\n", in1);

						inStruct[j].str = malloc(sizeof(wchar_t) * (wcslen(in1) + 1));
						wcpcpy((wchar_t*) inStruct[j].str, in1);
						// printf("%s\n", str);
					}
					else
					{
						Scierror(999, _("%s: Wrong type of input argument %d.\n"), fname, i);
						return STATUS_ERROR;
					}
				}
            }
			else
			{
				Scierror(999, _("%s: Wrong type of input argument %d.\n"), fname, i);
				return STATUS_ERROR;
			}
		}

		// Capturing Errors and warnings
		std::stringstream buffer_err;

		// set our error buffer
		std::cerr.rdbuf(buffer_err.rdbuf());

		// call the fun() function
		int status_fun = fun(argptr, funptr);

		// grab error buffer contents
		std::string err = buffer_err.str();

		if (!err.empty() && status_fun == 0)
			sciprint("Warning from Octave\n%s", err.c_str());
		buffer_err.str("");

		//printf("in scilab status_fun is: %d\n", status_fun);
		//printf("in scilab funcall.n_out_arguments is: %d\n", funcall.n_out_arguments);
		//printf("in scilab funcall.n_out_user is: %d\n", funcall.n_out_user);
		//printf("in scilab ins[0].n_out_rows is: %d\n", ins[0].n_out_rows);
		//printf("in scilab ins[0].n_out_cols is: %d\n", ins[0].n_out_cols);
		//printf("in scilab ouput args are: %d\n", funcall.n_out_arguments);

		if (status_fun == 1)
		{
			Scierror(999, "Error from Octave\n%s", err.c_str());
			return 1;
		}
		// Format output variable for SciLab
		else if (funcall.n_out_user <= funcall.n_out_arguments)
		{
			for (i = 0; i < nout; i++)
			{
				// Format Complex data type
				if (ins[i].is_out_cmplx == 1)
				{
					//printf("output %d is complex\n", i);
					out[i] = scilab_createDoubleMatrix2d(env, ins[i].n_out_rows, ins[i].n_out_cols, 1);
					double *out_real = NULL;
					double *out_img = NULL;
					scilab_getDoubleComplexArray(env, out[i], &out_real, &out_img);
					int len = ins[i].n_out_rows * ins[i].n_out_cols;
					double *ord = (double *)ins[i].out_data_real;
					double *ocd = (double *)ins[i].out_data_img;
					//printf("output length is: %d\n", len);
					for (j = 0; j < len; j++)
					{
						out_real[j] = ord[j];
					}

					for (j = 0; j < len; j++)
					{
						out_img[j] = ocd[j];
					}
				}
				// Format Struct data type
				else if (ins[i].is_out_struct == 1)
				{
					// creating scilab struct
					out[i] = scilab_createStruct(env);
					int structLen = ins[i].n_out_struct_len;

					FUNCSTRUCT *outStruct = ins[i].out_struct;

					for (int j = 0; j < structLen; j++)
					{
						// std::printf("currKey in sciOctave.cpp OP: %ls\n", outStruct[j].key);
						scilab_addField(env, out[i], (const wchar_t *)outStruct[j].key);
						scilabVar currValue = NULL;
						if (outStruct[j].type == TYPE_COMPLEX)
						{
							currValue = scilab_createDoubleMatrix2d(env, outStruct[j].rows, outStruct[j].cols, 1);

							double *outReal = NULL;
							double *outImg = NULL;
							scilab_getDoubleComplexArray(env, currValue, &outReal, &outImg);

							double* dReal = (double *) outStruct[j].dataReal;
							double* dImg = (double *) outStruct[j].dataImg;

							int size = outStruct[j].rows * outStruct[j].cols;
							for(int k = 0; k < size; k++){
								outReal[k] = dReal[k];
							}
							for(int k = 0; k < size; k++){
								outImg[k] = dImg[k];
							}

							// set the key-value pair in scilab struct
							scilab_setStructMatrix2dData(env, out[i], (const wchar_t*) outStruct[j].key, 0, 0, currValue);
						}
						else if (outStruct[j].type == TYPE_DOUBLE){
							currValue = scilab_createDoubleMatrix2d(env, outStruct[j].rows, outStruct[j].cols, 0);
							
							double *outReal = NULL;
							scilab_getDoubleArray(env, currValue, &outReal);

							double* dReal = (double *) outStruct[j].dataReal;
							
							int size = outStruct[j].rows * outStruct[j].cols;
							for(int k = 0; k < size; k++){
								outReal[k] = dReal[k];
							}

							// set the key-value pair in scilab struct
							scilab_setStructMatrix2dData(env, out[i], (const wchar_t*) outStruct[j].key, 0, 0, currValue);
						}
						else if (outStruct[j].type == TYPE_STRING){
							scilab_setStructMatrix2dData(env, out[i], (const wchar_t*) outStruct[j].key, 0, 0, scilab_createString(env, (const wchar_t*) outStruct[j].str));
						}
					}
				}
				else if (ins[i].is_out_string == 1){
					out[i] = scilab_createString(env, (wchar_t *) ins[i].out_data_real);
				}
				else
				{
					//printf("output %d is NOT complex\n", i);
					out[i] = scilab_createDoubleMatrix2d(env, ins[i].n_out_rows, ins[i].n_out_cols, 0);
					double *out1 = NULL;
					scilab_getDoubleArray(env, out[i], &out1);
					int len = ins[i].n_out_rows * ins[i].n_out_cols;
					double *dd = (double *)ins[i].out_data_real;
					//printf("output length is: %d\n", len);
					for (j = 0; j < len; j++)
					{
						out1[j] = dd[j]; //.float_value();
					}
				}
			}
		}
		else
		{
			Scierror(77, _("%s: Wrong number of output arguments: This function can return a maximum of %d output(s).\n"), fname, funcall.n_out_arguments);
			return 1;
		}

		// Free the mem allocated for out variables
		for (i = 0; i < nout; i++)
		{
			// 
			if (ins[i].is_out_struct == 1)
			{
				FUNCSTRUCT *tempStruct = ins[i].out_struct;
				for (int j = 0; j < ins[i].n_out_struct_len; j++)
				{
					// std::wstring tempWStr((wchar_t *) tempStruct[j].key);
					// std::string(tempWStr.begin(), tempWStr.end());
					// std::cout << "freeing key: " << std::string(tempWStr.begin(), tempWStr.end()) << std::endl;
					free(tempStruct[j].key);
					if (tempStruct[j].type == TYPE_STRING){
						free(tempStruct[j].str);
					}
					if (tempStruct[j].type == TYPE_DOUBLE){
						free(tempStruct[j].dataReal);
					}
					if (tempStruct[j].type == TYPE_COMPLEX){
						free(tempStruct[j].dataReal);
						free(tempStruct[j].dataImg);
					}
				}
				free(ins[i].out_struct);
			}
			else{
				free(ins[i].out_data_real);
			}

			if (ins[i].is_out_cmplx == 1){
				free(ins[i].out_data_img);
			}
		}
		for (i = 0; i < nin; i++)
		{
			if(ins[i].type == TYPE_STRUCT){
				FUNCSTRUCT* tempStruct = ins[i].in_struct;
				for (int j = 0; j < ins[i].n_in_struct_len; j++){
					free(tempStruct[j].key);
					if (tempStruct[j].type == TYPE_STRING){
						free(tempStruct[j].str);
					}
					if (tempStruct[j].type == TYPE_DOUBLE){
						free(tempStruct[j].dataReal);
					}
					if (tempStruct[j].type == TYPE_COMPLEX){
						free(tempStruct[j].dataReal);
						free(tempStruct[j].dataImg);
					}
				}
				free(ins[i].in_struct);
			}
			else{
				free(ins[i].in_data_real);
			}

			if (ins[i].is_in_cmplx == 1){
				free(ins[i].in_data_img);
			}
		}
		return 0;
	}
}
