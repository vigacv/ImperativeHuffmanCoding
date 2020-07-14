#include <iostream>
#include <vector>
using namespace std;

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
    Nodo* nodoTemp = NULL;
    Nodo* primerNodo = new Nodo();
    for(int i=0; i<v.size(); i++){
        if(v[i]==valor){
            frec++;
        }else{
            Nodo* nuevoNodo = CrearNodo(valor, frec);
            valor = v[i]; //se asigna el siguiente valor a contar
            frec = 1; //se reinicia la frecuencia
            if(nodoTemp != NULL){
                nodoTemp->sigNodo = nuevoNodo;
            }else{
                primerNodo = nuevoNodo;
            }
            nodoTemp = nuevoNodo;
        }
        if(i == v.size()-1){
            Nodo* nuevoNodo = CrearNodo(valor, frec);
            nodoTemp->sigNodo = nuevoNodo;
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

//ARBOL HUFFMAN
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

//CODIFICAR
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
    return "No se puede encontrar valores negativos";
};

//DECODIFICAR
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
        if(pArbol->valor!=-1){
            return to_string(pArbol->valor);
        }else{
            return "No es un codigo prefijo";
        }
    }
};

//MAIN
int main(){
    vector<int> val= {1,2,2,1,3,4,2,1,2,3};
    cout<<"Lista inicial: [ "; MostrarLista(val); cout<<"]\n"<<endl;
    Nodo* lF;   lF = ListaNodos(val);
    vector<ArbolBB*> lA; lA = ListaArboles(lF);
    cout<<"Lista Arbol\nf v\n---"<<endl; MostrarListaArboles(lA);
    cout<<"---------"<<endl;
    ArbolBB* ArbolH=GenerarArbolHuffman(lA);
    cout<<"Raiz final = "<<ArbolH->frecuencia<<":"<<ArbolH->valor << endl;
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
