//
// Created by YuXiao on 12/19/17.
//

#include "AliTracePreProcessor.h"
#include "string_helper.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <sys/stat.h>

namespace AliSimulator{

     AliTracePreProcessor::AliTracePreProcessor(const string& trace_path): trace_path_(trace_path) {

    }

    void AliTracePreProcessor::Run() {

        CalculateBatchInstanceRuntime();
    }

    void AliTracePreProcessor::CalculateBatchInstanceRuntime() {
        string out_batch_events_file_name;
        spf(&out_batch_events_file_name, "%s/batch_instance_events.csv", trace_path_.c_str());
        FILE* out_batch_events_file;
        if((out_batch_events_file = fopen(out_batch_events_file_name.c_str(), "w")) == NULL){
            LOG(FATAL)<<"Failed to open batch_events file for writing";
        }else{
            LOG(INFO)<<"OK, ready to write batch_events file";
        }



    }

    void AliTracePreProcessor::CalculateServiceInstanceRuntime() {

    }

    void AliTracePreProcessor::JobsNumTasks() {}

    void AliTracePreProcessor::PrintInstanceRuntime(bool IsBatch) {

    }


}