#ifndef Element_H
#define Element_H

#include <list>

using namespace std;

class Element{
	private:
		//Atributos
		string tagNam;
		list<string> attrList;
		string Id;
		string innerHtml;
		
	public:
		//Constructores
		Element () {}
		Element (string tag) : tagNam(tag) {}
		Element (string tag,list<string> attr) : tagNam(tag), attrList(attr) {}
		Element (string tag,list<string> attr,string html) : tagNam(tag), attrList(attr), innerHtml(html) {}
		Element (const Element& E) {tagNam = E.tagNam; attrList = E.attrList; innerHtml = E.innerHtml; Id = E.Id;}
		Element& operator=(const Element& E){if(this != &E){this->tagNam = E.tagNam; this->attrList = E.attrList; this->innerHtml = E.innerHtml; this->Id = E.Id;}return *this;}
		//Gets
		string tagName(){return tagNam;}
		list<string> attributeList () {return attrList;}
		string innerHTML () {return innerHtml;}
		string ID () {return Id;}
		//Sets
		void setTagName (string tag) {tagNam = tag;}
		void setAttributeList (list<string> L) {attrList = L;}
		void setInnerHTML (string html) {innerHtml = html;}
		void setID (string id) {Id = id;}
	
};

#endif

