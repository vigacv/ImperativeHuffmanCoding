#include <iostream>
#include <string>
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
            Nodo* nuevoNodo = CrearNodo(valor, frec);
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
            Nodo* nuevoNodo = CrearNodo(valor, frec);
            nodoPrevio->sigNodo = nuevoNodo;
        }
    }
    return primerNodo;
};

//ARBOL
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
    if(pArbol->valor != -1){
        return to_string(pArbol->valor);
    }else{
        return "*";
    }

};

vector<int> GenerarLista(int tam){
    vector<int> newLista = vector<int>();
    srand(time(NULL)); //para reiniciar el rand
    for(int i=0;i<tam;i++){
        newLista.push_back(rand() % 127+0); // [0-127]
    }
    return newLista;
};

int main(){
    int tam=-1, reps;
    while(tam!=0){
        cout << "Tamano de la entrada: " << endl;
        cin >> tam;
        reps=1000;
        int timeTotal=0;
        for(int i=0; i<reps; i++){
            vector<int> val = GenerarLista(tam);
            t0=clock();

            Nodo* lF;   lF = ListaNodos(val);
            vector<ArbolBB*> lA;    lA = ListaArboles(lF);
            ArbolBB* ArbolH=GenerarArbolHuffman(lA);

            t1 = clock();
            double time = (double(t1-t0)/CLOCKS_PER_SEC); //mide en segundos
            time=time*1000; //transforma a ms
            timeTotal+=time; //acumula
            //cout << "Execution Time: " << time <<" ms"<<endl;
            //cout << endl;
        }
        int timeProm = timeTotal/reps;
        cout<<tam<<" - Tiempo promedio: "<<timeProm<<" ms"<<endl;
    }

}
