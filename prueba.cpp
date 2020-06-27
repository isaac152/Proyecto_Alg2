#include <iostream>
#include "base64.cpp"

using namespace std;

int main(){
    cout<<base64_encode("12345678",true)<<endl;
    cout<<base64_decode("MTIzNDU2Nzg.",true)<<endl;
    /*
    apun_pacientes paciente;

    leeArchivoPaciente(lista_pacientes);
    mostrarLista(lista_pacientes);
    modificarPaciente(lista_pacientes);
    /*
    cout<<"Introduzca cedula de paciente a cambiar: "<<endl;
    cin>>cedula;
    if(existePaciente(lista_pacientes,cedula)){
        paciente=buscarPaciente(lista_pacientes,cedula);
        crearListaHistoriaOrdenada(paciente->historia,paciente->cedula);
        mostrarListaHistoria(paciente->historia);
    }
    else
    {
        cout<<"No existe"<<endl;
    }*/
    
    return 0;
}
