#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>


int nvueltas, ncaballos, largopista;

struct Caballos{
	long numero;
	int tiempo;
} Caballos;

void *CrearCaballo(void *e);
int Vueltas(struct Caballos *cab);

void *CrearCaballo(void *e) {
	clock_t inicio, termino;
	double segundos;
	inicio = clock();

	struct Caballos *caballo;
	caballo = (struct Caballos *) e;

	int i;
	caballo->tiempo = Vueltas(caballo);

	termino = clock();
	segundos = (double)(termino - inicio) / CLOCKS_PER_SEC;
}


int Vueltas(struct Caballos *cab) {
	int i, count = 0, pasos, suma=0;
	for(i = 1; i < nvueltas+1; i++) {
		int x = (rand() % 5)+1;
        printf("Numero Caballo: %ld \nVuelta: %d \nRecorrido: %d metros \n", cab->numero, i,pasos);
		sleep(x);
		count += x;

        while(pasos < largopista*i){
           pasos += rand() % 5;
		}

	}
	printf("Caballo %ld Cantidad : %d \n",cab->numero,pasos);
	return count;
}




int main() {

	srand(time(NULL));
	printf("----------------------¡Bienvenidos a la carrera!--------------------\n");

    printf("Ingresar el numero de caballos a participar, puede ser un minimo de 2 y un maximo de 7: ");
    scanf("%d", &ncaballos);


	while(ncaballos < 2 || ncaballos > 7){
        printf("La opcion esta fuera del rango mencionado(2-7): ");
        scanf("%d", &ncaballos);
	}

    printf("\n");

	printf("Ingresar numero de vueltas, puede ser de 1 a 4 vueltas: ");
	scanf("%d", &nvueltas);

	while(nvueltas < 1 || nvueltas > 4){
        printf("Opcion fuera del rango mencionado(1-4): ");
        scanf("%d \n", &nvueltas);
	}

    printf("\n");

	printf("Ingresa el largo de la pista(30, 40, 50 o 60 metros):");
	scanf("%d", &largopista);

	while(largopista!= 30 && largopista!=40 && largopista!=50 && largopista!=60){
        printf("Opcion fuera del rango mencionado(30,40,50 o 60):");
        scanf("%d \n", &largopista);
	}

	printf("\n");
	printf("Número caballos: %d \n", ncaballos);
	printf("Número vueltas: %d \n", nvueltas);
	printf("\n");

	pthread_t hilos[ncaballos];
	struct Caballos caballos[ncaballos];
	long c, d;
	for(c = 0; c < ncaballos; c++) {
		caballos[c].numero = c+1;
		pthread_create(&hilos[c], NULL, CrearCaballo, (void *) &caballos[c]);
	}

	for(c = 0; c < ncaballos; c++)
		pthread_join(hilos[c], NULL);
	int y, z;
	for(y = 0; y < ncaballos; y++) {
		for(z = 0; z < ncaballos; z++) {
			if(caballos[y].tiempo < caballos[z].tiempo) {
				int numero = caballos[y].numero;
				int tiempo = caballos[y].tiempo;
				caballos[y].numero = caballos[z].numero;
				caballos[y].tiempo = caballos[z].tiempo;
				caballos[z].numero = numero;
				caballos[z].tiempo = tiempo;
			}
		}
	}

	for(y = 0; y < ncaballos; y++) {
		printf("El caballo %ld llegó en el puesto %d \n", caballos[y].numero, y+1);

	}



	/*printf("El caballo ganador es : Caballo %ld", );*/



	pthread_exit(NULL);
	return 0;
	}
