#ifndef __HELP__
#define __HELP__

#include <vector>
#include <set>
#include <iostream>
#include <chrono>

using namespace std;

struct encode_unit
{
    uint16_t time, agent, vertex;

    friend bool operator==(const encode_unit &left, const encode_unit &right)
    {
        return (left.time == right.time && left.agent == right.agent && left.vertex == right.vertex);
    };

    friend bool operator<(const encode_unit &left, const encode_unit &right)
    {
        if (left.time == right.time)
        {
            if (left.agent == right.agent)
            {
                if (left.vertex == right.vertex)
                {
                }
                return left.vertex < right.vertex;
            }
            return left.agent < right.agent;
        }
        return left.time < right.time;
    };

    string print()
    {
        cout << time << " " << agent << " " << vertex;
        return "";
    }
};

class encode_MAP
{
public:
    vector<encode_unit> map;
    void add(uint16_t t, uint16_t a, set<uint16_t> &in)
    {
        for (const auto &i : in)
        {
            map.push_back({t, a, i});
        }
    };

    vector<vector<int>> encode_v(uint16_t t, uint16_t a, const vector<vector<int>> &in) // encode 2d
    {
        vector<vector<int>> result;
        for (const auto &i : in)
        {
            result.push_back(encode(t, a, i));
        }
        return result;
    }

    vector<int> encode_set(uint16_t t, uint16_t a, set<uint16_t> &in) // encode 1d
    {
        vector<int> result;
        for (const auto &i : in)
        {
            encode_unit tmp = {t, a, i};
            size_t index = map.size() / 2;
            size_t jump = map.size() / 4;
            // my map is created by order Time, Agent, Vertex
            while (true)
            {
                // cout << "index \t" << index << endl;
                // cout << "map " << map[index].print() << " tmp " << tmp.print() << endl;
                if (map[index] == tmp)
                {
                    result.push_back(index);
                    break;
                }
                else if (map[index] < tmp)
                {
                    index += jump;
                    jump /= 2;
                }
                else
                {
                    index -= jump;
                    jump /= 2;
                }
                if (!jump)
                    jump = 1;
            }
        }
        return result;
    }

    vector<int> encode(uint16_t t, uint16_t a, const vector<int> &in, bool verb = false) // TODO delete verb
    {
        vector<int> result;
        for (const auto &i : in)
        {
            uint16_t v = abs(i);
            encode_unit tmp = {t, a, v};
            size_t index = map.size() / 2;
            size_t jump = map.size() / 4;
            // my map is created by order Time, Agent, Vertex
            while (true)
            {
                if (verb)
                {
                    cout << "index \t" << index << endl;
                    cout << "map " << map[index].print() << " tmp " << tmp.print() << endl;
                }
                if (map[index] == tmp)
                {
                    result.push_back((i / v) * (index + 1));
                    break;
                }
                else if (map[index] < tmp)
                {
                    index += jump;
                    jump /= 2;
                }
                else
                {
                    index -= jump;
                    jump /= 2;
                }
                if (!jump)
                    jump = 1;
            }
        }
        return result;
    }
    
    vector<int> encode_one(uint16_t t, uint16_t a, const int i)
    {
        vector<int> result;
        uint16_t v = abs(i);
        encode_unit tmp = {t, a, v};
        size_t index = map.size() / 2;
        size_t jump = map.size() / 4;
        // my map is created by order Time, Agent, Vertex
        while (true)
        {
            if (map[index] == tmp)
            {
                result.push_back((i / v) * (index + 1));
                break;
            }
            else if (map[index] < tmp)
            {
                index += jump;
                jump /= 2;
            }
            else
            {
                index -= jump;
                jump /= 2;
            }
            if (!jump)
                jump = 1;
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const encode_MAP& m)
    {
        os << "Printing MAP:\n";
        for (const auto &a : m.map)
        {
            os << "[" << a.time << "," << a.agent << "," << a.vertex << "]  ";
        }
        return os;
    }

    // print mappping of specified agnet
    void print(uint16_t ag)
    {
        for (const auto &a : map)
        {
            if (ag == a.agent)
                cout << "[" << a.time << "," << a.agent << "," << a.vertex << "]  ";
        }
        cout << endl;
    }
};
#endif /* __HELP__ */