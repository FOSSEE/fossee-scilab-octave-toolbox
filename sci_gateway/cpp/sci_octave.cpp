#include <string>
#include "wchar.h"
#include <cstdlib>

extern "C"
{
#include<Scierror.h>
#include<sciprint.h>
#include<api_scilab.h>
#include "localization.h"
#include "fun.h"
#include <cstdio>
#include <math.h>
#include <stdio.h>
#include "os_string.h"
#include <stdlib.h>



static const char fname[] = "octave_fun";
int sci_octave_fun(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
//printf("nin: %d\n", nin);
	if (nin < 2)
    {
        Scierror(999, _("%s: Wrong number of input arguments. Atleast %d expected.\n"), fname, 2);
        return STATUS_ERROR;
    }

	FUNCCALL funcall;
	FUNCCALL *funptr = &funcall;
	funcall.n_in_arguments = nin;
	funcall.n_out_user = nout;

	FUNCARGS ins[funcall.n_in_arguments*nout];
	FUNCARGS *argptr = ins;

	int i,j;
	double* d;
	double* rd = NULL;;
	double* cd = NULL;;
	int size;
	char str[20];
	char* c;
	double* n = NULL;
	int row = 0;
  int col = 0;
	double* in_real;
	double* in_img;

	for(i=0;i<nin;i++)
	{
		if(scilab_getType(env, in[i])==1)
		{	
			ins[i].type = TYPE_DOUBLE;
			if(scilab_isComplex(env, in[i])==1)
			{
				//printf("input %d is complex \n", i);
				ins[i].is_in_cmplx=1;
				size = scilab_getDim2d(env, in[i], &row, &col);
				ins[i].n_in_rows = row;
				ins[i].n_in_cols = col;
				scilab_getDoubleComplexArray(env, in[i],&in_real, &in_img);

				ins[i].in_data_real = malloc(sizeof(double)*size);
				ins[i].in_data_img = malloc(sizeof(double)*size);
				rd = (double *)ins[i].in_data_real;
				cd = (double *)ins[i].in_data_img;

	////This code snippet is to flatten matrix row wise and then store it
				int p,q,k = 0;
				for(p=0;p<row;p++)
				{
					for(q=0;q<col;q++)
					{
						rd[k] = in_real[p + q*row];
						cd[k] = in_img[p + q*row];
						k++;
						//printf("%d\n",in_real[k]);
						//printf("%d\n",in_img[k]);
					}
				}
			}
			else
			{
				//printf("input %d is NOT complex \n", i);
				ins[i].is_in_cmplx=0;
				size = scilab_getDim2d(env, in[i], &row, &col);
				ins[i].n_in_rows = row;
				ins[i].n_in_cols = col;
				scilab_getDoubleArray(env, in[i], &n);

				ins[i].in_data_real = malloc(sizeof(double)*size);
				d = (double *)ins[i].in_data_real;

	////This code snippet is to flatten matrix row wise and then store it
				int p,q,k = 0;
				for(p=0;p<row;p++)
				{
					for(q=0;q<col;q++)
					{
						d[k] = n[p + q*row];
						k++;
						//printf("%f\n",d[j]);
					}
				}
			}
/////////////////////////////////////////
		}
		else if(scilab_getType(env, in[i])==10)
		{
			ins[i].is_in_cmplx=0;
			wchar_t* in1 = 0;

			scilab_getString(env, in[i], &in1);
			//printf("%S\n", in1);

			wcstombs(str, in1, sizeof(str));
			//printf("%s\n", str);
			if(str)
			{
				//printf("lenght of string input: %d\n", strlen(str));
				ins[i].type = TYPE_STRING;
				ins[i].n_in_rows = 1;
				ins[i].n_in_cols = strlen(str);
				size = (ins[i].n_in_rows)*(ins[i].n_in_cols);
				ins[i].in_data_real = malloc(sizeof(char)*size+1);
				c = (char *)ins[i].in_data_real;
				int ci;

				strcpy(c,str);	
				ins[i].n_in_cols = strlen(c);
				//printf("in scilab strin is: %s\n", c);

			}
		}
		else
		    {
        Scierror(999, _("%s: Wrong type of input argument %d.\n"), fname, i);
        return STATUS_ERROR;
    }
	}

			int status_fun = fun(argptr, funptr);
		//printf("in scilab status_fun is: %d\n", status_fun);
			//printf("in scilab funcall.n_out_arguments is: %d\n", funcall.n_out_arguments);
			//printf("in scilab funcall.n_out_user is: %d\n", funcall.n_out_user);
//printf("in scilab ins[0].n_out_rows is: %d\n", ins[0].n_out_rows);
//printf("in scilab ins[0].n_out_cols is: %d\n", ins[0].n_out_cols);


//printf("in scilab ouput args are: %d\n", funcall.n_out_arguments);
	if(status_fun==1)
	{
		Scierror(999, "\nOctave unable to process!\nCorrect usage:\n octave_fun(\"octave_function\",input1,input2,...)\n octave_fun(\"octave_function\",input1,input2,...,optional_input1,optional_input2,...)\n octave_fun(\"octave_function\",\"octave_package\",input1,input2,...)\n octave_fun(\"octave_function\",\"octave_package\",input1,input2,...,optional_input1,optional_input2,...)\n");
		return 1;
	}
	else if(funcall.n_out_user <= funcall.n_out_arguments)
	{	
		for(i=0;i<nout;i++)
		{	
			
		if(ins[i].is_out_cmplx==1)
		{
			//printf("output %d is complex\n", i);
			out[i] = scilab_createDoubleMatrix2d(env, ins[i].n_out_rows, ins[i].n_out_cols, 1);
			double* out_real = NULL;
			double* out_img = NULL;
			scilab_getDoubleComplexArray(env, out[i],&out_real, &out_img);
			int len = ins[i].n_out_rows*ins[i].n_out_cols;
			double* ord = (double *)ins[i].out_data_real;
			double* ocd = (double *)ins[i].out_data_img;
			//printf("output length is: %d\n", len);
			for(j=0; j<len; j++)
				{
					out_real[j] = ord[j];
				}

			for(j=0; j<len; j++)
				{
					out_img[j] = ocd[j];
				}
		}
		else
		{
			//printf("output %d is NOT complex\n", i);
			out[i] = scilab_createDoubleMatrix2d(env, ins[i].n_out_rows, ins[i].n_out_cols, 0);
			double* out1 = NULL;
		 	scilab_getDoubleArray(env, out[i], &out1);
			int len = ins[i].n_out_rows*ins[i].n_out_cols;
			double* dd = (double *)ins[i].out_data_real;
			//printf("output length is: %d\n", len);
			for(j=0; j<len; j++)
				{
					out1[j] = dd[j];//.float_value();
				}
			}
		}
	}
	else
	{
			Scierror(77, _("%s: Wrong number of output arguments: This function can return a maximum of %d output(s).\n"), fname, funcall.n_out_arguments);
			return 1;
		}




	for(i=0;i<nout;i++)
	{
		free(ins[i].out_data_real);

		if(ins[i].is_out_cmplx==1)
			free(ins[i].out_data_img);
	}

	for(i=0;i<nin;i++)
	{
		free(ins[i].in_data_real);

		if(ins[i].is_in_cmplx==1)
			free(ins[i].in_data_img);
	}
  return 0;
}
}
