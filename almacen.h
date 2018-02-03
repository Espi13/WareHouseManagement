#ifndef ALMACEN_H
#define ALMACEN_H

typedef struct {
    int codigo;
    char descripcion[10];
}T_Almacen;

void alta_almacen();
void baja_almacen();
void listar_almacenes();
void guardar_almacenes();
void cargar_almacenes();
int existe_almacen(int cod);
int existe_almacen_stock(int cod);

#endif // ALMACEN_H
