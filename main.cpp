#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Nodo{
    int frecuencia;
    int valor;
};

struct ArbolBB{
    Nodo* raiz;
    ArbolBB* subArbolIzq;
    ArbolBB* subArbolDer;
};

Nodo* CrearNodo(int f, int v){
    Nodo* newRaiz = new Nodo();
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


vector<Nodo*> ListaNodos(vector<int> v){
    vector<int> listaF;
    vector<int> listaV;
    listaF=ListaFrecuencias(v);
    listaV=ListaValores(v);
    cout<<"ListaF: ";MostrarLista(listaF);cout<<endl;
    cout<<"ListaV: ";MostrarLista(listaV);cout<<endl;
    vector<Nodo*> listaN;
    for(int i=0;i<listaV.size();i++){
        Nodo* newNodo = CrearNodo(listaF[i], listaV[i]);
        listaN.push_back(newNodo);
    }
    return listaN;
};

void MostrarListaNodos(vector<Nodo*> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]->frecuencia<<":"<<v[i]->valor<<endl;
    }
};

//ARBOL
bool esVacio(ArbolBB* tree){
    if(tree->raiz==NULL){
        return true;
    }
    return false;
};

void preOrden(ArbolBB* tree){
    if (esVacio(tree)!=true){
        cout<<tree->raiz->frecuencia<<"  ";
        if (tree->subArbolIzq!=NULL) {
            preOrden(tree->subArbolIzq);
        }
        if (tree->subArbolDer!=NULL) {
            preOrden(tree->subArbolDer);
        }
    }
};

ArbolBB* CrearArbol(Nodo* item, ArbolBB* left, ArbolBB* right){
    ArbolBB* newArbol = new ArbolBB();
    newArbol->raiz=item;
    newArbol->subArbolIzq=left;
    newArbol->subArbolDer=right;
    return newArbol;
};

void Agregar(ArbolBB* tree, Nodo* newItem) {
    if (esVacio(tree)==true) {
        tree->raiz = newItem;
    } else {
        if (newItem->frecuencia < tree->raiz->frecuencia) {
            if (tree->subArbolIzq==NULL) {
                tree->subArbolIzq = CrearArbol(newItem, NULL, NULL);
            } else {
                Agregar(tree->subArbolIzq, newItem);
            }
        } else if (newItem->frecuencia > tree->raiz->frecuencia) {
            if (tree->subArbolDer==NULL) {
                tree->subArbolDer = CrearArbol(newItem, NULL, NULL);
            } else {
                Agregar(tree->subArbolDer, newItem);
            }
        } else {
            cout<<"Ya existe el item: "<<newItem;
        }
    }
};

Nodo* generarArbolHuffman(Nodo* listaFrecuencias){
    return NULL;
};

string codificar(int x){
    return NULL;
};

int decodificar(string x){
    return 0;
};

int main(){
    vector<int> val= {1,2,2,1,3,4,2,1,2,3};
    val = OrdenarLista(val);
    MostrarLista(val);
    cout<<endl;
    vector<Nodo*> lF;
    lF = ListaNodos(val);
    cout<<endl;
    cout<<"Lista Frecuencia y Valor"<<endl;MostrarListaNodos(lF);
    ArbolBB* pArbol = new ArbolBB();
    Nodo* n1=CrearNodo(3,1);
    Nodo* n2=CrearNodo(4,2);
    Nodo* n3=CrearNodo(2,3);
    Nodo* n4=CrearNodo(1,4);
    Agregar(pArbol, n1);
    Agregar(pArbol, n2);
    Agregar(pArbol, n3);
    Agregar(pArbol, n4);
    cout<<"\nArbol en preOrden: ";preOrden(pArbol);cout<<endl;
}
