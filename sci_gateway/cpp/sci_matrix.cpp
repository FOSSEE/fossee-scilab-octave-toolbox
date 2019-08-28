#include <string>
#include <ctype.h>
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


//#include<iostream>

static const char fname[] = "octave_fun";
///////#####call octave_fun([2],"hamming") ########////////////
int sci_octave_fun(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
	double* out1 = NULL;
	wchar_t** out11 = NULL;
	double* n;//=*in;
    	wchar_t** in1 = NULL;
	wchar_t* in2 = 0;
    	int inr1 = 0;
	int inc1 = 0;
	int size1 = 0;
	wchar_t temp[128];
	int dim1 = 3;
    	int dims1[] = {0, 0, 2};
	scilab_getDoubleArray(env, in[0], &n);
	//scilab_getStringArray(env, in[0], &in1);
	//scilab_getString(env, in[1], &in2);
    	//dims1[0] = inr1;
    	//dims1[1] = inc1;
	//size1 = scilab_getDim2d(env, in[1], &inr1, &inc1);
	//for (int i = 0; i < 3; ++i)
    	//{
        //wcscpy(temp, in1[i]);
        //wcscat(temp, L".one");
        //out1[i] = os_wcsdup(temp);
	//}
	//scilab_getInteger32(env, in[0], &n);
	//std::cout << n << '\n';
	//wchar_t* dummy = L"hello";
	//printf("%S\n",in1);
	
	double ar[(int)n[0]];
	//printf("%d\n",inr1);
  
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
		//std::wstring ws(in1);
		//string str(ws.begin(), ws.end());
		//printf("%s\n",str);
		fun(ar, n[0],"hamming");
		*out = scilab_createDoubleMatrix2d(env, n[0], 1, 0);
    //double retval = fun();
		//printf("%f\n", retval); 
		//*out1 = retval;
   	scilab_getDoubleArray(env, out[0], &out1);
		//out1[0]=fun();

		for(int i=0; i<n[0]; i++)
		{
			out1[i] = ar[i];//.float_value();
		}


    return 0;
}
}
