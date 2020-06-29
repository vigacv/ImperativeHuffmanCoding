# ImperativeHuffmanCoding
Una implementación en C++ de la codificación Huffman usando el paradigma imperativo
PSEUDOCODIGO:
Algoritmo Huffman(valores):
//valores es una lista de números
Precondiciones: Existe una función llamada ordenarLista que permite ordenar una lista de números de menor a mayor
INICIO
1. valores  ordenarLista(valores)
2. listaFrecuencias  listaFrecuencias(valores)
.
.
FIN

Función listaFrecuencias(lista):
//lista es una lista de números
INICIO
1. frec <-- 0
2. valor <-- lista[0]
3. nodoPrevio <-- Null
4. Para v ϵ lista hacer:
	Si v = valor hacer:
		frec <-- frec + 1
	Si no hacer:
		nuevoNodo.valor <-- valor
		nuevoNodo.frecuencia <-- frec
		valor <-- v
		frec <-- 1
		Si nodoPrevio <> Null hacer:
			nodoPrevio.siguienteNodo <-- nuevoNodo
		Si no hacer:
			primerNodo <-- nuevoNodo
		Fin si
	nodoPrevio <-- nuevoNodo 
	Fin si
	Si v es el último elemente de lista hacer:
		nuevoNodo.valor <-- valor
		nuevoNodo.frecuencia <-- frec
		nodoPrevio.siguienteNodo <-- nuevoNodo
	Fin si
Fin para
Devolver primerNodo

Función decodificar(codigo, arbolHuffman):
INICIO
1. Palabra <-- “”
2. pArbol <-- arbolHuffman
2. Para letra ϵ codigo hacer:
	Si letra = “0” hacer:
		pArbol <-- pArbol.subArbolIzq
	Si no hacer:
		pArbol <-- pArbol.subArbolDer
	Fin si
	Si pArbol.raiz.valor <> Null hacer:
		Palabra <-- pArbol.raiz.valor
		pArbol <-- arbolHuffman
	Fin si
Fin Para
FIN
