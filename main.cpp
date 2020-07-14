#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
using namespace std;
unsigned t0, t1;


struct Nodo{
    int frecuencia;
    int valor;
    Nodo* sigNodo=NULL;
};

struct ArbolBB{
    int frecuencia;
    int valor;
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
    for(int i=0;i<v.size()-1;i++){
        cout<<v[i]<<", ";
    }
    cout<<v[v.size()-1]<<" ";
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
    if(tree==NULL){
        return true;
    }
    return false;
};

void preOrden(ArbolBB* tree){
    if (esVacio(tree)!=true){
        cout<<tree->frecuencia<<"  ";
        if (tree->subArbolIzq!=NULL) {
            preOrden(tree->subArbolIzq);
        }
        if (tree->subArbolDer!=NULL) {
            preOrden(tree->subArbolDer);
        }
    }
};

ArbolBB* CrearArbol(int frec, int val, ArbolBB* left, ArbolBB* right){
    ArbolBB* newArbol = new ArbolBB();
    newArbol->frecuencia = frec;
    newArbol->valor = val;
    newArbol->subArbolIzq=left;
    newArbol->subArbolDer=right;
    return newArbol;
};

vector<ArbolBB*> ListaArboles(Nodo* v){
    vector<ArbolBB*> listaA;
    Nodo* pV = v;
    while(pV != NULL){
        ArbolBB* newArbol = CrearArbol(pV->frecuencia,pV->valor, NULL, NULL);
        listaA.push_back(newArbol);
        pV = pV->sigNodo;
    }
    return listaA;
};

void MostrarListaArboles(vector<ArbolBB*> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]->frecuencia<<":"<<v[i]->valor<<endl;
    }
};

vector<ArbolBB*> OrdenarListaArbol(vector<ArbolBB*> v){
    for(int i=0;i<v.size()-1;i++){
        for(int j=i+1;j<v.size();j++){
            if(v[i]->frecuencia > v[j]->frecuencia){
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
            int suma= (v[0]->frecuencia)+(v[1]->frecuencia);
            ArbolBB* newArbol=CrearArbol(suma,-1, v[0], v[1]); //-1 es *
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
        if(arbol->valor == x){
            return true;
        }else{
            return estaEnArbol(x,arbol->subArbolIzq) || estaEnArbol(x,arbol->subArbolDer);
        }
    }
}

string codificando(int x, ArbolBB* pArbol, string cod){
    if(pArbol->valor == x){
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
    if(x>=0){
        return codificando(x, pArbol, "");
    }
    return "No se encuentra el valor "+to_string(x);
};

string Decodificar(string cod, ArbolBB* arbolHuff){
    ArbolBB* pArbol = arbolHuff;
    bool v = false;
    for(int i=0; i<cod.size(); i++){
        if(cod[i] == '0'){
            if(pArbol->subArbolIzq!=NULL){
                pArbol = pArbol->subArbolIzq;
            }else{
                v = true;
                break;
            }
        }else if (cod[i] == '1'){
            if(pArbol->subArbolDer!=NULL){
                pArbol = pArbol->subArbolDer;
            }else{
                v = true;
                break;
            }
        }else{
            return "No se puede decodificar";
        }
    }
    if(v == true){
        return "No se puede decodificar";
    }else{
        if(pArbol->valor !=-1){
            return to_string(pArbol->valor);
        }else{
            return "*";
        }
    }
};

vector<int> GenerarLista(){
    vector<int> newLista = vector<int>();
    srand(time(NULL)); //para reiniciar el rand
    //int tam = rand() % 1000 +5000; // %31+90 = [90-120]
    int tam=1000; //para Tam 10/50/100/200/500/700/1000 fijos
    cout<<"Tamano lista: "<<tam<<endl;
    for(int i=0;i<tam;i++){
        newLista.push_back(rand() % 127+0); // [0-127]
    }
    return newLista;
};

int main(){

    vector<int> val= {1,2,2,1,3,4,2,1,2,3};
    //vector<int> val = GenerarLista();
    cout<<"Lista inicial: [ "; MostrarLista(val);
    cout<<"]"<<endl<<endl;
    Nodo* lF;   lF = ListaNodos(val);
    vector<ArbolBB*> lA;    lA = ListaArboles(lF);
    cout<<"Lista Arbol"<<endl; MostrarListaArboles(lA);
    cout<<"---------"<<endl;
    cout<<"\n*(t)Empieza tiempo de procesamiento\n"<<endl;
    ArbolBB* ArbolH=GenerarArbolHuffman(lA);
    cout<<"Raiz final = "<<ArbolH->frecuencia<<":"<<ArbolH->valor << endl;
    cout<<"\n*(t)Termina tiempo de procesamiento\n"<<endl;
    int valor; string cod;
    cout<<"\nCodificar: ";
    while( ( cin>>valor ).fail() ) { //comprobamos los flags de error con la referencia que devuelve el operador
        cin.clear(); //reseteamos los flags
        fflush(stdin); //limpio buffer de entrada
        cout<<"Debe ingresar solo numeros: ";
    }
    cin.clear(); //reseteamos los flags
        fflush(stdin); //limpio buffer de entrada
    cout<<"\n* "<<valor<<" codificado --> "<<Codificar(valor,ArbolH)<<endl;
    cout<<"\nDecodificar: ";
    cin>>cod;
    cout<<"* '"<<cod<<"' decodificado --> "<<Decodificar(cod, ArbolH)<<endl;
    cout<<"\n";
}
