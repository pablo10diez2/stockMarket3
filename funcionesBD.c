#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include "funcionesBD.h"
#include <stdlib.h>
#include <stdbool.h>
#include "configuracion.h"


void insertar_nombre(const char *nombre, int id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;

    if (sqlite3_open(CONFIG_DB_PATH, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql = "UPDATE Usuario SET Nombre_Usuario = ? WHERE ID_Usuario = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error modificando el nombre: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Nombre modificado correctamente: %s\n", nombre);
        write_log("Nombre actualizado");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void insertar_apellido(const char *apellido, int id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;

    if (sqlite3_open(CONFIG_DB_PATH, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql = "UPDATE Usuario SET Apellido_Usuario = ? WHERE ID_Usuario = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, apellido, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error modificando el apellido: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Apellido modificado correctamente: %s\n", apellido);
        write_log("Apellido actualizado");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void consultarUsuario(const char *email) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ID_Usuario, Nombre_Usuario, Apellido_Usuario, Email, Contraseña, ID_Rol FROM Usuario WHERE Email = ?";

    if (sqlite3_open(CONFIG_DB_PATH, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar SELECT: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
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
        write_log("Consulta de usuario");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void actualizarContrasena(const char *email, const char *nuevaContrasena) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Usuario SET Contraseña = ? WHERE Email = ?";

    if (sqlite3_open(CONFIG_DB_PATH, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar UPDATE: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, nuevaContrasena, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error al actualizar la contrasena: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Contrasena actualizada correctamente.\n");
        write_log("Contrasena actualizada");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void verTodosLosUsuarios() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ID_Usuario, Nombre_Usuario, Apellido_Usuario, Email, ID_Rol FROM Usuario;";

    if (sqlite3_open(CONFIG_DB_PATH, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando SELECT: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    printf("---- Lista de Usuarios ----\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        const unsigned char *apellido = sqlite3_column_text(stmt, 2);
        const unsigned char *email = sqlite3_column_text(stmt, 3);
        int rol = sqlite3_column_int(stmt, 4);

        printf("ID: %d | Nombre: %s %s | Email: %s | Rol: %d\n", id, nombre, apellido, email, rol);
        write_log("Ver usuarios");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void verHistorialOrdenes(int idUsuario) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Orden WHERE ID_Usuario = ?;";

    if (sqlite3_open(CONFIG_DB_PATH, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando SELECT: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, idUsuario);
    printf("---- Historial de órdenes del Usuario %d ----\n", idUsuario);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idOrden = sqlite3_column_int(stmt, 0);
        const unsigned char *fechaCreacion = sqlite3_column_text(stmt, 1);
        const unsigned char *fechaEjecucion = sqlite3_column_text(stmt, 2);
        int estado = sqlite3_column_int(stmt, 3);
        double precioMin = sqlite3_column_double(stmt, 4);
        double precioMax = sqlite3_column_double(stmt, 5);
        double cantidad = sqlite3_column_double(stmt, 6);
        const unsigned char *ticker = sqlite3_column_text(stmt, 8);

        printf("Orden ID: %d | Fecha: %s | Estado: %d | Cantidad: %.2f | Ticker: %s\n",
               idOrden, fechaCreacion, estado, cantidad, ticker);
        write_log("Ver ordenes");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void verMonitorizaciones(int idUsuario) {
    sqlite3 *db;
    sqlite3_stmt *stmtMon, *stmtConsLink, *stmtConsulta;
    const char *sqlMon = "SELECT * FROM Monitorizar WHERE ID_Usuario = ?;";
    const char *sqlConsLink = "SELECT ID_Consulta FROM ConsultaEnMonitorizar WHERE ID_Monitorizar = ?;";
    const char *sqlConsulta = "SELECT Fecha_Hora, Precio_Actual, Mejor_Precio_Compra, Mejor_Precio_Venta, Volumen FROM Consulta WHERE ID_Consulta = ?;";

    if (sqlite3_open(CONFIG_DB_PATH, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sqlMon, -1, &stmtMon, NULL) != SQLITE_OK) {
        printf("Error preparando SELECT de monitorizaciones: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmtMon, 1, idUsuario);
    printf("---- Monitorizaciones del Usuario %d ----\n", idUsuario);

    while (sqlite3_step(stmtMon) == SQLITE_ROW) {
        int idMon = sqlite3_column_int(stmtMon, 0);
        const unsigned char *nombre = sqlite3_column_text(stmtMon, 1);
        const unsigned char *inicio = sqlite3_column_text(stmtMon, 2);
        const unsigned char *fin = sqlite3_column_text(stmtMon, 3);
        double intervalo = sqlite3_column_double(stmtMon, 4);
        const unsigned char *tipo = sqlite3_column_text(stmtMon, 5);
        const unsigned char *ticker = sqlite3_column_text(stmtMon, 6);

        printf("\n Monitorización ID: %d\n", idMon);
        printf("Nombre: %s | Desde: %s hasta %s | Intervalo: %.2f | Tipo: %s | Ticker: %s\n",
               nombre, inicio, fin, intervalo, tipo, ticker);

        // Obtener ID_Consulta desde ConsultaEnMonitorizar
        if (sqlite3_prepare_v2(db, sqlConsLink, -1, &stmtConsLink, NULL) != SQLITE_OK) {
            printf("Error preparando SELECT de vínculos: %s\n", sqlite3_errmsg(db));
            continue;
        }

        sqlite3_bind_int(stmtConsLink, 1, idMon);
        int hayConsultas = 0;

        while (sqlite3_step(stmtConsLink) == SQLITE_ROW) {
            hayConsultas = 1;
            int idConsulta = sqlite3_column_int(stmtConsLink, 0);

            // Buscar la información de la consulta
            if (sqlite3_prepare_v2(db, sqlConsulta, -1, &stmtConsulta, NULL) != SQLITE_OK) {
                printf("Error preparando SELECT de consulta: %s\n", sqlite3_errmsg(db));
                continue;
            }

            sqlite3_bind_int(stmtConsulta, 1, idConsulta);

            if (sqlite3_step(stmtConsulta) == SQLITE_ROW) {
                const unsigned char *fecha = sqlite3_column_text(stmtConsulta, 0);
                double precio = sqlite3_column_double(stmtConsulta, 1);
                double mejorCompra = sqlite3_column_double(stmtConsulta, 2);
                double mejorVenta = sqlite3_column_double(stmtConsulta, 3);
                double volumen = sqlite3_column_double(stmtConsulta, 4);

                printf("   - Consulta ID: %d | Fecha: %s | Precio: %.2f | Mejor Compra: %.2f | Mejor Venta: %.2f | Volumen: %.2f\n",
                       idConsulta, fecha, precio, mejorCompra, mejorVenta, volumen);
            }

            sqlite3_finalize(stmtConsulta);
        }

        if (!hayConsultas) {
            printf("   (No hay consultas registradas)\n");
        }

        sqlite3_finalize(stmtConsLink);
        write_log("Ver monitorizaciones con consultas");
    }

    sqlite3_finalize(stmtMon);
    sqlite3_close(db);
}


