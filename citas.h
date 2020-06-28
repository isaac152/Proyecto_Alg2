#include <iostream>
#include "fechapac.h"
#include "doctor-sesion.h"
//#include "fechadoc.h"

using namespace std;

struct nodo_cita{
    int cedula_paciente;
    string fecha_consulta;
    int hora_consulta;
    nodo_cita *sig;
};
struct nodo_calendario{
    int dia;
    int mes;
    int anio;
    string dia_semana;
    horas lista_horas;
    bool disponibilidad;
    nodo_calendario *sig;
};
typedef struct nodo_calendario *calendario; 
typedef struct nodo_cita *apun_citas; 
calendario calendario_app=NULL;
apun_citas lista_citas=NULL;

int algoritmoDia(int dia,int mes,int anio)
{
    int y,m,dia_semana;
	y = anio - (14-mes)/12;
	m = mes +12 * ((14-mes) / 12) -2;
	dia_semana= ( dia+ y + y / 4 - y / 100 + y / 400 + (31 * m / 12)) % 7;
    return dia_semana;
}
string fechaActual(){
    string fechaAct="";
    int dia,mes;
    int cond=0;
    int anio=registro_doctor->anio_sesion;
    while (cond==0)
    {
        dia=diaNacimiento();
        mes=mesNacimiento();
        
        if(fechaCorrecta(dia,mes,anio)){
            return formatoFecha(dia,mes,anio);
        }
        else
        {
            cout<<"Fecha invalida. Intente de nuevo"<<endl;
            cond=0;
        }
        
    }
}
calendario crearFecha(int dia, int mes, int anio){
    calendario fecha;
    int dia_semana;
    fecha=new(struct nodo_calendario);
    fecha->dia=dia;
    fecha->mes=mes;
    fecha->anio=anio;
    dia_semana=algoritmoDia(dia,mes,anio);
    fecha->dia_semana=diasSemana(dia_semana);
    fecha->lista_horas=registro_doctor->horas_lab;
    fecha->disponibilidad=true;
    return fecha;
}

void crearCalendario(calendario &calendario_app,calendario fechas){
    calendario aux1;
    if(calendario_app==NULL){
        calendario_app=fechas;
    }
    else
    {
        aux1=calendario_app;
    while (aux1->sig!=NULL)
    {
        aux1=aux1->sig;
    }
    aux1->sig=fechas;
    }
    
}
void generarFecha(calendario &calendario_app){
    calendario fecha;
    int anio=registro_doctor->anio_sesion;
    int contador=0;
    for (int i = 1; i < 13; i++)
    {
        for (int j = 1; j < 32; j++)
        {
            if (fechaCorrecta(j,i,anio))
            {

                fecha=crearFecha(j,i,anio);
                crearCalendario(calendario_app,fecha);

            }
            
        }
        
    }
    
}

string mostrarHoras(horas horas_dia){
    horas recorrido;
    string aux;
    string horas_t="";
    recorrido=horas_dia;
    while (recorrido!=NULL)
    {
        aux=to_string(recorrido->hora);
        if (recorrido->sig!=NULL)
        {
            horas_t=horas_t+aux+",";
        }
        else
        {
            horas_t=horas_t+aux;
        }   
        recorrido=recorrido->sig;
    }
    return horas_t;
    
}
string mostrarSemana(semana dias_semana){
    semana recorrido;
    string aux;
    string dias="";
    recorrido=dias_semana;
    while (recorrido!=NULL)
    {
        aux=recorrido->dia;
        if (recorrido->sig!=NULL)
        {
            dias=dias+aux+",";
        }
        else
        {
            dias=dias+aux;
        }   
        recorrido=recorrido->sig;
    }
    return dias;
    
}
void mostrarFecha(calendario fechas){
    calendario recorrido;
    int dia,mes,anio;
    string formato,horas;
    recorrido=fechas;
    while(recorrido != NULL){
        dia=recorrido->dia;
        mes=recorrido->mes;
        anio=recorrido->anio;
        formato=formatoFecha(dia,mes,anio);
        horas=mostrarHoras(recorrido->lista_horas);
        cout<<recorrido->dia_semana<<" - "<<formato<<" - "<<horas<<endl;
        recorrido=recorrido->sig;
    }

}
bool comprobarFecha(string dia,semana dias_lab){
    semana dias_recorrido=dias_lab;
    bool validacion=true;
    while (dias_recorrido!=NULL)
    {
        if (dia==dias_recorrido->dia)
        {
            validacion=true;
            return true;
            break;
        }
        else
        {
            validacion=false;
            dias_recorrido=dias_recorrido->sig;
        }

    }
    if(validacion==false){
        return false;
    }

}




void fechasDisponibles(calendario calendario_app){
    calendario recorrido;
    string formato,horas;
    int dia,mes,anio;
    int contador=0;
    cout<<"aca"<<endl;
    recorrido=calendario_app;
    while((recorrido!=NULL) && (contador<30)){
        if(comprobarFecha(recorrido->dia_semana,registro_doctor->dias))
        { 
        dia=recorrido->dia;
        mes=recorrido->mes;
        anio=recorrido->anio;
        formato=formatoFecha(dia,mes,anio);
        horas=mostrarHoras(recorrido->lista_horas);
        cout<<recorrido->dia_semana<<" - "<<formato<<" - "<<horas<<endl;

        contador++;
        }
        recorrido=recorrido->sig;
    }

}

string consolidarFechaCita(){
    string fecha_actual;
    fecha_actual=fechaActual();

}

/*
apun_citas crearCita(int cedula){
    apun_citas cita;
    cita=new(struct nodo_cita);
    cita->cedula_paciente=cedula;

    cita->fecha_consulta=fechaPaciente();*/
    /*
    fecha->dia=dia;
    fecha->mes=mes;
    fecha->anio=anio;
    fecha->dia_semana=algoritmoDia(dia,mes,anio);
    fecha->disponibilidad=true;
    return fecha;
}
    
    */