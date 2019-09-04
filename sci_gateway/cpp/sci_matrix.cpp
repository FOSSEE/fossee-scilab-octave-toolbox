#include <string>
#include "wchar.h"
#include <cstdlib>
//#include <ctype.h>
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



static const char fname[] = "octave_fun";
///////#####call octave_fun([2],"hamming") ########////////////
int sci_octave_fun(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
/*
	printf("%d\n", nin);
	int row = 0;
  int col = 0;
  int size = 0;
	size = scilab_getDim2d(env, in[0], &row, &col);
	printf("%d\n", row);
	printf("%d\n", col);
	int i=3;
*/
///////////////////First Input/////////////////////	
	double* n = NULL;
	int row = 0;
  int col = 0;
  int size = 0;
	size = scilab_getDim2d(env, in[0], &row, &col);
	scilab_getDoubleArray(env, in[0], &n);
	double ar[(int)n[0]];
	
//	if((int)n[0]!=NULL)
//	if(in[i]!=NULL)
//		printf("\nInput %d is not null\n",i);


////////////////Second Input/////////////////////
	wchar_t* in1 = 0;

	char str[20];

  scilab_getString(env, in[1], &in1);
	//printf("%S\n", in1);

	 wcstombs(str, in1, sizeof(str));
	//printf("%s\n", str);

////////////////Third Input/////////////////////
	wchar_t* in4 = 0;

	char str2[20];

  scilab_getString(env, in[2], &in4);
	//printf("%S\n", in1);

	 wcstombs(str2, in4, sizeof(str2));
	//printf("%s\n", str);



//if (nin != 0)
//    {
//        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 1);
//        return 1;
//    }

if (nout != 1)
    {
        Scierror(77, _("%s: Wrong number of output argument(s): %d expected.\n"), fname, 1);
        return 1;
    }

		double inp[col];

		for(int i=0; i<col; i++)
		{
			inp[i] = n[i];//.float_value();
		}

		fun(ar, inp, col, str, str2);
		out[0] = scilab_createDoubleMatrix2d(env, n[0], 1, 0);

		double* out1 = NULL;
   	scilab_getDoubleArray(env, out[0], &out1);

		for(int i=0; i<n[0]; i++)
		{
			out1[i] = ar[i];//.float_value();
		}


    return 0;
}
}
