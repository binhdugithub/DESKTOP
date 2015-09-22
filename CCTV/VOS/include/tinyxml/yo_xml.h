#pragma once
#include <vector>
#include "ticpp.h"

namespace elc {

class ElcXmlFileNode;

class ElcXmlFile
{
public:
    //! file storage mode
    enum
    {
        READ=0, //! read mode
        WRITE=1, //! write mode
        APPEND=2 //! append mode
    };

public:
	//! the default constructor
	ElcXmlFile(void);
	//! the full constructor that opens file storage for reading or writing
    ElcXmlFile(const std::string& filename, int flags);
	//! the destructor. calls release()
	~ElcXmlFile(void);

	//! get file node root
	ElcXmlFileNode* getRoot();

	//! get file node by name. nodeId is optional
	ElcXmlFileNode* getNode(ElcXmlFileNode *parentNode, std::string nodeName, std::string nodeId = "");

	void save();

protected:
	ticpp::Document doc;
};

class ElcXmlFileNode
{
	friend class ElcXmlFile;
public:
	ElcXmlFileNode(ticpp::Element* aNode);
	~ElcXmlFileNode(void);

	//! get name of node
	std::string getName();
	//! get value of node
	std::string getValue();
	//! get value of attribute
	std::string getAttribute(std::string);
	//! set value of attribute
	void setAttribute(std::string att, std::string value);

	//! get all child node
	std::vector<ElcXmlFileNode*> getAllChild();

protected:
	//! get child node within id
	ElcXmlFileNode* getChild(std::string nodeName, std::string nodeId);
	//! get child node
	ElcXmlFileNode* getChild(std::string nodeName);

protected:
	ticpp::Element* node;
};

}