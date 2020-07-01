#include <iostream>
#include <string>
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


calendario fechaActual(calendario calendario_app){
    int dia,mes;
    int cond=0;
    int anio=registro_doctor->anio_sesion;
    calendario fecha_actual=calendario_app;
    while (cond==0)
    {
        dia=diaNacimiento();
        mes=mesNacimiento();
        
        if(fechaCorrecta(dia,mes,anio)){
            while (fecha_actual !=NULL)
            {
                if ((fecha_actual->dia==dia) && (fecha_actual->mes==mes) && (fecha_actual->anio==anio)){
                    return fecha_actual;
                    break;
                }
                fecha_actual=fecha_actual->sig;
            }
            
        }
        else
        {
            cout<<"Fecha invalida. Intente de nuevo"<<endl;
            cond=0;
        }
        
    }
    return NULL;
}
bool diasDisponible(calendario calendario_app){
    calendario fecha=calendario_app;
    horas recorrido= fecha->lista_horas;
    bool disponibilidad=false;
    bool aux=false;
    while (recorrido!=NULL)
    {   
        aux=recorrido->disponibilidad;
        disponibilidad=disponibilidad || aux;
        recorrido=recorrido->sig;
    }
    return disponibilidad;
    
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
    return NULL;
}
calendario fechaConsulta(calendario calendario_app){
    bool cond=true;
    calendario fecha;
    string formato;
    int anio=registro_doctor->anio_sesion;
    while (cond){
        cout<<"Introduzca la fecha de consulta: "<<endl;
        int dia=diaNacimiento();
        int mes=mesNacimiento(); 
        if(fechaCorrecta(dia,mes,anio)){
                fecha=buscarFecha(calendario_app,dia,mes,anio);
                if((fecha->disponibilidad==true) && (comprobarFecha(fecha->dia_semana,lista_semana)))
                {
                    return fecha;
                }
                else
                {
                    cout<<"Fecha no laborable. Intente de nuevo"<<endl;
                }
                
            }
            else
            {
                cout<<"Fecha invalida. Intente de nuevo"<<endl;
                cond=0;
            }   
        }
    return NULL;
}
void fechasDisponibles(calendario calendario_app){
    cout<<"Introduzca la fecha actual: "<<endl;
    calendario recorrido=fechaActual(calendario_app);
    string formato,horas;
    int dia,mes,anio;
    int contador=0;
    while((recorrido!=NULL) && (contador<30)){
        cout<<"aca"<<endl;
        if((comprobarFecha(recorrido->dia_semana,lista_semana)) && (diasDisponible(recorrido)))
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
bool verificarHoraConsulta(int hora, horas lista_horas){
    horas recorrido=lista_horas;
    while (recorrido!=NULL)
    {
        if(recorrido->hora==hora){
            return true;
            break;
        }
        recorrido=recorrido->sig;
   }
    return false;
}
int horaConsulta(){
    string hora;
    int cond=0;
    while (cond==0){
        cout<<"Hora ";
        cin>>hora;
        cout<<endl;
        if((verificacionEntero(hora) && (verificarHoraConsulta(stoi(hora),lista_horas))))
        {
            return stoi(hora);
        }
        else
        {
            cout<<"Hora invalida. Intenta de nuevo"<<endl;
            cond=0;
        }
        
    }
    return 0;
}
int elegirHoraConsulta(calendario &calendario_app){
    int hora=horaConsulta();
    calendario fecha=calendario_app;
    horas hora_consulta=fecha->lista_horas;
    while (hora_consulta!=NULL)
    {
        if ((hora_consulta->hora==hora)&&(hora_consulta->disponibilidad==true))
        {
            hora_consulta->disponibilidad=false;
            return hora;
            break;    
        }
        hora_consulta=hora_consulta->sig;
    }
    
}

apun_citas crearCita(int cedula,calendario calendario_app){
    apun_citas cita;
    calendario fecha;
    cita=new(struct nodo_cita);
    cita->cedula_paciente=cedula;
    fechasDisponibles(calendario_app);
    fecha=fechaConsulta(calendario_app);
    cita->fecha_consulta=mostrarFecha(fecha);
    cita->hora_consulta=elegirHoraConsulta(fecha);
    cita->sig=NULL;
    return cita;
}

void crearListaCitas(apun_citas &citas,int cedula){
    apun_citas aux1,aux2;
    apun_citas nueva_cita=crearCita(cedula,calendario_app);
    aux1=citas;
    while ((aux1!=NULL) && (fechaReciente(aux1->fecha_consulta,nueva_cita->fecha_consulta)) )
    {
        aux2=aux1;
        aux1=aux1->sig;
    }
    if (citas==aux1){
        citas=nueva_cita;
    }
    else
    {
        aux2->sig=nueva_cita;
    }
    nueva_cita->sig=aux1;
}
void mostrarListaCitas(apun_citas lista){
    apun_citas recorrido;
    recorrido=lista;
    while(recorrido != NULL){
        //cout<<recorrido->cedula_paciente<<endl;
        cout<<"Fecha cita : "<<recorrido->fecha_consulta<<endl;
        cout<<"Hora de consulta : "<<recorrido->hora_consulta<<endl;
        recorrido=recorrido->sig;
    }
}