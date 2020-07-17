#include <iostream>
#include <string>
using namespace std;

//Libreria se encarga de tratar todo lo relacionado a las fechas del paciente

//Funcion que se encarga de verificar si un string recibido es equivalente a un entero
//Sirve para asegurarse de que el usuario introduzca solo numeros en las fechas
//Recibe como parametro un string que sera el dia,mes o anio introducido por el usuario
bool verificacionEntero(string linea){
    for (int i = 0; i < linea.size(); i++)
    {
        if (!isdigit(linea[i])){
            return false;
        }
    }
    return true;
}
//Funcion que se encarga de recoger un dia valido. Para ello pide un string, verifica que posea enteros 
//y luego verifica el rango del dia, mayor a 0 y menor o igual 31. 
//Devuelve un entero con dicho dia 
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
    return 0;
}
//Funcion que se encarga de leer el numero de mes que desea introducir el usuario.
//Verifica que la linea de entraada es un entero y que este numero se encuentra entre el rango de numeros de meses
//Devuelve un entero que es equivalente al mes indicado
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
    return 0;
}
//Funcion que se encarga de leer el anio introducido por el usuario
//Valida que el valor introducido sea un entero y cumpla con un rango especifico
//Devuelve un entero con dicho anio
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
    return 0;
}
//Funcion que recibe como parametro un entero que sera el dia o el mes y le anade un 0 para completar el formato de fecha
//Devuelve un string que sera la fecha con el 0, en caso de que el dia o mes sea menor a 10
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
//Funcion booleana que devuelve true en caso de que el anio introducido como parametro sea bisiesto
bool bisiesto(int anio){
    if((anio%400==0) || ((anio%4==0)&&(anio%100 !=0))){
        return true;
    }
    else
    {
        return false;
    }
    
}
//Funcion que se encarga de verificar si la fecha introducida es correcta segun el anio introducido
//Verifica la cantidad de dias que tiene cada mes y si el anio es bisiesto.
//Retorna true en caso de que la fecha sea correcta
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
//Funcion que recibe como parametro el dia, mes y anio y se encarga de que la fecha cumpla el formato establecido xx/xx/xxxx
//Devuelve un string con dicha fecha
string formatoFecha(int d, int m, int a){
    string dia, mes, anio,fechadef;
    dia=cerofecha(d);
    mes=cerofecha(m);
    anio=to_string(a);
    fechadef=dia+"/"+mes+"/"+anio;
    return fechadef;
    
}
//Funcion que se encarga de llamar a funciones anteriores para pedir dia,mes y anio, verificar que la fecha sea correcta
//y luego retornar como un string la fecha con el formato pautado.
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
            return formatoFecha(dia,mes,anio);
            break;
        }
        else
        {
            cout<<"Fecha invalida. Intente de nuevo"<<endl;
            cond=0;
        }
        
    }
    return "";
}
