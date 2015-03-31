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
