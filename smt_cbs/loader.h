#ifndef __SAT__
#define __SAT__
#include <vector>
#include <queue>

#include "SimpSolver.h"

using namespace std;

// class Formula
// {
// public:
//     vector<bool> literals;
//     vector<bool> used_literals; // a vector that stores which variable was assigned
//     size_t actual_size = 0;     // size of currently using literals, because we will be adding literals and clauses over time
//     vector<vector<int>> clauses;
//     Formula(){};

//     // copy constructor for copying a formula - each member is copied over
//     Formula(const Formula &f)
//     {
//         literals = f.literals;
//         used_literals = f.used_literals;
//         clauses = f.clauses;
//         actual_size = f.actual_size;
//     }
// };

class SAT_loader
{
private:
    // Formula formula;
    // queue<vector<vector<int>>> clauses_queue;
    // queue<size_t> literals_queue;
    // bool unit_propagate(Formula &);
    // bool pure_literal(Formula &);
    // bool delete_literal(Formula &, int);
    // int DPLL(Formula);
    // void show_formula(Formula &);

public:
    vector<vector<vector<int>>> clauses;
    SAT_loader() { clauses.push_back({}); };
    // void resize(size_t size)
    // {
    //     formula.literals.resize(size);
    //     fill(formula.literals.begin(), formula.literals.end(), 0);
    //     formula.used_literals.resize(size);
    //     fill(formula.used_literals.begin(), formula.used_literals.end(), 0);
    // };

    void add_clauses(const vector<vector<int>> &, size_t c = numeric_limits<short>::max());
    void add_milestone(size_t);                             // clauses and X literals are added to queue, where X is parameter
    void get_clauses(Glucose::Solver &, size_t);            // add clauses from queue
    bool end(size_t time) { return time > clauses.size(); } // TODO delete
    // void load_file();
    // vector<bool> solve();
    void print();
};

#endif /* __SAT__ */