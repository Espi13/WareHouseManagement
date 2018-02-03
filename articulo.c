#include "articulo.h"
#include "error.h"
#include "stock.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cabeceras Funciones Privadas
static void ordenar_articulo();

//Variables Privadas
static T_Articulo *art;
static int tam;

//Funciones Públicas
void listar_articulos(){
    ordenar_articulo();
    int i;
    char str[27];
    printf("\nLista de articulos:\n");
    for(i=0 ; i<tam ; i++)
    {
        sprintf(str, "%05d-%s", art[i].codigo, art[i].descripcion);
        printf("%s\n", str);
    }
    printf("\n");
}

void alta_articulo(){
    int cod;
    char des[20];
    do{
        printf("\nIntroduzca el codigo del articulo:  \n");
        scanf("%d", &cod);
        fflush(stdin);
    }while(existe_articulo(cod) || cod < 0 || cod > 99999);
    printf("\nIntroduzca descripcion(20 caracteres) del articulo:  \n");
    gets(des);
    fflush(stdin);
    art = (T_Articulo *) realloc(art, (tam+1)*sizeof(T_Articulo));
    art[tam].codigo = cod;
    strcpy(art[tam].descripcion, des);
    tam++;
}

void baja_articulo(){
    int cod, i, aux;

    printf("\nIntroduzca el codigo del articulo:  \n");
    scanf("%d", &cod);
    fflush(stdin);

    for(i=0 ; i<tam ; i++){
        if(art[i].codigo == cod) {
            aux = 1;
            i++;
        }
        if(aux == 1)
            art[i-1] = art[i];
        else
            art[i] = art[i];
    }
    if(aux == 1)
    {
        art = (T_Articulo *) realloc(art, (--tam)*sizeof(T_Articulo));
        borrar_stock(cod,0);
    }
}

void guardar_articulos(){
    int i;
    char str[27];
    printf("Guardado.\n");
    FILE *file;
    if((file = fopen("articulo.txt" , "w+")) == NULL){
        printf("ERROR: Error de lectura/escritura del archivo.");
    }else{
        for(i=0 ; i<tam ; i++)
        {
            sprintf(str, "%05d-%s", art[i].codigo, art[i].descripcion);
            strcat(str, "\n");
            fputs(str, file);
        }
        fclose(file);
    }
}

void cargar_articulos(){
	art = (T_Articulo *) calloc(0, sizeof(T_Articulo));
	FILE *file;
	int idx = 0;

	if((file = fopen("articulo.txt" , "r")) == NULL){
		printf("ERROR: No existe el archivo 'articulo.txt'\n");
	}else{
        char str[27] , cod[5], desc[20];
        while(fgets(str, 27, file) != NULL){
            T_Articulo a;
            if(sscanf(str, "%[^-]-%s", cod, desc) == 2){
                a.codigo = atoi(cod);
                strcpy(a.descripcion , desc);
            }
            else
                printf("Error de lectura articulos.\n");
            art = (T_Articulo *) realloc(art, (idx+1)*sizeof(T_Articulo));
            art[idx] = a;
            idx++;
        }
        fclose(file);
        tam = idx;
    }
}

int existe_articulo(int cod){
    int i;
    char error[256];
    for(i=0 ; i<tam ; i++){
        if(art[i].codigo == cod)
        {
            time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char output[128];
            strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
            sprintf(error,"[%s]: Se ha intentado anadir un articulo con codigo %d\n ",output,cod);
            add_error(error);
            printf("Ya hay un articulo con ese codigo.\n");
            return 1;
        }
    }
    return 0;
}

int existe_articulo_stock(int cod){
    int i;
    char error[256];
    for(i=0 ; i<tam ; i++){
        if(art[i].codigo == cod)
            return 1;
    }
    printf("No hay un articulo con ese codigo.\n");
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    sprintf(error,"[%s]: Se ha intentado anadir un stock con codigo de articulo que no existe %d\n ",output,cod);
    add_error(error);
    return 0;
}

//Funciones Privadas
void ordenar_articulo()
{
    int i,j, caux;
    char daux[20];
    for(i=1 ; i<=tam ; i++){
        for(j=0 ; j<=tam-2 ; j++){
            if(art[j].codigo > art[j+1].codigo){
                caux = art[j].codigo;
                strcpy(daux, art[j].descripcion);

                art[j].codigo = art[j+1].codigo;
                strcpy(art[j].descripcion, art[j+1].descripcion);

                art[j+1].codigo = caux;
                strcpy(art[j+1].descripcion, daux);
            }
        }
    }
}
