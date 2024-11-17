#define MAX_PLACAS 7
#define N 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <practica.h>

typedef struct
{
    int disponible;
    int x;
    int y;
    char tipo[15];
    float tarifa;
    char placas[MAX_PLACAS];
} Auto;

typedef struct
{
    int viajes_realizados;
    int autos_libres;
    float ganancias;
} App;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void inicializar_autos()
{
    Auto autos[N];
    const char *tipos[] = {"UberPlanet", "UberXL", "UberBlack"};
    const float tarifas[] = {10.0, 15.0, 25.0};

    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        autos[i].disponible = 1;  // Todos los autos están disponibles al inicio.
        autos[i].x = rand() % 51; // Coordenada x entre 0 y 50.
        autos[i].y = rand() % 51; // Coordenada y entre 0 y 50.

        int tipo_index = rand() % 3; // Tipo aleatorio.
        snprintf(autos[i].tipo, 15, "%s", tipos[tipo_index]);
        autos[i].tarifa = tarifas[tipo_index];

        snprintf(autos[i].placas, MAX_PLACAS, "%03d%c%c%c", rand() % 1000, 'A' + rand() % 26, 'A' + rand() % 26, 'A' + rand() % 26);
    }

    guardar_autos_csv(&autos);
}

void guardar_autos_csv(Auto *autos[])
{
    FILE *file = fopen("autos.txt", "w");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(file, "disponible,x,y,tipo,tarifa,placas\n");
    for (int i = 0; i < N; i++)
    {
        fprintf(file, "%d,%d,%d,%s,%.2f,%s\n",
                autos[i]->disponible, autos[i]->x, autos[i]->y, autos[i]->tipo,
                autos[i]->tarifa, autos[i]->placas);
    }

    fclose(file);
}

void inicializarEstado()
{
    App estado;
    estado.viajes_realizados = 0;
    estado.autos_libres = N;
    estado.ganancias = 0.0;

    guardarEstado(estado);
}

int autosDisponibles()
{
    // Leer autos desde el archivo de estado
    FILE *file = fopen("estado.txt", "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return -1;
    }

    char line[100];
    fgets(line, 100, file); // Ignorar la primera línea.

    int autos_libres;
    fscanf(file, "%*d,%d,%*f\n", &autos_libres);

    fclose(file);

    return autos_libres;
}

void guardarEstado(App estado)
{
    FILE *file = fopen("estado.txt", "w");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(file, "viajes_realizados,autos_libres,ganancias\n");
    fprintf(file, "%d,%d,%.2f\n",
            estado.viajes_realizados, estado.autos_libres, estado.ganancias);

    fclose(file);
}

void mostrar_autos(Auto autos[])
{
    for (int i = 0; i < N; i++)
    {
        printf("Auto %d: [%d, %d] %s $%.2f/km Placas: %s Disponible: %s\n",
               i, autos[i].x, autos[i].y, autos[i].tipo, autos[i].tarifa,
               autos[i].placas, autos[i].disponible ? "Sí" : "No");
    }
}

float calcular_distancia(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void obtener_autos_registro(Auto *autos[])
{
    FILE *file = fopen("autos.txt", "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    char line[100];
    fgets(line, 100, file); // Ignorar la primera línea.

    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%d,%d,%d,%[^,],%f,%s\n",
               &autos[i]->disponible, &autos[i]->x, &autos[i]->y, autos[i]->tipo,
               &autos[i]->tarifa, autos[i]->placas);
    }

    fclose(file);
}

void obtener_estado_registro(App *estado)
{
    FILE *file = fopen("estado.txt", "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    char line[100];
    fgets(line, 100, file); // Ignorar la primera línea.

    fscanf(file, "%d,%d,%f\n",
           &estado->viajes_realizados, &estado->autos_libres, &estado->ganancias);

    fclose(file);
}

void buscar_auto_cercano(Posicion pos, InfoAuto *result)
{
    Auto *autos[N];
    App *estado;

    obtener_autos_registro(autos);

    int auto_cercano = -1;
    float distancia_minima = 1000.0; // Distancia máxima entre dos puntos en un plano de 50x50.

    for (int i = 0; i < N; i++)
    {
        if (autos[i]->disponible)
        {
            float distancia = calcular_distancia(pos.x, pos.y, autos[i]->x, autos[i]->y);
            if (distancia < distancia_minima)
            {
                distancia_minima = distancia;
                auto_cercano = i;
            }
        }
    }

    // Una vez encontrado el auto más cercano, se asigna al resultado.

    if (auto_cercano == -1)
    {
        result = NULL;
    }
    else
    {
        result->posicion_auto.x = autos[auto_cercano]->x;
        result->posicion_auto.y = autos[auto_cercano]->y;
        result->tarifa = autos[auto_cercano]->tarifa;
        result->placa = autos[auto_cercano]->placas;
        result->tipo = autos[auto_cercano]->tipo;

        // Modificar valores antes de guardar
        autos[auto_cercano]->disponible = 0;
        estado->autos_libres--;

        // Guardar cambios
        actualizar_autos(&autos);
        actualizar_estado(&estado);
    }
}

void actualizar_autos(Auto *autos[])
{
    FILE *file = fopen("autos.txt", "w");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(file, "disponible,x,y,tipo,tarifa,placas\n");
    for (int i = 0; i < N; i++)
    {
        fprintf(file, "%d,%d,%d,%s,%.2f,%s\n",
                autos[i]->disponible, autos[i]->x, autos[i]->y, autos[i]->tipo,
                autos[i]->tarifa, autos[i]->placas);
    }

    fclose(file);
}

void actualizar_estado(App *estado)
{
    FILE *file = fopen("estado.txt", "w");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(file, "viajes_realizados,autos_libres,ganancias\n");
    fprintf(file, "%d,%d,%.2f\n",
            estado->viajes_realizados, estado->autos_libres, estado->ganancias);

    fclose(file);
}

int obtener_indice_auto(char *placas)
{
    Auto *autos[N];
    obtener_autos_registro(autos);

    for (int i = 0; i < N; i++)
    {
        if (strcmp(autos[i]->placas, placas) == 0)
        {
            return i;
        }
    }

    return -1;
}

void terminar_viaje(Posicion pos, float costo, char *placas)
{
    Auto *autos[N];
    App *estado;

    int indice = obtener_indice_auto(placas);
    autos[indice]->x = pos.x;
    autos[indice]->y = pos.y;
    autos[indice]->disponible = 1;

    estado->viajes_realizados++;
    estado->autos_libres++;
    estado->ganancias += costo;

    // Guardar cambios
    actualizar_autos(autos);
    actualizar_estado(estado);
}

void obtener_estado(InfoServicio *result)
{
    App *estado;
    obtener_estado_registro(estado);

    result->viajes_realizados = estado->viajes_realizados;
    result->autos_libres = estado->autos_libres;
    result->ganancia = estado->ganancias;
}

int randomPosicion()
{
    return rand() % 51;
}
