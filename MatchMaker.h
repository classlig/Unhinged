//
//  MatchMaker.h
//  Project 4
//
//  Created by Kristal Light on 3/2/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include "provided.h"
#include <string>
#include <vector>

class MatchMaker
{
public:
    MatchMaker();
    std::vector<EmailCount>* IdentifyRankedMatches(std::string email, int threshold) const;
};
#endif /* MatchMaker_h */
