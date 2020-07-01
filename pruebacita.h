#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct nodo_cita{
    int cedula_paciente;
    string nombre_paciente;
    string fecha_consulta;
    int hora_consulta=0;
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

void asignarHoras(horas &lista_horas, horas horas_lab){
    horas recorrido=horas_lab;
    while (recorrido!=NULL)
    {
        crearListahoras(lista_horas,recorrido->hora);
        recorrido=recorrido->sig;
    }
    
}

int algoritmoDia(int dia,int mes,int anio)
{
    int y,m,dia_semana;
	y = anio - (14-mes)/12;
	m = mes +12 * ((14-mes) / 12) -2;
	dia_semana= ( dia+ y + y / 4 - y / 100 + y / 400 + (31 * m / 12)) % 7;
    return dia_semana;
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
    asignarHoras(fecha->lista_horas,lista_horas);
    fecha->disponibilidad=true;
    return fecha;
}
void crearCalendario(calendario  &calendario_app,calendario fechas){
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
    //int anio=registro_doctor->anio_sesion;
    for (int i = 1; i < 13; i++)
    {
        for (int j = 1; j < 32; j++)
        {
            if (fechaCorrecta(j,i,2020))
            {   
                fecha=crearFecha(j,i,2020);
                crearCalendario(calendario_app,fecha);
            }
            
        }
        
    }
}
void mostrarCalendario(calendario fechas){
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
calendario buscarFecha(calendario calendario_app,int dia, int mes,int anio){
    calendario recorrido =calendario_app;
    while (recorrido!=NULL)
    {
        if((recorrido->dia==dia)&&(recorrido->mes==mes)&&(recorrido->anio==anio))
        {
            return recorrido;
            break;
        }
        recorrido=recorrido->sig;
    }
    return recorrido;
}

string mostrarFecha(calendario fechas){
    calendario recorrido;
    int dia,mes,anio;
    string formato,horas;
    recorrido=fechas;
    dia=recorrido->dia;
    mes=recorrido->mes;
    anio=recorrido->anio;
    formato=formatoFecha(dia,mes,anio);
    horas=mostrarHoras(recorrido->lista_horas);
    formato=formato+"-"+horas;
    return formato;
}
string fechaString(calendario fechas){
    calendario recorrido;
    string formato;
    recorrido=fechas;
    formato=formatoFecha(recorrido->dia,recorrido->mes,recorrido->anio);
    return formato;
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
bool elegirHoraConsulta(calendario &calendario_app,int hora){
    calendario fecha=calendario_app;
    horas hora_consulta=fecha->lista_horas;
    while (hora_consulta!=NULL)
    {
        if ((hora_consulta->hora==hora)&&(hora_consulta->disponibilidad==true))
        {
            hora_consulta->disponibilidad=false;
            return true;
            break;    
        }
        hora_consulta=hora_consulta->sig;
    }
    return false;
    
}
void  diasDisponible(calendario &calendario_app){
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
    calendario_app->disponibilidad=disponibilidad;
    
}
//
bool comprobarFecha(string dia,semana dias_lab){
    semana dias_recorrido=dias_lab;
    while (dias_recorrido!=NULL)
    {
        if (dia==dias_recorrido->dia)
        {
            return true;
            break;
        }

        dias_recorrido=dias_recorrido->sig;

    }
    return false;
}
calendario fechaActual(calendario calendario_app){
    cout<<"Introduzca la fecha actual: "<<endl;
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
                if ((fecha_actual->dia==dia) && (fecha_actual->mes==mes)){
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
void fechasDisponibles(calendario calendario_app,calendario fecha){
    string formato,horas;
    calendario recorrido=fecha;
    int dia,mes,anio;
    int contador=0;
    while((recorrido!=NULL) && (contador<30)){
        diasDisponible(recorrido);
        if((comprobarFecha(recorrido->dia_semana,lista_semana)) && (recorrido->disponibilidad))
        { 
            contador++;
            cout<<contador<<"-"<<recorrido->dia_semana<<"-------"<<mostrarFecha(recorrido)<<endl;
        }   
        recorrido=recorrido->sig;
    }
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
                    cout<<"Fecha no disponible. Intente de nuevo"<<endl;
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
int asignarHoraCita(calendario fecha){
    bool cond=true;
    while (cond)
        {
            int hora=horaConsulta();
            if (elegirHoraConsulta(fecha,hora))
            {
                cout<<"Hora usada: "<<hora<<endl;
                return hora;
                break;
            }
            else
            {
                cout<<"Hora no disponible"<<endl;
            }            
        }
    return 0;
}

apun_citas crearCita(int cedula,calendario calendario_app){
    apun_citas cita;
    calendario fecha;
    cita=new(struct nodo_cita);
    cita->cedula_paciente=cedula;
    fecha=fechaConsulta(calendario_app);
    cita->fecha_consulta=fechaString(fecha);
    cita->hora_consulta=asignarHoraCita(fecha);
    cita->nombre_paciente=obtenerNombre(cedula);
    cita->sig=NULL;
    return cita;
}

void mostrarListaCitas(apun_citas lista){
    apun_citas recorrido;
    recorrido=lista;
    while(recorrido != NULL){
        cout<<recorrido->cedula_paciente<<endl;
        cout<<"Fecha cita : "<<recorrido->fecha_consulta<<endl;
        cout<<"Hora de consulta : "<<recorrido->hora_consulta<<endl;
        recorrido=recorrido->sig;
    }
}

void mostrarCita(apun_citas lista){
    apun_citas recorrido;
    recorrido=lista;
        cout<<recorrido->cedula_paciente<<endl;
        cout<<"1-Fecha cita : "<<recorrido->fecha_consulta<<endl;
        cout<<"2-Hora de consulta : "<<recorrido->hora_consulta<<endl;
    }


void crearArchivoCita(apun_citas lista_citas){
    fstream archivo;
    apun_citas recorrido=lista_citas;
    archivo.open("citas.txt",ios::out);
    if(!archivo.fail())
        {
            while(recorrido !=NULL){
                archivo<<recorrido->cedula_paciente<<endl;
                archivo<<recorrido->nombre_paciente<<endl;
                archivo<<recorrido->fecha_consulta<<endl;
                archivo<<recorrido->hora_consulta<<endl;
                if (recorrido->sig!=NULL){
                    archivo<<"***********"<<endl;
                }
                else
                {
                    archivo<<"***********";
                }
                
                recorrido=recorrido->sig;
                
            }
        }
    archivo.close();
}

void crearListaCitas(apun_citas &citas,int cedula){
    apun_citas aux1,aux2;
    apun_citas nueva_cita=crearCita(cedula,calendario_app);
    aux1=citas;

    while ((aux1!=NULL) && (fechaReciente(nueva_cita->fecha_consulta,aux1->fecha_consulta)) )
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
    crearArchivoCita(citas);
}
//
void crearListaCitasArchivo(apun_citas &lista_citas, apun_citas citas_leidas)
{
    apun_citas aux2;
    if (lista_citas==NULL){
        lista_citas=citas_leidas;
    }
    else
    {
        aux2=lista_citas;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=citas_leidas;
    }
}
void probando(horas &listahoras,int horapautada){
    horas aux=listahoras;
    while (aux!=NULL)
    {
        if(aux->hora==horapautada){
            aux->disponibilidad=false;
        }
        aux=aux->sig;
    }
}
void horasOcupadasArchivo(calendario &calendario_app,apun_citas citas_leidas){
    apun_citas cita_aux=citas_leidas;
    int dia,mes,anio;
    while (cita_aux!=NULL)
    {
        cambiarFecha(dia,mes,anio,cita_aux->fecha_consulta);
        calendario fecha_cita=buscarFecha(calendario_app,dia,mes,anio);
        if(verificarHoraConsulta(cita_aux->hora_consulta,fecha_cita->lista_horas)){
            probando(fecha_cita->lista_horas,cita_aux->hora_consulta);
        }
        cita_aux=cita_aux->sig;
    }
    


}
apun_citas leerArchivoCita(){
    fstream archivo;
    string linea;
    apun_citas citas_leidas,aux2;
    aux2=NULL;
    archivo.open("citas.txt",ios::in);
            while(!archivo.eof())
            {
                citas_leidas=new(struct nodo_cita);
                getline(archivo,linea);
                citas_leidas->cedula_paciente=stoi(linea);
                getline(archivo,linea);
                citas_leidas->nombre_paciente=linea;
                getline(archivo,citas_leidas->fecha_consulta);
                getline(archivo,linea);
                citas_leidas->hora_consulta=stoi(linea);
                citas_leidas->sig=NULL;
                crearListaCitasArchivo(aux2,citas_leidas);
                getline(archivo,linea);
            }
            horasOcupadasArchivo(calendario_app,aux2);
            return aux2;
            

}
bool citaCedula(apun_citas lista_citas, int cedula){
    apun_citas recorrido=lista_citas;
    while (recorrido!=NULL)
    {
        if(recorrido->cedula_paciente==cedula){
            return true;
        }
        recorrido=recorrido->sig;
    }
    return false;
}
apun_citas buscarCitaCedula(apun_citas lista_citas,int cedula){
    apun_citas recorrido=lista_citas;
    while (recorrido!=NULL)
    {
        if(recorrido->cedula_paciente==cedula){
            return recorrido;
        }
        recorrido=recorrido->sig;
    }
    return NULL;
}
void campoCitaModificar(apun_citas cita_modificar){
    cout<<"Indique el numero de campo a modificar: "<<endl;
    int opcion=repetirEntero();
    int dia,mes,anio;
    bool cambio=true;
    int hora=0;
    calendario consulta,aux;
    while (opcion!=0)
    {
        switch (opcion)
        {
        case 0:
            break;
        case 1:
            consulta=fechaConsulta(calendario_app);
            if (hora!=0){
                if (elegirHoraConsulta(consulta,hora))
                {
                    cita_modificar->fecha_consulta=fechaString(consulta);
                }
                else
                {
                    cout<<"Hora no disponible para esta fecha. Intente de nuevo"<<endl;
                }
            }
            else
            {
                cita_modificar->fecha_consulta=fechaString(consulta);
            }
            
            //falta evaluar si la hora cambiada esta disponible
            break;
        case 2:
            cambiarFecha(dia,mes,anio,cita_modificar->fecha_consulta);
            aux=buscarFecha(calendario_app,dia,mes,anio); 
            cita_modificar->hora_consulta=asignarHoraCita(aux);
            hora=cita_modificar->hora_consulta;
            break;
        default:
            cout<<"Campo invalido"<<endl;
            break;
        }
        cout<<"Si desea modificar otro campo, coloque el numero, sino cooque 0: ";
        opcion=repetirEntero();
    }
} 

void modificarCita(apun_citas &lista_citas){
    apun_citas cita=lista_citas;
    mostrarCita(cita);
    campoCitaModificar(cita);
    cout<<"La cita fue modificada correctamente"<<endl;
    cout<<"**********************"<<endl;
    mostrarCita(cita);
    cout<<"**********************"<<endl;
    crearArchivoCita(lista_citas);
}
string fechaCita(){
    int dia,mes,anio;
    bool cond=true;
    string fecha_texto;
    anio=registro_doctor->anio_sesion;
    while (cond){
        dia=diaNacimiento();
        mes=mesNacimiento();
        if(fechaCorrecta(dia,mes,anio)){
            fecha_texto=formatoFecha(dia,mes,anio);
            return fecha_texto;
        }
        else
         {
            cout<<"Fecha incorrecta, intente de nuevo"<<endl;
            cond=true;
        }
    
    }
    return "";
}
bool existeFechaCita(apun_citas lista_citas,string fecha){
    apun_citas recorrido=lista_citas;
    while (recorrido!=NULL)
    {
        if (fecha==recorrido->fecha_consulta)
        {
            return true;
        }
        recorrido=recorrido->sig;
    }
    return false;
}

string probando(apun_citas cita){
    string linea,nombre,fecha,hora;
    apun_citas probando=cita;
    nombre=probando->nombre_paciente;
    fecha=probando->fecha_consulta;
    hora=to_string(probando->hora_consulta);
    //cout<<fecha<<'\n';
    //cout<<nombre<<'\n';
    //cout<<probando->hora_consulta<<' ';
    return hora;
}


void mostrarVariasFechasCitas (apun_citas lista_citas )
{
    apun_citas citas=lista_citas;
    string completo="";
    string fecha=fechaCita();
    if(existeFechaCita(citas,fecha)){
        while (citas!=NULL)
        {
            if(fecha==citas->fecha_consulta){
                cout<<citas->fecha_consulta<<"-"<<citas->nombre_paciente<<"-"<<citas->hora_consulta<<endl;
            }

            citas=citas->sig;
        }
        
    }
    else
    {
        cout<<"No existe citas para esa fecha"<<endl;
    }
    
}
