#include <iostream>
#include "fechapac.h"
using namespace std;

struct nodo_historia {
    int cedula_paciente;
    string sintomas;
    string diagnostico;
    string recipe;
    string examenes;
    string fconsulta;
    string comentario;
    nodo_historia * sig;
};
typedef struct nodo_historia *historia_paciente;
historia_paciente lista_historia=NULL; //Va en cada paciente, no puede ser global

string lineasTextoExtensas(){
    string linea;
    getline(cin,linea);
    return linea;
}

historia_paciente crearHistoria(int cedula){
    historia_paciente historia;
    historia=new(struct nodo_historia);
    cout<<"Historia de paciente:"<<endl;
    historia->cedula_paciente=cedula;

    cout<<"Sintomas: ";
    historia->sintomas=lineasTextoExtensas();
    cout<<endl;

    cout<<"Diagnostico: ";
    historia->diagnostico=lineasTextoExtensas();
    cout<<endl;

    cout<<"Recipe: ";
    historia->recipe=lineasTextoExtensas();
    cout<<endl;

    cout<<"Examenes: ";
    historia->examenes=lineasTextoExtensas();
    cout<<endl;

    cout<<"Fecha consulta: "<<endl;
    historia->fconsulta=fechaPaciente();

    cout<<"Comentario: ";
    historia->comentario=lineasTextoExtensas();
    cout<<endl;

    historia->sig=NULL;
    return historia;
} 
void cambiarFecha(int &dia, int &mes, int &anio,string fecha){
    string digito="";
    for (int i = 0; i<2; i++)
    {
        digito=digito+fecha[i];
    }
    dia=stoi(digito);
    digito="";
    for (int i =3; i<5;i++){
        digito=digito+fecha[i];
    }
    mes=stoi(digito);
    digito="";
    for (int i=6; i<10;i++){
        digito=digito+fecha[i];
    }
    anio=stoi(digito);

}
bool fechaMayor(int numero1, int numero2){
    if (numero1>numero2){
        return true;
    }
    else
    {
        return false;
    }
    
}

bool fechaReciente(string fecha1, string fecha2){
    int dia1,mes1,anio1;
    int dia2,mes2,anio2;
    cambiarFecha(dia1,mes1,anio1,fecha1);
    cambiarFecha(dia2,mes2,anio2,fecha2);
    if (anio1==anio2){
        if (mes1==mes2){
            return fechaMayor(dia1,dia2);
        }
        else
        {
            return fechaMayor(mes1,mes2);
        }
        
    }
    else
    {
        return fechaMayor(anio1,anio2);
    }
}

//verificar si las fechas no son iguales

void crearListaHistoriaOrdenada(historia_paciente &historial,int cedula){
    historia_paciente aux1,aux2;
    bool cond=false;
    historia_paciente nueva_historia=crearHistoria(cedula);
    if (historial==NULL){
        historial=nueva_historia;
    }
    else
    {
        if(fechaReciente(nueva_historia->fconsulta,aux1->fconsulta)){//Si la fecha consulta es mas reciente que la de la lista
            aux1=historial;
            nueva_historia->sig=aux1;
            historial=nueva_historia;
        }
        else
        {
            while ((aux1->sig!=NULL)&&fechaReciente(aux1->fconsulta,nueva_historia->fconsulta))
            {

                if(fechaReciente(nueva_historia->fconsulta,aux1->fconsulta)){
                    nueva_historia->sig=aux1;
                    aux1=nueva_historia;
                    cond=true;
                    break;
                }
                aux1=aux1->sig;
            
             }
             if (!cond){
                 aux1->sig=nueva_historia;
             }
        
        
         }
    }
}


void mostrarLista(historia_paciente lista){
    historia_paciente recorrido;
    recorrido=lista;
    while(recorrido != NULL){
        cout<<recorrido->cedula_paciente<<endl;
        cout<<recorrido->fconsulta<<endl;
        cout<<recorrido->comentario<<endl;
        cout<<recorrido->sintomas<<endl;
        cout<<recorrido->diagnostico<<endl;
        cout<<recorrido->recipe<<endl;
        recorrido=recorrido->sig;

    }

}

