#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "loader.h"
#include "SimpSolver.h"

using namespace std;
using namespace Glucose;

void SAT_loader::print()
{
    cout << "Printing SAT:\n";
    cout << "-- literals\n";
    // for (const auto &a : formula.literals)
    // {
    //     cout << a << " ";
    // }
    cout << "\n-- clauses\n";
    for (const auto &c : clauses)
    {
        cout << "[";
        for (const auto &ar : c)
        {
            for (const auto &a : ar)
            {
                if (&a == &ar.back())
                    cout << a << "] ";
                else
                    cout << a << ",";
            }
        }
    }
    cout << endl;
}

void SAT_loader::add_clauses(const vector<vector<int>> &v, size_t c)
{
    if (c == numeric_limits<short>::max())
        c = clauses.size() - 1;
    clauses[c].insert(clauses[c].end(), v.begin(), v.end());
}

void SAT_loader::add_milestone(size_t literals_size)
{
    clauses.push_back({});
    // cout << "PUSH literals_size " << literals_size << endl;
}

void SAT_loader::get_clauses(Solver &S, size_t time)
{
    // cout << "== get_clauses == \n";
    for (size_t i = 0; i < time; i++)
    {
        for (const auto &ar : clauses[i])
        {
            vec<Lit> lits;
            for (const auto a : ar)
            {
                // cout << a << " ";
                if (a == 0)
                    break;
                int var = abs(a) - 1;
                while (var >= S.nVars())
                    S.newVar();
                lits.push((a > 0) ? mkLit(var) : ~mkLit(var));
            }
            S.addClause(lits);
            // cout << endl;
        }
    }
}

// void SAT_loader::load_file()
// {
//     /* DUMMY */
//     formula.literals = {0, 0, 0, 0, 0};
//     formula.used_literals = {0, 0, 0, 0, 0};
//     formula.clauses = {
//         {-1, 5},
//         {1, 3},
//         {-1, 2, -3},
//         {-1, 2, 3},
//         {-3, -4, 5},
//     };

//     // formula.literals.resize(20);
//     // fill(formula.literals.begin(), formula.literals.end(), 0);
//     // formula.used_literals.resize(20);
//     // fill(formula.used_literals.begin(), formula.used_literals.end(), 0);

//     // ifstream file;
//     // string filename = "..\\SAT_problems\\uuf50-218\\uuf50-03.cnf";
//     // file.open(filename, ifstream::in);

//     // if (file.is_open())
//     // {
//     //     while (true)
//     //     {
//     //         vector<int> tmp(3);
//     //         int c;

//     //         file >> tmp[0] >> tmp[1] >> tmp[2] >> c;
//     //         if (tmp[0] == 0)
//     //             break;
//     //         formula.clauses.push_back(tmp);
//     //     }
//     //     file.close();
//     // }
//     // show_formula(formula);
// }

// bool SAT_loader::unit_propagate(Formula &f)
// {
//     bool unit_clause_found = true; // whether the current iteration found a unit clause
//     while (unit_clause_found)
//     {
//         unit_clause_found = false;
//         for (int i = 0; i < f.clauses.size(); i++)
//         {
//             if (f.clauses[i].size() == 1)
//             {
//                 unit_clause_found = true;

//                 f.literals[abs(f.clauses[i][0]) - 1] = f.clauses[i][0] > 0; // set literal
//                 // cout << " UP set literal " << abs(f.clauses[i][0]) << " to " << (f.clauses[i][0] > 0) << endl;
//                 f.used_literals[abs(f.clauses[i][0]) - 1] = 1;
//                 if (delete_literal(f, abs(f.clauses[i][0]) - 1))
//                 {
//                     return true;
//                 }

//                 break; // exit the loop to check for another unit clause
//             }
//         }
//     }
//     return false;
// }

// bool SAT_loader::pure_literal(Formula &f)
// {
//     bool literal_found = true; // whether the current iteration found a unit clause
//     while (literal_found)
//     {
//         literal_found = false;
//         for (int i = 0; i < f.actual_size; i++)
//         {
//             int sign = 0;
//             for (int c = 0; c < f.clauses.size(); c++)
//             {
//                 // same sign
//                 if (find(f.clauses[c].begin(), f.clauses[c].end(), i + 1) != f.clauses[c].end())
//                 {
//                     if (sign == 0)
//                     {
//                         // cout << "signed + on clause: ";
//                         // for (int p = 0; p < f.clauses[c].size(); ++p)
//                         // {
//                         //     cout << f.clauses[c][p] << " ";
//                         // }
//                         // cout << endl;
//                         sign = 1;
//                         literal_found = true;
//                     }
//                     else if (sign == -1)
//                     {
//                         // cout << "Break on +" << endl;
//                         literal_found = false;
//                         break;
//                     }
//                 }
//                 // different sign
//                 if (find(f.clauses[c].begin(), f.clauses[c].end(), -i - 1) != f.clauses[c].end())
//                 {
//                     if (sign == 0)
//                     {
//                         // cout << "signed " << -i - 1 << "  c: " << c << endl;
//                         sign = -1;
//                         literal_found = true;
//                     }
//                     else if (sign == 1)
//                     {
//                         // cout << "Break on -" << endl;
//                         literal_found = false;
//                         break;
//                     }
//                 }
//             }
//             if (literal_found)
//             {
//                 f.literals[i] = sign > 0; // set literal
//                 // cout << " Pure set literal " << i + 1 << " to " << (sign > 0) << endl;
//                 f.used_literals[i] = true;
//                 if (delete_literal(f, i))
//                 {
//                     return true;
//                 }
//                 break;
//             }
//         }
//     }

