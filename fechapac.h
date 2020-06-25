#include <iostream>
using namespace std;

bool verificacionEntero(string linea){
    for (int i = 0; i < linea.size(); i++)
    {
        if (!isdigit(linea[i])){
            return false;
        }
    }
    return true;
}
int diaNacimiento(){
    string dia;
    int cond=0;
    while (cond==0){
        cout<<"Dia: ";
        cin>>dia;
        cout<<endl;
        if(verificacionEntero(dia) && (stoi(dia)<=31) && (stoi(dia)>0)){
            return stoi(dia);
        }
        else
        {
            cout<<"Dia invalido. Intenta de nuevo"<<endl;
            cond=0;
        }
        
    }
}
int mesNacimiento(){
    string mes;
    int cond=0;
    while (cond==0){
        cout<<"Mes: ";
        cin>>mes;
        cout<<endl;
        if(verificacionEntero(mes) && (stoi(mes)<=12) && (stoi(mes)>0)){
            return stoi(mes);
        }
        else
        {
            cout<<"Mes invalido. Intenta de nuevo"<<endl;
            cond=0;
        }
        
    }
}
int anioNacimiento(){
    string anio;
    int cond=0;
    while (cond==0){
        cout<<"Anio: ";
        cin>>anio;
        cout<<endl;
        if(verificacionEntero(anio) && (stoi(anio)<=9999) && (stoi(anio)>1900)){
            return stoi(anio);
        }
        else
        {
            cout<<"Anio invalido. Intenta de nuevo"<<endl;
            cond=0;
        }
        
    }
}
string cerofecha(int fecha){
    string agregado="";
    if (fecha<10){
        agregado="0"+to_string(fecha);
        return agregado;
    }
    else
    {
        return to_string(fecha);
    }
    
}

bool bisiesto(int anio){
    if((anio%400==0) || ((anio%4==0)&&(anio%100 !=0))){
        return true;
    }
    else
    {
        return false;
    }
    
}
bool fechaCorrecta(int dia, int mes, int anio){
    if (mes<=7){
        if (mes%2!=0){
            if (dia<=31){
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (mes==2){
                if(((bisiesto(anio))&&(dia<=29))||(!bisiesto(anio)&&(dia<=28))){
                    return true;
                }
                else
                {
                    return false;
                }
                
            }
            else
            {
                if (dia<=30){
                    return true;
                }
                else
                {
                    return false;
                }
                
            }
            
        }
           
    }
    else
    {
        if (mes%2!=0){
           if(dia<=30){
               return true;
           }
           else
           {
               return false;
           }
           
        }
        else
        {
            if(dia<=31){
                return true;
            }
            else
            {
                return false;
            }
            
            
        }
        
    }
    
}
string fechaPaciente(){
    string fechadef="";
    int dia,mes,anio;
    int cond=0;
    while (cond==0)
    {
        dia=diaNacimiento();
        mes=mesNacimiento();
        anio=anioNacimiento();
        if(fechaCorrecta(dia,mes,anio)){
            fechadef=to_string(dia)+"/"+to_string(mes)+"/"+to_string(anio);
            return fechadef;
        }
        else
        {
            cout<<"Fecha invalida. Intente de nuevo"<<endl;
            cond=0;
        }
        
    }
}