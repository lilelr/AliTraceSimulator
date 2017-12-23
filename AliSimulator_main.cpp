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


int main() {
        AliSim::SimulatedWallTime simulatedWallTime(10000000);
        string trace_path = "/home/lilelr/trace_201710";
        AliSim::AliTraceLoader traceLoader(trace_path);
        AliSim::AliSimulator aliSimulator(simulatedWallTime,traceLoader);
        aliSimulator.Run();

    return 0;
}