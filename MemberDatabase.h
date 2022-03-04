//
//  MemberDatabase.h
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include "PersonProfile.h"
#include "provided.h"
#include <string>

class MemberDatabase
{
public:
    MemberDatabase();
    
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
    
};
#endif /* MemberDatabase_h */
