// Tarea1ProgramacionParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;


#define N 1000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d);

int main()
{
	std::cout << "Sumando Arreglos en Paralelo!\n\n";
	// Creando un valor semilla para los numeros aleatorios
	srand((unsigned)time(NULL));

	float a[N], b[N], c[N];
	int i;

	for (i = 0; i < N; i++) {
		a[i] = (rand() % 1000) + 1;
		b[i] = (rand() % 1000) + 1;
	}
	int pedazos = chunk;

	// Definimos que la instruccion for se debe de ejecutar de manera paralela usando OpenMP.
	// El comando shared nos sirve para indicar que los arreglos y pedazos pertenecen a un area de memoria compartida
	// De esta manera permitimos que los hilos que se crean puedan accesar a los valores. Tambien indicamos el tamaño de 
	// del arreglo que debe tomar cada hilo e indicar que la variable i es privada, evitando que se cambie el valor en 
	// los diferentes hilos creados. La ultima linea de este segmento nos indica que la planificacion se realiza de manera
	// estatica, indicando tambien el tamaño que debe tomar cada hilo en la planificacion.
#pragma omp parallel for \
	shared(a,b,c,pedazos) private(i)\
	schedule(static, pedazos)

	// Finalmente ejecutamos nuestra suma de arreglos de una manera comun.
	for (i = 0; i < N; i++)
		c[i] = a[i] + b[i];

	std::cout << "Primeros " << mostrar << " valores del arreglo a: |";
	imprimeArreglo(a);
	std::cout << "Primeros " << mostrar << " valores del arreglo b: |";
	imprimeArreglo(b);
	std::cout << "Primeros " << mostrar << " valores del arreglo c: |";
	imprimeArreglo(c);
}

void imprimeArreglo(float* d) {
	for (int x = 0; x < mostrar; x++) {
		std::cout << d[x] << "|-|";
	}
	std::cout << std::endl;
}