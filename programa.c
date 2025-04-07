#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "programa.h"
#include <time.h>
#include "configuracion.h"

char LOG_NAME[30];

const char* get_current_time() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    static char time_str[20];
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", tm_info);
    return time_str;
}

void write_log(char* message) {
    FILE *log_file = fopen(CONFIG_LOG_PATH, "a");
    fprintf(log_file, "[%s] [Persona: %s] %s\n", get_current_time(), LOG_NAME, message);
    fclose(log_file);
}

void gestionarFicheroEmpresa() {
    int num;

    while (1) {
        printf("\n--- Gestión de Empresas ---\n");
        printf("Pulsa 1 para buscar una empresa por su nombre \n");
        printf("Pulsa 2 para añadir una empresa \n");
        printf("Pulsa 3 para eliminar una empresa \n");
        printf("Pulsa 0 para volver al menú anterior\n");
        fflush(stdout);
        fflush(stdin);
        scanf("%d", &num);

        switch (num) {
            case 1:
                buscarEmpresa();
                break;
            case 2:
                anadirEmpresa();
                break;
            case 3:
                eliminarEmpresa();
                break;
            case 0:
                return;  // Volver al menú anterior
            default:
                printf("Opción inválida\n");
                break;
        }
    }
}

void gestionarUsuario() {
    int opcion;

    while (1) {
        printf("\n--- Gestión de Usuarios ---\n");
        printf("1. Ver todos los usuarios\n");
        printf("2. Ver historial de órdenes de un usuario\n");
        printf("3. Ver monitorizaciones de un usuario\n");
        printf("4. Consultar información de un usuario por email\n");
        printf("5. Actualizar contraseña de un usuario\n");
        printf("0. Volver al menú anterior\n");
        printf("Selecciona una opción: ");
        fflush(stdout);
        fflush(stdin);
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                verTodosLosUsuarios();
                break;

            case 2: {
                int id;
                printf("Introduce el ID de usuario: \n");
                fflush(stdout);
                fflush(stdin);
                scanf("%d", &id);
                verHistorialOrdenes(id);
                break;
            }

            case 3: {
                int id;
                printf("Introduce el ID de usuario: \n");
                fflush(stdout);
                fflush(stdin);
                scanf("%d", &id);
                verMonitorizaciones(id);
                break;
            }

            case 4: {
                char email[100];
                printf("Introduce el email del usuario: \n");
                fflush(stdout);
                fflush(stdin);
                scanf("%s", email);
                consultarUsuario(email);
                break;
            }

            case 5: {
                char email[100];
                char nuevaContrasena[100];
                printf("Introduce el email del usuario: \n");
                fflush(stdout);
                fflush(stdin);
                scanf("%s", email);
                printf("Introduce la nueva contraseña: \n");
                fflush(stdout);
                fflush(stdin);
                scanf("%s", nuevaContrasena);
                actualizarContrasena(email, nuevaContrasena);
                break;
            }

            case 0:
                return;  // Volver al menú anterior

            default:
                printf("Opción inválida. Intenta de nuevo.\n");
        }
    }
}


void menuAdministrador() {
    int num;

    while (1) {
        printf("\n--- Bienvenido al menú administrador ---\n");
        printf("Introduce 1 para gestionar el fichero de empresas \n");
        printf("Introduce 2 para gestionar un usuario \n");
        printf("Introduce 0 para cerrar sesión \n");
        fflush(stdout);
        fflush(stdin);
        scanf("%d", &num);

        switch (num) {
            case 1:
                gestionarFicheroEmpresa();
                break;
            case 2:
                gestionarUsuario();
                break;
            case 0:
                printf("Cerrando sesión...\n");
                return;
            default:
                printf("Opción no válida\n");
                break;
        }
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
    fflush(stdout);
    fflush(stdin);
    scanf("%s", mail);

    printf("Introduce tu contraseña: \n");
    fflush(stdout);
    fflush(stdin);
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


