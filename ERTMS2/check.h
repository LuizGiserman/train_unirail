#ifndef CHECK_H__
#define CHECK_H__

#define EXIT_FAIL	-1

#define CHECK_NOT(stat, val, msg)   \
	if ( (stat) == val )            \
	{                               \
		printf ("%s\n", msg);       \
		exit( EXIT_FAIL );       \
    } 
#define PTHREAD_CHECK(stat, msg)    \
	if ( (stat) != 0 )              \
	{                               \
		printf ("%s\n", msg);       \
		exit( EXIT_FAIL );       \
    } 

#define CHECK_EQUALS(stat, val, msg) \
	if ( (stat) != val )            \
	{                               \
		printf ("%s\n", msg);       \
		exit( EXIT_FAIL );       \
    } 


#define CHECK_NOT_LT(stat, val, msg) \
    if ( (stat) < val )              \
    {                               \
        printf ("%s\n", msg);       \
        exit( EXIT_FAIL );       \
    } 
	
typedef enum {
    FALSE,
    TRUE
} bool;


#endif
