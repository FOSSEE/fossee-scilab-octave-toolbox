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
///////#####call octave_fun("hamming",[5],"periodic") ########////////////
int sci_octave_fun(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
//printf("nin: %d\n", nin);
	if (nin < 1)
    {
        Scierror(999, _("%s: Wrong number of input arguments. Atleast %d expected.\n"), fname, 1);
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
	int size;
	char str[20];
	char* c;
	double* n = NULL;
	int row = 0;
  int col = 0;

	for(i=0;i<nin;i++)
	{
		if(scilab_getType(env, in[i])==1)
		{	
			ins[i].type = TYPE_DOUBLE;
			size = scilab_getDim2d(env, in[i], &row, &col);
			ins[i].n_in_rows = row;
			ins[i].n_in_cols = col;
			scilab_getDoubleArray(env, in[i], &n);

			ins[i].in_data = malloc(sizeof(double)*size);
			d = (double *)ins[i].in_data;

			for(j=0;j<size;j++)
			{
				d[j] = n[j];
				//printf("%f\n",d[j]);
			}
		}
		else if(scilab_getType(env, in[i])==10)
		{
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
				ins[i].in_data = malloc(sizeof(char)*size+1);
				c = (char *)ins[i].in_data;
				int ci;

				strcpy(c,str);	
				ins[i].n_in_cols = strlen(c);
				//printf("in scilab strin is: %s\n", c);

			}
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
		return 1;
	}
	else if(funcall.n_out_user <= funcall.n_out_arguments)
	{	
		for(i=0;i<nout;i++)
		{	
			out[i] = scilab_createDoubleMatrix2d(env, ins[i].n_out_rows, ins[i].n_out_cols, 0);

			double* out1 = NULL;
		 	scilab_getDoubleArray(env, out[i], &out1);
			int len = ins[i].n_out_rows*ins[i].n_out_cols;
			double* dd = (double *)ins[i].out_data;
			//printf("output length is: %d\n", len);
			for(j=0; j<len; j++)
				{
					out1[j] = dd[j];//.float_value();
				}
		}
	}
	else
	{
			Scierror(77, _("%s: Wrong number of output argument(s): This function can return a maximum of %d output(s).\n"), fname, funcall.n_out_arguments);
			return 1;
		}




	for(i=0;i<nout;i++)
	{
		//printf("%ld : ",&ins[i].in_data);
	//	printf("%f\n",(*(double *)ins[i].in_data));
	
		free(ins[i].out_data);	
	}
	for(i=0;i<nin;i++)
	{
		//printf("%ld : ",&ins[i].in_data);
	//	printf("%f\n",(*(double *)ins[i].in_data));
	
		free(ins[i].in_data);	
	}
  return 0;
}
}
