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
    Set():container{}{};

    Set(const std::string& str){
        for (auto ch : str) {
            add(ch);
        }
    };

    Set(const Set& another):container{another.container} {};
    Set(Set&& another):container{another.container} {};

    Set& operator = (const Set& another) {
        if (this != &another)
            container = another.container;
        return *this;
    };

    Set& operator = (Set&& another) {
        if (this != &another)
            container = another.container;
        return *this;
    };
    ~Set() {};


    void add(T element) {
        if (!contains(element)) {
            container.push_back(element);
        }
    };

    void remove(T element) {
        container.remove(element);
    };

    bool contains(T element) const {
        for (auto element_in_set : container) {
            if (element == element_in_set)
                return true;
        }
        return false;
    };

    Set operator & (Set& another) const {
        Set new_set {};

        for (auto element_in_this_set : container) {
            for (auto element_in_another_set : another.container)
                if (element_in_this_set == element_in_another_set) {
                    new_set.add(element_in_this_set);
                }
        }

        return new_set;
    };

    Set operator | (Set& another) const {
        Set new_set {};

        for (auto element_in_this_set : container) {
            bool is_found = false;
            for (auto element_in_another_set : another.container) {
                if (element_in_this_set == element_in_another_set) {
                    is_found = true;
                    break;
                }
            }

            if (!is_found) {
                new_set.add(element_in_this_set);
            }
        }
        for (auto element_in_another_set : another.container) {
            new_set.add(element_in_another_set);
        }

        return new_set;
    };

};

template <typename T>
std::ostream& operator << ( std::ostream& os, const Set<T>& set) {
    for (auto elem : set.container)
        os << elem;
    return os;
};

#endif
