#include <iostream>
#include "menu.h"

using namespace std;

int main(){
    
    crearDoctor(registro_doctor);
    cout<<registro_doctor->anio_sesion<<endl;
    generarFecha(calendario_app);
    fechasDisponibles(calendario_app);
    return 0;
}
