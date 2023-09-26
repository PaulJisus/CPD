#include <iostream>
#include <chrono>
#include <random>

using namespace std;

void ejecutar(int);
int **reservarMatriz(int);
int *reservarVector(int);
void ingresarMatriz(int **, int);
void ingresarVector(int *, int, int);
void bucle(int **, int *, int *, int);
void liberarMatriz(int **, int);
void liberarVector(int *);

int main()
{
    for (int i{1000}; i <= 10000; i += 1000)
    {
        ejecutar(i);
    }
    return 0;
}

void ejecutar(int tam)
{
    const int MAX = tam;
    int **A{reservarMatriz(MAX)}, *x{reservarVector(MAX)}, *y{reservarVector(MAX)};
    ingresarMatriz(A, MAX);
    ingresarVector(x, MAX, MAX);
    ingresarVector(y, MAX, 0);
    auto inicio = std::chrono::high_resolution_clock::now();
    bucle(A, x, y, MAX);
    auto fin = std::chrono::high_resolution_clock::now();
    std::cout << "Para " << MAX << " elemetos:\nTiempo de ejecucion:\t" << std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count() << " microsegundos" << std::endl;
    liberarMatriz(A, MAX);
    liberarVector(x);
    liberarVector(y);
}

int **reservarMatriz(int tam)
{
    int **matriz = new int*[tam];
	for(int i{0}; i < tam; i++)
    {
		matriz[i] = new int[tam];
	}
	return matriz;
}

int *reservarVector(int tam)
{
    int *Vector = new int[tam];
	return Vector;
}

void ingresarMatriz(int **matriz, int tam)
{
    for(int i{0}; i < tam; i++)
    {
		for(int j{0}; j < tam; j++)
        {
			*(*(matriz + i)+ j) = std::rand() % tam;
		}
	}
}

void ingresarVector(int *Vector, int tam, int valor)
{
    for(int i{0}; i < tam; i++)
    {
		if(valor == 0)
            *(Vector + i) = 0;
        else
            *(Vector + i) = std::rand() % tam;
	}
}

void bucle(int **A, int *x, int *y, int MAX)
{
    for (int i{0}; i < MAX; i++)
        for (int j{0}; j < MAX; j++)
            y[i] += A[i][j]*x[j];
}

void liberarMatriz(int **matriz, int tam)
{
    for(int i{0}; i < tam; i++)
    {
		delete[] matriz[i];
	}
	delete[] matriz;
}

void liberarVector(int *Vector)
{
	delete[] Vector;
}
