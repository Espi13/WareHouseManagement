#include "articulo.h"
#include "almacen.h"
#include "stock.h"
#include "error.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cabeceras Funciones Privadas

//Variables Privadass
static T_Stock *stock;
static int tam;

void add_stock(){
    int c_art, c_alm, cant;
    do{
        do{
            printf("Introduce codigo de articulo(0-99999).");
            scanf("%d", &c_art);
            fflush(stdin);
        }while(!existe_articulo_stock(c_art));
    
        do{
            printf("Introduce codigo de almacen(0-99).");
            scanf("%d", &c_alm);
            fflush(stdin);
        }while(!existe_almacen_stock(c_alm));
    }while(existe_stock(c_art,c_alm));
    
    do{
        printf("Introduce la cantidad del articulo(0-999999).");
        scanf("%d", &cant);
        fflush(stdin);
    }while(cant < 0 || cant > 999999);
    
    stock = (T_Stock *) realloc(stock, (tam+1)*sizeof(T_Stock));
    stock[tam].c_articulo = c_art;
    stock[tam].c_almacen = c_alm;
    stock[tam].cantidad = cant;
    tam++;
}

void guardar_stock()
{
    int i;
    char str[17], aux[7];
    printf("Guardado.\n");
    FILE *file;
    if((file = fopen("stock.txt" , "w+")) == NULL)
        printf("ERROR: Error de lectura/escritura del archivo.");
    else
    {
        for(i=0 ; i<tam ; i++)
        {
            sprintf(str, "%05d-", stock[i].c_articulo);
            sprintf(aux, "%02d-", stock[i].c_almacen);
            strcat(str, aux);
            
            sprintf(aux, "%06d", stock[i].cantidad);
            strcat(str, aux);
            strcat(str, "\n");
            
            fputs(str, file);
        }
        fclose(file);
    }
}

void cargar_stock(){
	stock = (T_Stock *) calloc(0, sizeof(T_Stock));
	FILE *file;
	int idx = 0;
    char cadena[15];
	if((file = fopen("stock.txt" , "r")) == NULL){
		printf("ERROR: No existe el archivo 'stock.txt'\n");
	}else{
        char str[20] , c_art[6], c_alm[3], cant[7];
        while(fgets(str, 20, file) != NULL){
            T_Stock a;
            if(sscanf(str, "%[^-]-%s", c_art, cadena ) == 2)
            {
                if(sscanf(cadena, "%[^-]-%s", c_alm, cant ) == 2)
                {
                    a.c_articulo = atoi(c_art);
                    a.c_almacen = atoi(c_alm);
                    a.cantidad = atoi(cant);
                }
            }
            else
                printf("Error de lectura\n");
            stock = (T_Stock *) realloc(stock, (idx+1)*sizeof(T_Almacen));
            stock[idx] = a;
            idx++;
        }
        fclose(file);
        tam = idx;
    }
}

void listar_stock()
{
    int i;
    char str[19], aux[7];
    for(i=0 ; i<tam ; i++)
    {
        sprintf(str, "%05d-", stock[i].c_articulo);
        sprintf(aux, "%02d-", stock[i].c_almacen);
        strcat(str, aux);
        
        sprintf(aux, "%06d", stock[i].cantidad);
        strcat(str, aux); 
        printf("%s\n", str);
    }
    printf("\n");
}

void borrar_stock(int c_articulo, int c_almacen)
{
    int i, aux=0,cont=0;
    
    if(c_articulo == 0 && c_almacen == 0)
    {
        int c_art, c_alm;
        printf("\nIntroduzca el codigo del articulo:  \n");
        scanf("%d", &c_art);
        fflush(stdin);
        printf("\nIntroduzca el codigo del almacen:  \n");
        scanf("%d", &c_alm);
        fflush(stdin);
    
        for(i=0 ; i<tam ; i++){
            if(stock[i].c_articulo == c_art && stock[i].c_almacen == c_alm){
                cont++;
            }
        }
        while(cont > 0){
            aux=0;
            for(i=0 ; i<tam ; i++)
            {
                if(stock[i].c_articulo == c_art && stock[i].c_almacen == c_alm && aux == 0)
                {
                    aux = 1;
                    i+=1;
                }
                if(aux == 1)
                    stock[i-1] = stock[i];
                else
                    stock[i] = stock[i];
            }
            if(aux==1)
            {
                stock = (T_Stock *) realloc(stock, (--tam)*sizeof(T_Stock));
            }
            cont--;
        }
    }
    
    if(c_articulo != 0)
    {
        for(i=0 ; i<tam ; i++){
            if(stock[i].c_articulo == c_articulo){
                cont++;
            }
        }
        while(cont > 0){
            aux=0;
            for(i=0 ; i<tam ; i++)
            {
                if(stock[i].c_articulo == c_articulo && aux == 0)
                {
                    aux = 1;
                    i+=1;
                }
                if(aux == 1)
                    stock[i-1] = stock[i];
                else
                    stock[i] = stock[i];
            }
            if(aux==1)
            {
                stock = (T_Stock *) realloc(stock, (--tam)*sizeof(T_Stock));
            }
            cont--;
        }
    }
    
    if(c_almacen != 0)
    {
        for(i=0 ; i<tam ; i++){
            if(stock[i].c_almacen == c_almacen){
                cont++;
            }
        }
        while(cont > 0){
            aux=0;
            for(i=0 ; i<tam ; i++)
            {
                if(stock[i].c_almacen == c_almacen && aux == 0)
                {
                    aux = 1;
                    i+=1;
                }
                if(aux == 1)
                    stock[i-1] = stock[i];
                else
                    stock[i] = stock[i];
            }
            if(aux==1)
            {
                stock = (T_Stock *) realloc(stock, (--tam)*sizeof(T_Stock));
            }
            cont--;
        }
    }
}

int existe_stock(int c_articulo, int c_almacen){
    int i;
    char error[256];
    for(i=0 ; i<tam ; i++){
        if(stock[i].c_articulo == c_articulo && stock[i].c_almacen == c_almacen)
        {
            time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char output[128];
            strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
            sprintf(error,"[%s]: Se ha intentado anadir un stock con codigo articulo %d y codigo almacen %d\n ",output,c_articulo,c_almacen);
            add_error(error);
            printf("Ya hay un stock con ese articulo y almacen.\n");
            return 1;
        }
    }
    return 0;
}
