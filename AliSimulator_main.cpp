//
// Created by lilelr on 12/20/17.
//

#include <iostream>

#include <sstream>  // NOLINT
#include <vector>
#include <set>
#include <string>
#include <limits>

#include <glog/logging.h>
#include <gflags/gflags.h>

#include "AliTracePreProcessor.h"
#include "AliSimulator.h"
#include "AliTraceLoader.h"

using namespace std;

DEFINE_string(trace_path, "/home/lilelr/trace_201710/", "Path where the trace files are.");

inline void init(int argc, char* argv[]){
    // Set up usage message.

    google::ParseCommandLineFlags(&argc, &argv, false);

    // Set up glog for logging output.
    google::InitGoogleLogging(argv[0]);

}


int main(int argc, char* argv[]) {

        init(argc, argv);
        AliSim::SimulatedWallTime simulatedWallTime(10000000);
        string trace_path = FLAGS_trace_path;
        AliSim::AliTraceLoader traceLoader(trace_path);
        AliSim::AliSimulator aliSimulator(simulatedWallTime,traceLoader);
        aliSimulator.Run();

    return 0;
}