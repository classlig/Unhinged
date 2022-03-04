//
//  AttributeTranslator.cpp
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#include "AttributeTranslator.h"
#include <functional>
#include <string>
#include <vector>

AttributeTranslator::AttributeTranslator()
{
}

bool AttributeTranslator::Load(std::string filename)
//How do you load a file?
{
    return false;
}

unsigned int AttributeTranslator::mapFunc(std::string att,  std::string val) const
{
    std::hash<std::string> att_hash, val_hash;
    unsigned long hashValue = att_hash(att) + val_hash(val);
    
    unsigned int bucketNum = hashValue % NUM_BUCK;
    return bucketNum;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    //Create vector to store the found (or not found) pair
    std::vector<AttValPair> compatiblePair;
    
    //Locate where the pair would be
    int bucket = mapFunc(source.attribute, source.value);
    BUCKET attributeBucket = m_buckets[bucket];
    
    
    if (attributeBucket.used == false)
    {
       return compatiblePair;
    }
    
    else if (attributeBucket.used == true)
    {
        while (attributeBucket.source != source)
        {
            if (attributeBucket.next == nullptr)
            {
                return compatiblePair;
            }
            
            attributeBucket = *attributeBucket.next;
        }
        
        if (attributeBucket.source == source)
        {
            compatiblePair.push_back(attributeBucket.compatible);
            return compatiblePair;
        }
    }
    
    return compatiblePair;
}
