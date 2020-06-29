#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Raiz{
    int frecuencia;
    int valor;
};

struct ArbolBB{
    Raiz* item;
    ArbolBB* subArbolIzq;
    ArbolBB* subArbolDer;
};

Raiz* CrearRaiz(int f, int v){
    Raiz* newRaiz = new Raiz();
    newRaiz->frecuencia=f;
    newRaiz->valor=v;
    return newRaiz;
};
//LISTAS
void MostrarLista(vector<int> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
};

vector<int> OrdenarLista(vector<int> v){
    for(int i=0;i<v.size()-1;i++){
        for(int j=i+1;j<v.size();j++){
            if(v[i]>v[j]){
                int temp=v[i];
                v[i]=v[j];
                v[j]=temp;
            }
        }
    }
    return v;
};

vector<int> ListaFrecuencias(vector<int> v){
    vector<int> newLista;
    OrdenarLista(v);
    int cont=0;
    int cant=0;
    int valor=v[cont];
    while(cont!=v.size()){
        if(v[cont]==valor){
            cant++;
            cont++;
        }else{
            newLista.push_back(cant);
            valor=v[cont];
            cant=0;
        }
    }
    newLista.push_back(cant);
    return newLista;
};

vector<int> ListaValores(vector<int> v){
    vector<int> newLista;
    OrdenarLista(v);
    int cont=0;
    int valor=v[cont];
    while(cont!=v.size()){
        if(v[cont]==valor){
            cont++;
        }else{
            newLista.push_back(valor);
            valor=v[cont];
        }
    }
    newLista.push_back(valor);
    return newLista;
};


vector<Raiz*> ListaNodos(vector<int> v){
    vector<int> listaF;
    vector<int> listaV;
    listaF=ListaFrecuencias(v);
    listaV=ListaValores(v);
    cout<<"ListaF: ";MostrarLista(listaF);cout<<endl;
    cout<<"ListaV: ";MostrarLista(listaV);cout<<endl;
    vector<Raiz*> listaN;
    for(int i=0;i<listaV.size();i++){
        Raiz* newRaiz = CrearRaiz(listaF[i], listaV[i]);
        listaN.push_back(newRaiz);
    }
    return listaN;
};

void MostrarListaNodos(vector<Raiz*> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]->frecuencia<<":"<<v[i]->valor<<endl;
    }
};

//ARBOL
bool esVacio(ArbolBB* tree){
    if(tree->item==NULL){
        return true;
    }
    return false;
};

void preOrden(ArbolBB* tree){
    //if (esVacio(ArbolBB* tree->item)!=true){
      //  cout<<tree->item->frecuencia<<"  ";
        //if (subArbolIzq != null) {
          //  preOrden(subArbolIzq);
        //
        //if (subArbolDer != null) {
          //  preOrden(subArbolDer);
        //}
    //}
};

Raiz* generarArbolHuffman(Raiz* listaFrecuencias){
    return NULL;
};

string codificar(int x){
    return NULL;
};

int decodificar(string x){
    return NULL;
};

int main(){
    vector<int> val= {1,2,2,1,9,5,5,3,4,7,2,1,2,3};
    val = OrdenarLista(val);
    MostrarLista(val);
    cout<<endl;
    vector<Raiz*> lF;
    lF = ListaNodos(val);
    cout<<endl;
    cout<<"Lista Frecuencia y Valor"<<endl;MostrarListaNodos(lF);
}
