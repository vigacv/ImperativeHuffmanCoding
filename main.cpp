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

Nodo* ListaNodos(vector<int> v){
    v = OrdenarLista(v);
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

vector<ArbolBB*> ListaArboles(Nodo* v){
    vector<ArbolBB*> listaA;
    Nodo* pV = v;
    while(pV != NULL){
        ArbolBB* newArbol = CrearArbol(pV, NULL, NULL);
        listaA.push_back(newArbol);
        pV = pV->sigNodo;
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


bool estaEnArbol(int x, ArbolBB* arbol){
    if(arbol == NULL){
        return false;
    }else{
        if(arbol->raiz->valor == x){
            return true;
        }else{
            return estaEnArbol(x,arbol->subArbolIzq) || estaEnArbol(x,arbol->subArbolDer);
        }
    }
}

string codificando(int x, ArbolBB* pArbol, string cod){
    if(pArbol->raiz->valor == x){
        return cod;
    }else{
        if(estaEnArbol(x, pArbol->subArbolIzq)){
            return codificando(x, pArbol->subArbolIzq,(cod+="0"));
        }else if(estaEnArbol(x, pArbol->subArbolDer)){
            return codificando(x, pArbol->subArbolDer,(cod+="1"));
        }else{
            return "No se encuentra el valor "+to_string(x);
        }
    }
};

string Codificar(int x, ArbolBB* pArbol){
    if(x==0){
        return "No se encuentra el valor 0";
    }
    return codificando(x, pArbol, "");
};

string Decodificar(string cod, ArbolBB* arbolHuff){
    ArbolBB* pArbol = arbolHuff;
    for(int i=0; i<cod.size(); i++){
        if(cod[i] == '0'){
            pArbol = pArbol->subArbolIzq;
        }else if (cod[i] == '1'){
            pArbol = pArbol->subArbolDer;
        }
    }
    if(pArbol->raiz->valor != 0){
        return to_string(pArbol->raiz->valor);
    }else{
        return "*";
    }

};

int main(){
    vector<int> val= {1,2,2,1,3,4,2,1,2,3};
    cout<<"Lista inicial: [ "; MostrarLista(val);
    cout<<"]"<<endl<<endl;
    Nodo* lF;   lF = ListaNodos(val);
    vector<ArbolBB*> lA;    lA = ListaArboles(lF);
    cout<<"Lista Arbol"<<endl; MostrarListaArboles(lA);
    cout<<"---------"<<endl;
    ArbolBB* ArbolH=GenerarArbolHuffman(lA);
    cout<<"Raiz final = "<<ArbolH->raiz->frecuencia<<":"<<ArbolH->raiz->valor << endl;
    cout<<"Codificar 4 --> "<<Codificar(4,ArbolH)<<endl;
    cout<<"Decodificar 110 --> "<< Decodificar("1110", ArbolH) << endl;
}
