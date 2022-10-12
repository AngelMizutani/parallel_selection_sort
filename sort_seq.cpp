#include <cstdio>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>

void selection_sort(int vetor[], int tam) {
    for (int indice = 0; indice < tam; ++indice) {
        int indiceMenor = indice;
        for (int indiceSeguinte = indice+1; indiceSeguinte < tam; ++indiceSeguinte) {
            if (vetor[indiceSeguinte] < vetor[indiceMenor]) {
                indiceMenor = indiceSeguinte;
            }
        }
        int aux = vetor[indice];
        vetor[indice] = vetor[indiceMenor];
        vetor[indiceMenor] = aux;
    }
    
    for (int i = 0; i < tam; ++i) {
    	printf("%i ", vetor[i]);
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
