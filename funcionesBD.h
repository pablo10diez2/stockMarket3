#ifndef FUNCIONBD_H
#define	FUNCIONBD_H

#include <stdio.h>
#include "sqlite3.h"
#include <string.h>

void insertar_nombre(const char *nombre, int id);
void insertar_apellido(const char *apellido, int id);
void consultarUsuario(const char *email);
void actualizarContrasena(const char *email, const char *nuevaContrasena);

#endif
