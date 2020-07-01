#include <iostream>
#include <string>
#include <fstream>
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

string lineasTextoExtensas(){
    string linea;
    getline(cin,linea);
    return linea;
}
int repetirEntero(){
    string opcion;
    bool cond=false;;
    while (!cond)
    {
        cin>>opcion;
        if (verificacionEntero(opcion))
        {
            cond=true;
        }
        else
        {
            cout<<"Valor invalido."<<endl;
        }  
    }
    return stoi(opcion);
}
historia_paciente crearHistoria(int cedula){
    historia_paciente historia;
    historia=new(struct nodo_historia);
    cout<<"Historia de paciente:"<<endl;
    historia->cedula_paciente=cedula;
    cout<<"Fecha consulta: "<<endl;
    historia->fconsulta=fechaPaciente();
    cin.ignore(256,'\n');

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
    dia=atoi(digito.c_str());
    digito="";
    for (int i =3; i<5;i++){
        digito=digito+fecha[i];
    }
    mes=atoi(digito.c_str());
    digito="";
    for (int i=6; i<10;i++){
        digito=digito+fecha[i];
    }
    anio=atoi(digito.c_str());

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

void listaHistoriaParemetro(historia_paciente &historial,historia_paciente historia_modificada){
    historia_paciente aux1,aux2;
    aux1=historial;

    while ((aux1!=NULL) && (fechaReciente(aux1->fconsulta,historia_modificada->fconsulta)))
    {
        aux2=aux1;
        aux1=aux1->sig;
    }
    if (historial==aux1){
        historial=historia_modificada;
    }
    else
    {
        aux2->sig=historia_modificada;
    }
    historia_modificada->sig=aux1;
    
}
bool existeArchivoHistoria(int cedula){
    fstream archivo;
    string cedula_archivo;
    cedula_archivo="Pacientes/"+to_string(cedula)+".txt";
    archivo.open(cedula_archivo,ios::in);
    if(!archivo.fail())
        {
            return true;
        }
    else
    {
        return false;
    }
    

}
void crearArchivoHistorial(historia_paciente historial){
    fstream archivo;
    string cedula_archivo;
    historia_paciente recorrido=historial;
    cedula_archivo="Pacientes/"+to_string(historial->cedula_paciente)+".txt";
    archivo.open(cedula_archivo,ios::out);
    if(!archivo.fail())
        {
            while(recorrido !=NULL){
                archivo<<recorrido->fconsulta<<endl;
                archivo<<recorrido->sintomas<<endl;
                archivo<<recorrido->diagnostico<<endl;
                archivo<<recorrido->recipe<<endl;
                archivo<<recorrido->examenes<<endl;
                archivo<<recorrido->comentario<<endl;
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
void crearListaHistoriaOrdenada(historia_paciente &historial,int cedula){
    historia_paciente aux1,aux2;
    historia_paciente nueva_historia=crearHistoria(cedula);
    aux1=historial;

    while ((aux1!=NULL) && (fechaReciente(aux1->fconsulta,nueva_historia->fconsulta)) )
    {
        aux2=aux1;
        aux1=aux1->sig;
    }
    if (historial==aux1){
        historial=nueva_historia;
    }
    else
    {
        aux2->sig=nueva_historia;
    }
    nueva_historia->sig=aux1;
    crearArchivoHistorial(historial);
}

void mostrarListaHistoria(historia_paciente lista){
    historia_paciente recorrido;
    recorrido=lista;
    while(recorrido != NULL){
        //cout<<recorrido->cedula_paciente<<endl;
        cout<<"Fecha consulta: "<<recorrido->fconsulta<<endl;
        cout<<"Sintomas: "<<recorrido->sintomas<<endl;
        cout<<"Diagnostico: "<<recorrido->diagnostico<<endl;
        cout<<"Recipe: "<<recorrido->recipe<<endl;
        cout<<"Examenes: "<<recorrido->examenes<<endl;
        cout<<"Comentarios: "<<recorrido->comentario<<endl;
        recorrido=recorrido->sig;
    }
}
void crearListaHistoriaArchivo(historia_paciente &lista_historia, historia_paciente historia_reciente)
{
    historia_paciente aux2;
    if (lista_historia==NULL){
        lista_historia=historia_reciente;
    }
    else
    {
        aux2=lista_historia;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=historia_reciente;
    }
}  

historia_paciente leerArchivoHistoria(int cedula){
    fstream archivo;
    string linea,cedula_archivo;
    historia_paciente historia_reciente,aux2;
    aux2=NULL;
    cedula_archivo="Pacientes/"+to_string(cedula)+".txt";
    archivo.open(cedula_archivo,ios::in);
            while(!archivo.eof())
            {
                historia_reciente=new(struct nodo_historia);
                getline(archivo,historia_reciente->fconsulta);
                getline(archivo,historia_reciente->sintomas);
                getline(archivo,historia_reciente->diagnostico);
                getline(archivo,historia_reciente->recipe);
                getline(archivo,historia_reciente->examenes);
                getline(archivo,historia_reciente->comentario);
                historia_reciente->sig=NULL;
                crearListaHistoriaArchivo(aux2,historia_reciente);
                getline(archivo,linea);
            }
            return aux2;
            

}
void imprimirUltimaHistoria(historia_paciente historial)
{
    historia_paciente recorrido=historial;
    cout <<"Historial"<<endl;
    cout <<"1.Fecha consulta: "<<recorrido->fconsulta<<endl;
    cout <<"2.Sintomas : "<<recorrido->sintomas<<endl;
    cout <<"3.Diagnostico : "<<recorrido->diagnostico<<endl;
    cout <<"4.Recipe : "<<recorrido->recipe<<endl;
    cout <<"5.Examenes: "<<recorrido->examenes<<endl;
    cout <<"6.Comentario : "<<recorrido->comentario<<endl;
}

void modificarUltimaHistoria(historia_paciente historia){
    cout<<"Indique el numero de campo a modificar: "<<endl;
    int opcion=repetirEntero();
    cin.ignore();
    while (opcion!=0)
    {
        switch (opcion)
        {
        case 0:
            break;
        case 1:
            cout<<"Fecha consulta: "<<endl;
            historia->fconsulta=fechaPaciente();
            cin.ignore();
            break;
        case 2:
            cout<<"Sintomas: ";
            historia->sintomas=lineasTextoExtensas();
            cout<<endl;
            break;
        case 3:
            cout<<"Diagnostico: ";
            historia->diagnostico=lineasTextoExtensas();
            cout<<endl;
            break;
        case 4:
            cout<<"Recipe: ";
            historia->recipe=lineasTextoExtensas();
            cout<<endl;
            break;
        case 5:
            cout<<"Examenes: ";
            historia->examenes=lineasTextoExtensas();
            cout<<endl;
            break;
        case 6:
            cout<<"Comentario: ";
            historia->comentario=lineasTextoExtensas();
            cout<<endl;
            break; 
        default:
            cout<<"Campo invalido"<<endl;
            break;
        }
        cout<<"Si desea modificar otro campo, coloque el numero, sino cooque 0: ";
        opcion=repetirEntero();
        cin.ignore();
    }
}  
void borrarHistoria(historia_paciente &lista_historia){
    historia_paciente aux=NULL;
    historia_paciente lista=lista_historia;
    aux=lista;
    lista_historia=lista_historia->sig;
    delete(lista);
}
historia_paciente copiarHistoria(historia_paciente historial){
    historia_paciente aux1,copia;
    copia=historial;
    aux1=new (struct nodo_historia);
    aux1->fconsulta=copia->fconsulta;
    aux1->sintomas=copia->sintomas;
    aux1->diagnostico=copia->diagnostico;
    aux1->recipe=copia->recipe;
    aux1->examenes=copia->examenes;
    aux1->comentario=copia->comentario;
    aux1->sig=NULL;
    return aux1;
}
void modificarHistoria(historia_paciente  &lista_historia){
    historia_paciente aux=lista_historia;
    historia_paciente historia_modificar=copiarHistoria(aux);
    imprimirUltimaHistoria(historia_modificar);
    cout<<"*********************"<<endl;
    modificarUltimaHistoria(historia_modificar);
    cout<<"Los datos del paciente fueros modificados correctamente"<<endl;
    cout<<"**********************"<<endl;
    imprimirUltimaHistoria(historia_modificar);
    cout<<"**********************"<<endl;
    if (historia_modificar->fconsulta!=aux->fconsulta){
        borrarHistoria(lista_historia);
        listaHistoriaParemetro(lista_historia,historia_modificar);
    }
    crearArchivoHistorial(lista_historia);
}

//verificar si las fechas no son iguales
/*

void crearListaHistoriaOrdenada(historia_paciente &historial,int cedula){
    historia_paciente aux1,aux2;
    bool cond=false;
    historia_paciente nueva_historia=crearHistoria(cedula);
    aux1=historial;
    if (historial==NULL){
        historial=nueva_historia;
    }
    else
    {
        if(fechaReciente(nueva_historia->fconsulta,aux1->fconsulta)){//Si la fecha consulta es mas reciente que la de la lista
            cout<<"Si"<<endl;
            aux2=historial;
            nueva_historia->sig=aux2;
            historial=nueva_historia;
            cond=true;
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
                 //historial=aux1;
             }
        
        
         }
    }
}
*/