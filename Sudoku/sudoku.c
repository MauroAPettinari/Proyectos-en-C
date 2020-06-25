#include <stdio.h>
#include <stdlib.h>

#define AYUDAS_EASY 3
#define AYUDAS_MEDIUM 4
#define AYUDAS_HARD 5

#define TABLERO_EASY 1
#define TABLERO_MEDIUM 2
#define TABLERO_HARD 3

#define MAX_JUEGOS 10
#define MAX_CASILLAS 81

#define LIMPIAR_CONSOLA

int tableroSudokuEasy[9][9] = {
	{3, 0, 0, 	9, 0, 0, 	0, 0, 0},
	{0, 0, 4, 	7, 0, 0, 	8, 0, 0},
	{0, 0, 0, 	8, 0, 5, 	0, 0, 2},

	{0, 8, 0,	6, 0, 0, 	0, 0, 4},
	{0, 5, 0, 	0, 0, 4, 	0, 3, 0},
	{1, 0, 0, 	2, 0, 3, 	0, 7, 9},

	{0, 6, 0, 	0, 0, 7, 	0, 0, 0},
	{2, 0, 7, 	0, 0, 0, 	3, 0, 0},
	{4, 0, 9, 	0, 2, 0, 	0, 0, 0}
};

int solucionSudokuEasy[9][9] = {
	{3, 2, 8, 	9, 4, 6, 	1, 5, 7},
	{5, 9, 4, 	7, 1, 2, 	8, 6, 3},
	{6, 7, 1, 	8, 3, 5, 	9, 4, 2},

	{7, 8, 3,	6, 5, 9, 	2, 1, 4},
	{9, 5, 2, 	1, 7, 4, 	6, 3, 8},
	{1, 4, 6, 	2, 8, 3, 	5, 7, 9},

	{8, 6, 5, 	3, 9, 7, 	4, 2, 1},
	{2, 1, 7, 	4, 6, 8, 	3, 9, 5},
	{4, 3, 9, 	5, 2, 1, 	7, 8, 6}
};

int tableroSudokuMedium[9][9] = {
	{0, 0, 0,	0, 0, 2, 	9, 1, 0},
	{0, 4, 0, 	0, 7, 1, 	0, 2, 0},
	{0, 0, 0, 	0, 0, 0, 	0, 6, 7},

	{0, 0, 0, 	0, 0, 3, 	0, 0, 4},
	{5, 0, 1, 	0, 0, 0, 	0, 0, 0},
	{0, 2, 0, 	6, 0, 0, 	0, 0, 5},

	{0, 0, 6, 	2, 8, 0, 	0, 5, 0},
	{7, 0, 0, 	0, 0, 4, 	0, 0, 0},
	{0, 0, 5, 	0, 0, 0, 	0, 0, 0}
};

int solucionSudokuMedium[9][9] = {
	{8, 5, 7,	4, 6, 2, 	9, 1, 3},
	{6, 4, 9, 	3, 7, 1, 	5, 2, 8},
	{2, 1, 3, 	8, 9, 5, 	4, 6, 7},

	{9, 6, 8, 	5, 2, 3, 	1, 7, 4},
	{5, 7, 1, 	9, 4, 8, 	6, 3, 2},
	{3, 2, 4, 	6, 1, 7, 	8, 9, 5},

	{4, 3, 6, 	2, 8, 9, 	7, 5, 1},
	{7, 9, 2, 	1, 5, 4, 	3, 8, 6},
	{1, 8, 5, 	7, 3, 6, 	2, 4, 9}
};

int tableroSudokuHard[9][9] = {
	{4, 3, 6, 	1, 2, 9, 	8, 7, 5},
	{5, 9, 8, 	4, 7, 6, 	2, 3, 1},
	{7, 2, 1, 	5, 3, 8, 	0, 0, 0},

	{9, 1, 2, 	6, 5, 3, 	7, 8, 4},
	{3, 5, 4, 	8, 1, 7, 	9, 6, 2},
	{8, 6, 7, 	2, 9, 4, 	5, 1, 3},

	{1, 8, 5,	7, 6, 2, 	3, 4, 9},
	{6, 4, 9, 	3, 8, 5, 	1, 2, 7},
	{2, 7, 3, 	9, 4, 1, 	6, 5, 8}
};

