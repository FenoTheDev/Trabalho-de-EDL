#ifndef NOHASH_HPP
#define NOHASH_HPP

#include "Item.hpp"

class NoHash {
public:
    Item* item;
    NoHash* proximo;

    NoHash(Item* i){
        item = i;
        proximo = nullptr;
    }
};

#endif