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
#include <stdexcept>
#include <iostream>


class wrong_input_error : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

template <typename T>
class Transversal {
private:
    Graph<T> graph;
    Set<T> superset;
    std::vector<std::pair<T,T>> last_route;

public:
    Transversal() = delete;
    Transversal(const Transversal&) = delete;
    Transversal(Transversal&&) = delete;
    Transversal operator = (const Transversal&) = delete;
    Transversal operator = (Transversal&&) = delete;

    Transversal (const std::vector< Set<T> >& sets) : graph{}, superset{}, last_route{} {
        build_superset(sets);

        if (sets.size() > superset.power()) {
            throw wrong_input_error{"Transversal cannot be builded with current input"};
        }

        build_graph(sets);

        while (has_routes_left()) {
            build_some_route();
            change_direction_of_edges();
        }
    };

    ~Transversal() {};

    void show_common_set() {
        superset.show();
    };

    void show_graph() {
        graph.show();
    };

    void get_result() {

    };

private:
    void build_superset(const std::vector< Set<T> >& sets) {
        for (auto subset : sets) {
            superset |= subset;
        };
    };
    void build_graph(const std::vector< Set<T> >& sets) {
        for (auto subset : sets) {
            graph.add_edge_from_to(T{"ss" + subset.to_str()}, T{"END"});
            for (auto element : subset.container) {
                graph.add_edge_from_to(T{element}, T{"ss" + subset.to_str()});
            }
        }
        for (auto element : superset.container) {
            graph.add_edge_from_to(T{"BEGIN"}, T{element});
        }

    };

    bool has_routes_left() const {
        return graph.has_edge_ending_with("END");
    };

    void build_some_route() {
        auto start_edge = graph.get_edge_starting_with("BEGIN");

        build_route_from(start_edge);
        last_route.push_back(start_edge);

        std::cout << "Reverse route: " << std::endl;
        for (auto elem : last_route) {
            std::cout << "[ " << elem.first << ", " << elem.second << " ]" << std::endl;
        }

        if (last_route[0].second != "END")
            throw std::runtime_error{"Cannot build way in graph!"};
    };

    bool build_route_from(std::pair<T,T> edge) {
        if ( edge.second == "END" ) {
            return true;
        }

        auto possible_ways = graph.get_edges_starting_with(edge.second);
        for (auto way : possible_ways) {
            auto has_chance_to_reach_end = build_route_from(way);
            if (has_chance_to_reach_end ) {
                last_route.push_back(way);
            }
            return has_chance_to_reach_end;
        }
        return false;
    };

    void change_direction_of_edges() {

    };

    void remove_start_and_end() {

    };



};

#endif
