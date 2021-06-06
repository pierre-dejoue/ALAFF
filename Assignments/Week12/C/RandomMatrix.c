#define _XOPEN_SOURCE
#include <stdlib.h>

#ifdef _MSC_VER
  // Windows
  #include <Windows.h>
#endif

#define A( i,j ) *( ap + (j)*lda + (i) )          // map A( i,j )    to array ap    in column-major order

double double_rand()
{
#ifdef _MSC_VER
    unsigned int random_val;
    rand_s(&random_val);
    return (double) random_val / (double) UINT_MAX;
#else
    return drand48();
#endif
}

void RandomMatrix( int m, int n, double *ap, int lda )
/*
   RandomMatrix overwrite A with random values.
*/
{
  int  i, j;

  for ( i=0; i<m; i++ )
    for ( j=0; j<n; j++ )
      A( i,j ) = double_rand();
}
