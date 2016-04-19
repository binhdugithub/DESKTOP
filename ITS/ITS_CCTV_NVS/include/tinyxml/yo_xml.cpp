#include <string>
#include "yo_xml.h"

using namespace std;

namespace elc {

//===========================================================================
ElcXmlFile::ElcXmlFile(void)
//===========================================================================
:doc((char*)0)
{
}
//===========================================================================
ElcXmlFile::ElcXmlFile(const string& filename, int flags)
//===========================================================================
:doc(filename.c_str())
{
	doc.LoadFile();
}
//===========================================================================
ElcXmlFile::~ElcXmlFile(void)
//===========================================================================
{
}
//===========================================================================
ElcXmlFileNode* ElcXmlFile::getRoot()
//===========================================================================
{
	return new ElcXmlFileNode(doc.FirstChildElement("elcom"));
}
//===========================================================================
ElcXmlFileNode* ElcXmlFile::getNode(ElcXmlFileNode *parentNode, 
									std::string nodeName,
									std::string nodeId)
//===========================================================================
{
	if (!parentNode)
		return 0;
	if (nodeId == "")
		return parentNode->getChild(nodeName);
	else
		return parentNode->getChild(nodeName, nodeId);
}
//===========================================================================
void ElcXmlFile::save()
//===========================================================================
{
	doc.SaveFile();
}
/////////////////////////////////////////////////////////////////////////////
// ElcXmlFileNode class
/////////////////////////////////////////////////////////////////////////////

//===========================================================================
ElcXmlFileNode::ElcXmlFileNode(ticpp::Element* aNode)
//===========================================================================
{
	node = aNode;
}
//===========================================================================
ElcXmlFileNode::~ElcXmlFileNode()
//===========================================================================
{
}
//===========================================================================
std::string ElcXmlFileNode::getName()
//===========================================================================
{
	return node->Value();
}
//===========================================================================
std::string ElcXmlFileNode::getValue()
//===========================================================================
{
	return node->GetText();
}
//===========================================================================
ElcXmlFileNode* ElcXmlFileNode::getChild(std::string nodeName, std::string nodeId)
//===========================================================================
{
	// iterate over all "entry" items
	ticpp::Iterator<ticpp::Element>
	 child(node->FirstChildElement(nodeName), nodeName);
	while ( child != child.end() )
	{
		string entry_id;
		// read the attribute <entry name="[attribute]"...
		child->GetAttribute("id", &entry_id);
		if ( entry_id == nodeId ) {
			return new ElcXmlFileNode(child->ToElement());
		}
		// advance to next item
		++child;
	}
	return 0;
}
//===========================================================================
ElcXmlFileNode* ElcXmlFileNode::getChild(std::string nodeName)
//===========================================================================
{
    std::string strName;
	// iterate over all "entry" items
	/*ticpp::Iterator<ticpp::Element> child;
    for(child = child.begin(node->FirstChildElement()); child != child.end(); child++)
    {
		child->GetValue(&strName);
		if (strName == nodeName)
			return new ElcXmlFileNode(child->ToElement());
    }*/

	ticpp::Iterator<ticpp::Element>
	 child(node->FirstChildElement(nodeName), nodeName);
	while ( child != child.end() )
	{
		child->GetValue(&strName);
		if (strName == nodeName)
			return new ElcXmlFileNode(child->ToElement());
		// advance to next item
		++child;
	}

	return 0;
}

std::vector<ElcXmlFileNode*> ElcXmlFileNode::getAllChild()
{
	std::string strName;
	static std::vector<ElcXmlFileNode*> listNodes;
	while (listNodes.size()) {
		ElcXmlFileNode* node = listNodes[0];
		listNodes.erase(listNodes.begin());
		delete node;
		node = 0;
	}
	try {
		ticpp::Iterator<ticpp::Element>	 child(node->FirstChildElement());
		while ( child != child.end() )
		{
			listNodes.push_back(new ElcXmlFileNode(child->ToElement()));
			++child;
		}
	}
	catch(...) {
	}
	return listNodes;
}

//===========================================================================
std::string ElcXmlFileNode::getAttribute(std::string attr)
//===========================================================================
{
	static string value;
	node->GetAttribute(attr.c_str(), &value);	
	return value;
}
//===========================================================================
void ElcXmlFileNode::setAttribute(std::string att, std::string value)
//===========================================================================
{
	node->SetAttribute(att, value);
}

}