//     return false;
// }

// bool SAT_loader::delete_literal(Formula &f, int literal) // from 0
// {
//     literal = (f.literals[literal]) ? literal + 1 : -literal - 1;
//     // cout << "deleting " << literal << endl;
//     // iterate over the clauses in formula
//     for (vector<vector<int>>::iterator it = f.clauses.begin(); it != f.clauses.end();)
//     {
//         bool deleted = false;
//         // iterate over the literals in clause
//         for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); it2++)
//         {
//             if (*it2 == literal)
//             {
//                 it = f.clauses.erase(it);
//                 deleted = true;
//                 break;
//             }
//             else if (*it2 == -literal)
//             {
//                 if (*it2 == 1)
//                 {
//                     return true;
//                 }
//                 it->erase(it2);
//                 break;
//             }
//         }
//         if (!deleted)
//             it++;
//     }

//     // cout << endl;
//     return false;
// }

// int SAT_loader::DPLL(Formula f)
// {
//     // cout << "=========================" << endl;
//     // show_formula(f);
//     // cout << "=========================" << endl;
//     if (unit_propagate(f))
//     {
//         // cout << "unit_propagate failed" << endl;
//         return false;
//     }
//     // cout << "Before Pure" << endl;
//     if (pure_literal(f))
//     {
//         // cout << "pure_literal failed" << endl;
//         return false;
//     }
//     // cout << "continue" << endl;
//     if (f.clauses.size() == 0) // if the formula contains no clauses
//     {
//         // cout << "== TRUE ==" << endl;
//         formula.literals = f.literals;
//         return true;
//     }

//     // find n-th unassigned variable
//     int n = 0;
//     for (; n < f.actual_size; ++n)
//     {
//         if (!f.used_literals[n])
//         {
//             break;
//         }
//     }

//     if (n == f.actual_size)
//     {
//         return false;
//     }
//     // cout << "HERE" << endl;
//     // show_formula(f);
//     Formula tmp = f;
//     tmp.used_literals[n] = 1;
//     tmp.literals[n] = 1;
//     if (delete_literal(tmp, n))
//     {
//         // cout << "deleting failed " << n + 1 << endl;
//         return false;
//     }
//     if (DPLL(tmp))
//     {
//         return true;
//     }
//     tmp = f;
//     tmp.literals[n] = 0;
//     if (delete_literal(tmp, n))
//     {
//         // cout << "deleting failed -" << n - 1 << endl;
//         return false;
//     }
//     if (DPLL(tmp))
//     {
//         return true;
//     }
//     return false;
// }

// void SAT_loader::show_formula(Formula &f)
// {
//     cout << endl;
//     for (int i = 0; i < f.actual_size; i++)
//     {
//         int n = (f.literals[i] > 0) ? f.literals[i] : -f.literals[i];
//         cout << n << " ";
//     }
//     cout << endl;
//     // used
//     for (int i = 0; i < f.actual_size; i++)
//     {
//         cout << f.used_literals[i] << " ";
//     }
//     cout << endl;
//     // clauses
//     // cout << "-- clauses\n";
//     // for (const auto &c : f.clauses)
//     // {
//     //     cout << "[";
//     //     for (const auto &a : c)
//     //     {
//     //         if (&a == &c.back())
//     //             cout << a << "] ";
//     //         else
//     //             cout << a << ",";
//     //     }
//     // }
//     // cout << endl;
// }

// vector<bool> SAT_loader::solve()
// {
//     // TODO cut formula on actual size and pass it
//     // return DPLL(formula) TODO might be smarter
//     show_formula(formula);

//     if (DPLL(formula))
//     {
//         show_formula(formula);
//         // cout << "literals " << formula.literals.size() << " actual " << formula.actual_size << endl;
//         return formula.literals;
//     }
//     return {};
// }