int solucionSudokuHard[9][9] = {
	{4, 3, 6, 	1, 2, 9, 	8, 7, 5},
	{5, 9, 8, 	4, 7, 6, 	2, 3, 1},
	{7, 2, 1, 	5, 3, 8, 	4, 9, 6},

	{9, 1, 2, 	6, 5, 3, 	7, 8, 4},
	{3, 5, 4, 	8, 1, 7, 	9, 6, 2},
	{8, 6, 7, 	2, 9, 4, 	5, 1, 3},

	{1, 8, 5,	7, 6, 2, 	3, 4, 9},
	{6, 4, 9, 	3, 8, 5, 	1, 2, 7},
	{2, 7, 3, 	9, 4, 1, 	6, 5, 8}
};

int tableroSudoku[9][9]; // TABLERO GENERAL DEL SUDOKU
int solucionSudoku[9][9]; // SOLUCION TABLERO GENERAL DEL SUDOKU
int casillaModificable[9][9]; // VALOR DE LA COORDENADA MODIFICABLE. 0 = ES MODIFICABLE - SI > 0 = NO PUEDE MODIFICARSE
int filaRepetida(int coordenadaFilas, int numero); // VALOR REPETIDO EN FILA. DEVUELVE 0 = NO SE REPITE - 1 = SE REPITE
int columnaRepetida(int coordenadaColumna, int numero); // VALOR REPETIDO EN COLUMNA. DEVUELVE 0 = NO SE REPITE - 1 = SE REPITE
int cuadradoRepetido(int coordenadaFilas, int coordenadaColumnas, int numero); // VALOR REPETIDO EN FILA, COLUMNA O CUADRADO 3X3. DEVUELVE 0 = NO SE REPITE - 1 = SE REPITE
int idTablero = 0; // VARIABLE PARA SABER DIFICULTAD DEL TABLERO
int tableroCompleto = 0; // VARIABLE PARA SABER SI COMPLETO EL SUDOKU
int ayudasTablero = 0; // VARIABLE PARA SABER LA CANTIDAD MAXIMA DE AYUDAS DISPONIBLES
int ayudasUsadas = 0; // VARIABLE PARA SABER LA CANTIDAD DE AYUDAS USADAS
int juegosJugados = 0; // VARIABLE PARA SABER LA CANTIDAD DE JUEGOS EN LA SESION

void menuJuego();
void mostrarSudoku();
void jugarSudoku();
void restringirCasillas();
void guardarSudoku();
void reiniciarSudoku();
void checkSudoku();
void ayudaSudoku();

int main()
{
	menuJuego();

	return 0;
}

void menuJuego()
{
	int opcMenu, opcDificultad;

	printf ("\n\t\tMENU\n");
	printf ("\t\t----\n");
	printf ("1. Nuevo juego\n\n");
	printf ("0. Salir\n\n");

	printf ("Elige una opcion: ");
	scanf ("%d", &opcMenu);

	switch (opcMenu){
		case 1:{
#ifdef LIMPIAR_CONSOLA
#if __linux__
			system("clear");
#elif _WIN32
			system("cls");
#endif
#endif
			printf ("\n\t\tDIFICULTAD\n");
			printf ("\t\t-----------\n");
			printf ("1. Facil\n\n");
			printf ("2. Medio\n\n");
			printf ("3. Dificil\n\n");
			printf ("0. Salir\n\n");

			printf ("Elige la dificultad: ");
			scanf ("%d", &opcDificultad);

			switch(opcDificultad){
				case 1:{
#ifdef LIMPIAR_CONSOLA
#if __linux__
					system("clear");
#elif _WIN32
					system("cls");
#endif
#endif
					idTablero = TABLERO_EASY;
					ayudasTablero = AYUDAS_EASY;
					ayudasUsadas = 0;
					juegosJugados++;

					guardarSudoku();
					restringirCasillas();
					mostrarSudoku();

					break;
				}
				case 2:{
#ifdef LIMPIAR_CONSOLA
#if __linux__
					system("clear");
#elif _WIN32
					system("cls");
#endif
#endif
					idTablero = TABLERO_MEDIUM;
					ayudasTablero = AYUDAS_MEDIUM;
					ayudasUsadas = 0;
					juegosJugados++;

					guardarSudoku();
					restringirCasillas();
					mostrarSudoku();

					break;
				}
				case 3:{
#ifdef LIMPIAR_CONSOLA
#if __linux__
					system("clear");
#elif _WIN32
					system("cls");
#endif
#endif
					idTablero = TABLERO_HARD;
					ayudasTablero = AYUDAS_HARD;
					ayudasUsadas = 0;
					juegosJugados++;

					guardarSudoku();
					restringirCasillas();
					mostrarSudoku();

					break;
				};
				default:
				{
#ifdef LIMPIAR_CONSOLA
#if __linux__
					system("clear");
#elif _WIN32
					system("cls");
#endif
#endif
					printf("\nOpcion incorrecta!\n");
					menuJuego();
				}
			}
		}
		case 0:{
			break;
		}
		default:
		{
#ifdef LIMPIAR_CONSOLA
#if __linux__
            system("clear");
#elif _WIN32
            system("cls");
#endif
#endif
			printf("\nOpcion incorrecta!\n");
			menuJuego();
		}
	}
}

