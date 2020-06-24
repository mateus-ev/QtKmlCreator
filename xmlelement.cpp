#include "xmlelement.h"

XmlElement::XmlElement(){}


XmlElement::XmlElement(const std::string& Tag, const std::string& Attribute, const std::string& Text):
    m_Tag(Tag), m_Attribute(Attribute), m_Text(Text){}


