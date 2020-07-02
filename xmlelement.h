/*
 *  author: Mateus Evangelista
 *  license model: GPLv3
*/

#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <sstream>


class XmlBuilder;

class XmlElement
{
public:
    XmlElement();
    XmlElement(const std::string& Tag, const std::string& Attribute, const std::string& Text);



private:
    std::string m_Tag;
    std::string m_Attribute;
    std::string m_Text;

    friend class XmlBuilder;
};

#endif // XMLELEMENT_H
