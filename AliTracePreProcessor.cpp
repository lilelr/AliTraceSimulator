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
            if(fscanf(batch_events_file, "%[^\n]%*[\n]", &line[0]) > 0){
                boost::split(line_cols, line, is_any_of(","), token_compress_off);
                if(line_cols.size() !=12){
                    LOG(ERROR)<<"Unexpected structure of batch instance event on line"<< num_line<<": found" <<line_cols.size() <<" columns";
                }else{
                   BatchInstance  batchInstance;
                    try {
                        batchInstance.start_timestamp_ = lexical_cast<int64_t>(line_cols[0]);
                        batchInstance.end_timestamp_ = lexical_cast<int64_t>(line_cols[1]);

                        // job_id or task_id is empty
                        if(line_cols[2].empty()){
                            batchInstance.job_id_ = 0;
                        }else{
                            batchInstance.job_id_ = lexical_cast<uint64_t>(line_cols[2]);
                        }

                        if(line_cols[3].empty()){
                            batchInstance.task_id_ = 0;
                        }else{
                            batchInstance.task_id_ = lexical_cast<uint64_t>(line_cols[3]);
                        }

                        // do not have machine_ID
                        if(line_cols[4].empty()){
                            batchInstance.machine_ID_ = -1;
                        }else{
                            batchInstance.machine_ID_ = lexical_cast<int32_t>(line_cols[4]);
                        }
                        batchInstance.status_ = line_cols[5];
                        batchInstance.seq_no_ = lexical_cast<int32_t>(line_cols[6]);
                        batchInstance.total_seq_no_ = lexical_cast<int32_t>(line_cols[7]);

                        // do not have cpu
                        if(line_cols[8].empty()){
                            batchInstance.max_real_cpu_num_ = -1;
                        }else{
                            batchInstance.max_real_cpu_num_ = lexical_cast<float>(line_cols[8]);

                        }
                        if(line_cols[9].empty()){
                            batchInstance.avg_real_cpu_num_ = -1;

                        }else{
                            batchInstance.avg_real_cpu_num_ = lexical_cast<float>(line_cols[9]);

                        }
//                    batchInstance.max_mem_usage_ = lexical_cast<float>(line_cols[10]);
                        batchInstance.avg_mem_usage_ = -1;

                        // get the total runtime of the current running
                        if(batchInstance)
                        batchInstance.total_runtime = batchInstance.end_timestamp_ - batchInstance.start_timestamp_;
                    }catch (bad_cast& e){
                        LOG(INFO)<<e.what()<<endl;
                        LOG(INFO)<<"num line: "<< num_line <<endl;
                    }


                }
            }
//            LOG(INFO)<<(line_cols.size());
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