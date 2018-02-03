#ifndef ARTICULO_H
#define ARTICULO_H

typedef struct {
    int codigo;
    char descripcion[20];
}T_Articulo;

void alta_articulo();
void baja_articulo();
void listar_articulos();
void guardar_articulos();
void cargar_articulos();
int existe_articulo(int cod);
int existe_articulo_stock(int cod);

#endif // ARTICULO_H
