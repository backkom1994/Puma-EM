/**********************************************************************
 *
 * dictionary.h
 *
 * Copyright (C) 2016 Idesbald Van den Bosch
 *
 * This file is part of Puma-EM.
 * 
 * Puma-EM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Puma-EM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Puma-EM.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Suggestions/bugs : <vandenbosch.idesbald@gmail.com>
 *
 **********************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <algorithm>

// we need the following Dictionary class in various places
template <typename K, typename V>
class Dictionary {
    K key;
    V val;
  public:
    // constructors
    Dictionary(const K k, const V v) {key = k; val = v;};
    const V getVal(void) const {return val;};
    const K getKey(void) const {return key;};
    Dictionary(const Dictionary & dictionaryToCopy) {val = dictionaryToCopy.getVal(); key = dictionaryToCopy.getKey();}; // copy constructor
    ~Dictionary(){};
    // overloaded operators for sorting
    bool operator== (const Dictionary & right) const {if ( getKey() == right.getKey() ) return 1; else return 0;};
    bool operator< (const Dictionary & right) const {if ( getKey() < right.getKey() ) return 1; else return 0;};
};

template <typename K, typename V1, typename V2>
class Dictionary2 {
    K key;
    V1 val1;
    V2 val2;
  public:
    // constructors
    Dictionary2(const K k, const V1 v1, const V2 v2) {key = k; val1 = v1; val2 = v2;};
    const V1 getVal1(void) const {return val1;};
    const V2 getVal2(void) const {return val2;};
    const K getKey(void) const {return key;};
    Dictionary2(const Dictionary2 & dictionary2ToCopy) {val1 = dictionary2ToCopy.getVal1(); val2 = dictionary2ToCopy.getVal2(); key = dictionary2ToCopy.getKey();}; // copy constructor
    ~Dictionary2(){};
    // overloaded operators for sorting
    bool operator== (const Dictionary2 & right) const {if ( getKey() == right.getKey() ) return 1; else return 0;};
    bool operator< (const Dictionary2 & right) const {if ( getKey() < right.getKey() ) return 1; else return 0;};
};

#endif
