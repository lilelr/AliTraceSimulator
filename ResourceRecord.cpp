//
// Created by lilelr on 12/21/17.
//

#include "ResourceRecord.h"
#include "collection_helper.h"

namespace AliSim {
    ResourceRecord::ResourceRecord( SimulatedWallTime* simulated_time):simulated_time_(simulated_time_) {

    }

    unordered_map<int32_t, ResourceStatus> *ResourceRecord::GetServerMap() {
        return &server_map_;
    }

    void
    ResourceRecord::UpdateServerResourceStatus(const int32_t &action, BatchInstance *batchInstance, float avg_memory, uint64_t ts) {
        // get the reference then update the reference
        ResourceStatus &resource_status = server_map_.at(batchInstance->machine_ID_);
        switch (action) {
            case 1: // Add
            {
                resource_status.used_mem_ += avg_memory;
                resource_status.used_cpu_ += batchInstance->avg_real_cpu_num_;
                LOG(INFO)<<"Machine "<<resource_status.machine_id_ << "'s used memory by programs is "<< resource_status.used_mem_<<", used cpu is "<<resource_status.used_cpu_<<"at " <<ts<<" second"<< endl;
                break;
            }

            case 2: // Reduce
            {
                resource_status.used_mem_ -= avg_memory;
                resource_status.used_cpu_ -= batchInstance->avg_real_cpu_num_;
                LOG(INFO)<<"Machine "<<resource_status.machine_id_ << "'s used memory by programs is "<< resource_status.used_mem_<<", used cpu is "<<resource_status.used_cpu_<<"at " <<ts<<" second"<<endl;
                break;
            }

            default:
                break;
        }

    }

    void ResourceRecord::UpdateServerInstanceStatus(const int32_t &action, int32_t machine_ID, int64_t end_ts,
                                                    uint64_t task_id, int32_t seq_no,uint64_t ts) {

        switch (action) {
            case 1: // Add
            {
                BatchInstanceIdentifier batch_instance_identifier;
                batch_instance_identifier.machine_id_ = machine_ID;
                batch_instance_identifier.end_ts_ = end_ts;
                batch_instance_identifier.task_id_ = task_id;
                batch_instance_identifier.seq_no_ = seq_no;
                vector<BatchInstanceIdentifier> new_instance_vector;

                auto &instance_list = machine_instance_map_[machine_ID];
                instance_list.push_back(batch_instance_identifier);
                LOG(INFO)<<"Machine "<<machine_ID << " adds a task. The task ID is "<< task_id <<". It has total "<<instance_list.size()<<" tasks at " <<ts<<" second"<<endl;
                break;
            }
            case 2: // Delete
            {

                auto &existed_instance_list = machine_instance_map_.at(machine_ID);
                for (auto iter = existed_instance_list.begin(); iter != existed_instance_list.end(); iter++) {
                    if (iter->task_id_ == task_id && iter->end_ts_ == end_ts && iter->seq_no_ == seq_no) {
                        existed_instance_list.erase(iter);
                        LOG(INFO)<<"Machine "<<machine_ID << " deletes a task. The task ID is "<< task_id <<". It has total "<<existed_instance_list.size()<<"tasks at " <<ts<<" second"<<endl;
                        break;
                    }
                }
                break;
            }
            default:
                break;
        }

    }
}