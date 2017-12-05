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
#include <algorithm>
#include <stdexcept>
#include <iostream>


class wrong_input_error : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

class no_way_in_graph_error : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

template <typename T>
class Transversal {
private:
    Graph<T> graph;
    Set<T> superset;
    std::vector<std::pair<T,T>> last_route;
    std::vector<std::pair<T,T>> tmp_route;
    std::vector<std::pair<T,T>> bijection;

public:
    Transversal() = delete;
    Transversal(const Transversal&) = delete;
    Transversal(Transversal&&) = delete;
    Transversal operator = (const Transversal&) = delete;
    Transversal operator = (Transversal&&) = delete;

    Transversal (const std::vector< Set<T> >& sets) : graph{}, superset{}, last_route{}, tmp_route{}, bijection{} {
        build_superset(sets);

        if (sets.size() > superset.power()) {
            throw wrong_input_error{"Transversal cannot be builded with current input"};
        }

        build_graph(sets);
        show_graph();

        while (has_routes_left()) {
            try {
                build_some_route();
            }
            catch (no_way_in_graph_error) {
                graph.remove_edge(std::pair<T,T>{T{"BEGIN"}, T{last_route.back().second}});
                //std::cout << "Defective element" << std::endl;
            }
            show_last_route();
            change_direction_of_edges();
            remove_start_and_end();
        }

        build_bijection(sets);
    };

    ~Transversal() {};

    void show_common_set() {
        std::cout << "Transversal Superset: " << std::endl;
        superset.show();
    };

    void show_graph() {
        std::cout << "Transversal Graph: " << std::endl;
        graph.show();
    };

    void show_result() {
        std::cout << "Transversal: " << std::endl;
        std::cout << "{ ";
        for (auto view : bijection) {
            std::cout << view.first << " -> " << view.second << ", ";
        }
        std::cout << "}" << std::endl;
    };

private:
    void show_last_route() {
        for (auto edge : last_route) {
            std::cout << "[ " << edge.first << ", " << edge.second  << " ]" << std::endl;
        }
    };

    void build_superset(const std::vector< Set<T> >& sets) {
        for (auto subset : sets) {
            superset |= subset;
        };
    };

    void build_graph(const std::vector< Set<T> >& sets) {
        for (auto subset : sets) {
            graph.add_edge_from_to(T{subset.get_unique_str_id()}, T{"END"});
            for (auto element : subset.container) {
                graph.add_edge_from_to(T{element}, T{subset.get_unique_str_id()});
            }
        }
        for (auto element : superset.container) {
            graph.add_edge_from_to(T{"BEGIN"}, T{element});
        }
    };

    void build_bijection(const std::vector< Set<T> >& sets) {
        for (auto set : sets) {
            auto edge = graph.get_edge_starting_with(T{set.get_unique_str_id()});
            bijection.push_back(std::pair<T,T>{edge.second, set.to_str()});
        }
    };

    bool has_routes_left() const {
        return graph.has_edge_ending_with("END");
    };

    void build_some_route() {
        last_route.clear();
        tmp_route.clear();
        auto start_edge = graph.get_edge_starting_with(T{"BEGIN"});

        build_route_from(start_edge);
        last_route.push_back(start_edge);

        if (last_route.front().second != "END")
            throw no_way_in_graph_error{"Cannot build way in graph!"};
    };

    bool build_route_from(std::pair<T,T> edge) {
        if ( edge.second == "END" ) {
            return true;
        }

        auto possible_ways = graph.get_edges_starting_with(edge.second);
        for (auto way : possible_ways) {
            if (std::find(tmp_route.begin(), tmp_route.end(), way) == tmp_route.end()) {
                tmp_route.push_back(way);
                auto has_reached_the_end = build_route_from(way);
                if (has_reached_the_end ) {
                    last_route.push_back(way);
                    return true;
                }
                tmp_route.pop_back();
            }
        }
        return false;
    };

    void change_direction_of_edges() {
        for (auto edge : last_route) {
            graph.change_edge_direction(edge);
        }
    };

    void remove_start_and_end() {
        graph.remove_edge(std::pair<T,T>{last_route.front().second, last_route.front().first});
        graph.remove_edge(std::pair<T,T>{last_route.back().second, last_route.back().first});
    };

};

#endif
