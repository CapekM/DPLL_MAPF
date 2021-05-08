#include <chrono>
#include <ctime>
#include <iomanip>

#include "loader.h"
#include "mapf.h"
#include "Solver.h"

using namespace std;
using namespace Glucose;

int main(int argc, char **argv)
{
    // load problem from file - dummy problem is provided if there's no specified file
    string filename = (argc > 1) ? argv[1] : "";
    bool testing = (argc > 3) ? atoi(argv[3]) : false;
    CMAPF problem = CMAPF(filename, testing);
    // start measuring time
    auto start = chrono::high_resolution_clock::now();
    // get initial makespan (total time of plan)
    problem.time = problem.get_shortest_path();
    // cout << "Initial makespan: " << problem.time << endl;

    if (problem.time < 1)
    {
        cerr << "No time.\n";
        return 42;
    }

    chrono::duration<double> encoding_time;

    while (true)
    {
        bool unsat = false;
        Solver solver;
        problem.encode(solver);
            solver.setIncrementalMode();
            solver.verbosity = -1;
        while (true)
        {
            if (!solver.solve()) {
                    unsat = true;
                    break;
            }

            vector<bool> result;
            for (int i = 0; i < solver.nVars(); i++)
                if (solver.model[i] != l_Undef)
                    result.push_back(solver.model[i] == l_True);

            vector<vector<int>> coll = problem.check_collisions(result);
            if (coll.empty()) {
                break;
            }
            solver.add_clauses_mc(coll);
        }
        if (!unsat)
        {
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;

                /* Measurement output*/
            if (testing) {
                cout << ", " << setprecision(4) << diff.count(); // filename.substr(filename.rfind("/") + 1) << 
            }
            else {
                /* Console output */
            // cout << "Makespan: " << problem.time << "\t solve_count " << solve_cnt << endl;
            cout << "Time: \t\t" << setprecision(4) << diff.count() << endl;

            // problem.print(result);
            }
            break;
        }
        problem.time++;
        // cout << "time" << problem.time << endl;
    }

    return 0;
}
