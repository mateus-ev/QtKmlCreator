#pragma once
#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <sstream>
#include <vector>

class XmlBuilder;

class XmlElement
{
public:
    XmlElement();
    XmlElement(const std::string& Tag, const std::string& Text);

    std::string str(size_t ident_level = 1) const;

private:
    std::string m_Tag;
    std::string m_Text;

    std::vector<XmlElement> m_Elements;

    friend class XmlBuilder;
};

#endif // XMLELEMENT_H
