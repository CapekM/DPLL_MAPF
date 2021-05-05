#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <chrono>

#include "Solver.h"
#include "mapf.h"

using namespace Glucose;
using namespace std;

MAPF_handler::MAPF_handler(string filename, bool testing)
{
    size_t default_length = 50;
    if (filename != "")
    {
        std::ifstream file;
        file.open(filename, ios_base::in);
        if (file.is_open())
        {
            /* Loading agents */
            string tmp;
            getline(file, tmp);

            vector<int> start(default_length, 0);
            vector<int> target(default_length, 0);
            size_t size = 0;
            while (true)
            {
                if (file.eof())
                    break;
                string line;
                getline(file, line);
                if (line.at(0) == 'E')
                    break;
                ++size;

                string str = line.substr(1, line.find(':'));
                int vertex = atoi(str.c_str());
                line.erase(0, str.size() + 5);
                str = line.substr(0, line.find(':'));
                int first = atoi(str.c_str());
                line.erase(0, str.size() + 1);
                str = line.substr(0, line.find(':'));
                int second = atoi(str.c_str());

                // cout << vertex << " " << first << " " << second << endl;

                if (first != 0)
                {
                    // cout << vertex << " " << first << "\n";
                    start[first] = vertex + 1;
                }
                if (second != 0)
                {
                    target[second] = vertex + 1;
                }
            }

            for (size_t i = 0; i < default_length; i++)
                if (start[i] != 0 || target[i] != 0)
                    this->add_agent(start[i], target[i]);

            /* Loading edges */
            vector<vector<bool>> graph(size, vector<bool>(size, 0));
            for (size_t i = 0; i < size; i++)
            {
                graph[i][i] = true;
            }

            while (true)
            {
                if (file.eof())
                    break;
                string line;
                getline(file, line);
                if (line.empty())
                    break;
                string str = line.substr(1, line.find(','));
                int primus = atoi(str.c_str());
                line.erase(0, str.size() + 1);
                str = line.substr(0, line.find('}'));
                int secundus = atoi(str.c_str());

                // cout << primus << " " << secundus << "\n";
                graph[primus][secundus] = true;
                graph[secundus][primus] = true;
            }
            file.close();
            this->graph = graph;
            if (!testing)
                cout << "file \"" << filename << "\" successfully loaded" << endl;
        }
        else
        {
            cerr << "Couldn't open the file" << endl;
            exit(42);
        }
    }
    else
    {

        /* DUMMY 0 */
        this->graph = {
            {1, 0, 1, 0, 0},
            {0, 1, 1, 0, 0},
            {1, 1, 1, 1, 1},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 0, 1},
        };
        this->add_agent(2, 4);
        this->add_agent(5, 1);

        /* DUMMY 1 */
        // this->graph = {
        //     {1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        //     {1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        //     {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        //     {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        //     {1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0},
        //     {0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0},
        //     {0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        //     {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0},
        //     {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0},
        //     {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
        //     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        //     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        // };
        // this->add_agent(12, 3);
        // this->add_agent(4, 7);
        // this->add_agent(13, 2);

        cout << "default problem" << endl;
    }
}

void MAPF_handler::add_agent(uint16_t from, uint16_t to)
{
    agents.push_back(make_pair(from, to));
}

uint16_t MAPF_handler::get_shortest_path()
{
    uint16_t max = 0;
    for (const auto &agent : agents)
    {
        uint16_t tmp = shortest_path(agent.first, agent.second);
        max = (tmp > max) ? tmp : max;
    }
    return max;
}

uint16_t MAPF_handler::shortest_path(uint16_t a, uint16_t b)
{
    if (a == b)
    {
        return 0;
    }
    uint16_t time = 0;
    set<uint16_t> start{a};
    set<uint16_t> target{b};
    while (true)
    {
        set<uint16_t> tmp = expand_2(start);
        time++;

        vector<uint16_t> intersection;
        set_intersection(tmp.begin(), tmp.end(),
                         target.begin(), target.end(),
                         back_inserter(intersection));
        if (!intersection.empty())
        {
            break;
        }
        start.insert(tmp.begin(), tmp.end());

        tmp = expand_2(target);
        time++;

        set_intersection(tmp.begin(), tmp.end(),
                         start.begin(), start.end(),
                         back_inserter(intersection));
        if (!intersection.empty())
        {
            break;
        }
        target.insert(tmp.begin(), tmp.end());
    }

    return time;
}

set<uint16_t> MAPF_handler::expand_2(set<uint16_t> &in)
{
    set<uint16_t> result;
    for (const auto &v : in)
    {
        for (size_t i = 0; i < graph.size(); ++i)
        {
            if (graph[v - 1][i] && find(in.begin(), in.end(), i + 1) == in.end())
            {
                result.insert(i + 1);
            }
        }
    }
    return result;
}

