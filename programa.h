#ifndef PROGRAMA_H
#define	PROGRAMA_H

#include <stdbool.h>
#include <stdio.h>
#include "funcionesBD.h"
#include "fichero.h"

const char* get_current_time();
void write_log(char* message);
void gestionarUsuario();
void gestionarFicheroEmpresa();
void iniciarSesion();
void iniciarPrograma();

#endif
