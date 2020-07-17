#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include<iomanip>
using namespace std;

//Libreria que se encarga de englobar todas las funciones y estructuras que se encarguen del manejo de las citas

//Estructura que representa a un nodo de la lista citas
struct nodo_cita{
    int cedula_paciente;
    string nombre_paciente;
    string fecha_consulta;
    string dia_semana;
    int hora_consulta;
    nodo_cita *sig;
};
//Estructura que representa un nodo perteneciente a la lista de fechas o calendario
struct nodo_calendario{
    int dia;
    int mes;
    int anio;
    string dia_semana;
    horas lista_horas=NULL;
    bool disponibilidad;
    nodo_calendario *sig;
};
typedef struct nodo_calendario *calendario; 
typedef struct nodo_cita *apun_citas; 
//Variables globales de las fechas de la app y la lsita de citas
calendario calendario_app=NULL;
apun_citas lista_citas=NULL;
//Funcion que se encarga de copiar la lista de horas global a la lista de horas de cada fecha
//Recibe como parametro por referencia la lista de horas del nodo calendario y la lista de horas globales, extraidas del doctor
void asignarHoras(horas &lista_horas, horas horas_lab){
    horas recorrido=horas_lab;
    while (recorrido!=NULL)
    {
        crearListahoras(lista_horas,recorrido->hora);
        recorrido=recorrido->sig;
    }
    
}
//Funcion que se encarga replicar la congruencia de Zeller para calcular el dia de la semana de cualquier dia,
//dado un dia,mes y anio en particular
//Regresa un entero que va desde 0 hasta 6, siendo el 0 domingo y 6 el sabado
int algoritmoDia(int dia,int mes,int anio)
{
    int y,m,dia_semana;
	y = anio - (14-mes)/12;
	m = mes +12 * ((14-mes) / 12) -2;
	dia_semana= ( dia+ y + y / 4 - y / 100 + y / 400 + (31 * m / 12)) % 7;
    return dia_semana;
}
//Funcion que se encarga de crear el nodo de fecha, recibe como parametro dia,mes y anio
//Se usan funciones anteriores para completar el resto de los atributos
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
    fecha->sig=NULL;
    return fecha;
}
//Funcion que crea una lista de fechas para formar el calendario de la app
//Recibe como parametro por referencia la lista de fechas y una fecha creada en otra funcion
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
//Funcion que se encarga de generar los 365 dias del calendario a partir de dos iteraciones
//Luego crea un nodo fecha con esos datos y lo pasa a la funcion de crear calendario
void generarFecha(calendario &calendario_app){
    calendario fecha;
    int anio=registro_doctor->anio_sesion;
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
//Funcion auxiliar que se encarga de imprimir el calendario con sus respectivas horas. No se implementa en el codigo
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
//Funcion que se encarga de buscar una fecha particular en al calendario a partir de un dia, mes y anio dado como parametro
//Regresa el nodo que contiene dicha fecha
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
    return NULL;
}
//Funcion que se encarga de mostrar una fecha en concreto con sus respectivas horas
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
    formato=formato+"          "+horas;
    return formato;
}
//Funcion que convierte los enteros de dia, mes y anio de una fecha en concreto a string
//pasandolas al formato establecido anteriormente
string fechaString(calendario fechas){
    calendario recorrido;
    string formato;
    recorrido=fechas;
    formato=formatoFecha(recorrido->dia,recorrido->mes,recorrido->anio);
    return formato;
}
//Funcion que se encarga de validar si una hora se encuentra dentro de la lista de horas en las que trabaja el doctor
//Recibe como parametro la hora a evaluar y la lista de horas (global) para realizar la validacion
//Devuelve un booleano con dicha comparacion
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
//Funcion que se encarga de recibir como input un numero que sera la hora de consulta
//De modo que devuelve un entero con dicha hora tras realizar las respectivas validaciones
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
//Funcion que se encarga de evaluar si una hora introducida se encuentra disponible para cierto dia
//Recibe como parametro la fecha a la que se esta evaluando y un entero como hora
//Devuelve un boolean en base a dicha comparacion. Si la hora esta libre para esa fecha, devuelve un true
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
//Funcion que se encarga de recorrer la lista de horas de un dia y pauta el estado de un dia
//en base a cuantas horas libres le quedan. Ejm. Si el dia tiene solo horas ocupadas, entonces el dia no esta libre.
//Recibe como parametro por referencia el dia al que se le busca evaluar la disponibilidad
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
//Funcion que se encarga de verificar que un dia coincide con los dias laborables del doctor
//Recibe como parametro el string del dia y la lista de dias (globales), llenadas en la creacion del doctor
//Devuelve el booleano respectivo de dicha comparacion
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
//Funcion que se encarga de pedir al usuario los datos para buscar en el calendario la fecha actual
//y asi regresar esa fecha para su posterior manipulacion. Se usa para comprobar las fechas disponibles 30 dias despues
//de la fecha actual
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
//Funcion que se encarga de mostrar 30 fechas disponibles a partir de la fecha actual.
//Recibe como parametro la fecha actual.
void fechasDisponibles(calendario fecha){
    string formato,horas;
    calendario recorrido=fecha;
    int dia,mes,anio;
    int contador=0;
    cout<<"*************Citas Disponibles*************"<<endl;
    while((recorrido!=NULL) && (contador<30)){
        diasDisponible(recorrido);
        if((comprobarFecha(recorrido->dia_semana,lista_semana)) && (recorrido->disponibilidad))
        { 
            contador++;
            cout<<contador<<"-"<<recorrido->dia_semana<<setw(60)<<mostrarFecha(recorrido)<<endl;
        }   
        recorrido=recorrido->sig;
    }
}
//Funcion que sirve para crear una fecha de consulta a traves de otras funciones auxiliares
//Verifica la disponibilidad del dia y que se encuentre entre los dias laborables del doctor
//Recibe como parametro la lista de fecha, calendario (global) y devuelve una fecha en concreto
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
//Funcion que se encarga de asignar una hora existente y disponible a una cita mientras se crea
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
//Funcion que se encarga de crear el nodo de citas. Recibe como parametro un nodo calendario y un entero como cedula
apun_citas crearCita(int cedula,calendario calendario_app){
    apun_citas cita;
    calendario fecha;
    calendario fecha_actual;
    bool validacion_fecha=true;

    cita=new(struct nodo_cita);
    cita->cedula_paciente=cedula;
    
    fecha_actual=fechaActual(calendario_app);
    cout<<'\n';
    fechasDisponibles(fecha_actual);
    cout<<"********************************************"<<endl;
    while (validacion_fecha)
    {
        fecha=fechaConsulta(calendario_app);
        if(fecha==fecha_actual){
            validacion_fecha=false;
            break;
        }
        if(fechaReciente(fechaString(fecha_actual),fechaString(fecha)))
        {
            cout<<endl;
            cout<<"Fecha invalida. No se puede agendar fechas pasadas"<<endl;
            cout<<endl;
            validacion_fecha=true;
        }
        else
        {
            validacion_fecha=false;
        }
        
    }
    
    cita->fecha_consulta=fechaString(fecha);
    cita->hora_consulta=asignarHoraCita(fecha);
    if(existePaciente(lista_pacientes,cedula)){
        cita->nombre_paciente=obtenerNombre(cedula);
    }
    else
    {
        cin.ignore(256,'\n');
        cout<<"Indique nombre del paciente: "<<endl;
        cita->nombre_paciente=lineasTextoExtensas();
    }
    cita->dia_semana=fecha->dia_semana;
    cita->sig=NULL;
    return cita;
}
//Funcion auxiliar que se encarga de mostrar todas las citas en la lista. No se encuentra en la logica principal
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
//Funcion que se encarga de mostrar una cita en particulas, la cual recibe como parametro
void mostrarCita(apun_citas lista){
    apun_citas recorrido;
    recorrido=lista;
    cout<<"Cedula: "<<recorrido->cedula_paciente<<endl;
    cout<<"Nombre: "<<recorrido->nombre_paciente<<endl;
    cout<<"1-Fecha cita : "<<recorrido->fecha_consulta<<endl;
    cout<<"2-Hora de consulta : "<<recorrido->hora_consulta<<endl;
}
//Funcion que se encarga de guardar la lista de citas en un archivo plano
//Recibe como parametro la lista de citas (global)
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
                archivo<<recorrido->dia_semana<<endl;
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
//Funcion que se encarga de crear la lista de citas.
//Recibe como parametro por referencia la lista de citas(global) y el numero de cedula con la cual sera creada la nueva cita
void crearListaCitas(apun_citas &citas,int cedula){
    apun_citas aux1,aux2;
    apun_citas nueva_cita=crearCita(cedula,calendario_app);
    aux1=citas;

    while ((aux1!=NULL) && (fechaReciente(nueva_cita->fecha_consulta,aux1->fecha_consulta)))
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
    cout<<endl;
    cout<<"Cita creada con exito"<<endl;
    mostrarCita(nueva_cita);
    cout<<endl;
    crearArchivoCita(citas);
}
//Funcion que se encarga de crear la lista de citas a partir de la cita creada en la lectura del archivo
//Recibe como paremtro por referencia la lista de citas(global) y la cita creada a partir de la lectura del archivo
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
//Funcion que se encarga de comprobar si una hora corresponde a la lista de horas laborables del doctor
//Recibe como parametro por referencia la lista de horas de una fecha y un entero con la hora leida
void validarHora(horas &listahoras,int horapautada){
    horas aux=listahoras;
    while (aux!=NULL)
    {
        if(aux->hora==horapautada){
            aux->disponibilidad=false;
        }
        aux=aux->sig;
    }
}
//Funcion que se encarga de tachar las horas agendadas en el calendario de la app, para que no se 
//creen citas en horas ocupadas. Todo a partir de las horas leidas en el archivo de citas cuando se crea su lista
//Recibe como parametro por referencia el calendario y la cita leida en la lectura del archivo
void horasOcupadasArchivo(calendario &calendario_app,apun_citas citas_leidas){
    apun_citas cita_aux=citas_leidas;
    int dia,mes,anio;
    while (cita_aux!=NULL)
    {
        cambiarFecha(dia,mes,anio,cita_aux->fecha_consulta);
        calendario fecha_cita=buscarFecha(calendario_app,dia,mes,anio);
        if(verificarHoraConsulta(cita_aux->hora_consulta,fecha_cita->lista_horas)){
            validarHora(fecha_cita->lista_horas,cita_aux->hora_consulta);
        }
        cita_aux=cita_aux->sig;
    }
}
//Funcion que se encarga de organizar las horas de las citas. Si hay varias citas en una misma fecha
//Muestra la menor hora hasta la mayor hora
//Recibe como parametro por referencia la lista citas (global)
void ordernarHoras(apun_citas lista_citas){
    apun_citas aux1,aux2,recorrido;
    string nombre1;
    int cedula1;
    recorrido=NULL;
    aux1=NULL;
    int numero;
    recorrido=lista_citas;
    while (recorrido!=NULL)
    {
        aux1=recorrido->sig;
        while (aux1!=NULL)
        {
            if((recorrido->fecha_consulta==aux1->fecha_consulta)&&(recorrido->hora_consulta>aux1->hora_consulta))
            {
                cedula1=recorrido->cedula_paciente;
                nombre1=recorrido->nombre_paciente;
                numero=recorrido->hora_consulta;
                
                recorrido->hora_consulta=aux1->hora_consulta;
                recorrido->cedula_paciente=aux1->cedula_paciente;
                recorrido->nombre_paciente=aux1->nombre_paciente;

                aux1->hora_consulta=numero;
                aux1->cedula_paciente=cedula1;
                aux1->nombre_paciente=nombre1;
            }
            aux1=aux1->sig;
        
        }
        recorrido=recorrido->sig;
    }
}
//Funcion que se encarga leer los datos del archivo citas para la creacion de su respectiva lista
//Recibe como parametro por referencia la lista de citas (global)
void leerArchivoCita(apun_citas &lista_citas){
    fstream archivo;
    string linea;
    apun_citas citas_leidas;
    archivo.open("citas.txt",ios::in);
       if(!archivo.fail())
        {
            while(!archivo.eof())
            {
                citas_leidas=new(struct nodo_cita);
                getline(archivo,linea);
                citas_leidas->cedula_paciente=stoi(linea);
                getline(archivo,linea);
                citas_leidas->nombre_paciente=linea;
                getline(archivo,linea);
                citas_leidas->fecha_consulta=linea;
                getline(archivo,linea);
                citas_leidas->dia_semana=linea;
                getline(archivo,linea);
                citas_leidas->hora_consulta=stoi(linea);
                citas_leidas->sig=NULL;
                crearListaCitasArchivo(lista_citas,citas_leidas);
                getline(archivo,linea);
            }
            horasOcupadasArchivo(calendario_app,lista_citas);
        }
    else
    {
        cout<<" * "<<endl;
    }
    
}
//Funcion que se encarga de recorrer la lista de citas para ver si alguna cita 
//coincide con un numero de cedula. Devuelve un boleano correspondiente a esa comparacion
//Recibe como pametro la lista de citas(global) y un entero con la cedula
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
//Funcion que se encarga de buscar una cita a partir de su cedula
//Cuando la consigue, retorna el nodo cita correspondiente para su posterior modificacion
//Recibe como parametro la lista de citas(global) y un entero que contiene la cedula del paciente
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
//Funcion que se encarga de buscar una cita con un numero de cedula en concreto y luego cambia
//todas las citas que contienen esa cedula por la nueva cedula
//Recibe como parametro por referencia la lista de citas, y dos enteros que van a ser la cedula vieja y la cedula nueva
void cambiarCedulaCita(apun_citas &lista_citas,int cedula_v,int cedula_n){
    apun_citas recorrido=lista_citas;
    while (recorrido!=NULL){
        if(recorrido->cedula_paciente==cedula_v){
            recorrido->cedula_paciente=cedula_n;
        }
        recorrido=recorrido->sig;
    }   
}
//Funcion que lleva acabo la logica de modificar cualquier atributo de una cita en particular
//Se repite en un bucle hasta que el usuario indique su salida
//Recibe como paremtro la cita a modificar
void campoCitaModificar(apun_citas cita_modificar){
    cout<<"Indique el numero de campo a modificar: ";
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
                    cita_modificar->dia_semana=consulta->dia_semana;
                }
                else
                {
                    cout<<"Hora no disponible para esta fecha. Intente de nuevo"<<endl;
                }
            }
            else
            {
                cita_modificar->fecha_consulta=fechaString(consulta);
                cita_modificar->dia_semana=consulta->dia_semana;
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
//Funcion que se encarga mostrar una cita en particular y llamar a la logica encargada de modificarla
//para luego mostrarla modificada
//Recibe como parametro por referencia la cita a modificar
void modificarCita(apun_citas &lista_citas){
    apun_citas cita=lista_citas;
    mostrarCita(cita);
    campoCitaModificar(cita);
    cout<<"La cita fue modificada correctamente"<<endl;
    cout<<"**********************"<<endl;
    mostrarCita(cita);
    cout<<"**********************"<<endl;
}
//Funcion que se encarga de convertir los numeros de dia, mes y anio en un string que contiene la fecha
//con el formato adecuado
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
//Funcion que se encarga de comprobar si existe una cita en la lista que contenga una fecha en concreto
//Recibe como parametro la lista de citas y un string con la fecha de consulta
//Devuelve un booleano equivalente a la comparacion
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
//Funcion que se encarga de buscar una cita por su fecha
//Recibe como parametro la lista de citas y un string que contiene la fecha a buscar
//Devuelve el nodo cita perteneciente a la lista de citas con dicho valor
apun_citas buscarCitaFecha(apun_citas lista_citas,string fecha){
    apun_citas recorrido=lista_citas;
    while ((recorrido!=NULL))
    {
        if(fecha==recorrido->fecha_consulta){
            return recorrido;
            break;
        }
        recorrido=recorrido->sig;
    }
    return NULL;
}
//Funcion que se encarga de mostrar varias citas para una fecha en particular. 
//Recibe como parametro la lista de citas y un nodo de citas para comprar la fecha de consulta
void mostrarVariasFechasCitas (apun_citas lista_citas,apun_citas fecha_cita )
{
    apun_citas citas=lista_citas;
    ordernarHoras(lista_citas);
        cout<<"Fechas"<<setw(15)<<"Nombres"<<setw(20)<<"Horas"<<endl;
        cout<<"*****************************************"<<endl;
        while (citas!=NULL)
        {
            if(fecha_cita->fecha_consulta==citas->fecha_consulta){
                printf(" %s - %s - %d \n",citas->fecha_consulta.c_str(),citas->nombre_paciente.c_str(),citas->hora_consulta);
            }

            citas=citas->sig;
        }
        
    
}
//Funcion que se encarga de recoger dos fechas y mostrar en pantalla todas las fechas de citas que se encuentre 
//en ese rango en cuestion. La primera fecha indicada debe tener una cita, de lo contrario marcara un error
//La segunda fecha no es necesaria que tenga una cita pero de tenerla, se indicara.
void mostrarRangoFechasCitas(apun_citas lista_citas){
    apun_citas citas=lista_citas;
    ordernarHoras(lista_citas);
    bool cond=false;
    cout<<"Introduzca la primera fecha: "<<endl;
    calendario fecha=fechaConsulta(calendario_app);
    string fecha_v=fechaString(fecha);
    cout<<"Introduzca la segunda fecha: "<<endl;
    calendario fecha2=fechaConsulta(calendario_app);
    string fecha_r=fechaString(fecha2);
    if(existeFechaCita(citas,fecha_v)&& (fechaReciente(fecha_r,fecha_v))){
        
            cout<<"Fechas"<<setw(15)<<"Nombres"<<setw(20)<<"Horas"<<endl;
        cout<<"*****************************************"<<endl;
        while ((citas!=NULL)&& (!fechaReciente(citas->fecha_consulta,fecha_r)))
        {
            if (citas->fecha_consulta==fecha_v)
            {
                cond=true;
            }
            if(cond){
                printf(" %s - %s - %d \n",citas->fecha_consulta.c_str(),citas->nombre_paciente.c_str(),citas->hora_consulta);
            }
            citas=citas->sig;
        }
    }
    else{
        cout<<"Rango invalido. Primera fecha no existe o segunda fecha es menor."<<endl;
    }
}
//Funcion que se encarga de eliminar una cita de la lista de citas a partir de su cedula y la fecha de consulta
//Recibe como parametro por referencia la lista de citas, como entero la cedula y como string la fecha de dicha cita
void eliminarCita(apun_citas &lista_citas, int cedula){
    apun_citas lista,cita_aux,cita_sig;
    lista=lista_citas;
    cita_aux=NULL;
    if ((lista->cedula_paciente==cedula))
    {
        cita_aux=lista;
        lista_citas=lista_citas->sig;
        delete(lista);
    }
    else
    {
        while (lista->sig!=NULL)
        {
            if ((lista->sig->cedula_paciente==cedula))
            {
                cita_sig=lista->sig;
                cita_aux=cita_sig;
                lista->sig=lista->sig->sig;
                delete (cita_sig);              
                break;
            }
            lista=lista->sig;
        }
    }
  
}