set<uint16_t> MAPF_handler::expand(set<uint16_t> &in)
{
    set<uint16_t> tmp = in;
    for (const auto &v : in)
    {
        for (size_t i = 0; i < graph.size(); ++i)
        {
            if (graph[v - 1][i])
            {
                tmp.insert(i + 1);
            }
        }
    }
    return tmp;
}

vector<vector<int>> MAPF_handler::check_collisions(const vector<bool> &solver_result)
{
    /* decoding */
    vector<vector<uint16_t>> decoded(agents.size());
    for (size_t i = 0; i < solver_result.size(); i++)
    {
        if (solver_result[i])
        {
            decoded[map.map[i].agent].push_back(map.map[i].vertex); // map is in time order so I can ignore time
        }
    }
    /* checking collisions */
    vector<vector<int>> collisions;
    for (size_t t = 0; t < decoded[0].size(); t++)
    {
        for (size_t a = 0; a < agents.size(); a++)
        {
            // cout << "\tDecoded[a]size " << decoded[a].size() << endl; // TODO error Nektere maji jinou velikost. Veschny maji mit stejnou!
            size_t tmp_agent = a + 1;
            if (tmp_agent == agents.size())
            {
                break;
            }
            while (tmp_agent < agents.size())
            {
                if (decoded[a][t] == decoded[tmp_agent][t])
                {
                    vector<int> tmp = {map.encode(t, a, {-decoded[a][t]})[0], map.encode(t, tmp_agent, {-decoded[tmp_agent][t]})[0]};
                    collisions.push_back(tmp);
                }
                tmp_agent++;
            }
        }
    }
    if (decoded[0].size() == 1) // if start and target are in swap we continue
        return collisions;
    /* add agents target for checking swaps */
    for (size_t a = 0; a < agents.size(); a++)
    {
        decoded[a].push_back(agents[a].second);
    }
    /* checking swaps */
    for (size_t t = 1; t < decoded[0].size(); t++)
    {
        for (size_t a = 0; a < agents.size(); a++)
        {
            size_t tmp_agent = a + 1;
            if (tmp_agent == agents.size())
            {
                break;
            }
            while (tmp_agent < agents.size())
            {
                if ((decoded[a][t] == decoded[tmp_agent][t - 1]) && (decoded[a][t - 1] == decoded[tmp_agent][t]))
                {
                    vector<int> tmp;
                    if (t < decoded[0].size() - 1)
                    {
                        tmp = {map.encode(t, a, {-decoded[a][t]})[0], map.encode(t, tmp_agent, {-decoded[tmp_agent][t]})[0], map.encode(t - 1, a, {-decoded[a][t - 1]})[0], map.encode(t - 1, tmp_agent, {-decoded[tmp_agent][t - 1]})[0]};
                    }
                    else // if last time forbid only last pair
                    {
                        tmp = {map.encode(t - 1, a, {-decoded[a][t - 1]})[0], map.encode(t - 1, tmp_agent, {-decoded[tmp_agent][t - 1]})[0]};
                    }
                    collisions.push_back(tmp);
                }
                tmp_agent++;
            }
        }
    }
    return collisions;
}

bool MAPF_handler::check_result(const vector<bool> &result)
{
    vector<vector<uint16_t>> decoded(agents.size());

    for (size_t i = 0; i < result.size(); i++)
    {
        if (result[i])
        {
            decoded[map.map[i].agent].push_back(map.map[i].vertex); // map is in time order so I can ignore time
        }
    }

    for (size_t t = 1; t < decoded[0].size(); t++)
    {
        for (size_t a = 0; a < agents.size(); a++)
        {
            if (!graph[decoded[a][t] - 1][decoded[a][t - 1] - 1]) // graph consistency
            {
                cerr << "consistency " << decoded[a][t] - 1 << " " << decoded[a][t - 1] - 1 << "\n";
                return true;
            }
            size_t tmp_agent = a + 1;
            if (tmp_agent == agents.size())
            {
                break;
            }
            while (tmp_agent < agents.size())
            {
                if (decoded[a][t] == decoded[tmp_agent][t]) // collisons
                {
                    return true;
                }
                if ((decoded[a][t] == decoded[tmp_agent][t - 1]) && (decoded[a][t - 1] == decoded[tmp_agent][t])) // swaps
                {
                    return true;
                }
                tmp_agent++;
            }
        }
    }
    return false;
}

void MAPF_handler::print(const vector<bool> &result)
{
    vector<vector<uint16_t>> decoded(agents.size());
    for (size_t i = 0; i < result.size(); i++)
    {
        if (result[i])
        {
            decoded[map.map[i].agent].push_back(map.map[i].vertex); // map is in time order so I can ignore time
        }
    }
    cout << "RESULT:\n";
    int i = 0;
    for (const auto &d : decoded)
    {
        cout << " A" << i << ":\t";
        for (const auto vertex : d)
        {
            cout << vertex << ((vertex > 10) ? ((vertex > 100) ? " " : "  ") : "   ");
        }
        cout << "| " << agents[i].second << endl;
        i++;
    }
}

