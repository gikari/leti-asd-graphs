/*
 * Simple oriented graph, implemented as edges list
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

#ifndef GRAPH_H
#define GRAPH_H


#include <utility>
#include <iostream>
#include "Set.h"

template <typename T>
class Graph {
private:
    std::list < std::pair<T,T> > edges;

public:
    Graph() : edges{} {};
    Graph(const Graph&) = delete;
    Graph(Graph&&) = delete;
    Graph operator = (const Graph&) = delete;
    Graph operator = (Graph&&) = delete;
    ~Graph() {};

    void add_edge(std::pair<T,T> edge) {
        edges.push_back(edge);
    };

    void remove_edge(std::pair<T,T> edge) {
        edges.remove(edge);
    };

    void add_edge_from_to(T from, T to) {
        add_edge(std::pair<T,T>{from, to});
    }

    void show() {
        std::cout << *this << std::endl;
    }

    friend std::ostream& operator << ( std::ostream& os, const Graph& graph) {
        for (auto elem : graph.edges)
            os << "{ " << elem.first << ", " << elem.second << " }; \n";
        return os;
    };

};

#endif
