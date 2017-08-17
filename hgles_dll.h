#if defined _WIN32 || defined __CYGWIN__
  #ifdef HGLES_BUILDING_DLL
	#ifdef __GNUC__
	  #define HGLES_DLL_PUBLIC __attribute__ ((dllexport))
	#else
	  #define HGLES_DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
	#endif
  #else
	#ifdef __GNUC__
	  #define HGLES_DLL_PUBLIC __attribute__ ((dllimport))
	#else
	  #define HGLES_DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
	#endif
  #endif
  #define HGLES_DLL_LOCAL
#else
  #if __GNUC__ >= 4
	#define HGLES_DLL_PUBLIC __attribute__ ((visibility ("default")))
	#define HGLES_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
	#define HGLES_DLL_PUBLIC
	#define HGLES_HGLES_DLL_LOCAL
  #endif
#endif
