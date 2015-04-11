//DOM Tree. Alvaro Roman aarb17.91@gmail.com

#ifndef	DOM_Tree_H
#define DOM_Tree_H

#include "Element.h"
#include "node.h"

using namespace std;

class DOM_Tree{
	private:
		Node *raiz, *doc;
		Node* copiarNodos(Node *p);
		void destruirNodos(Node*& p);
		void updateDoc(){doc->setFirstChild(raiz);}
		DOM_Tree createTree (string& html); //crea un arbol a partir de codigo html
		Node* createNode (string& html, int &i);
		void viewTree(Node *p); //imprime por pantalla el codigo
		void viewTree() {viewTree(raiz);}
		Node* posElem (string ID, Node* P); //busca y devuelve la direccion del elemento si se encuentra en el arbol
	public:
		DOM_Tree();
		DOM_Tree(Element elem, list<DOM_Tree> L); //Parametro Elem y una lista con sus hijos
		DOM_Tree(const DOM_Tree& DT) {doc = copiarNodos(DT.doc);}
		DOM_Tree& operator=(const DOM_Tree& A);
		void appendChild(DOM_Tree DT, int p); //Agrega un arbol como hijo en la posicion indicada
		void appendChild(string cHtml, int p); //Agrega un hijo a partir de codigo HTML en la posicion indicada
		void appendChild(DOM_Tree DT); //Agrega un arbol como ultimo hijo
		void appendChild(string cHtml); //Agrega como ultimo hijo a partir de codigo HTML
		void removeChild(int p); //elimina el hijo de la posicion p del arbol
		void replaceChild(DOM_Tree DT, int p); //reemplaza el arbol de la posicion indicada
		void replaceChild(string cHtml, int p); //reemplaza el arbol de la posicion indicada
		DOM_Tree childNode(int p); //devuelve el hijo correspondiente a la posicion p del arbol
		DOM_Tree getElementByID (string ID); //cada element tiene un id
		friend ostream &operator<<(ostream &output,DOM_Tree &T);
		~DOM_Tree(){destruirNodos(doc);}
};


#endif
