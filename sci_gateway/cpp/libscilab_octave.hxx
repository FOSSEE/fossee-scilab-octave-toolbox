#ifndef __LIBSCILAB_OCTAVE_GW_HXX__
#define __LIBSCILAB_OCTAVE_GW_HXX__

#ifdef _MSC_VER
#ifdef LIBSCILAB_OCTAVE_GW_EXPORTS
#define LIBSCILAB_OCTAVE_GW_IMPEXP __declspec(dllexport)
#else
#define LIBSCILAB_OCTAVE_GW_IMPEXP __declspec(dllimport)
#endif
#else
#define LIBSCILAB_OCTAVE_GW_IMPEXP
#endif

extern "C" LIBSCILAB_OCTAVE_GW_IMPEXP int libscilab_octave(wchar_t* _pwstFuncName);



#endif /* __LIBSCILAB_OCTAVE_GW_HXX__ */
