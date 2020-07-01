#include <iostream>
#include <string>
#include "doctor-sesion.h"
#include "menu.h"

using namespace std;

//8,9,10,11,12,15,16,17
//Archivo principal de la app
int main(){
    calendario prueba,elegir;
    apun_citas prueb,xx;
    string aaa,bbb,ccc,linea;
    bool a=true;
    int  b=1;
    crearDoctor(registro_doctor,lista_semana);
    cout<<registro_doctor->anio_sesion<<endl;
    cout<<mostrarHoras(lista_horas)<<endl;
    generarFecha(calendario_app);
    leeArchivoPaciente(lista_pacientes);
    lista_citas=leerArchivoCita();
    xx=lista_citas;
    mostrarVariasFechasCitas(xx);
    
    //prueba=fechaActual(calendario_app);
    /*
    prueb=buscarCitaCedula(lista_citas,25676145);
    mostrarListaCitas(lista_citas);
    mostrarCalendario(calendario_app);

    cout<<probando(prueb)<<endl;
    aaa=probando(prueb);
    cout<<aaa<<endl;
    aaa=prueb->fecha_consulta+' '+aaa;
    cout<<aaa<<endl;*/

    //mostrarVariasFechasCitas(lista_citas);

    /*
    cout<<mostrarFecha(prueba)<<endl;
    cout<<endl;   
    fechasDisponibles(calendario_app,prueba);
    */
/*
    while (a)
    {
        cout<<"***********************"<<endl;
        fechasDisponibles(calendario_app,prueba);
        cout<<"***********************"<<endl;
        if (b!=0)
        {
            crearListaCitas(lista_citas,25676145);
            cout<<"continuar: ";
            cin>>b;

        }
        else
        {
            a=false;
        }

    }
   mostrarListaCitas(lista_citas);*/
    /*
    calendario fecha; 
    bool a=true;
    int cont=0;
    int numero;
    while (a)
    {
        crearListaCitas(lista_citas,25676145);
        cout<<"continuar: "<<endl;
        cin>>numero;
        if(numero==0){
            a=false;
        }
    }
    
    mostrarListaCitas(lista_citas);
    /*
    bool a=true;
    if(inicioSesion()){
            leeArchivoPaciente(lista_pacientes);
            cout<<registro_doctor->anio_sesion<<endl;
            logicaMenu();
            a=false;
    }
*/
    system("pause");
    return 0;
}