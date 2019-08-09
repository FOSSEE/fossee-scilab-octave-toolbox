#ifndef __LIBSCILAB_TOOLBOX_GW_HXX__
#define __LIBSCILAB_TOOLBOX_GW_HXX__

#ifdef _MSC_VER
#ifdef LIBSCILAB_TOOLBOX_GW_EXPORTS
#define LIBSCILAB_TOOLBOX_GW_IMPEXP __declspec(dllexport)
#else
#define LIBSCILAB_TOOLBOX_GW_IMPEXP __declspec(dllimport)
#endif
#else
#define LIBSCILAB_TOOLBOX_GW_IMPEXP
#endif

extern "C" LIBSCILAB_TOOLBOX_GW_IMPEXP int libscilab_toolbox(wchar_t* _pwstFuncName);



#endif /* __LIBSCILAB_TOOLBOX_GW_HXX__ */
