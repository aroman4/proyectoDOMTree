#ifndef Element_H
#define Element_H

using namespace std;

class Element{
	private:
		//Atributos
		string tagNam;
		list<string> attrList;
		string innerHtml;
		
	public:
		//Constructores
		Element () {}
		Element (string tag) : tagNam(tag) {}
		Element (string tag,list<string> attr) : tagNam(tag), attrList(attr) {}
		Element (string tag,list<string> attr,string html) : tagNam(tag), attrList(attr), innerHtml(html) {}
		Element (const Element& E) {tagNam = E.tagNam; attrList = E.attrList; innerHtml = E.innerHtml;}
		//Gets
		string tagName(){return tagNam;}
		list<string> attributeList () {return attrList;}
		string innerHTML () {return innerHtml;}
		//Sets
		void setTagName (string tag) {tagNam = tag;}
		void setAttributeList (list<string> L) {attrList = L;}
		void setInnerHTML (string html) {innerHtml = html;}
	
};

#endif
