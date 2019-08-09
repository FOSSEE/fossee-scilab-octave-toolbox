#include <wchar.h>
#include "libscilab_toolbox.hxx"
extern "C"
{
#include "libscilab_toolbox.h"
#include "addfunction.h"
}

#define MODULE_NAME L"libscilab_toolbox"

int libscilab_toolbox(wchar_t* _pwstFuncName)
{
    if(wcscmp(_pwstFuncName, L"octave_fun") == 0){ addCFunction(L"octave_fun", &sci_octave_fun, MODULE_NAME); }

    return 1;
}
