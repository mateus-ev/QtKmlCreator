/*
 *  author: Mateus Evangelista
 *  license model:
*/

#ifndef XMLBUILDER_H
#define XMLBUILDER_H


#include <vector>
#include <memory>
#include "xmlelement.h"


class XmlBuilder
{
public:
    XmlBuilder(const std::string& GroupName, const std::string& GroupAttribute, const std::string& GroupText);

    XmlBuilder& add_child(XmlBuilder& builder);

    std::string str(size_t ident_level = 1) const;


private:
    XmlElement m_GroupRoot;
    std::vector<std::unique_ptr<XmlBuilder>> m_BuilderChilds;

};

#endif // XMLBUILDER_H
