//
//  RadixTree.h
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#ifndef RadixTree_h
#define RadixTree_h

#include <string>
#include <map>

template <typename ValueType>
class RadixTree
{
public:
    RadixTree();
    //~RadixTree();
    
    void insert(std::string key, const ValueType& value)
    {
        radixTree[key] = value;
    }
    
    ValueType* search(std::string key) const
    {
        typename std::map<std::string, ValueType>::const_iterator it;
        it = radixTree.find(key);
        
        if (it == radixTree.end())
        {
            return nullptr;
        }
        const ValueType* valueType = &it->second;
        //const ValueType valueType = it->second;
        
        return valueType;
    }
    
private:
    std::map<std::string, ValueType> radixTree;
};

#endif /* RadixTree_h */
