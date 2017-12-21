#include <iostream>

#include <sstream>  // NOLINT
#include <vector>
#include <set>
#include <string>
#include <limits>

#include <glog/logging.h>
#include <gflags/gflags.h>

#include "AliTracePreProcessor.h"

using namespace std;

DEFINE_string(trace_path, "/home/lilelr/trace_201710/", "Path where the trace files are.");


int main() {

    AliSim::AliTracePreProcessor instance_processor(FLAGS_trace_path);
    instance_processor.Run();
   cout << "end!" <<endl;


    return 0;
}