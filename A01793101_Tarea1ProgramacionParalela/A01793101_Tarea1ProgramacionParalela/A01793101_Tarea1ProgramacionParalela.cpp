// Tarea1ProgramacionParalela.cpp

// En la primera sección de código se importan las librerías necesarias para el funcionamiento del programa.
// Entre ellas la librería “omp.h” la cual permite a mi programa utilizar las funciones de OpenMP para el procesamiento paralelo.
// Así mismo importe la librería cstdlib la cual me es útil para generar los valores aleatorios que explicare mas adelante.

#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;

// En la siguiente sección defino 3 variables globales, N nos indica el numero de elementos dentro de los arreglos, 
// chunk indica el numero de pedazos que cada hilo va a tomar de los arreglos para su procesamiento y 
// finalmente mostrar la cual nos ayuda en nuestra función para imprimir la cantidad indicada de números contenidos en los arreglos.
// También en esta sección se incluye la definición de la función imprimeArreglo(), 
// la cual mediante el uso de un apuntador nos da la dirección de memoria de el arreglo que deseemos mostrar en la implementación de dicha función.

#define N 1000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d);

// En la tercera sección nos encontramos con la definición de nuestro método principal, 
// un valor semilla de aleatoriedad con la función srand, nuestros arreglos inicializados con tamaño N 
// y posteriormente el llenado con valores aleatorios generados con la función rand() que utiliza la semilla previamente mencionada. 
// Dentro del for de llenado de los arreglos observamos que se generan números dentro del rango 1 a 1000, 
// esto puede cambiarse según sea necesario, pero para este ejemplo nos es útil.
// Al final asignamos una variable llamada pedazos con la cantidad de recursos a consumir por cada hilo de ejecución.

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

	// A continuación, definimos que la instrucción for se debe de ejecutar de manera paralela usando la instrucción #pragma de OpenMP.
	// El comando shared nos sirve para indicar que los arreglos y pedazos pertenecen a un área de memoria compartida 
	// de esta manera permitimos que los hilos que se crean puedan acceder a los valores.también indicamos el tamaño del arreglo 
	// que debe tomar cada hilo e indicar que la variable i es privada, evitando que se cambie el valor en los diferentes hilos creados.
	//	La última línea de este segmento nos indica que la planificación se realiza de manera estática, 
	// indicando también el tamaño que debe tomar cada hilo en la planificación.

	#pragma omp parallel for \
	shared(a,b,c,pedazos) private(i)\
	schedule(static, pedazos)

	// Una vez implementada la sección anterior, ahora podemos ejecutar nuestro for de manera tradicional, 
	// el compilador sabrá que debe de dividir el proceso entre el numero de hilos indicados 
	// y lo relizara mediante la librería OpenMP. 
	// Dentro del for, asignamos al arreglo de resultados C la suma correspondiente al índice indicado por i de los 2 arreglos aleatorios A y B generados. 
	for (i = 0; i < N; i++)
		c[i] = a[i] + b[i];
	// Finalmente, mediante el parámetro “mostrar” definido al inicio 
	// y la implementación de la función “imprimeArreglo” desplegamos en la consola los n primeros elementos de cada arreglo.
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