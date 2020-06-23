#include "xmlelement.h"

XmlElement::XmlElement(){}


XmlElement::XmlElement(const std::string& Tag, const std::string& Text):
    m_Tag(Tag), m_Text(Text){}

std::string XmlElement::str(size_t ident_level) const
{
    std::ostringstream oss;
    std::string ident_tabs(ident_level, '\t');
    oss << ident_tabs << "<" << m_Tag << ">\n";

    if(m_Text.length() > 0)
        oss << ident_tabs << '\t' <<  m_Text << '\n';

    for(const auto& element: m_Elements)
        oss << element.str(ident_level+1);

    oss << "</" << m_Tag << ">\n";
    return oss.str();
}