void mostrarSudoku()
{
	int i, j;

	printf("\n\t    0 1 2   3 4 5   6 7 8\n");
	printf("\t  +-------+-------+-------+\n");

	for(i = 0; i < 9; i++){
		printf("\t%d ", i);

		for(j = 0; j < 9; j++){
			if(j == 0)
				printf("| ");

            printf("%d ", tableroSudoku[i][j]);

			if((j+1) % 3 == 0)
				printf("| ");
		}

		if((i+1) % 3 == 0)
			printf("\n\t  +-------+-------+-------+");

		printf("\n");
	}

	if(tableroCompleto != 1)
		jugarSudoku();

	return;
}

void jugarSudoku()
{
	int numero, coordFil, coordCol;
	char opAyuda;

	if(ayudasUsadas < ayudasTablero){
		printf("Necesitas ayuda (S/N)? (%i/%i): ", ayudasUsadas, ayudasTablero );
		scanf(" %c", &opAyuda);
	}

	if(opAyuda == 's' || opAyuda == 'S'){
#ifdef LIMPIAR_CONSOLA
#if __linux__
        system("clear");
#elif _WIN32
        system("cls");
#endif
#endif
		ayudaSudoku();
		checkSudoku();

		return;
	}

	printf("Escribe la coordenada para la fila: ");
	scanf("%d", &coordFil);

	if((coordFil < 0 || coordFil > 8)){
#ifdef LIMPIAR_CONSOLA
#if __linux__
        system("clear");
#elif _WIN32
        system("cls");
#endif
#endif
		printf("El numero que ingresaste no esta entre 0 y 8...\n\n");
		mostrarSudoku();
	}

	printf("Escribe la coordenada para la columna: ");
	scanf("%d", &coordCol);

	if((coordCol < 0 || coordCol > 8)){
#ifdef LIMPIAR_CONSOLA
#if __linux__
        system("clear");
#elif _WIN32
        system("cls");
#endif
#endif
		printf("El numero que ingresaste no esta entre 0 y 8...\n\n");
		mostrarSudoku();
	}

	if (casillaModificable[coordFil][coordCol]){
		printf("Escribe un numero: ");
		scanf("%d", &numero);
#ifdef LIMPIAR_CONSOLA
#if __linux__
        system("clear");
#elif _WIN32
        system("cls");
#endif
#endif
        if (numero < 0 || numero > 9){
#ifdef LIMPIAR_CONSOLA
#if __linux__
            system("clear");
#elif _WIN32
            system("cls");
#endif
#endif
            printf("El numero que ingresaste no esta entre 1 y 9...\n\n");
            mostrarSudoku();
            return;
        }
        else if(numero != 0 && filaRepetida(coordFil, numero)){
#ifdef LIMPIAR_CONSOLA
#if __linux__
            system("clear");
#elif _WIN32
            system("cls");
#endif
#endif
            printf("Cuidado! En esta fila ya se repite este numero...\n\n");
            mostrarSudoku();
            return;
        }
        else if(numero != 0 && columnaRepetida(coordCol, numero)){
#ifdef LIMPIAR_CONSOLA
#if __linux__
            system("clear");
#elif _WIN32
            system("cls");
#endif
#endif
            printf("Cuidado! En esta columna ya se repite este numero...\n\n");
            mostrarSudoku();
            return;
        }
        else if(numero != 0 && cuadradoRepetido(coordFil, coordCol, numero)){
#ifdef LIMPIAR_CONSOLA
#if __linux__
            system("clear");
#elif _WIN32
            system("cls");
#endif
#endif
            printf("Cuidado! En este cuadrado 3x3 ya se repite este numero...\n\n");
            mostrarSudoku();
            return;
        }

        tableroSudoku[coordFil][coordCol] = numero;
        checkSudoku();
	}
	else{
#ifdef LIMPIAR_CONSOLA
#if __linux__
        system("clear");
#elif _WIN32
        system("cls");
#endif
#endif
		printf ("La coordenada que elegiste esta ocupada por un numero que no se puede modificar\n\n");
		mostrarSudoku();
		return;
	}

	return;
}