void MAPF_handler::encode(Glucose::Solver &solver)
{
    map.map.clear();                                   // delete previous mapping if reapeted encoding
    vector<vector<set<uint16_t>>> TEGS(agents.size()); // TEGS[agent][time][vertex]
    uint16_t TEGS_count = 0;

    for (const auto &agent : agents)
    {
        // Time Expansion
        vector<set<uint16_t>> TEG(time + 1);
        TEG[0].insert(agent.first);     // first element is start
        TEG[time].insert(agent.second); // last element is target

        for (int t = 0; t < time - 1; ++t)
        {
            TEG[t + 1] = expand(TEG[t]);
        }
        // Back pruning of TEG
        vector<set<uint16_t>> back_TEG(time);
        back_TEG[0].insert(agent.second);
        for (int t = 1; t < time; t++)
        {
            back_TEG[t] = expand(back_TEG[t - 1]);

            vector<uint16_t> intersection;
            set_intersection(TEG[time - t].begin(), TEG[time - t].end(),
                             back_TEG[t].begin(), back_TEG[t].end(),
                             back_inserter(intersection));

            set<uint16_t> tmp(intersection.begin(), intersection.end());
            if (tmp == TEG[time - t])
            {
                break;
            }
            TEG[time - t] = tmp;
        }

        TEGS[TEGS_count++] = TEG;
    }

    /* Finding single vertex in TEGs */
    for (size_t a = 0; a < TEGS.size(); a++)
    {
        for (size_t t = 1; t < TEGS[a].size() - 1; t++)
        {
            if (TEGS[a][t].size() < 2)
            { // delete this vertex from other TEGs
                for (size_t a_tmp = 0; a_tmp < TEGS.size(); a_tmp++)
                {
                    if (a != a_tmp)
                        TEGS[a_tmp][t].erase(*TEGS[a][t].begin());
                }
            }
        }
    }

    for (size_t t = 0; t < time; t++)
    {
        for (size_t a = 0; a < TEGS.size(); a++) // for each agent's TEG
        {
            map.add(t, a, TEGS[a][t]);
            for (size_t i = 0; i < TEGS[a][t].size(); i++)
            {
                solver.newVar();
            }
            /* Create, Encode and Add rules */
            if (TEGS[a][t].size() == 1) // special case if there is just one vertex in time slice
            {
                solver.add_clauses({map.encode_one(t, a, *TEGS[a][t].begin())});
            }
            else
            {
                solver.add_disallowing_pairs(map.encode_set(t, a, TEGS[a][t]));
                solver.add_clauses(create_edges(t, a, TEGS[a][t - 1], TEGS[a][t]));
            }
        }
    }

    /* Adding chokepoints eagerly */
    // for (size_t a = 0; a < TEGS.size(); a++)
    // {
    //     for (size_t t = 1; t < TEGS[a].size() - 1; t++)
    //     {
    //         if (TEGS[a][t].size() == 2) // we found chokepoint in TEG -> we could create collisions here
    //         {
    //             for (size_t a_tmp = 0; a_tmp < TEGS.size(); a_tmp++)
    //             {
    //                 vector<int> intersection;
    //                 set_intersection(TEGS[a][t].begin(), TEGS[a][t].end(),
    //                                  TEGS[a_tmp][t].begin(), TEGS[a_tmp][t].end(),
    //                                  back_inserter(intersection));
    //                 if (!intersection.empty())
    //                 {
    //                     vector<vector<int>> tmp;
    //                     tmp.push_back({map.encode(t, a, intersection)[0], map.encode(t, a_tmp, intersection)[0]});
    //                     if (intersection.size() > 1)
    //                         tmp.push_back({map.encode(t, a, intersection)[1], map.encode(t, a_tmp, intersection)[1]});
    //                     solver.add_clauses(tmp);
    //                 }
    //                 if (a - 1 == a_tmp)
    //                     a_tmp++;
    //             }
    //         }
    //     }
    // }
}

vector<vector<int>> MAPF_handler::create_edges(size_t t, size_t a, set<uint16_t> &last_slices, set<uint16_t> &slices)
{
    vector<vector<int>> result;
    for (const auto &element : last_slices)
    {
        set<uint16_t> expanded = {element};
        for (size_t i = 0; i < graph.size(); ++i)
        {
            if (graph[element - 1][i])
            {
                expanded.insert(i + 1);
            }
        }
        vector<int> intersection;
        set_intersection(slices.begin(), slices.end(),
                         expanded.begin(), expanded.end(),
                         back_inserter(intersection));
        intersection = map.encode(t, a, intersection);
        vector<int> tmp = map.encode(t - 1, a, {-element});
        intersection.insert(intersection.end(), tmp.begin(), tmp.end());
        result.push_back(intersection);
    }
    return result;
}
