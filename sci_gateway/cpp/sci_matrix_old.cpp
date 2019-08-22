extern "C"
{
#include<Scierror.h>
#include<api_scilab.h>
#include "localization.h"
#include<fun.h>

static const char fname[] = "octave_fun";

int sci_octave_fun(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
   	int i = 0;
    int row1 = 0;
    int col1 = 0;
    int size1 = 0;
    double* in1 = NULL;
    double* out1 = NULL;

    int row2 = 0;
    int col2 = 0;
    int size2 = 0;
    double* in2 = NULL;
    double* out2 = NULL;


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

		out1 = fun();
		size1 = sizeof(out1)/sizeof(out1[0]);

		//Creating scilab matrix and saving in pointers out[0] and out[1]
    out[0] = scilab_createDoubleMatrix2d(env, size1, 1, 0);

		//saving the output in out1 and out2
    scilab_getDoubleArray(env, out[0], &out1);
		
		

    return 0;
}
}
