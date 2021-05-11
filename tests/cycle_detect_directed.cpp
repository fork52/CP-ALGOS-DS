#include <bits/stdc++.h>
#include "../Graphs/Directed/cycle_detect_directed.cpp"
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
using namespace std;

using int_vec = vector<int>;

const int RAND_SEED = 10; 

/* Tested on: https://binarysearch.com/problems/Course-Scheduling*/
struct Graph_Trusted {
    enum node_status { unvisited = 0, explore = 1, visited = 2 };
    vector<vector<int>> graph;
    vector<node_status> status;

    Graph_Trusted(vector<vector<int>> &adj_list) {
        graph = adj_list;
        status.assign(adj_list.size(), unvisited);
    }

    bool dfs(int node) {
        if (status[node] == visited) return false;
        if (status[node] == explore) return true;
        status[node] = explore;
        for (auto const &neigh : graph[node])
            if (dfs(neigh)) return true;
        status[node] = visited;
        return false;
    }
    bool check_cycle(){
        for(int i=0;i<graph.size();i++)
            if(dfs(i)) return true;
        return false;
    }
};

vector<int_vec> generate_graph(
    int nodes,
    int density,
    bool no_cycle = false,
    bool want_selfcycle = false
)
{
    vector<int_vec> graph(nodes);
    srand(RAND_SEED);

    bool choose;
    int randno;

    for (int n1 = 0; n1 < nodes; n1++)
    {
        for (int n2 = no_cycle ? n1 + 1 : 0; n2 < nodes; n2++)
        {

            if (n1 == n2 && !want_selfcycle)
                continue;

            randno = rand() % 101;
            if (randno <= density)
            {
                graph[n1].push_back(n2);
            }
        }
    }

    return graph;
}

TEST_CASE("Single Node Cycle")
{
    vector<int_vec> graph = {{0}}; 
    Graph<int> g = Graph<int>(graph);
    REQUIRE( g.is_cyclic() == true);
}

TEST_CASE("500 nodes - no cycle")
{

    int density = GENERATE(5,10,20,50,70,100);
    CAPTURE(density);

    bool no_cycle = true;
    vector<int_vec> sample_g = generate_graph(500,density,no_cycle);
    Graph<int> g = Graph<int>(sample_g);
    REQUIRE( g.is_cyclic() == false );
}


TEST_CASE("5000 nodes - with or without cycle")
{

    int density = GENERATE(5,10,20,50,70,100);
    CAPTURE(density);

    bool no_cycle = true;
    vector<int_vec> sample_g = generate_graph(5000,density,no_cycle);
    Graph_Trusted trusted(sample_g);
    Graph<int> g = Graph<int>(sample_g);
    REQUIRE( g.is_cyclic() == trusted.check_cycle() );
}
