#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#define MAX_PATH 256
#define MAX_STR 100

extern char CONFIG_ADMIN_EMAIL[MAX_STR];
extern char CONFIG_ADMIN_PASS[MAX_STR];
extern char CONFIG_DB_PATH[MAX_PATH];
extern char CONFIG_LOG_PATH[MAX_PATH];
extern char CONFIG_STOCK_PATH[MAX_PATH];

void cargarConfiguracion(const char *rutaConfig);

#endif
