//DOM Tree. Alvaro Roman aarb17.91@gmail.com

#ifndef	DOM_Tree_H
#define DOM_Tree_H

#include "Element.h"
#include "node.h"

using namespace std;

class DOM_Tree{
	private:
		Node* raiz;
		
	public:
		DOM_Tree(){
			Element elem("document"); //crea el elemento document
			raiz = new Node (elem); //asigna el nodo raiz
		}
	
};


#endif
