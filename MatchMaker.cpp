//
//  MatchMaker.cpp
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#include "AttributeTranslator.h"
#include "MatchMaker.h"
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
//Do we load files in this class?

std::vector<EmailCount>* MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    AttributeTranslator at;
    std::string pathname =  "/Users/Kristal/Documents/CS 32/Project 4/Unhinged/translator.txt";
    if (at.Load(pathname) == false)
    {
        std::cout << "error" << std::endl;
        
    }
    
    MemberDatabase md;
    std::string mdpathname = "/Users/Kristal/Documents/CS 32/Project 4/Unhinged/members.txt";
    if (md.LoadDatabase(mdpathname) == false)
    {
        std::cout << "error at md" << std::endl;
        
    }
    
    
    const PersonProfile* memberProfile = md.GetMemberByEmail(email);
    std::list<AttValPair> compatPairs;
    
    for (int n = 0; n != memberProfile->GetNumAttValPairs(); n++)
    {
        
        AttValPair av;
        memberProfile->GetAttVal(n, av);
        
        std::vector<AttValPair> translatedCompatPairs = at.FindCompatibleAttValPairs(av);
        
        std::vector<AttValPair>::iterator it;
        it = translatedCompatPairs.begin();
        while(it != translatedCompatPairs.end())
        {
            AttValPair compatible = *it;
            std::list<AttValPair>::iterator lit = compatPairs.begin();
            
            bool hasCopy = false;
            while (lit != compatPairs.end())
            {
                if ( compatible == *lit)
                {
                    hasCopy = true;
                }
                lit++;
            }
            if (hasCopy == false)
            {
                compatPairs.push_back(compatible);
                std::cout << it->attribute << " " << it->value << std::endl;
            }
            it++;
        }
    }
    
    
    
    return nullptr;
}

