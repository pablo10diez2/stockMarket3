#include "configuracion.h"
#include <stdio.h>
#include <string.h>

char CONFIG_ADMIN_EMAIL[MAX_STR] = "";
char CONFIG_ADMIN_PASS[MAX_STR] = "";
char CONFIG_DB_PATH[MAX_PATH] = "";
char CONFIG_LOG_PATH[MAX_PATH] = "";
char CONFIG_STOCK_PATH[MAX_PATH] = "";

void cargarConfiguracion(const char *rutaConfig) {
    FILE *file = fopen(rutaConfig, "r");
    if (!file) {
        printf("No se pudo abrir el archivo de configuración: %s\n", rutaConfig);
        return;
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), file)) {
        if (linea[0] == '#' || linea[0] == '\n') continue;

        char clave[50], valor[200];
        if (sscanf(linea, "%[^=]=%[^\n]", clave, valor) == 2) {
            if (strcmp(clave, "admin_email") == 0)
                strncpy(CONFIG_ADMIN_EMAIL, valor, MAX_STR);
            else if (strcmp(clave, "admin_pass") == 0)
                strncpy(CONFIG_ADMIN_PASS, valor, MAX_STR);
            else if (strcmp(clave, "db_path") == 0)
                strncpy(CONFIG_DB_PATH, valor, MAX_PATH);
            else if (strcmp(clave, "log_path") == 0)
                strncpy(CONFIG_LOG_PATH, valor, MAX_PATH);
            else if (strcmp(clave, "stock_path") == 0)
            	strncpy(CONFIG_STOCK_PATH, valor, MAX_PATH);
        }
    }

    fclose(file);
}


