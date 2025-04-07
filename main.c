#include "configuracion.h"
#include "programa.h"


int main() {
    cargarConfiguracion("data/config.txt");

    iniciarPrograma();
    return 0;
}
