//
//  AttributeTranslator.cpp
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#include "AttributeTranslator.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

AttributeTranslator::AttributeTranslator()
{}


AttributeTranslator::~AttributeTranslator()
{
    int i = 0;
    BUCKET* bucketPointer = &m_buckets[i];
    BUCKET* mainBucketPointer;
    
    while (i < NUM_BUCK)
    {
         
        mainBucketPointer = &m_buckets[i];
        //bucketPointer = &m_buckets[i];
        
        
        BUCKET* prev = bucketPointer;
        while (bucketPointer->used == true && bucketPointer->next != nullptr)
        {
            prev = bucketPointer;
            bucketPointer = bucketPointer->next;
        }
        
        if (bucketPointer == mainBucketPointer)
        {
            i++;
            if (i != NUM_BUCK)
            {
                mainBucketPointer = &m_buckets[i];
            }
        }
        
        if (bucketPointer->used == true && bucketPointer->next == nullptr)
        {
            delete bucketPointer->source;
            bucketPointer->source = nullptr;
            delete bucketPointer->compatible;
            bucketPointer->compatible = nullptr;
            
            bucketPointer->used = false;
        }
        
        //If the bucket is empty and unused
        if ( bucketPointer->used == false &&  bucketPointer->next == nullptr)
        {
            prev->next = nullptr;
            if (prev != bucketPointer) //If prev == next then we are at a bucket that is not dynamically allocated (A.K.A. the main array)
            {
                delete bucketPointer;
            }
            
            bucketPointer = mainBucketPointer;
        }
        
        
    }
}

 
bool AttributeTranslator::Load(std::string filename)
{
    
    //Load file and if anything doesn't load properly, return false
    std::ifstream translator(filename);
    if (!translator)
    {
        return false;
    }

    std::string line;
    while (getline(translator, line))
    {
        std::istringstream iss(line);

        std::string source_attribute, source_value, compatible_attribute, compatible_value, trash;
        if (!getline(iss, source_attribute, ','))
        {
            return false;
        }
        if (!getline(iss, source_value, ','))
        {
            return false;
        }
        if (!getline(iss, compatible_attribute, ','))
        {
            return false;
        }
        if (!getline(iss, compatible_value))
        {
            return false;
        }
        
        sourceCompatAttPair.insert(source_attribute, source_attribute);
        
        //If getting the line goes smoothly, create a bucket# and try to fill it
        int numBucket = mapFunc(source_attribute, source_value);
        
        BUCKET* bucketPointer = &m_buckets[numBucket];
        
        while (bucketPointer->used == true && bucketPointer->next != nullptr)
        {
            bucketPointer = bucketPointer->next;
        }
        
        if (bucketPointer->used == false)
        {
            AttValPair* sourcePair = new AttValPair(source_attribute, source_value);
            
            AttValPair* compatiblePair = new AttValPair(compatible_attribute, compatible_value);
            
            m_buckets[numBucket].next = new BUCKET;
            m_buckets[numBucket].next->source = sourcePair;
            m_buckets[numBucket].next->compatible = compatiblePair;
            m_buckets[numBucket].next->used = true;
            bucketPointer->used = true;
        }
    }
    return true;
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
        if (attributeBucket.source == nullptr)
        {
            attributeBucket = *attributeBucket.next;
        }
        
        while (*attributeBucket.source != source)
        {
            if (attributeBucket.next == nullptr)
            {
                return compatiblePair;
            }
            
            attributeBucket = *attributeBucket.next;
        }
        
        if (*attributeBucket.source == source)
        {
            compatiblePair.push_back(*attributeBucket.compatible);
            return compatiblePair;
        }
    }
    
    return compatiblePair;
}

