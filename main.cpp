#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Nodo{
    int frecuencia;
    int valor;
    Nodo* sigNodo=NULL;
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


Nodo* ListaNodos(vector<int> v){
    int frec = 0;
    int valor = v[0];
    Nodo* nodoPrevio = NULL;
    Nodo* primerNodo = new Nodo();
    for(int i=0; i<v.size(); i++){
        if(v[i]==valor){
            frec++;
        }else{
            Nodo* nuevoNodo = new Nodo();
            nuevoNodo->valor = valor;
            nuevoNodo->frecuencia = frec;
            valor = v[i];
            frec = 1;
            if(nodoPrevio != NULL){
                nodoPrevio->sigNodo = nuevoNodo;
            }else{
                primerNodo = nuevoNodo;
            }
            nodoPrevio = nuevoNodo;
        }
        if(i == v.size()-1){
            Nodo* nuevoNodo = new Nodo();
            nuevoNodo->valor = valor;
            nuevoNodo->frecuencia = frec;
            nodoPrevio->sigNodo = nuevoNodo;
        }
    }
    return primerNodo;
};

void MostrarListaNodos(Nodo* listaN){
    Nodo* pNodo = listaN;
    while(pNodo!=NULL){
        cout << pNodo->frecuencia << ":" << pNodo->valor << endl;
        pNodo = pNodo->sigNodo;
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

vector<ArbolBB*> ListaArboles(vector<Nodo*> v){
    vector<ArbolBB*> listaA;
    for(int i=0;i<v.size();i++){
        ArbolBB* newArbol = CrearArbol(v[i], NULL, NULL);
        listaA.push_back(newArbol);
    }
    return listaA;
};

void MostrarListaArboles(vector<ArbolBB*> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]->raiz->frecuencia<<":"<<v[i]->raiz->valor<<endl;
    }
};

vector<ArbolBB*> OrdenarListaArbol(vector<ArbolBB*> v){
    for(int i=0;i<v.size()-1;i++){
        for(int j=i+1;j<v.size();j++){
            if(v[i]->raiz->frecuencia > v[j]->raiz->frecuencia){
                ArbolBB* temp=v[i];
                v[i]=v[j];
                v[j]=temp;
            }
        }
    }
    return v;
};

ArbolBB* GenerarArbolHuffman(vector<ArbolBB*> v){
    if(v.empty()){
        return NULL;
    }else{
        while(v.size()!=1){
            v=OrdenarListaArbol(v);
            int suma= (v[0]->raiz->frecuencia)+(v[1]->raiz->frecuencia);
            ArbolBB* newArbol=CrearArbol(CrearNodo(suma, 0), v[0], v[1]);
            v.erase(v.begin(),v.begin()+2);
            v.push_back(newArbol);
        }
        return v[0];
    }
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
    Nodo* lF;
    lF = ListaNodos(val);
    cout<<endl;
    vector<ArbolBB*> lA;
    lA = ListaArboles(lF);
    ArbolBB* ArbolH=GenerarArbolHuffman(lA);
    MostrarListaArboles(lA);
    cout<<"---------"<<endl;
    cout<<ArbolH->r    //cout<<"\nArbol en preOrden: ";preOrden(pArbol);cout<<endl;aiz->frecuencia<<":"<<ArbolH->raiz->valor;

}
