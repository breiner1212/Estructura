#include <iostream>
#include <malloc.h>
using namespace std;

struct nodo{
    int edad;
    int identificacion;
    nodo *izq;
    nodo *der;
};

struct nodo *raiz, *aux, *aux2, *padre;

int posicionar(){    
    if(aux->edad < aux2->edad){        
        if(aux2->izq==NULL){
            aux2->izq = aux;            
            return 0;
        }
        else {
            aux2 = aux2->izq;
            posicionar();
        }
    } 
    else {
        if(aux2->der==NULL){
            aux2->der = aux;            
            return 0;
        } else {
            aux2 = aux2->der;
            posicionar();
            return 0;
        }
    }
}

int registrar(){
    aux = ((struct nodo *) malloc (sizeof(struct nodo))); 
    cout<<"Registre la edad del Paciente: "<<endl;
    cin>>aux->edad;
    cout<<"Registre el numero de identificacioln del Paciente: "<<endl;
    cin>>aux->identificacion;
    aux->izq = aux->der = NULL;
    if(!raiz){
        raiz = aux;
        aux = NULL;
        free(aux);
    }
    else {        
        aux2 = raiz;
        posicionar();
        aux = NULL;
        free(aux);
    }
    
    return 0;
}

int recorrer(nodo *a) {
     
    if(a->der!=NULL){
        recorrer(a->der);
    }
    cout<<"Edad del Paciente: "<<a->edad<<endl;
    cout<<"Identificacion: "<<a->identificacion<<endl; 
    cout<<"-------------------------"<<endl; 
    
    if(a->izq!=NULL){
        recorrer(a->izq);
    }
    
    return 0;
}

int mostrar(){
    if(raiz){        
        recorrer(raiz);
    }
}
int ubicar(nodo *a, int aguja){
    if(a->identificacion==aguja){
        aux2 = a;
        return 0;
    } else {
        if(a->izq!=NULL){
            ubicar(a->izq, aguja);
        }return 0; 
        
        if(a->der!=NULL){
            ubicar(a->der, aguja);
        }         
    }
    return 0;
}

int buscar(int aguja){
    aux = NULL;
    if(raiz!=NULL){
        aux = raiz;
        ubicar(aux, aguja);
    }
}
int pedirAguja(){
    aux2 = NULL;
    int dato;
    cout<<"Paciente a buscar o eliminar"<<endl;
    cin>>dato;
    buscar(dato);
    if(aux2){
        cout<<"Paciente: "<<endl;
        cout<<" Identificacion: "<< aux2->identificacion <<endl;
        cout<<" Edad: "<< aux2->edad <<endl;
    } else {
        cout<<"El Paciete no fue encontrado"<<endl;
    }
}

int ubicarPadre(nodo *a){
    if((a->izq==aux2)||(a->der==aux2)){
        padre = a;
    }
    else {
        if(a->izq!=NULL){
            ubicarPadre(a->izq);
        } 
        
        if(a->der!=NULL){
            ubicarPadre(a->der);
        }         
    }
}
int eliminar(){
    pedirAguja();
    if(aux2){
        if(aux2!=raiz){
            ubicarPadre(raiz);
            if(padre->izq==aux2){
                padre->izq=NULL;
            } else 
                padre->der = NULL;
        }
        free(aux2);
    }   

}
int main(){
    int opc;
    do{
        cout<<"GESTION DE PACIENTES"<<endl;
        cout<<"1. Registrar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Buscar"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Salir"<<endl;
        cin>>opc;
        switch(opc){
            case 1: registrar(); break;
            case 2: mostrar(); break;
            case 3: pedirAguja(); break;
            case 4: eliminar(); break;
            }
    }while(opc!=5);
    return 0;
}
