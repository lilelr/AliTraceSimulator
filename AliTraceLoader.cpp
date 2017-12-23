//
// Created by lilelr on 12/21/17.
//



#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <sys/stat.h>

#include "AliTraceLoader.h"
#include "string_helper.h"


using boost::lexical_cast;
using boost::algorithm::is_any_of;
using boost::token_compress_off;


namespace AliSim {

    AliTraceLoader::AliTraceLoader() {}
    AliTraceLoader::AliTraceLoader(string trace_path):trace_path_(trace_path) {
    }

    void AliTraceLoader::LoadServerEvents(multimap<uint64_t, ServerEvent> *server_events_map) {

        string file_name;
//        spf(&file_name, "%s/server_event.csv", trace_path_.c_str());
        file_name = trace_path_+"/server_event.csv";
        FILE* server_events_file;
        if ((server_events_file = fopen(file_name.c_str(), "r")) == nullptr) {
            LOG(FATAL) << "Failed to open server_event file for reading";
        }

        int64_t num_line = 1;
        char line[150];
        vector<string> line_cols;
        while (!feof(server_events_file)) {
            if (fscanf(server_events_file, "%[^\n]%*[\n]", &line[0]) > 0) {
                boost::split(line_cols, line, is_any_of(","), token_compress_off);
                if (line_cols.size() != 7) {
                    LOG(ERROR) << "Unexpected structure of sever event on line" << num_line << ": found"
                               << line_cols.size() << " columns";
                } else {
                    ServerEvent server_event;
                    try {
                        server_event.ts_ = lexical_cast<uint64_t>(line_cols[0]);
                        server_event.machine_id_ = lexical_cast<int32_t>(line_cols[1]);

                        string event_type_temp = line_cols[2];
                        if (event_type_temp == "add") {
                            server_event.event_type_ = SERVER_EVENT_TYPE::ADD;
                        } else if (event_type_temp == "softerror") {
                            server_event.event_type_ = SERVER_EVENT_TYPE::SOFT_ERROR;
                        }
                        server_event.event_detail_ = line_cols[3];
                        server_event.norm_cpu_ = lexical_cast<float>(line_cols[4]) / 100;
                        server_event.norm_mem_ = lexical_cast<float>(line_cols[5]);
                        server_event.norm_disk_ = lexical_cast<float>(line_cols[6]);

                        server_events_map->insert(pair<uint64_t,ServerEvent>(server_event.ts_,server_event));
//                            LOG(INFO)<<batchInstance.status_<<endl;
                    } catch (bad_cast& e) {
                        LOG(INFO) << e.what() << endl;
                        LOG(INFO) << "num line: " << num_line << endl;
                    }
                }
            }
//            LOG(INFO) << "read num line: " << num_line << endl;
            num_line++;
        }
//            LOG(INFO)<<(line_cols.size());
        fclose(server_events_file);
    }





void AliTraceLoader::LoadBatchInstanceEvent(multimap<uint64_t, BatchInstance>* batch_instance_events_map) {
    string file_name;
//        spf(&file_name, "%s/server_event.csv", trace_path_.c_str());
    file_name = trace_path_+"/batch_instance_events.csv";
    FILE* batch_instance_file;
    if ((batch_instance_file = fopen(file_name.c_str(), "r")) == nullptr) {
        LOG(FATAL) << "Failed to open batch_instance file for reading";
    }

    int64_t num_line = 1;
    char line[200];
    vector<string> line_cols;
    while (!feof(batch_instance_file)) {
        if (fscanf(batch_instance_file, "%[^\n]%*[\n]", &line[0]) > 0) {
            boost::split(line_cols, line, is_any_of(","), token_compress_off);
            if (line_cols.size() != 13) {
                LOG(ERROR) << "Unexpected structure of batch instance on line" << num_line << ": found "
                           << line_cols.size() << " columns";
            } else {
                BatchInstance batch_instance;
                try {
                  batch_instance.start_timestamp_ = lexical_cast<int64_t >(line_cols[0]);
                    batch_instance.end_timestamp_ = lexical_cast<int64_t > (line_cols[1]);
                    batch_instance.total_runtime_ = lexical_cast<int64_t >(line_cols[2]);
                    batch_instance.job_id_ = lexical_cast<uint64_t>(line_cols[3]);
                    batch_instance.task_id_ = lexical_cast<uint64_t>(line_cols[4]);
                    batch_instance.machine_ID_ = lexical_cast<int32_t>(line_cols[5]);
                    batch_instance.status_ = line_cols[6];
                    batch_instance.seq_no_ = lexical_cast<int32_t>(line_cols[7]);
                    batch_instance.total_seq_no_=lexical_cast<int32_t>(line_cols[8]);
                    batch_instance.max_real_cpu_num_= lexical_cast<float>(line_cols[9]);
                    batch_instance.avg_real_cpu_num_ = lexical_cast<float>(line_cols[10]);
                    batch_instance.max_mem_usage_ = lexical_cast<float>(line_cols[11]);
                    batch_instance.avg_mem_usage_ = lexical_cast<float>(line_cols[12]);

                    batch_instance_events_map->insert(pair<uint64_t ,BatchInstance>(batch_instance.start_timestamp_, batch_instance));

                } catch (bad_cast& e) {
                    LOG(INFO) << e.what() << endl;
                    LOG(INFO) << "num line: " << num_line << endl;
                }
            }
        }
//            LOG(INFO) << "read num line: " << num_line << endl;
        num_line++;
    }
//            LOG(INFO)<<(line_cols.size());
    fclose(batch_instance_file);
}

void AliTraceLoader::LoadTaskEvent(multimap<uint64_t, TaskIdentifier>* task_events_map) {
    string file_name;
//        spf(&file_name, "%s/server_event.csv", trace_path_.c_str());
    file_name = trace_path_+"/batch_task.csv";
    FILE* batch_task_file;
    if ((batch_task_file = fopen(file_name.c_str(), "r")) == nullptr) {
        LOG(FATAL) << "Failed to open batch_task file for reading";
    }

    int64_t num_line = 1;
    char line[200];
    vector<string> line_cols;
    while (!feof(batch_task_file)) {
        if (fscanf(batch_task_file, "%[^\n]%*[\n]", &line[0]) > 0) {
            boost::split(line_cols, line, is_any_of(","), token_compress_off);
            if (line_cols.size() != 8) {
                LOG(ERROR) << "Unexpected structure of batch task on line" << num_line << ": found"
                           << line_cols.size() << " columns";
            } else {
                TaskIdentifier task_identifier;
                try {
                    task_identifier.create_timestamp_ = lexical_cast<int64_t>(line_cols[0]);
                    task_identifier.modify_timestamp_ = lexical_cast<int64_t>(line_cols[1]);

                    task_identifier.job_id_ = lexical_cast<uint64_t>(line_cols[2]);
                    task_identifier.task_id_ = lexical_cast<uint64_t>(line_cols[3]);
                    task_identifier.instance_num_=lexical_cast<int32_t >(line_cols[4]);
                    task_identifier.status_ = line_cols[5];

                    // owns cpu requirements
                    if(!line_cols[6].empty()){
                        task_identifier.plan_cpu_ = lexical_cast<float>(line_cols[6])/100;
                        task_identifier.plan_men_ = lexical_cast<float>(line_cols[7]);
                    }else{
                        task_identifier.plan_cpu_ = -1;
                        task_identifier.plan_men_ = -1;
                    }
                    task_events_map->insert(pair<uint64_t, TaskIdentifier>(task_identifier.task_id_, task_identifier));
//                            LOG(INFO)<<batchInstance.status_<<endl;
                } catch (bad_cast& e) {
                    LOG(INFO) << e.what() << endl;
                    LOG(INFO) << "num line: " << num_line << endl;
                }
            }
        }
//            LOG(INFO) << "read num line: " << num_line << endl;
        num_line++;
    }
//            LOG(INFO)<<(line_cols.size());
    fclose(batch_task_file);
}

}
