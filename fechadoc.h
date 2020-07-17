#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//Libreria que se encarga de trabajar las horas y dias en las que trabaja el doctor

//Estructura que almacena las horas y su disponibilidad
struct nodo_hora
{
    int hora;
    bool disponibilidad;
    struct nodo_hora* sig=NULL;
};
typedef struct nodo_hora *horas;
//Estructura que guarda los dias, sus horas y su respectiva disponbilidad
struct nodo_dia
{
    string dia;
    bool disponibilidad;
    horas horas_dis;
    struct nodo_dia* sig=NULL;
};
typedef struct nodo_dia *semana;
//Funcion que recibe como parametro un dia y dependiendo del mismo retorna su correspondiente en letras
string diasSemana(int dia){
    switch (dia)
    {
    case 1:
        return "Lunes";  
        break;
    case 2:
        return "Martes";  
        break;
    case 3:
        return "Miercoles";  
        break;    
    case 4:
        return "Jueves";  
        break;
    case 5:
        return "Viernes";  
        break;
    case 6:
        return "Sabado";  
        break;
    case 0:
        return "Domingo";  
        break;
    default:
        return "";
        break;
    }
}
//Funcion que crea un nodo dia y lo retorna
//Recibe como parametro un string que indica el dia de la semana

semana crearSemana(string dia){
    semana dia_semana;
    dia_semana=new(struct nodo_dia);
    dia_semana->dia=dia;
    dia_semana->disponibilidad=true;
    dia_semana->sig=NULL;
    return dia_semana;
};
//Funcion que crea un nodo hora y lo retorna.
//Recibe como parametro un entero que va a ser cada hora del nodo
horas crearHoras(int hora){
    horas horas_elemento;
    horas_elemento=new(struct nodo_hora);
    horas_elemento->hora=hora;
    horas_elemento->disponibilidad=true;
    horas_elemento->sig=NULL;
    return horas_elemento;
}
//Funcion que se encarga de crear la lista semana
//Recibe como parametros la lista de dias/semana por referencia y un string del dia para crear el nodo
void crearListasemana(semana &semana_lab,string dia)
{
    semana aux1,aux2;
    aux1=crearSemana(dia);
    if (semana_lab==NULL){
        semana_lab=aux1;
    }
    else
    {
        aux2=semana_lab;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=aux1;
    }
    
}
//Funcion que se encarga de crear la lista horas
//Recibe como parametro la lista de horas por referencia y el entero para crear el nodo de hora
void crearListahoras(horas &lista_horas,int hora)
{
    horas aux1,aux2;
    aux1=crearHoras(hora);
    if (lista_horas==NULL){
        lista_horas=aux1;
    }
    else
    {
        aux2=lista_horas;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=aux1;
    }
    
}
//Funcion que recibe un string con las  horas leidas en el archivo y las separa para crear la lista de horas
//Es llamada en la creacion del doctor
//Recibe como parametro la lista de horas por referencia y un string que sera la linea leida
void asingarHoras(horas &lista_horas,string linea){
    int valor;
    string copia="";
    for (int i = 0; i < linea.size(); i++)
    {
        if(linea[i]!=',')
        {
            copia=copia+linea[i];
        }
        else
        {
            valor=atoi(copia.c_str());
            crearListahoras(lista_horas,valor);
            copia="";        
        }
    }
    
}
//Funcion que recibe un string con los dias de la semana y los separa para crear la lista de dias
//Es llamada en la creacion del doctor
//Recibe como parametro un string que es la linea leida del archivo y la lista de dias por referencia
void asignarSemana(string linea, semana &lista_semana){
    int valor;
    for (int i = 0; i < linea.size(); i++)
    {
        if(i%2==0)
        {
            valor=linea[i]-'0';
            crearListasemana(lista_semana,(diasSemana(valor)));
        }
    }
    
}
//Funcion que se encarga de recorrer la lista de horas y devuelve su contenido como un string
//Recibe como parametro la lista de horas
string mostrarHoras(horas horas_dia){
    horas recorrido;
    string aux;
    string horas_t="";
    recorrido=horas_dia;
    while (recorrido!=NULL)
    {
        if(recorrido->disponibilidad==true){
            aux=to_string(recorrido->hora);
            if (recorrido->sig!=NULL)
            {
                horas_t=horas_t+aux+",";
            }
            else
            {
                horas_t=horas_t+aux;
            }   
        }
        recorrido=recorrido->sig;
    
    }
    return horas_t;
    
}
//Funcion que se encarga de leer la lista de dias/semana y devuelve un string con todos los dias juntos
//Recibe como parametro la lista de dias.
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