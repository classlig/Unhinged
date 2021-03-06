//
//  main.cpp
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include "RadixTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    /*
    PersonProfile pp ("Kristal Light", "kristallee365@gmail.com");
    AttValPair a("hobby", "reading");
    AttValPair b("hobby", "gaming");
    AttValPair c("quality", "nice");
    AttValPair d("quality", "nice");
    pp.AddAttValPair(a);
    pp.AddAttValPair(b);
    pp.AddAttValPair(c);
    pp.AddAttValPair(d);
    
    for (int k = 0; k != pp.GetNumAttValPairs(); k++)
    {
        AttValPair av;
        pp.GetAttVal(k, av);
        cout << av.attribute << "->" << av.value << endl;
    }
    
    AttributeTranslator at;
    //Comment out either pathname depending on compiler
    string pathname =  "/Users/Kristal/Documents/CS 32/Project 4/Unhinged/translator.txt";
    
    //string pathname = "translator.txt";
    if (at.Load(pathname) == false)
    {
        cout << "error" << endl;
    }
    
    
    MemberDatabase md;
    //Comment out either pathname depending on compiler
    string mdpathname = "/Users/Kristal/Documents/CS 32/Project 4/Unhinged/members.txt";
    //string mdpathname = "members.txt";
    
    
    if (md.LoadDatabase(mdpathname) == false)
    {
        cout << "error at md" << endl;
    }
    
    AttValPair mba("trait", "quirky");
    md.FindMatchingMembers(mba);
    
    AttValPair mbb("hobby", "eating");
    vector<string> v = md.FindMatchingMembers(mbb);
    if (v.empty() == true)
    {
        cout << "good" << endl;
    }
    
    const PersonProfile* personProfilePointer = md.GetMemberByEmail("AbFow2483@charter.net");
    string email = personProfilePointer->GetEmail();
    cout << email << endl;
    */
    MatchMaker mm;
    mm.IdentifyRankedMatches("anisha@gmail.com", 2);
    
    RadixTree<string> rt;
    rt.insert("apples", "oranges");
    rt.insert("bananas", "peaches");
    
    string* s;
    s = rt.search("bananas");
    cout << *s << endl;
     
}

        
    
    















/*
const std::string MEMBERS_FILE    = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}
*/
