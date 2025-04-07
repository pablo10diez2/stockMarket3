#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "fichero.h"
#include "programa.h"
#include "configuracion.h"

void buscarEmpresa() {
    char linea[256];
    FILE *file = fopen(CONFIG_STOCK_PATH, "r");
    if (!file) {
        printf("No se pudo abrir el archivo de empresas.\n");
        return;
    }

    char busqueda[32];
    printf("---Introduce el nombre de la empresa (primera mayúscula): ");
    fflush(stdout);
    fflush(stdin);
    scanf("%s", busqueda);
    write_log("Búsqueda de empresa");

    bool encontrada = false;

    while (fgets(linea, sizeof(linea), file) != NULL) {
        char *ticker = strtok(linea, ",");
        char *nombre = strtok(NULL, "\n");

        if (nombre != NULL && strncmp(nombre, busqueda, strlen(busqueda)) == 0) {
            printf("Nombre de la empresa: %s, Ticker: %s\n", nombre, ticker);
            fflush(stdout);
            fflush(stdin);
            encontrada = true;
        }
    }

    if (!encontrada) {
        printf("Empresa no encontrada.\n");
        fflush(stdout);
        fflush(stdin);
    }

    fclose(file);
}

void anadirEmpresa() {
    FILE *file = fopen(CONFIG_STOCK_PATH, "a");
    if (!file) {
        printf("No se pudo abrir el archivo para añadir.\n");
        fflush(stdout);
        fflush(stdin);
        return;
    }

    char ticker[10];
    char nombre[100];

    printf("Introduce el TICKER de la empresa: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%s", ticker);

    printf("Introduce el nombre de la empresa: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%s", nombre);

    fprintf(file, "%s,%s\n", ticker, nombre);
    fflush(stdout);
    fflush(stdin);
    write_log("Empresa añadida");

    fclose(file);
}

void eliminarEmpresa() {
    char original[] = "data/stock_info.txt";
    char temporal[] = "data/temporal.txt";
    char tickerUsuario[10];
    char linea[256];
    bool eliminado = false;

    FILE *ficheroOriginal = fopen(original, "r");
    FILE *ficheroTemporal = fopen(temporal, "w");

    if (!ficheroOriginal || !ficheroTemporal) {
        printf("Error abriendo archivos.\n");
        fflush(stdout);
        fflush(stdin);
        return;
    }

    printf("Introduce el ticker de la empresa que quieres borrar: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%s", tickerUsuario);

    while (fgets(linea, sizeof(linea), ficheroOriginal)) {
        char lineaCopia[256];
        strcpy(lineaCopia, linea);  // para no modificar la original al tokenizar

        char *tickerEmpresa = strtok(linea, ",");

        if (tickerEmpresa && strcmp(tickerEmpresa, tickerUsuario) != 0) {
            fputs(lineaCopia, ficheroTemporal);
        } else {
            eliminado = true;
        }
    }

    fclose(ficheroOriginal);
    fclose(ficheroTemporal);

    remove(original);
    rename(temporal, original);

    if (eliminado) {
        printf("Empresa eliminada.\n");
        fflush(stdout);
        fflush(stdin);
        write_log("Empresa eliminada");
    } else {
        printf("Empresa no encontrada.\n");
        fflush(stdout);
        fflush(stdin);
    }
}

bool comprobarCredenciales(char mail[], char contrasena[]) {
    return strcmp(mail, CONFIG_ADMIN_EMAIL) == 0 && strcmp(contrasena, CONFIG_ADMIN_PASS) == 0;
}
