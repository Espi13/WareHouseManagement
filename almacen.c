#include "almacen.h"
#include "error.h"
#include "stock.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cabeceras Funciones Privadas
static void ordenar_almacenes();

//Variables Privadas
static T_Almacen *alm;
static int tam;

//Funciones Públicas
void listar_almacenes(){
    ordenar_almacenes();
    int i;
    char str[14];
    printf("\nLista de almacenes:\n");
    for(i=0 ; i<tam ; i++)
    {
        sprintf(str, "%02d-%s", alm[i].codigo, alm[i].descripcion);
        printf("%s\n", str);
    }
    printf("\n");
}

void alta_almacen(){
    int cod;
    char des[10];
    do{
        printf("\nIntroduzca el codigo del almacen(0-99): \n");
        scanf("%d", &cod);
        fflush(stdin);
    }while(existe_almacen(cod) || cod < 0 || cod > 99);
    printf("\nIntroduzca descripcion(10 caracteres) del almacen: \n");
    gets(des);
    fflush(stdin);
    alm = (T_Almacen *) realloc(alm, (tam+1)*sizeof(T_Almacen));
    alm[tam].codigo = cod;
    strcpy(alm[tam].descripcion, des);
    tam++;
}

void baja_almacen(){
    int cod, i, aux;

    printf("\nIntroduzca el codigo del almacén:  \n");
    scanf("%d", &cod);
    fflush(stdin);

    for(i=0 ; i<tam ; i++){
        if(alm[i].codigo == cod) {
            aux = 1;
            i++;
        }
        if(aux == 1)
            alm[i-1] = alm[i];
        else
            alm[i] = alm[i];
    }
    if(aux==1){
        alm = (T_Almacen *) realloc(alm, (--tam)*sizeof(T_Almacen));
        borrar_stock(0,cod);
    }
}

void guardar_almacenes(){
    int i;
    char str[15];
    printf("Guardado.\n");
    FILE *file;
    if((file = fopen("almacenes.txt" , "w+")) == NULL){
        printf("ERROR: Error de lectura/escritura del archivo.");
    }else{
        for(i=0 ; i<tam ; i++)
        {
            sprintf(str, "%02d-%s", alm[i].codigo, alm[i].descripcion);
            strcat(str, "\n");
            fputs(str, file);
        }
        fclose(file);
    }
}

void cargar_almacenes(){
	alm = (T_Almacen *) calloc(0, sizeof(T_Almacen));
	FILE *file;
	int idx = 0;

	if((file = fopen("almacenes.txt" , "r")) == NULL)
    {
		printf("ERROR: No existe el archivo 'almacenes.txt'\n");
	}
    else
    {
        char str[15] , cod[2], desc[10];
        while(fgets(str, 15, file) != NULL)
        {
            T_Almacen a;
            if(sscanf(str, "%[^-]-%s", cod, desc) == 2){
                a.codigo = atoi(cod);
                strcpy(a.descripcion , desc);
            }
            else
                printf("Error de lectura almacenes.\n");
            alm = (T_Almacen *) realloc(alm, (idx+1)*sizeof(T_Almacen));
            alm[idx] = a;
            idx++;
        }
        fclose(file);
        tam = idx;
    }
}
int existe_almacen(int cod){
    int i;
    char error[256];
    for(i=0 ; i<tam ; i++){
        if(alm[i].codigo == cod){
            time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char output[128];
            strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
            sprintf(error,"[%s]: Se ha intentado anadir un almacen con codigo %d\n ",output,cod);
            add_error(error);
            printf("Ya hay un almacen con ese codigo.\n");
            return 1;
        }
    }
    return 0;
}

int existe_almacen_stock(int cod){
    int i;
    char error[256];
    for(i=0 ; i<tam ; i++){
        if(alm[i].codigo == cod)
            return 1;
    }
    printf("No hay un almacen con ese codigo.\n");
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    sprintf(error,"[%s]: Se ha intentado anadir un stock con codigo de almacen que no existe %d\n ",output,cod);
    add_error(error);
    return 0;
}

//Funciones Privadas
void ordenar_almacenes(){
    int i,j, caux;
    char daux[10];
    for(i=1 ; i<=tam ; i++){
        for(j=0 ; j<=tam-2 ; j++){
            if(alm[j].codigo > alm[j+1].codigo){
                caux = alm[j].codigo;
                strcpy(daux, alm[j].descripcion);

                alm[j].codigo = alm[j+1].codigo;
                strcpy(alm[j].descripcion, alm[j+1].descripcion);

                alm[j+1].codigo = caux;
                strcpy(alm[j+1].descripcion, daux);
            }
        }
    }
}
