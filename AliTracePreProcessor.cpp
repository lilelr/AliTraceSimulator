//
// Created by YuXiao on 12/19/17.
//

#include "AliTracePreProcessor.h"
#include "string_helper.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <sys/stat.h>

using boost::lexical_cast;
using boost::algorithm::is_any_of;
using boost::token_compress_off;

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

        string file_name;
        spf(&file_name, "%s/batch_instance.csv",trace_path_.c_str());
        FILE* batch_events_file;
        if((batch_events_file = fopen(file_name.c_str(),"r")) == NULL){
            LOG(FATAL)<<"Failed to open batch_events file for reading";
        }

        int64_t num_line = 1;
        char line[200];
        vector<string> line_cols;
        while(!feof(batch_events_file)){
            if(fscanf(batch_events_file, "%[^\n]*%[\n]", &line[0]) > 0){
                boost::split(line_cols, line, is_any_of(","), token_compress_off);
            }
            LOG(INFO)<<(line_cols.size());
            num_line++;
        }

        fclose(batch_events_file);

    }

    void AliTracePreProcessor::CalculateServiceInstanceRuntime() {

    }

    void AliTracePreProcessor::JobsNumTasks() {}

    void AliTracePreProcessor::PrintInstanceRuntime(bool IsBatch) {

    }


}