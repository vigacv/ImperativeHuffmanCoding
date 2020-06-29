#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Raiz{
    int frecuencia;
    int valor;
    Raiz* nodoLeft;
    Raiz* nodoRight;
};

struct ArbolBB{
    Raiz* item;
    ArbolBB* subArbolIzq;
    ArbolBB* subArbolDer;
};

void crearNodo(int f, int v){
    Raiz* newNodo = new Raiz();
    newNodo->frecuencia=f;
    newNodo->valor=v;
    newNodo->nodoLeft=NULL;
    newNodo->nodoRight=NULL;
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

vector<int> ListaFrecuencia(vector<int> v){
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
    vector<int> val= {1,2,2,1,3,4,2,1,2,3};
    val = OrdenarLista(val);
    MostrarLista(val);
    cout<<endl;
    vector<int> fre;
    fre=ListaFrecuencia(val);
    MostrarLista(fre);
}
