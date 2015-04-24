#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getResidual(double* u, double* residuals, long N, double d1, double d2)
{
  long i = 0;
  double residual = 0;

#pragma omp parallel for reduction(+:residual)
  for(i=1;i<=N;i++){
    residuals[i-1] = d2*(u[i-1]  + u[i+1]) + d1*u[i] - 1;
    residual += residuals[i-1]*residuals[i-1];
  }

  residual = sqrt(residual);

  return residual;
}

int main ( long argc, char *argv[] )
{
  long N = atoi(argv[1]);

  double h = 1;
  h = h/(N+1);
  double h2 = h*h;
  double d1 = 2/h2;
  double d2 = -1/h2;

  double* pre_u;
  double* u;
  double* residuals;

  long i;

  double residual;

  pre_u = (double*) calloc (N+2,sizeof(double));
  u = (double*) calloc (N+2,sizeof(double));
  residuals = (double*) calloc (N,sizeof(double));

  residual = getResidual(pre_u,residuals,N,d1,d2);
  double threshold = residual;
  threshold /= 1000000;

  //Jacobi
  long k;
  int j;
  for(k=0;;k++){
    for(j=0;j<2;j++){
#pragma omp parallel for
      for(i=1+j;i<=N;i += 2){
        u[i] = (1 - d2*(u[i-1] + pre_u[i+1]))/d1;
      }
    }
     // for(i=2;i<=N;i += 2){
      //  u[i] = (1 - d2*(u[i-1] + pre_u[i+1]))/d1;
     // }

#pragma omp parallel for
    for(i=1;i<=N;i++){
      pre_u[i] = u[i];
    }

    residual = getResidual(u,residuals,N,d1,d2);
	//	printf("%li %12.10f\n",k,residual);

    if(residual<=threshold){
      printf("%ld iterations\n",k+1);
      break;
    }
  }

  free(u);
  free(pre_u);
  free(residuals);
}
