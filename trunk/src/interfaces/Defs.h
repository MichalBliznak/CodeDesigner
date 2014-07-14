#ifndef _DEFS_H
#define _DEFS_H

#ifdef USING_SOURCE_CD
	#define WXDLLIMPEXP_CD
    #define WXDLLIMPEXP_DATA_CD(type) type
#elif defined( LIB_USINGDLL )
    #define WXDLLIMPEXP_CD
    #define WXDLLIMPEXP_DATA_CD(type)
#elif defined( WXMAKINGDLL_CD )
    #define WXDLLIMPEXP_CD WXEXPORT
    #define WXDLLIMPEXP_DATA_CD(type) WXEXPORT type
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_CD WXIMPORT
    #define WXDLLIMPEXP_DATA_CD(type) WXIMPORT type
#else // not making nor using DLL
    #define WXDLLIMPEXP_CD
    #define WXDLLIMPEXP_DATA_CD(type) type
#endif

#endif//_DEFS_H
