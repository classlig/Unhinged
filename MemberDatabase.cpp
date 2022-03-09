//
//  MemberDatabase.cpp
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#include "MemberDatabase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

MemberDatabase::~MemberDatabase()
{
    std::list<PersonProfile*>::iterator it = pointerToProfiles.begin();
    while (it != pointerToProfiles.end())
    {
        delete *it;
        it = pointerToProfiles.erase(it);
    }
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    //Load file and if anything doesn't load properly, return false
    std::ifstream members(filename);
    if (!members)
    {
        return false;
    }
    
    std::string line;
    do //In this loop I am assuming we won't be passed an empty file and will return true if it does process an empty file
    {
        std::vector<std::string> memberInfo;
        
        std::string name;
        if (!getline(members, name))
        {
            break;
        }
        //std::cout << name << std::endl;;
        
        std::string email;
        if (!getline(members, email))
        {
            return false;
        }
        //std::cout << email << std::endl;
        
        std::string n;
        if (!getline(members, n))
        {
            return false;
        }
        //std::cout << numPairs << std::endl;
        
        for (int numPairs = stoi(n); numPairs > 0; numPairs--)
        {
            std::string pair;
            if (!getline(members, pair))
            {
                return false;
            }
            memberInfo.push_back(pair);
            //std::cout << pair << std::endl;
            
            std::list<std::string> emails;
            emails.push_back(email);
            
            std::list<std::string>* ValueTypePointer = pairToEmail.search(pair); //Remember search function
            
            // The next two if statements fill out the pairToEmail tree
            if (ValueTypePointer == nullptr) //If the pair is not already in the map
            {
                pairToEmail.insert(pair, emails);
            }
            if (ValueTypePointer != nullptr) //If the pair is already in the map
            {
                ValueTypePointer->push_back(email); //Add another email address
            }
        }
        
        
        std::vector<std::string>::iterator it = memberInfo.begin(); //Start at index where pairs are located
        //std::cout << *it << std::endl;
        
        PersonProfile* profilePointer = new PersonProfile(name, email);
        pointerToProfiles.push_back(profilePointer); //To delete later
        while (it != memberInfo.end())
        {
            std::string at, val, pair = *it;
            unsigned long index = pair.find(',');
            //Store the attribute
            for (int i = 0; i < index; i++)
            {
                at += pair[i];
            }
            //Store the value
            for (unsigned long i = index + 1; i < pair.length(); i++)
            {
                val += pair[i];
            }
            //std::cout << at << " " << val << std::endl;
            
            AttValPair profilePair(at, val);
            profilePointer->AddAttValPair(profilePair);
            
            it++;
        }
        
        //This fills out the emailToProfile tree
        emailToProfile.insert(email, profilePointer);
        /* //list all pairs in profile
        std::cout << profilePointer->GetEmail() << std::endl;
        for (int k = 0; k != profilePointer->GetNumAttValPairs(); k++)
        {
            AttValPair av;
            profilePointer->GetAttVal(k, av);
            std::cout << av.attribute << "->" << av.value << std::endl;
        }
        */
        
        
        
        
    } while (getline(members, line)); //This consumes the blank line
    
    /* //Testing pairToEmail tree
    std::list<std::string>* ValueTypePointer = pairToEmail.search("trait,quirky");
    if (ValueTypePointer != nullptr)
    {
        std::list<std::string>::iterator it = ValueTypePointer->begin();
        int n = 0;
        while(it != ValueTypePointer->end())
        {
            std::cout << *it <<std::endl;
            it++;
            n++;
        }
        std::cout << n << std::endl;
    }
    */
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    std::string att = input.attribute;
    std::string val = input.value;
    std::string pair = att + ',' + val;
    
    std::vector<std::string> emails;
    
    std::list<std::string>* ValueTypePointer = pairToEmail.search(pair);
    if (ValueTypePointer != nullptr)
    {
        std::list<std::string>::iterator it = ValueTypePointer->begin();
        //int n = 0;
        while(it != ValueTypePointer->end())
        {
            emails.push_back(*it);
            it++;
            //n++;
        }
        //std::cout << n << std::endl;
    }
    return emails;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    return *emailToProfile.search(email);
}


