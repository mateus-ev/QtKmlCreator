#include "xmlbuilder.h"

XmlBuilder::XmlBuilder(const std::string& GroupName, const std::string& GroupAttribute, const std::string& GroupText):
    m_GroupRoot(XmlElement(GroupName, GroupAttribute, GroupText)){}


XmlBuilder& XmlBuilder::add_child(XmlBuilder& builder)
{
    m_BuilderChilds.push_back(std::make_shared<XmlBuilder>(std::move(builder)));
    return *this;
}


std::string XmlBuilder::str(size_t ident_level) const
{
    std::ostringstream oss;
    std::string ident_tabs(ident_level, '\t');
    oss << ident_tabs << "<" << m_GroupRoot.m_Tag << m_GroupRoot.m_Attribute << ">\n";

    if(m_GroupRoot.m_Text.length() > 0)
        oss << ident_tabs << '\t' <<  m_GroupRoot.m_Text << '\n';

    for(auto element: m_BuilderChilds)
        oss << element->str(ident_level+1);

    oss << ident_tabs << "</" << m_GroupRoot.m_Tag << ">\n";

    return oss.str();

}

