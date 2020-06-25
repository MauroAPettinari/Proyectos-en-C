#include <stdio.h>
#include <stdlib.h>

// struct para la arista, con grafo origen, destino y peso
struct Aristas
{
	int origen;
	int destino;
	int peso;
};

// struct para representar el grafo, representado como un array de aristas
struct Grafo
{
	int V;
	int E;

	struct Aristas* arista;
};

// crea un grafo con V vertices y E aristas
struct Grafo* crearGrafo(int V, int E)
{
	struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo));

	grafo->V = V;
	grafo->E = E;
	grafo->arista = (struct Aristas*)malloc(grafo->E * sizeof(struct Aristas));

	return grafo;
}

// struct de vertices para buscar ciclos en el grafo
struct subconjunto
{
	int padre;
	int grado;
};

// busca en el conjunto de vertices el elemento que le damos (buscar ciclos)
int buscarConjunto(struct subconjunto subconjuntos[], int i)
{
	if (subconjuntos[i].padre != i)
		subconjuntos[i].padre = buscarConjunto(subconjuntos, subconjuntos[i].padre);

	return subconjuntos[i].padre;
}

// une dos conjuntos para formar uno, formando raices (buscar ciclos)
void buscarUniones(struct subconjunto subconjuntos[], int x, int y)
{
	int raiz1 = buscarConjunto(subconjuntos, x);
	int raiz2 = buscarConjunto(subconjuntos, y);

	if (subconjuntos[raiz1].grado < subconjuntos[raiz2].grado)
		subconjuntos[raiz1].padre = raiz2;
	else if (subconjuntos[raiz1].grado > subconjuntos[raiz2].grado)
		subconjuntos[raiz2].padre = raiz1;
	else
	{
		subconjuntos[raiz2].padre = raiz1;
		subconjuntos[raiz1].grado++;
	}
}

// comparamos aristas segun su peso
int compararAristas(const void* a, const void* b)
{
	struct Aristas* ari1 = (struct Aristas*)a;
	struct Aristas* ari2 = (struct Aristas*)b;

	return ari1->peso > ari2->peso;
}

void funcionKruskal(struct Grafo* grafo)
{
	int V = grafo->V;
	struct Aristas resultado[V]; // guardamos el resultado
	int j = 0; // usamos un indice para el resultado
	int i = 0; // usamos un indice para ordenar aristas
	int costo = 0; // usamos para guardar el costo total del arbol generado

	//ordenamos las aristas segun su peso usado en compararAristas
	qsort(grafo->arista, grafo->E, sizeof(grafo->arista[0]), compararAristas);

	// guardamos memoria para crear el conjunto de vertices
	struct subconjunto *subconjuntos = (struct subconjunto*)malloc(V * sizeof(struct subconjunto));

	// creamos V conjuntos con elementos del indice
	for (int v = 0; v < V; ++v)
	{
		subconjuntos[v].padre = v;
		subconjuntos[v].grado = 0;
	}

	while (j < V - 1 && i < grafo->E)
	{
		// elegimos la arista de menor peso y aumentamos en 1 la posicion (siguiente)
		struct Aristas arista_siguiente = grafo->arista[i++];

		int vorigen = buscarConjunto(subconjuntos, arista_siguiente.origen);
		int vdestino = buscarConjunto(subconjuntos, arista_siguiente.destino);

		// si unir estos vertices no forma un ciclo, guardamos y aumentamos la posicion de aristas
		if (vorigen != vdestino)
		{
			resultado[j++] = arista_siguiente;
			buscarUniones(subconjuntos, vorigen, vdestino);
		}
	}

	printf("\n\nConstruyendo aristas del arbol generado usando Algoritmo de Kruskal...\n\n");

	for (i = 0; i < j; ++i){
		printf("\tVertice '%d' a vertice '%d', costo de la arista: %d\n", resultado[i].origen, resultado[i].destino, resultado[i].peso);
		costo = costo + resultado[i].peso;
	}

	printf("\nCosto total del arbol generado = %d\n", costo);

	return;
}


int main()
{
	int V, E, i, nodoorigen, nododestino, nodopeso;

	printf("\tAlgoritmo de Kruskal\n\n");

	printf("Cuantos vertices tiene el grafo? \n");
	scanf(" %d", &V);

	printf("Cuantas aristas tiene el grafo? \n");
	scanf(" %d", &E);

	struct Grafo* grafo = crearGrafo(V, E);

	for(i = 0; i < E; i++){
		printf("\n\tArista %d\n", i+1);

		printf("Ingrese el nodo origen: \n");
		scanf(" %d", &nodoorigen);

		printf("Ingrese el nodo destino del nodo %d: \n", nodoorigen);
		scanf(" %d", &nododestino);

		printf("Ingrese el peso de la arista del nodo %d al nodo %d: \n", nodoorigen, nododestino);
		scanf(" %d", &nodopeso);

		grafo->arista[i].origen = nodoorigen;
		grafo->arista[i].destino = nododestino;
		grafo->arista[i].peso = nodopeso;
	}

	/*for(i = 0; i < E; i++){
		printf("DEBUG---> Nodo origen: %d - Nodo destino: %d - Arista: %d\n", grafo->arista[i].origen, grafo->arista[i].destino, grafo->arista[i].peso);
	}*/

	funcionKruskal(grafo);

	return 0;
}
