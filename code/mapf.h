#ifndef MAPF_H
#define MAPF_H

#include <vector>
#include <set>

#include "Solver.h"
#include "map.h"

using namespace std;

class MAPF_handler
{
private:
    vector<vector<int>> create_edges(size_t, size_t, set<uint16_t> &, set<uint16_t> &);

public:
    vector<vector<bool>> graph;
    vector<pair<uint16_t, uint16_t>> agents;
    encode_MAP map;
    uint16_t time;

    MAPF_handler(){};
    MAPF_handler(vector<vector<bool>> in) : graph(in) {}
    MAPF_handler(string, bool);

    uint16_t get_shortest_path(); // get max of shortest paths
    uint16_t shortest_path(uint16_t, uint16_t);
    void add_agent(uint16_t, uint16_t);
    void encode(Glucose::Solver &);
    bool check_result(const vector<bool> &);
    void print(const vector<bool> &);        // print SAT solver result
    set<uint16_t> expand(set<uint16_t> &);   // expand for encoding
    set<uint16_t> expand_2(set<uint16_t> &); // expand for shortest path
    vector<vector<int>> check_collisions(const vector<bool> &);
};

#endif