int filaRepetida(int coordenadaFilas, int numero)
{
	int j;

	for(j = 0; j <= 8; j++){
		if(tableroSudoku[coordenadaFilas][j] == numero){
			return 1;
		}
	}

	return 0;
}

int columnaRepetida(int coordenadaColumnas, int numero)
{
	int j;

	for(j = 0; j <= 8; j++){
		if(tableroSudoku[j][coordenadaColumnas] == numero){
			return 1;
		}
	}

	return 0;
}

int cuadradoRepetido(int coordenadaFilas, int coordenadaColumnas, int numero)
{
	int i, j;
	int inicioFilas = (coordenadaFilas/3) * 3;
	int inicioColumnas = (coordenadaColumnas/3) * 3;

	for(i = inicioFilas; i <= inicioFilas+2; i++){
		for(j = inicioColumnas; j <=inicioColumnas+2; j++){
			if(tableroSudoku[i][j] == numero){
				return 1;
			}
		}
	}

	return 0;
}

void restringirCasillas()
{
	int filas = 0, columnas = 0;

	for(filas = 0; filas < 9; filas++){
		for(columnas = 0; columnas < 9; columnas++){
			if(tableroSudoku[filas][columnas] == 0){
				casillaModificable[filas][columnas] = 1;
			}
		}
	}
}

void guardarSudoku()
{
	switch(idTablero)
	{
		case TABLERO_EASY: {
			int filas = 0, columnas = 0;

			for(filas = 0; filas < 9; filas++){
				for(columnas = 0; columnas < 9; columnas++){
					tableroSudoku[filas][columnas] = tableroSudokuEasy[filas][columnas];
					solucionSudoku[filas][columnas] = solucionSudokuEasy[filas][columnas];
				}
			}

			break;
		}
		case TABLERO_MEDIUM: {
			int filas = 0, columnas = 0;

			for(filas = 0; filas < 9; filas++){
				for(columnas = 0; columnas < 9; columnas++){
					tableroSudoku[filas][columnas] = tableroSudokuMedium[filas][columnas];
					solucionSudoku[filas][columnas] = solucionSudokuMedium[filas][columnas];
				}
			}

			break;
		}
		case TABLERO_HARD: {
			int filas = 0, columnas = 0;

			for(filas = 0; filas < 9; filas++){
				for(columnas = 0; columnas < 9; columnas++){
					tableroSudoku[filas][columnas] = tableroSudokuHard[filas][columnas];
					solucionSudoku[filas][columnas] = solucionSudokuHard[filas][columnas];
				}
			}

			break;
		}
	}
}

void reiniciarSudoku()
{
	int filas = 0, columnas = 0;

	tableroCompleto = 0;

	for(filas = 0; filas < 9; filas++){
		for(columnas = 0; columnas < 9; columnas++){
			tableroSudoku[filas][columnas] = 0;
		}
	}
}

void checkSudoku()
{
	int valCorrectos = 0;

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(tableroSudoku[i][j] == solucionSudoku[i][j]){
				valCorrectos++;
			}
		}
	}

	if(valCorrectos == MAX_CASILLAS)
		tableroCompleto = 1;

	if(tableroCompleto > 0){
        mostrarSudoku();
		printf("\nFelicitaciones! Tablero sudoku completado!\n");

		if(juegosJugados < MAX_JUEGOS){
			char opcNuevo;

			printf("Queres jugar de nuevo (S/N)? (%i/%i): ", juegosJugados, MAX_JUEGOS);
			scanf(" %c", &opcNuevo);

			if(opcNuevo == 's' || opcNuevo == 'S'){
#ifdef LIMPIAR_CONSOLA
#if __linux__
                system("clear");
#elif _WIN32
                system("cls");
#endif
#endif
				reiniciarSudoku();
				menuJuego();
				return;
			}
		}
		else{
			printf("Ya jugaste todas las veces disponibles! (%i/%i)\n", juegosJugados, MAX_JUEGOS);
			return;
		}
	}
	else{
		mostrarSudoku();
		return;
	}
}

void ayudaSudoku()
{
	int x = 0, y = 0;

	x = rand() % 9;
	y = rand() % 9;

	if(tableroSudoku[x][y] == 0){
		printf("Tu ayuda elegida fue el numero %d, en la fila %d columna %d\n", solucionSudoku[x][y], x, y);
		tableroSudoku[x][y] = solucionSudoku[x][y];
		ayudasUsadas++;
	}
	else
		ayudaSudoku();

	return;
}
