
extern "C"
{
#include<Scierror.h>
#include<sciprint.h>
#include<api_scilab.h>
#include "localization.h"
#include "fun.h"
#include <cstdio>
#include <math.h>

static const char fname[] = "octave_fun";

int sci_octave_fun(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
	double* out1 = NULL;
	int n=5;
	double ar[n];
  
if (nin != 0)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 2);
        return 1;
    }

if (nout != 1)
    {
        Scierror(77, _("%s: Wrong number of output argument(s): %d expected.\n"), fname, 1);
        return 1;
    }

		fun(ar, n);
		*out = scilab_createDoubleMatrix2d(env, n, 1, 0);
    //double retval = fun();
		//printf("%f\n", retval); 
		//*out1 = retval;
   	scilab_getDoubleArray(env, out[0], &out1);
		//out1[0]=fun();

		for(int i=0; i<n; i++)
		{
			out1[i] = ar[i];//.float_value();
		}


    return 0;
}
}
