#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_error(char *v)
{
    FILE *file;
    if((file = fopen("errores.txt", "a+")) == NULL)
        printf("ERROR: Error de lectura/escritura del archivo.");
    else
    {
        strcat(v, "\n");
        fputs(v, file);
    }
    fclose(file);
}
