/*
 *  author: Mateus Evangelista
 *  license model:
*/
#include "xmlbuilder.h"

XmlBuilder::XmlBuilder(const std::string& GroupName, const std::string& GroupAttribute, const std::string& GroupText):
    m_GroupRoot(XmlElement(GroupName, GroupAttribute, GroupText)){}


XmlBuilder& XmlBuilder::add_child(XmlBuilder& builder)
{
    m_BuilderChilds.emplace_back(std::make_unique<XmlBuilder>(std::move(builder)));
    return *this;
}


std::string XmlBuilder::str(size_t ident_level) const
{
    std::ostringstream oss;
    std::string ident_tabs(ident_level, '\t');


    if(this->m_BuilderChilds.empty())
    {
        oss << ident_tabs << "<" << m_GroupRoot.m_Tag << m_GroupRoot.m_Attribute << ">";
        if(m_GroupRoot.m_Text.length() > 0)
            oss << m_GroupRoot.m_Text;
        oss << "</" << m_GroupRoot.m_Tag << ">\n";
    }

    else
    {

        oss << ident_tabs << "<" << m_GroupRoot.m_Tag << m_GroupRoot.m_Attribute << ">\n";

        if(m_GroupRoot.m_Text.length() > 0)
            oss << ident_tabs << '\t' <<  m_GroupRoot.m_Text << '\n';

        for(const auto& element: m_BuilderChilds)
            oss << element->str(ident_level+1);

        oss << ident_tabs << "</" << m_GroupRoot.m_Tag << ">\n";

    }
        return oss.str();

}

