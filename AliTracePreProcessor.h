//
// Created by YuXiao on 12/19/17.
//

#ifndef ALISIMULATOR_ALITRACEPREPROCESSOR_H
#define ALISIMULATOR_ALITRACEPREPROCESSOR_H

#include <iostream>
#include <string>

# include <map>
#include <unordered_map>
#include <vector>

using namespace std;

namespace AliSim{
    struct TaskIdentifier{

        uint64_t job_id_;
        uint64_t task_id_;
        int64_t create_timestamp_;
        int64_t modify_timestamp_;

        int32_t instance_num_;
        string status_;
        float plan_cpu_;
        float plan_men_;

    };

    struct BatchInstance{
        int64_t  start_timestamp_;
        int64_t  end_timestamp_;
        int64_t  total_runtime_;
        uint64_t  job_id_;
        uint64_t  task_id_;
        int32_t machine_ID_;
        string status_;
        int32_t seq_no_;
        int32_t total_seq_no_;
        float max_real_cpu_num_;
        float avg_real_cpu_num_;
        float max_mem_usage_;
        float avg_mem_usage_;

    };

    struct ContainerInstance{
        int64_t ts_;
        int64_t runtime_;
        string event_;
        uint64_t instance_id_;
        uint32_t machine_id_;
        int32_t plan_cpu_;
        float plan_mem_;
        float plan_disk_;
        string cpuset_;
    };

    enum SERVER_EVENT_TYPE{
        ADD,
        SOFT_ERROR,
        HARD_ERROR
    };

    struct ServerEvent{
        uint64_t ts_;
        int32_t machine_id_;
        SERVER_EVENT_TYPE event_type_;
        string event_detail_;
        vector<int> cpus_;
        float norm_cpu_;
        float norm_mem_;
        float norm_disk_;

    };

    struct BatchInstanceIdentifier{
        int64_t end_ts_;
        int32_t machine_id_;
        uint64_t task_id_;
        int32_t seq_no_;
    };




    class AliTracePreProcessor {

private:
   string trace_path_;

public:
    explicit AliTracePreProcessor(const string& trace_path);

    void JobsNumTasks();

    void Run();

    void CalculateBatchInstanceRuntime();
    void CalculateServiceInstanceRuntime();

    void PrintInstanceRuntime(bool IsBatch);


};

}


#endif //ALISIMULATOR_ALITRACEPREPROCESSOR_H
