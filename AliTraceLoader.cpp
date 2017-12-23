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
        if ((server_events_file = fopen(file_name.c_str(), "r")) == NULL) {
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
            LOG(INFO) << "read num line: " << num_line << endl;
            num_line++;
        }
//            LOG(INFO)<<(line_cols.size());
        fclose(server_events_file);
    }





void AliTraceLoader::LoadBatchInstanceEvent(multimap<uint64_t, BatchInstance> *batch_instance_events_map) {

}

void AliTraceLoader::LoadTaskEvent(multimap<uint64_t, TaskIdentifier> *task_events_map) {}

}
