//
//  PersonProfile.cpp
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#include "PersonProfile.h"
#include <list>
#include <string>

PersonProfile::PersonProfile(std::string name, std::string email)
: m_name(name), m_email(email), m_numPairs(0)
{}

std::string PersonProfile::GetName() const
{
    return m_name;
}

std::string PersonProfile::GetEmail() const
{
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
    /*
    std::unordered_map<std::string, std::string>::iterator it;
    
    if (m_numPairs == 0)
    {
        avp.insert(attval.attribute, attval.value);
        m_numPairs++;
        return;
    }
    
    it = avp.search(attval.attribute);
    
    while (it != avp.end())
    {
        //Check if attval already exists in the list
        if (*it == attval)
        {
            return;
        }
    
        it++;
    }
    avp.push_back(attval);
    m_numPairs++;
    return;
    */
    
    std::list<AttValPair>::iterator it = avp.begin();
    
    if (m_numPairs == 0)
    {
        avp.push_back(attval);
        m_numPairs++;
        return;
    }
    
    while (it != avp.end())
    {
        //Check if attval already exists in the list
        if (*it == attval)
        {
            return;
        }
    
        it++;
    }
    avp.push_back(attval);
    m_numPairs++;
    return;
     
}

int PersonProfile::GetNumAttValPairs() const
{
    return m_numPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const //?????????????
{
    if (0 > attribute_num || attribute_num >= m_numPairs)
    {
        return false;
    }
        
    std::list<AttValPair>::const_iterator it = avp.begin();
    //Iterate through the list attribute_num times
    for (int k = 0; k < attribute_num; k++)
    {
        if (it != avp.end())
        {
            it++;
        }
    }
    //If it reaches the end then return false
    if (it == avp.end())
    {
        return false;
    }
    
    attval = *it;
    
    return true;
}



