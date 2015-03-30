#ifndef node_H
#define node_H

class Node {
	private:
		Element e;
		Node *firstCh;
		Node *nextSib;
	public:
		Node () : firstCh(NULL), nextSib(NULL) {}
		Node (Element elem) : firstCh(NULL), nextSib(NULL), e(elem) {}
		Node (Element elem, Node* fc, Node* ns) {e = elem; firstCh = fc; nextSib = ns;}
		Node (const NodoA& n){firstCh = n.firstCh; nextSib = n.nextSib; e = n.e;}
		Element element() {return e;}
		Node* firstChild() {return firstCh;}
		Node* nextSibling() {return nextSib;}
		void setElement(T e){info = e;}
		void setFirstChild (NodoA* hiz) {firstCh = hiz;}
		void setNextSibling (NodoA* hde) {nextSib = hde;}
};


#endif
