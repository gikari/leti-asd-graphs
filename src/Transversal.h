/*
 * Constructs transversal for array of sets
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

#ifndef TRANSVERSAL_H
#define TRANSVERSAL_H

#include "Set.h"
#include "Graph.h"
#include <vector>
#include <utility>
//#include <iostream>


template <typename T>
class Transversal {
private:
    Graph<T> graph;
    Set<T> common_set;

public:
    Transversal() = delete;
    Transversal(const Transversal&) = delete;
    Transversal(Transversal&&) = delete;
    Transversal operator = (const Transversal&) = delete;
    Transversal operator = (Transversal&&) = delete;

    Transversal (const std::vector< Set<T> >& sets) : graph{}, common_set{} {
        build_superset(sets);
        build_graph(sets);


    };
    ~Transversal() {};

    void show_common_set() {
        common_set.show();
    }

    void show_graph() {
        graph.show();
    }

    void get_result() {};

private:
    void build_superset(const std::vector< Set<T> >& sets) {
        for (auto subset : sets) {
            common_set |= subset;
        }
    }
    void build_graph(const std::vector< Set<T> >& sets) {
        for (auto subset : sets) {
            graph.add_edge_from_to(T{"ss" + subset.to_str()}, T{"END"});
            for (auto element : subset.container) {
                graph.add_edge_from_to(T{element}, T{"ss" + subset.to_str()});
            }
        }
        for (auto element : common_set.container) {
            graph.add_edge_from_to(T{"BEGIN"}, T{element});
        }

    };

    bool has_routes_left() const {
        return graph.has_edge_starting_with("BEGIN");
    };
    void build_route() {};
    void change_direction_of_edges() {};
    void remove_start_and_end() {};



};

#endif
