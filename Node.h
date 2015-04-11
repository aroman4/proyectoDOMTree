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
		Node (const Node& n){firstCh = n.firstCh; nextSib = n.nextSib; e = n.e;}
		Node& operator=(const Node& n) {if(this != &n){this->firstCh = n.firstCh; this->nextSib = n.nextSib; this->e = n.e;}return *this;}
		Element element() {return e;}
		Node* firstChild() {return firstCh;}
		Node* nextSibling() {return nextSib;}
		void setElement(Element elem){e = elem;}
		void setFirstChild (Node* hiz) {firstCh = hiz;}
		void setNextSibling (Node* hde) {nextSib = hde;}
		void appendNode(Node* pt);
};


#endif

