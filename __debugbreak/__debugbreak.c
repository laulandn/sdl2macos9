#include <stdio.h>#include <stdlib.h>/* Not sure when this would get called, so we just exit... */void __debugbreak(){  printf("__debugbreak called!\n");  exit(EXIT_FAILURE);}