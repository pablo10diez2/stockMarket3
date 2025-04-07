#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "programa.h"
#include "fichero.h"
#include <time.h>

char LOG_NAME[30];

const char* get_current_time() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    static char time_str[20];
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", tm_info);
    return time_str;
}

void write_log(char* message) {
    FILE *log_file = fopen("data/logfile.txt", "a");
    fprintf(log_file, "[%s] [Persona: %s] %s\n", get_current_time(), LOG_NAME, message);
    fclose(log_file);
}

void gestionarFicheroEmpresa(){
    int num;

    printf("Pulsa 1 para buscar una empresa por su nombre \n");
    printf("Pulsa 2 para añadir una empresa \n");
    printf("Pulsa 3 para eliminar una empresa \n");

    scanf("%d", &num);

    switch(num){
        case 1:
            buscarEmpresa();
            break;

        case 2:
            añadirEmpresa();
            break;

        case 3:
            eliminarEmpresa();
            break;

        default:
            printf("Opción invalida");
            break;
    }
    gestionarFicheroEmpresa();
}

void gestionarUsuario(){
    int num;

    printf("Introduce 1 para ver todos los usuarios \n");
    printf("Introduce 2 para ver el historial de órdenes de un usuario \n");
    printf("Introduce 3 para ver las monitorizaciones de un usuario");

    scanf("%d", &num);

    switch(num){
        case 1:
            //buscarEmpresa();
            break;

        case 2:
            //añadirEmpresa();
            break;

        case 3:
            //eliminarEmpresa();
            break;

        default:
            printf("Opción invalida");
            break;
    }
}

void menuAdministrador(){
    int num;
    printf("---Bienvenido al menú administrador \n");
    printf("Introduce 1 para gestionar el fichero de empresas \n");
    printf("Introduce 2 para gestionar un usuario \n");
    printf("Introduce 3 para ... \n");

    scanf("%d", &num);

    switch(num){
        case 1:
            gestionarFicheroEmpresa();
            break;
        case 2:
            gestionarUsuario();
            break;
        case 3:
            break;
        default:
            printf("Opción no valida \n");
    }
}



void iniciarPrograma(){
    char str[30];

    printf("---Welcome to the Admin Menu \n");

    iniciarSesion();

}

void iniciarSesion(){
    char mail[30];
    char pass[30];

    printf("Introduce tu e-mail: \n");
    scanf("%s", mail);

    printf("Introduce tu contraseña: \n");
    scanf("%s", pass);

    if(comprobarCredenciales(mail, pass)){
        strcpy(LOG_NAME, mail);
        write_log("Inicio de sesión");
        menuAdministrador();

   }
    else{
        printf("Credenciales invalidas \n");
        iniciarSesion();
    }
}


