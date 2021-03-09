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
    CMAPF problem = CMAPF((argc > 1) ? argv[1] : "");
    // start measuring time
    auto start = chrono::high_resolution_clock::now();
    // get initial makespan (total time of plan)
    problem.time = problem.get_shortest_path();
    cout << "Initial makespan: " << problem.time << endl;

    if (problem.time < 1)
    {
        cerr << "No time.\n";
        return 42;
    }

    size_t solve_count = 0;
    size_t collision_count = 0;
    chrono::duration<double> encoding_time;

    while (true)
    {
        Solver solver;
        auto start_encoding = chrono::high_resolution_clock::now();
        problem.encode(solver);
        auto end_encoding = chrono::high_resolution_clock::now();
        encoding_time = encoding_time + (end_encoding - start_encoding);

        solver.setIncrementalMode();
        // solver.s_Glucose_timeout = m_timeout;
        solver.verbosity = -1;
        solver.map = &problem.map;
        solver.agents = &problem.agents;
        solver.makespan = problem.time;
        // if (!solver.simplify()) // maybe redundant
        // {
        //     cout << "UNSAT?" << endl;
        // }
        if (solver.solve())
        {
            if (problem.check_result({})) // TODO
                cout << "Checking failed!\n";
            else
            {
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> diff = end - start;
                cout << "Makespan: " << problem.time << "\t solve_ count " << solver.solve_cnt << endl;
                cout << "Time: \t\t" << setprecision(4) << diff.count() << endl;
                cout << "Encoding time: \t" << setprecision(4) << encoding_time.count() << endl;
                // cout << "Collision time: \t" << setprecision(4) << solver.encoding_time.count() << endl;

                // problem.print(result);
            }

            break;
        }
        problem.time++;
        // cout << "next time " << problem.time << endl;
        // auto end = chrono::high_resolution_clock::now();
        // chrono::duration<double> diff = end - start;
        // cout << "\nTime:  " << setprecision(4) << diff.count() << endl;
    }

    return 0;
}
