#include <iostream>
#include <chrono>
#include <random>

using namespace std;

void ejecutar(int);
int **reservar(int);
void ingresar(int **, int);
int generar(int);
void multiplicar(int **, int **, int **, int);
void liberar(int **, int);
void mostrar(int **, int);

int main()
{
    for (int i{100}; i <= 1000; i+= 100)
    {
        ejecutar(i);
    }
}

void ejecutar(int tam)
{
	int **A{reservar(tam)}, **B{reservar(tam)}, **C{reservar(tam)};
	ingresar(A, tam);
	ingresar(B, tam);
	auto inicio = std::chrono::high_resolution_clock::now();
    multiplicar(A, B, C, tam);
    auto fin = std::chrono::high_resolution_clock::now();
    //mostrar(C, tam);
    std::cout << "Para " << tam << " elemetos:\nTiempo de ejecucion:\t" << std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count() << " microsegundos" << std::endl;
    liberar(A, tam);
    liberar(B, tam);
    liberar(C, tam);
}

int **reservar(int tam)
{
    int **matriz = new int*[tam];
	for(int i{0}; i < tam; i++)
    {
		matriz[i] = new int[tam];
	}
	return matriz;
}

void ingresar(int **matriz, int tam)
{
    for(int i{0}; i < tam; i++)
    {
		for(int j{0}; j < tam; j++)
        {
			*(*(matriz + i)+ j) = generar(tam);
		}
	}
}

int generar(int tam)
{
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
    (std::mt19937::result_type)
    std::chrono::duration_cast<std::chrono::seconds>(
    std::chrono::system_clock::now().time_since_epoch()
    ).count() + (std::mt19937::result_type)
    std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distrib(-tam, tam);

    return distrib(gen);
}

void multiplicar(int **A, int **B, int **C, int tam)
{
	for(int i = 0; i < tam; i++)
    {
		for(int j = 0; j < tam; j++)
		{
			*(*(C + i)+ j) = 0;
			for(int k = 0; k < tam; k++)
			{
				*(*(C + i)+ j) += (*(*(A + i)+ k)) * (*(*(B + k)+ j));
            }
		}
	}
}

void liberar(int **matriz, int tam)
{
    for(int i{0}; i < tam; i++)
    {
		delete[] matriz[i];
	}
	delete[] matriz;
}

void mostrar(int **matriz, int tam)
{
	for(int i{0}; i < tam; i++)
    {
		for(int j{0}; j < tam; j++)
		{
			cout << *(*(matriz + i)+ j) << " ";
		}
		cout << endl;
	}
}

