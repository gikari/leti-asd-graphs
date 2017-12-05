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
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>

template <typename T>
class Set {
private:
    std::list<T> container;
    int init_id;
    static int last_id;
public:
    Set():container{}, init_id{++last_id} {};

    Set(const std::string& str): container{}, init_id{++last_id}{
        for (auto ch : str) {
            add_element(T{ch});
        }
    };

    Set(const Set& another):container{another.container}, init_id{another.init_id} {};
    Set(Set&& another):container{another.container}, init_id{another.init_id} {};

    Set& operator = (const Set& another) {
        if (this != &another) {
            container = another.container;
        }
        return *this;
    };

    Set& operator = (Set&& another) {
        if (this != &another) {
            container = another.container;
        }
        return *this;
    };
    ~Set() {};


    void add_element(T element) {
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

    void show() {
        std::cout << *this << std::endl;
    };

    std::string get_unique_str_id() const {
        std::string str{"ss"};
        str += std::to_string(init_id);
        str += "ss";
        for (auto elem : container)
            str += std::string{elem};
        return str;
    };

    int get_id() const {
        return init_id;
    }

    std::string to_str() const {
        std::string str{};
        for (auto elem : container)
            str += std::string{elem};
        return str;
    }

    int power() const {
        return container.size();
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

    Set& operator &= (Set& another) {
        Set new_set{*this & another};
        *this = new_set;
        return *this;
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
                new_set.add_element(element_in_this_set);
            }
        }
        for (auto element_in_another_set : another.container) {
            new_set.add_element(element_in_another_set);
        }

        return new_set;
    };

    Set& operator |= (Set& another) {
        Set new_set{*this | another};
        *this = new_set;
        return *this;
    };

    template <typename U>
    friend class Transversal;

    friend std::ostream& operator << ( std::ostream& os, const Set& set) {
        for (auto elem : set.container)
            os << elem;
        return os;
    };

};
template <typename T>
int Set<T>::last_id = 0;

#endif
