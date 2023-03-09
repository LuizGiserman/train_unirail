#ifndef CHECK_H
#define CHECK_H

#define CHECK_NOT(stat, val, msg)   \
	if ( (stat) == val )            \
	{                               \
		printf ("%s\n", msg);       \
		exit( EXIT_FAILURE );       \
    } 
#define PTHREAD_CHECK(stat, msg)    \
	if ( (stat) != 0 )              \
	{                               \
		printf ("%s\n", msg);       \
		exit( EXIT_FAILURE );       \
    } 

#define CHECK_EQUALS(stat, val, msg) \
	if ( (stat) != val )            \
	{                               \
		printf ("%s\n", msg);       \
		exit( EXIT_FAILURE );       \
    } 


#define CHECK_NOT_LT(stat, val, msg) \
    if ( (stat) < val )              \
    {                               \
        printf ("%s\n", msg);       \
        exit( EXIT_FAILURE );       \
    } 


#endif
