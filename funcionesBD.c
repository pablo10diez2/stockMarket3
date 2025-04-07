#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include "funcionesBD.h"

void insertar_nombre(const char *nombre, int id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;

    // Abrir la base de datos y verificar errores
    if (sqlite3_open("JP.sqlite", &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));

    }

    // Consulta SQL corregida
    const char *sql = "UPDATE usuario SET nombre_usuario = ? WHERE id_usuario = ?;";

    // Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

    }

    // Asignar valores a los parámetros
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    // Ejecutar la consulta
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error modificando el nombre: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Nombre modificado correctamente: %s\n", nombre);
    }

    // Liberar recursos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void insertar_apellido(const char *apellido, int id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;

    // Abrir la base de datos y verificar errores
    if (sqlite3_open("JP.sqlite", &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));

    }

    // Consulta SQL corregida
    const char *sql = "UPDATE usuario SET apellido_usuario = ? WHERE id_usuario = ?;";

    // Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    // Asignar valores a los parámetros
    sqlite3_bind_text(stmt, 1, apellido, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    // Ejecutar la consulta
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error modificando el apellido: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Apellido modificado correctamente: %s\n", apellido);
    }

    // Liberar recursos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void consultarUsuario(const char *email) {
	sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ID_Usuario, Nombre_Usuario, Apellido_Usuario, Email, Contraseña, ID_Rol FROM Usuario WHERE Email = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar SELECT: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        const unsigned char *apellido = sqlite3_column_text(stmt, 2);
        const unsigned char *correo = sqlite3_column_text(stmt, 3);
        const unsigned char *contrasena = sqlite3_column_text(stmt, 4);
        int id_rol = sqlite3_column_int(stmt, 5);

        printf("--- Información del Usuario ---\n");
        printf("ID: %d\nNombre: %s %s\nEmail: %s\nContraseña: %s\nID Rol: %d\n",
               id, nombre, apellido, correo, contrasena, id_rol);
    }

    sqlite3_finalize(stmt);
}

void actualizarContrasena(const char *email, const char *nuevaContrasena) {
	sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Usuario SET Contraseña = ? WHERE Email = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar UPDATE: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, nuevaContrasena, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error al actualizar la contraseña: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Contraseña actualizada correctamente.\n");
    }

    sqlite3_finalize(stmt);


}
