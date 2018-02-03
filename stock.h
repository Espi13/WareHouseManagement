#ifndef STOCK_H
#define STOCK_H

typedef struct {
    int c_articulo;
    int c_almacen;
    int cantidad;
}T_Stock;

void add_stock();
void guardar_stock();
void cargar_stock();
void listar_stock();
void borrar_stock(int c_articulo, int c_almacen);
int existe_stock(int c_articulo, int c_almacen);

#endif // STOCK_H
