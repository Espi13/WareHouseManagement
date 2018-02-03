#include <stdio.h>
#include <stdlib.h>
#include "almacen.h"
#include "articulo.h"
#include "stock.h"

static void Menu();
static void Articulos();
static void Almacenes ();
static void Stock ();


int main(int argc, char *argv[]) 
{   
    cargar_articulos();
    cargar_almacenes();
    cargar_stock();
    Menu();
    
	system("pause");
	return 0;
}


static void Menu()
{
    int a;
    do{ 
        printf("------------------------------------Menu---------------------------------------- \n");
        
        puts("1.Articulos.\n");
        puts("2.Almacenes.\n");
        puts("3.Stock.\n");
        puts("4.Salir/Exit.\n");
        puts("Introduzca una opcion: ");  
        scanf("%d",&a);
        
        switch(a)
        {
            case 1:
                Articulos();break;
            case 2:
                Almacenes();break;
            case 3:
                Stock();break;
            case 4: guardar_stock();guardar_articulos();guardar_almacenes();exit(1);
        }
    }while(a!=4);
}

static void Articulos()
{
    int a;
    do{
        printf(" 1.Altas de articulos ordenados por codigo. \n");
        printf(" 2.Bajas de articulos por codigo.\n");
        printf(" 3.Guardar articulos.\n");
        printf(" 4.Listar articulos.\n");
        printf(" 5.Volver.\n");
        puts("Introduzca una opcion: ");  
        scanf("%d",&a);
    
        switch(a)
        {
            case 1: alta_articulo(); break;
            case 2: baja_articulo(); break;
            case 3: guardar_articulos(); break;
            case 4: listar_articulos(); break;
        }
    }while(a!=5);
}    

static void Almacenes()
{
    int a;
    do{
        printf(" 1.Altas de almacenes ordenados por codigo. \n");
        printf(" 2.Bajas de almacenes por codigo.\n");
        printf(" 3.Guardar almacenes.\n");
        printf(" 4.Listar almacenes.\n");
        printf(" 5.Volver.\n");
        puts("Introduzca una opcion: ");  
        scanf("%d",&a);
    
        switch(a)
        {
            case 1: alta_almacen(); break;
            case 2: baja_almacen(); break;
            case 3: guardar_almacenes(); break;
            case 4: listar_almacenes(); break;
        }
    }while(a!=5);
}

static void Stock()
{
    int a;
    do{
        printf(" 1.Anadir stock.\n");
        printf(" 2.Borrar stock.\n");
        printf(" 3.Guardar stock.\n");
        printf(" 4.Listar stock.\n");
        printf(" 5.Volver.\n");
        puts("Introduzca una opcion: ");  
        scanf("%d",&a);
        
        switch(a)
        {
            case 1: add_stock(); break;
            case 2: borrar_stock(0,0); break;
            case 3: guardar_stock(); break;
            case 4: listar_stock(); break;
        }
    }while(a!=5);
}
