#pragma once

#ifndef LOG
#define LOG(...) do{\
	fprintf(stderr,"[ LOG ] ");\
	fprintf(stderr,__VA_ARGS__);\
	fprintf(stderr,"\n");\
	}while(0)
#endif

#ifndef WARNING
#define WARNING(...) do{\
	fprintf(stderr,"[ WRN ] ");\
	fprintf(stderr,__VA_ARGS__);\
	fprintf(stderr,"\n");\
	}while(0)
#endif


#ifndef ERROR
#define ERROR(...) do{\
	fprintf(stderr,"[ ERR ] %d - %s\n\t",__LINE__,__FILE__);\
	fprintf(stderr,__VA_ARGS__);\
	fprintf(stderr,"\n");\
	}while(0)
#endif

#ifndef CRIT_ERROR
#define CRIT_ERROR(...) do{\
	fprintf(stderr,"[ ERR ] %d - %s\n\t",__LINE__,__FILE__);\
	fprintf(stderr,__VA_ARGS__);\
	fprintf(stderr,"\n");\
	exit(0);\
	}while(0)
#endif
