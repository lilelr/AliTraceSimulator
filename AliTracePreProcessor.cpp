//
// Created by YuXiao on 12/19/17.
//

#include "AliTracePreProcessor.h"
#include "string_helper.h"
#include "collection_helper.h"


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

//        CalculateBatchInstanceRuntime();
        CalculateServiceInstanceRuntime();
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
                        batchInstance.max_mem_usage_ = -1;
                        batchInstance.avg_mem_usage_ = -1;

                        // get the total runtime of the current batchInstance of status including
                        // "Terminated, Cancelled, Interupted"
                        if(batchInstance.end_timestamp_ > batchInstance.start_timestamp_){
                            batchInstance.total_runtime_ = batchInstance.end_timestamp_ - batchInstance.start_timestamp_;

//                            LOG(INFO)<<batchInstance.status_<<endl;
                            fprintf(out_batch_events_file,"%jd,%jd,%jd,%ju,%ju,%d,%s,%d,%d,%f,%f,%f,%f\n",batchInstance.start_timestamp_,batchInstance.end_timestamp_, batchInstance.total_runtime_,batchInstance.job_id_, batchInstance.task_id_, batchInstance.machine_ID_, batchInstance.status_, batchInstance.seq_no_, batchInstance.total_seq_no_,batchInstance.max_real_cpu_num_,batchInstance.avg_real_cpu_num_,batchInstance.max_mem_usage_,batchInstance.avg_mem_usage_);
                        }

                    }catch (bad_cast& e){
                        LOG(INFO)<<e.what()<<endl;
                        LOG(INFO)<<"num line: "<< num_line <<endl;
                    }


                }
            }
//            LOG(INFO)<<(line_cols.size());
            num_line++;
        }
        fclose(out_batch_events_file);
        fclose(batch_events_file);

    }

    void AliTracePreProcessor::CalculateServiceInstanceRuntime() {
        string out_container_events_file_name;
        spf(&out_container_events_file_name, "%s/container_instance_events.csv", trace_path_.c_str());
        FILE* out_container_events_file;
        if((out_container_events_file = fopen(out_container_events_file_name.c_str(), "w")) == NULL){
            LOG(FATAL)<<"Failed to open container_events file for writing";
        }else{
            LOG(INFO)<<"OK, ready to write container_events file";
        }

        string file_name;
        spf(&file_name, "%s/container_event.csv",trace_path_.c_str());
        FILE* container_events_file;
        if((container_events_file = fopen(file_name.c_str(),"r")) == NULL){
            LOG(FATAL)<<"Failed to open container_events file for reading";
        }

        int64_t num_line = 1;
        char line[200];
        vector<string> line_cols;
        unordered_map<uint64_t , ContainerInstance> containerMap;
        while(!feof(container_events_file)){
            if(fscanf(container_events_file, "%[^\n]%*[\n]", &line[0]) > 0){
                boost::split(line_cols, line, is_any_of(","), token_compress_off);
                if(line_cols.size() !=9){
                    LOG(ERROR)<<"Unexpected structure of container event on line"<< num_line<<": found" <<line_cols.size() <<" columns";
                }else{
                    ContainerInstance  containerInstance;
                    try {
                        containerInstance.ts_ = lexical_cast<int64_t>(line_cols[0]);
                        containerInstance.event_ = line_cols[1];
                        containerInstance.instance_id_ = lexical_cast<uint64_t>(line_cols[2]);
                        containerInstance.machine_id_ = lexical_cast<uint32_t >(line_cols[3]);
                        containerInstance.plan_cpu_ = lexical_cast<int32_t>(line_cols[4]);
                        containerInstance.plan_mem_ = lexical_cast<float>(line_cols[5]);
                        containerInstance.plan_disk_ = lexical_cast<float>(line_cols[6]);
                        containerInstance.cpuset_ = line_cols[7];
//                        vector<string> tempstrv;
//                        boost::split(tempstrv,line_cols[7],is_any_of("|"));
//                        for(auto& i:tempstrv){
//                            containerInstance.cpuset_.push_back(lexical_cast<int32_t>(i));
//                        }
//
                        if(!InsertIfNotPresent(&containerMap,containerInstance.instance_id_,containerInstance)){
                        // this container has been in the map, calculate its runtime
                            if(containerInstance.event_ == "Remove"){
                               ContainerInstance* existedContainer;
                                FindCopy(containerMap, containerInstance.instance_id_, existedContainer);
                                containerInstance.runtime_ = containerInstance.ts_ - existedContainer->ts_;
                                fprintf(out_container_events_file,"%jd,Create,%jd,%ju,%d,%d,%f,%f,%s\n",existedContainer->ts_,containerInstance.runtime_,existedContainer->instance_id_,existedContainer->machine_id_,existedContainer->plan_cpu_,existedContainer->plan_mem_,existedContainer->plan_disk_,existedContainer->cpuset_);
                            }
                        }


                    }catch (bad_cast& e){
                        LOG(INFO)<<e.what()<<endl;
                        LOG(INFO)<<"num line: "<< num_line <<endl;
                    }


                }
            }
//            LOG(INFO)<<(line_cols.size());
            num_line++;
        }
        fclose(out_container_events_file);
        fclose(container_events_file);

    }

    void AliTracePreProcessor::JobsNumTasks() {}

    void AliTracePreProcessor::PrintInstanceRuntime(bool IsBatch) {

    }


}