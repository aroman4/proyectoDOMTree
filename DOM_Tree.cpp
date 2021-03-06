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

DOM_Tree :: DOM_Tree(Element elem, list<DOM_Tree> L){
	raiz = new Node(elem); //asigno el elemento
	updateDoc();
	
	list<DOM_Tree>::iterator it;
	
	for(it = L.begin(); it != L.end(); it++){ //recorro la lista
		appendChild(*it); //inserto como ultimo hijo cada hijo
	}
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
		this->raiz=copiarNodos(A.raiz);
		updateDoc();
	}
	return *this;
}

void DOM_Tree :: appendChild(string cHtml, int p){
	appendChild(createTree(cHtml),p);
}

void DOM_Tree :: appendChild(string cHtml){
	appendChild(createTree(cHtml));
}

void DOM_Tree :: appendChild(DOM_Tree DT){
	Node *aux;
	if(raiz != NULL){
		if(raiz->firstChild() == NULL){
			raiz->setFirstChild(copiarNodos(DT.raiz));
		}else{
			aux = raiz->firstChild();
			while(aux->nextSibling() != NULL){
				aux = aux->nextSibling();
			}
			aux->setNextSibling(copiarNodos(DT.raiz));
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

void DOM_Tree :: replaceChild(DOM_Tree DT, int p){
	Node *aux, *elim;
	int i;
	
	if(p == 1){
		elim = raiz->firstChild();
		raiz->setFirstChild(copiarNodos(DT.raiz->firstChild()));
	}else{
		aux = raiz->firstChild();
		i=2;
		while(i <= p-1){
			aux = aux->nextSibling();
			i++;
		}
		elim = aux->nextSibling();
		aux->setNextSibling(copiarNodos(DT.raiz->firstChild()));
	}
	elim->setNextSibling(NULL);
	destruirNodos(elim);
	updateDoc();
}

void DOM_Tree :: replaceChild(string cHtml, int p){
	replaceChild(createTree(cHtml),p);
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

void Node :: appendNode(Node* pt){
	
	if(this->firstChild() == NULL){
		this->setFirstChild (pt);
	}else{
		Node *aux;
		aux = this->firstChild();
		while(aux->nextSibling() != NULL){
			aux = aux->nextSibling();
		}
		aux->setNextSibling(pt);
	}
}

DOM_Tree DOM_Tree :: createTree (string& html){
	DOM_Tree T;
	int i = 0;
	
	T.raiz = createNode(html,i);
	T.updateDoc();
	
	return T;
}

Node* DOM_Tree :: createNode (string& html, int &i){
	Node *N;
	Element e;
	int j;
	string tag,id,htmlInt,cTag;
	list<string> attL;
	
	N = new Node ();
	
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
				e.setInnerHTML(htmlInt);
				j=i+1;
				if(html.at(j) == '/'){ //si en la pos j hay un /
					i=j+1;
					while(html.at(i) != '>'){
						cTag.push_back(html.at(i));
						i++;
					}
					if(cTag == tag){ //si cTag es igual a tag entonces se cierra la etiqueta
						N->setElement(e); //asigno el element al node
						return N;
					}
					
				}else{ //si el caracter en la pos j no es un /
					N->appendNode(createNode(html,i)); //llama recursivamente y agrega el nodo como ultimo hijo
				}
				i++;
			}
			
		}
	}
}

ostream& operator<<(ostream &output,DOM_Tree &T){
	T.viewTree();
}

void DOM_Tree :: viewTree(Node *p){
	Element e;
	list<string> attL;
	
	if(p != NULL){
		e = p->element(); //obtengo el element
		
		cout << "<" << e.tagName();
		
		if((e.ID() != e.tagName())&&(!e.ID().empty())){ //si existe ID se imprime
			cout << " id=\"" << e.ID() << "\"";
		}
		
		attL = e.attributeList(); //asigno a attL la lista de atributos
		if(!attL.empty()){ //si la lista de atributos no es vacia
			list<string>::iterator it;
			for (it = attL.begin(); it != attL.end(); it++){
				cout << " ";
				cout << *it;
			}
		}
		cout << ">";
		if(!e.innerHTML().empty()){ //si existe inner HTML
			cout << e.innerHTML();
			
		}else{ //si no existe innerhtml
			cout << "\n\t";
		}
		viewTree(p->firstChild());
		cout << "</" << e.tagName() << ">" << endl;
		viewTree(p->nextSibling());
		
	}
}

DOM_Tree DOM_Tree :: getElementByID (string ID){
	DOM_Tree T;
	
	T.raiz = posElem(ID,this->raiz);
	T.updateDoc();
	
	return T;
	
}

Node* DOM_Tree :: posElem (string ID, Node* P){ //busca y devuelve la direccion del elemento si se encuentra en el arbol
	Node* ret;
	ret = NULL;
	
	if(P!=NULL){
		if(P->element().ID() == ID){
			ret = P;
		}else{
			if (ret == NULL){ //aun no se ha encontrado el elemento
				ret = posElem (ID, P->firstChild());
			}
			if (ret == NULL){ //aun no se ha encontrado el elemento
				ret = posElem (ID, P->nextSibling());
			}
		}
	}
	
	return ret;
}
