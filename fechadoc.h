#include <iostream>
#include <stdlib.h>
using namespace std;


struct nodo_dia
{
    string dia;
    struct nodo_dia* sig=NULL;
};
struct nodo_hora
{
    int hora;
    bool disponibilidad;
    struct nodo_hora* sig=NULL;
};
typedef struct nodo_dia *semana;
typedef struct nodo_hora *horas;

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
    }
}


semana crearSemana(string dia){
    semana dia_semana;
    dia_semana=new(struct nodo_dia);
    dia_semana->dia=dia;
    dia_semana->sig=NULL;
    return dia_semana;
};
horas crearHoras(int hora){
    horas horas_elemento;
    horas_elemento=new(struct nodo_hora);
    horas_elemento->hora=hora;
    horas_elemento->disponibilidad=true;
    horas_elemento->sig=NULL;
    return horas_elemento;
}
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
