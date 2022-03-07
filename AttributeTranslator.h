//
//  AttributeTranslator.h
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include "provided.h"
#include "RadixTree.h"
#include <string>
#include <vector>

class AttributeTranslator
{
public:
    AttributeTranslator();
    ~AttributeTranslator();
    
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
    
private:
    
    struct BUCKET
    {
        //Initialize buckets with empty pairs
        AttValPair* source = nullptr;
        AttValPair* compatible = nullptr;
        
        bool used = false;
        BUCKET* next = nullptr;
    };
    
    static const int NUM_BUCK = 222223;
    BUCKET m_buckets[NUM_BUCK];
    
    unsigned int mapFunc(std::string att, std::string val) const;
    
    
    RadixTree<std::string> sourceCompatAttPair;
    
};
#endif /* AttributeTranslator_h */
