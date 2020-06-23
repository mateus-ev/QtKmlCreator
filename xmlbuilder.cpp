#include "xmlbuilder.h"

XmlBuilder::XmlBuilder(const std::string& GroupName):
    m_GroupRoot(XmlElement(GroupName, "")){}


XmlBuilder& XmlBuilder::add_child(const std::string& Tag, const std::string& Text)
{
    m_GroupRoot.m_Elements.emplace_back(Tag, Text);
    return *this;
}
