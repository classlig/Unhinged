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
    /*
    //TESTS
    std::map<std::string,int>::iterator testIt = myCompatEmailsMap.begin();
    while (testIt != myCompatEmailsMap.end())
    {
        std::cout << testIt->first << " " << testIt->second << std::endl;
        testIt++;
    }
    std::cout << counter << std::endl;
    */
    
    std::map<std::string,int> mapRankedMatches;
    
    std::map<std::string,int>::iterator compatEmailsIt = myCompatEmailsMap.begin();
    std::map<int,std::string> sortByCount;
    while (compatEmailsIt != myCompatEmailsMap.end())
    {
        if (compatEmailsIt->second >= threshold)
        {
            
            std::string email = compatEmailsIt->first;
            int count = compatEmailsIt->second;
            
            mapRankedMatches[email] = count;
            //sortByCount[count] = email;
            
            EmailCount match(email, count);
            //rankedMatches.push_back(match);  //UNCOMMENT WHEN DONE TESTING
            std::cout << match.email << " " << match.count << std::endl;

        }
        
        compatEmailsIt++;
    }
    /*
    std::map<std::string,int>::iterator sortIt = mapRankedMatches.begin();
    do
    {
        int c = sortIt->second;
        
        
    } while (sortIt != mapRankedMatches.end());
    */
    /*
    for (int t = threshold; t > 0; t--)
    {
        std::unordered_map<std::string,int>::iterator unordered_mapIt = mapRankedMatches.begin();
        while (unordered_mapIt != mapRankedMatches.end())
        {
            if (unordered_mapIt->second >= t)
            {
                std::cout << t << std::endl;
                std::string email = compatEmailsIt->first;
                int count = compatEmailsIt->second;
                EmailCount match(email, count);
                rankedMatches.push_back(match);
                std::cout << match.email << " " << match.count << std::endl;
            }
            unordered_mapIt++;
        }
    }
    */
    /*
    std::map<int,std::string>::iterator sortByCountIt = sortByCount.begin();
    while (sortByCountIt != sortByCount.end())
    {
        std::cout << sortByCountIt->first << " " << sortByCountIt->second << std::endl;
        int count = sortByCountIt->first;
        std::string email = sortByCountIt->second;
        
        EmailCount match(email, count);
        rankedMatches.push_back(match);
        //std::cout << match.email << " " << match.count << std::endl;
        sortByCountIt++;
    }
    */
    return &rankedMatches;
}

