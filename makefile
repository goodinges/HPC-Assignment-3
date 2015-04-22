a: omp_solved6.c
	gcc -fopenmp omp_solved2.c -o omp_solved2
	gcc -fopenmp omp_solved3.c -o omp_solved3
	gcc -fopenmp omp_solved4.c -o omp_solved4
	gcc -fopenmp omp_solved5.c -o omp_solved5
	gcc -fopenmp omp_solved6.c -o omp_solved6
	gcc -fopenmp jacobi-omp.c -lrt -lm -o jacobi-omp
	gcc -fopenmp gs-omp.c -lrt -lm -o gs-omp
