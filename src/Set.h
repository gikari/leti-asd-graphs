/*
 * Simple Set - structure to store some unordered unique values
 * Copyright (C) 2017  Mikhail <zomial@yandex.ru>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef SET_H
#define SET_H

#include <string>
#include <list>

template <typename T>
class Set;

template <typename T>
std::ostream& operator << ( std::ostream&, const Set<T>&);

template <typename T>
class Set {
    friend std::ostream& operator << <T>( std::ostream&, const Set<T>&);
private:
    std::list<T> container;

public:
    Set(){};
    Set(const std::string&){};
    Set(const Set&) {};
    Set(Set&&) {};
    Set operator = (const Set&) {};
    Set operator = (Set&&) {};
    ~Set() {};

    void add(T) {};
    void remove(T) {};
    bool contains(T) const {};
    Set operator & (Set&) const {};
    Set operator | (Set&) const {};

};

template <typename T>
std::ostream& operator << ( std::ostream& os, const Set<T>& set) {
    for (auto elem : set.container)
        os << elem;
    return os;
};

#endif
