#include <wchar.h>
#include "libscilab_octave.hxx"
extern "C"
{
#include "libscilab_octave.h"
#include "addfunction.h"
}

#define MODULE_NAME L"libscilab_octave"

int libscilab_octave(wchar_t* _pwstFuncName)
{
    if(wcscmp(_pwstFuncName, L"octave_fun") == 0){ addCFunction(L"octave_fun", &sci_octave_fun, MODULE_NAME); }

    return 1;
}
