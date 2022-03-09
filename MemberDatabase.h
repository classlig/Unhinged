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
#include "RadixTree.h"
#include <list>
#include <string>
#include <vector>

class MemberDatabase
{
public:
    MemberDatabase() {};
    ~MemberDatabase();
    
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
    
private:
    RadixTree<std::list<std::string>> pairToEmail;
    RadixTree<PersonProfile*> emailToProfile;
    std::list<PersonProfile*> pointerToProfiles;
    
};
#endif /* MemberDatabase_h */
