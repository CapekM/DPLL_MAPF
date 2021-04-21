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
    CMAPF problem = CMAPF(filename, testing);
    // start measuring time
    auto start = chrono::high_resolution_clock::now();
    // get initial makespan (total time of plan)
    problem.time = problem.get_shortest_path();

    if (problem.time < 1)
    {
        cerr << "No time.\n";
        return 42;
    }

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
        solver.checking_parameter = (argc > 2) ? atoi(argv[2]) : 3;
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
                    cout << "Makespan: " << problem.time << "\t solve_count " << solver.solve_cnt << endl;
                    cout << "Time: \t\t" << setprecision(4) << diff.count() << endl;
                    cout << "Non-Encoding time: \t" << setprecision(4) << (diff - encoding_time).count() << endl;
                    // problem.print(solver.my_model);
                }
            }

            break;
        }
        problem.time++;
    }

    return 0;
}
