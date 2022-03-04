//
//  AttributeTranslator.h
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include "provided.h"
#include <string>

class AttributeTranslator
{
public:
    AttributeTranslator();
    
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    
    struct BUCKET
    {
        AttValPair source;
        AttValPair compatible;
        
        bool used = false;
        BUCKET* next = nullptr;
    };
    
    static const int NUM_BUCK = 222223;
    
    unsigned int mapFunc(std::string att, std::string val) const;
    BUCKET m_buckets[NUM_BUCK];
    
};
#endif /* AttributeTranslator_h */
