//Alvaro Roman aarb17.91@gmail.com
#include <iostream>
#include <list>
#include "Element.h"
#include "node.h"
#include "DOM_Tree.h"

using namespace std;

DOM_Tree :: DOM_Tree(){
	Element elem("document"); //crea el elemento document
	doc = new Node (elem); //asigna el nodo raiz
	raiz = NULL;
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

DOM_Tree& DOM_Tree :: operator=(const DOM_Tree& A){ //sobrecarga asignacion
	if(this != &A){//si son diferentes y A no es nulo
		this->doc=copiarNodos(A.doc);
	}
	return *this;
}

void DOM_Tree :: appendChild(DOM_Tree DT){
	Node *aux;
	if(raiz != NULL){
		if(raiz->firstChild() == NULL){
			raiz->setFirstChild(copiarNodos(DT.raiz->firstChild()));
		}else{
			aux = raiz->firstChild();
			while(aux->nextSibling() != NULL){
				aux = aux->nextSibling();
			}
			aux->setNextSibling(copiarNodos(DT.raiz->firstChild()));
		}
	}else{
		raiz = copiarNodos(DT.raiz);
	}
	updateDoc();
}

void DOM_Tree :: appendChild(DOM_Tree DT, int p){
	Node *aux,*aux2;
	int i;
	
	if(p == 1){
		aux = raiz; //aux apunta al primer hijo del arbol
		raiz = copiarNodos(DT.raiz); //asigna el primer hijo de DT como primer hijo
		aux2 = raiz; //obtiene el hermano del subarbol
		while(aux2->nextSibling() != NULL){
			aux2 = aux2->nextSibling();
		}
		aux2->setNextSibling(aux); //agrega el arbol que apunta aux como hermano derecho
	}else{
		i=2;
		aux2 = copiarNodos(DT.raiz);
		aux = raiz; //aux apunta al primer hijo del arbol
		while((i <= p-1)&&(aux->nextSibling() != NULL)){ //busca la posicion para colocar el arbol
			aux = aux->nextSibling();
			i++;
		}
		aux2->setNextSibling(aux->nextSibling()); //enlaza el hermano derecho de aux como hermano derecho de aux2
		aux->setNextSibling(aux2); //enlaza aux2 como hermano de aux
	}
	updateDoc();
}

void DOM_Tree :: removeChild(int p){
	Node *aux, *elim;
	int i;
	
	if(p == 1){
		elim = raiz->firstChild();
		raiz->setFirstChild(raiz->firstChild()->nextSibling());
	}else{
		aux = raiz->firstChild();
		i=2;
		while(i <= p-1){
			aux = aux->nextSibling();
			i++;
		}
		elim = aux->nextSibling();
		aux->setNextSibling(aux->nextSibling()->nextSibling());
	}
	elim->setNextSibling(NULL);
	destruirNodos(elim);
	updateDoc();
}

void DOM_Tree :: destruirNodos(Node*& p){
	Node *aux;
	if(p != NULL){
		if(p->nextSibling() != NULL){
			aux = p->nextSibling();
			destruirNodos(aux);
		}
		if(p->firstChild() != NULL){
			aux = p->firstChild();
			destruirNodos(aux);
		}
		delete p;
	}
	
}

DOM_Tree DOM_Tree :: childNode(int p){
	DOM_Tree DT;
	Node *aux;
	int i;
	
	if(raiz != NULL){
		if(p == 1){
			DT.raiz = copiarNodos(raiz->firstChild());
		}else{
			aux = raiz->firstChild();
			i=2;
			while(i <= p-1){
				aux = aux->nextSibling();
				i++;
			}
			DT.raiz = copiarNodos(aux->nextSibling());
		}
		DT.updateDoc();
	}
	return DT;
	
}

DOM_Tree DOM_Tree :: createTree (string html, int &i){
	DOM_Tree T;
	Element e;
	int j;
	string tag,id,htmlInt,cTag;
	list<string> attL;
	
	T.raiz = new Node ();
	
	if( html.at(i) == '<' ){ //si abre <
		i++; //se coloca en la siguiente posicion
		while((html.at(i) != ' ')&&(html.at(i) != '>')&&(i < html.length())){ //mientras no consiga un espacio o un >, lee el tagName
			tag.push_back(html.at(i)); //inserto el caracter al final del string tag
			i++;
		}
		e.setTagName (tag); //inserto el tag name
		
		//atributos
		if(html.at(i) != '>'){
			if(html.at(i) == ' '){ //si el caracter actual es un espacio, prosigue
				i++; //siguiente pos
				j=i; //guardo la pos de i
				//verifico si hay un id explicito
				while((html.at(j) != '=')&&(i < html.length())){
					id.push_back(html.at(j));
					j++;
				}
				i=j;
				i+=2; //avanza i dos posiciones
				if(id == "id"){ //si hay un id explicito
					id.clear(); //limpio la cadena
					while((html.at(i) != '"')&&(html.at(i) != '\'')&&(i < html.length())){ //mientras no consiga una comilla
						id.push_back(html.at(i));
						i++;
					}
					i++;//se coloca en la siguiente posicion
				}else{
					id = tag; //si no hay un id explicito asigno el tagname como id
				}
				e.setID(id); //asigno el id
				
				while((html.at(i) == ' ')&&(i < html.length())){ //lee los atributos
					i++;
					string att;
					while((html.at(i) != ' ')&&(html.at(i) != '>')&&(i < html.length())){ //mientras no consiga un espacio
						att.push_back(html.at(i));
						i++;
					}
					attL.push_back(att); //inserto el atributo en la lista
				}
				e.setAttributeList(attL); //inserta la lista de atributos
			}
		}
		if(html.at(i) == '>'){ //si cierra leer html interno hasta que consiga un < , si consigue un < entonces llama recursivamente a la funcion
			i++;//se coloca en la siguiente posicion
			while(i < html.length()){
				while((html.at(i) != '<')&&(i < html.length())){ //mientras no consiga <, lee el html interno
					htmlInt.push_back(html.at(i));
					i++;
				}
				j=i+1;
				if(html.at(j) == '/'){ //si en la pos j hay un /
					i=j+1;
					while(html.at(i) != '>'){
						cTag.push_back(html.at(i));
						i++;
					}
					if(cTag == tag){ //si cTag es igual a tag entonces se cierra la etiqueta
						T.raiz->setElement(e); //asigno el element al node
						return T;
					}
					
				}else{ //si el caracter en la pos j no es un /
					T.appendChild(createTree(html,i); //llama recursivamente y agrega el arbol como ultimo hijo
				}
				i++
			}
			
		}
	}
}
