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
#include <map>
#include <string>
#include <vector>
//Do we load files in this class?
int counter; //REMOVE ME AFTER TESTING


void MatchMaker::orderByCount(std::vector<EmailCount>& source, unsigned long n1, unsigned long n2, std::vector<EmailCount> temp) const
{
    int i1 = 0, i2 = 0, k = 0;
    EmailCount* A1 = &source[0], *A2 = &source[0 + n1];
    
    while (i1 < n1 || i2 < n2)
    {
        if (i1 == n1)
        {
            temp[k++] = A2[i2++];
        }
        
        else if (i2 == n2)
        {
            temp[k++] = A1[i1++];
        }
        
        else if (source[i1].count >= A2[i2].count)
        {
            temp[k++] = A1[i1++];
        }
        
        else
            temp[k++] = A2[i2++];
    }
    
    for (int i = 0; i < n1 + n2; i++)
    {
        source[i] = temp[i];
        std::cout << source[i].email << " " << source[i].count << std::endl;
    }
        
}

std::vector<EmailCount>* MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    static std::vector<EmailCount> rankedMatches;
    
    //Load the AttributeTranslator
    AttributeTranslator at;
    std::string pathname =  "/Users/Kristal/Documents/CS 32/Project 4/Unhinged/translatorTest.txt";
    if (at.Load(pathname) == false)
    {
        return &rankedMatches;
    }
    
    //Load the MemberDatabase
    MemberDatabase md;
    std::string mdpathname = "/Users/Kristal/Documents/CS 32/Project 4/Unhinged/membersTest.txt";
    if (md.LoadDatabase(mdpathname) == false)
    {
        return &rankedMatches;
    }
    
    //Retrieve the profile associated with the email
    const PersonProfile* memberProfile = md.GetMemberByEmail(email);
    if (memberProfile == nullptr) //Member doesn't exist
    {
        return &rankedMatches;
    }
    
    std::list<AttValPair> myListOfCompatPairs; //Keep a list of the compatible pairs
    
    int totNumPairs = memberProfile->GetNumAttValPairs();
    for (int n = 0; n != totNumPairs; n++)
    {
        AttValPair av;
        memberProfile->GetAttVal(n, av);
        
        //Retrieve vector of compatible pairs
        std::vector<AttValPair> vectorOfCompatPairs = at.FindCompatibleAttValPairs(av);
        
        std::vector<AttValPair>::iterator it = vectorOfCompatPairs.begin();
        while(it != vectorOfCompatPairs.end())
        {
            AttValPair compatiblePair = *it;
            std::list<AttValPair>::iterator myListIt = myListOfCompatPairs.begin();
            
            bool hasCopy = false;
            while (myListIt != myListOfCompatPairs.end())
            {
                if ( compatiblePair == *myListIt)
                {
                    hasCopy = true;
                }
                myListIt++;
            }
            if (hasCopy == false)
            {
                myListOfCompatPairs.push_back(compatiblePair);
                //std::cout << it->attribute << " " << it->value << std::endl;
            }
            it++;
        }
        
    }
    std::list<AttValPair>::iterator myListIt = myListOfCompatPairs.begin();
    std::map<std::string, int> myCompatEmailsMap;
    
    while (myListIt != myListOfCompatPairs.end())
    {
        
        AttValPair compatiblePair = *myListIt;
        //Retrieve vector of emails associated to the compatible pair
        std::vector<std::string> emailList = md.FindMatchingMembers(compatiblePair);
        
        //Iterate through the vector and add it to the map of emails
        std::vector<std::string>::iterator emailIt = emailList.begin();
        
        
        while (emailIt != emailList.end())
        {
            std::map<std::string,int>::iterator mapIt = myCompatEmailsMap.find(*emailIt); //Check if email exists in map
            if (mapIt == myCompatEmailsMap.end())
            {
                counter++;
                if (*emailIt != email)
                {
                    myCompatEmailsMap[*emailIt] = 1;
                }
            }
            else if (mapIt != myCompatEmailsMap.end())
            {
                mapIt->second++;
            }
            emailIt++;
            
        }
        myListIt++;
    }
    
    std::vector<EmailCount> emailCountVec;
    
    std::map<std::string,int>::iterator compatEmailsIt = myCompatEmailsMap.begin();
    std::map<int,std::string> sortByCount;
    while (compatEmailsIt != myCompatEmailsMap.end())
    {
        if (compatEmailsIt->second >= threshold)
        {
            
            std::string email = compatEmailsIt->first;
            int count = compatEmailsIt->second;
            
            //mapRankedMatches[email] = count;
            //sortByCount[count] = email;
            
            EmailCount match(email, count);
            
            emailCountVec.push_back(match);
            
            std::cout << match.email << " " << match.count << std::endl;

        }
        
        compatEmailsIt++;
    }
    
    unsigned long n = emailCountVec.size();
    unsigned long n1 = n - n/2;
    unsigned long n2 = n - (n - n/2);
    
    std::vector<EmailCount> temp;
    for (int i = 0; i < n; i++) //Fill up temp vector
    {
        std::string em;
        int c = 0;
        EmailCount e(em, c);
        temp.push_back(e);
    }
    
    this->orderByCount(emailCountVec, n1, n2, temp);
    
    std::vector<EmailCount>::iterator ecvIt = emailCountVec.begin();
    while (ecvIt != emailCountVec.end())
    {
        rankedMatches.push_back(*ecvIt);
        ecvIt++;
    }
    
    return &rankedMatches;
}


