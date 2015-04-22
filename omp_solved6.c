/******************************************************************************
* FILE: omp_bug6.c
* DESCRIPTION:
*   This program compiles and runs fine, but produces the wrong result.
*   Compare to omp_orphan.c.
* AUTHOR: Blaise Barney  6/05
* LAST REVISED: 06/30/05
******************************************************************************/
//The problem: The program didn't compile because there was a problem with the
//scope of sum. The reduction pragma was defined inside of a method and it was
//outside of the method which thread forking took place. This caused the
//compilation error which said that variable sum is private outside. I fixed
//it by moving the statements inside of the method to the main method and
//forked the theads there and reduced results to sum yet there.
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100

float a[VECLEN], b[VECLEN];

int main (int argc, char *argv[]) {
int i,tid;
float sum;

for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
sum = 0.0;

#pragma omp parallel shared(sum)
{
  tid = omp_get_thread_num();
#pragma omp for reduction(+:sum)
  for (i=0; i < VECLEN; i++)
  {
    sum = sum + (a[i]*b[i]);
  }
}
printf("Sum = %f\n",sum);

}

