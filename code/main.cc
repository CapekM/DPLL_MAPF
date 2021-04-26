#include <chrono>
#include <ctime>
#include <iomanip>

#include "mapf.h"
#include "Solver.h"

using namespace std;
using namespace Glucose;

int main(int argc, char **argv)
{
    // load problem from file - dummy problem is provided if there's no specified file
    string filename = (argc > 1) ? argv[1] : "";
    bool testing = (argc > 3) ? atoi(argv[3]) : false;
    bool exp = (argc > 4) ? atoi(argv[4]) : false;

    MAPF_handler problem = MAPF_handler(filename, testing);
    // start measuring time
    auto start = chrono::high_resolution_clock::now();
    // get initial makespan (total time of plan)
    problem.time = problem.get_shortest_path();

    if (problem.time < 1)
    {
        cerr << "No time.\n";
        return 42;
    }

    while (true)
    {
        Solver solver;
        problem.encode(solver);

        solver.setIncrementalMode();
        // solver.s_Glucose_timeout = 60;
        solver.verbosity = -1;
        solver.checking_parameter = (argc > 2) ? atoi(argv[2]) : 3;
        solver.exp = exp;
        solver.map = &problem.map;
        solver.agents = &problem.agents;
        solver.makespan = problem.time;
        if (solver.solve())
        {
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            if (problem.check_result(solver.my_model))
            {
                cerr << "Checking failed!\n";
                exit(42);
            }
            else
            {

                /* Measurement output*/
                if (testing)
                {
                    cout << ", " << setprecision(4) << diff.count();
                }
                else
                {
                    /* Console output */
                    cout << "Makespan: " << problem.time << endl;
                    cout << "Time: \t\t" << setprecision(4) << diff.count() << endl;
                    problem.print(solver.my_model);
                }
            }

            break;
        }
        problem.time++;
    }

    return 0;
}
