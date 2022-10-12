#include <cstdio>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>

void selection_sort (int *vetor, int tam)
{
	int min, nt, tid;
	
	
	#pragma omp parallel 
	{
		#pragma omp master 
		nt = omp_get_num_threads();
	}
	
	struct {
		int valor;
		int min;
		char lixo[60];
	} v[nt];
	
	for (int indice = 0; indice < tam; ++indice) {
		min = indice;
		#pragma omp parallel
		{
			int indiceMenor = indice;
			tid = omp_get_thread_num();
			v[tid].valor = 0;
			v[tid].min = 0;			

			#pragma omp for			
			for (int indiceSeguinte = indice+1; indiceSeguinte < tam; ++indiceSeguinte) {
				if (vetor[indiceSeguinte] < vetor[indiceMenor]) {
					indiceMenor = indiceSeguinte;
				}	
			}			
	
			#pragma omp critical
			if (vetor[indiceMenor] < vetor[min]) {
					min = indiceMenor;
			}			
		}
		
		int aux = vetor[indice];
		vetor[indice] = vetor[min];
		vetor[min] = aux;	
	}

	
	for (int ind = 0; ind < tam; ind++) {
		printf("%i ", vetor[ind]);
	}
	
	
}

int main (int argc, char **argv)
{

	int vetor[12] = {5, 7, 3, 4, 9, 0, 1, 2, 10, 8, 11, 6};

	std::chrono::steady_clock::time_point tbegin, tend;
	double elapsed;

	tbegin = std::chrono::steady_clock::now();

	selection_sort(vetor, 12);

	tend = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_ = std::chrono::duration_cast<std::chrono::duration<double>>(tend - tbegin);
	elapsed = elapsed_.count();

	printf("\ntime: %f\n", elapsed);

	return 0;
}
