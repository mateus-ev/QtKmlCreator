#pragma once
#ifndef XMLBUILDER_H
#define XMLBUILDER_H

#include "xmlelement.h"

class XmlBuilder
{
public:
    XmlBuilder(const std::string& GroupName);
    XmlBuilder& add_child(const std::string& Tag, const std::string& Text);

private:
    XmlElement m_GroupRoot;
};

#endif // XMLBUILDER_H
