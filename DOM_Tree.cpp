//Alvaro Roman aarb17.91@gmail.com
#include <iostream>
#include <list>
#include "Element.h"
#include "node.h"
#include "DOM_Tree.h"

using namespace std;

DOM_Tree :: DOM_Tree(){
	Element elem("document"); //crea el elemento document
	raiz = new Node (elem); //asigna el nodo raiz
}

Node* DOM_Tree :: copiarNodos(Node *p){
	Node *nuevo;
	if (p == NULL){
		return NULL;
	}else{
		nuevo = new Node (p->element(),copiarNodos(p->firstChild()),copiarNodos(p->nextSibling()));
		return nuevo;
	}
}

void DOM_Tree :: appendChild(DOM_Tree DT){
	Node *aux;
	
	if(raiz->firstChild() == NULL){
		raiz->setFirstChild(copiarNodos(DT.raiz->firstChild()));
	}else{
		aux = raiz->firstChild();
		while(aux->nextSibling() != NULL){
			aux = aux->nextSibling();
		}
		aux->setNextSibling(copiarNodos(DT.raiz->firstChild()));
	}
}

void DOM_Tree :: appendChild(DOM_Tree DT, int p){
	Node *aux,*aux2;
	int i;
	
	if(p == 1){
		aux = raiz->firstChild(); //aux apunta al primer hijo del arbol
		raiz->setFirstChild(DT.raiz->firstChild()); //asigna el primer hijo de DT como primer hijo
		aux2 = raiz->nextSibling(); //obtiene el hermano del subarbol
		while(aux2->nextSibling() != NULL){
			aux2 = aux2->nextSibling();
		}
		aux2->setNextSibling(aux); //agrega el arbol que apunta aux como hermano derecho
	}else{
		i=2;
		aux2 = DT.raiz->firstChild();
		aux = raiz->firstChild(); //aux apunta al primer hijo del arbol
		while((i <= p-1)&&(aux->nextSibling() != NULL)){ //busca la posicion para colocar el arbol
			aux = aux->nextSibling();
			i++;
		}
		aux2->setNextSibling(aux->nextSibling()); //enlaza el hermano derecho de aux como hermano derecho de aux2
		aux->setNextSibling(aux2); //enlaza aux2 como hermano de aux
	}
}
