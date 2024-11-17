#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "practica.h"

#define AUTOS_FILE "autos.txt"
#define ESTADO_FILE "estado.txt"

void inicializar_archivo_autos()
{
    FILE *file = fopen(AUTOS_FILE, "w");
    if (file == NULL)
    {
        perror("Error al crear el archivo de autos");
        exit(1);
    }
    fprintf(file, "id,disponible,pos_x,pos_y\n"); // Cabeceras del CSV
    fclose(file);
}

void inicializar_archivo_estado()
{
    FILE *file = fopen(ESTADO_FILE, "w");
    if (file == NULL)
    {
        perror("Error al crear el archivo de estado");
        exit(1);
    }
    fprintf(file, "viajes_realizados,autos_libres,ganancias\n"); // Cabeceras del CSV
    fclose(file);
}

void leer_autos(InfoAuto autos[], int *num_autos)
{
    FILE *file = fopen(AUTOS_FILE, "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo de autos");
        exit(1);
    }
    char line[256];
    *num_autos = 0;
    fgets(line, sizeof(line), file); // Leer cabecera
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%d,%d,%f,%f", &autos[*num_autos].id, &autos[*num_autos].disponible, &autos[*num_autos].pos.x, &autos[*num_autos].pos.y);
        (*num_autos)++;
    }
    fclose(file);
}

void escribir_autos(InfoAuto autos[], int num_autos)
{
    FILE *file = fopen(AUTOS_FILE, "w");
    if (file == NULL)
    {
        perror("Error al abrir el archivo de autos");
        exit(1);
    }
    fprintf(file, "id,disponible,pos_x,pos_y\n"); // Cabeceras del CSV
    for (int i = 0; i < num_autos; i++)
    {
        fprintf(file, "%d,%d,%f,%f\n", autos[i].id, autos[i].disponible, autos[i].pos.x, autos[i].pos.y);
    }
    fclose(file);
}

void leer_estado(App *estado)
{
    FILE *file = fopen(ESTADO_FILE, "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo de estado");
        exit(1);
    }
    char line[256];
    fgets(line, sizeof(line), file); // Leer cabecera
    fgets(line, sizeof(line), file);
    sscanf(line, "%d,%d,%f", &estado->viajes_realizados, &estado->autos_libres, &estado->ganancias);
    fclose(file);
}

void escribir_estado(App *estado)
{
    FILE *file = fopen(ESTADO_FILE, "w");
    if (file == NULL)
    {
        perror("Error al abrir el archivo de estado");
        exit(1);
    }
    fprintf(file, "viajes_realizados,autos_libres,ganancias\n"); // Cabeceras del CSV
    fprintf(file, "%d,%d,%f\n", estado->viajes_realizados, estado->autos_libres, estado->ganancias);
    fclose(file);
}