//
//  PersonProfile.h
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include "provided.h"
#include <list>
#include <string>

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    
private:
    std::string m_name;
    std::string m_email;
    int m_numPairs;
    std::list<AttValPair> avp;
};



#endif /* PersonProfile_h */
