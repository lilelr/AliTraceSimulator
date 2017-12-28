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

DEFINE_string(trace_path, "", "Path where the trace files are.");

inline void init(int argc, char* argv[]){
    // Set up usage message.

    google::ParseCommandLineFlags(&argc, &argv, false);

    // Set up glog for logging output.
    google::InitGoogleLogging(argv[0]);

}

int main(int argc, char* argv[]) {
    init(argc, argv);

    AliSim::AliTracePreProcessor instance_processor(FLAGS_trace_path);
    instance_processor.Run();
   cout << "end!" <<endl;


    return 0;
}