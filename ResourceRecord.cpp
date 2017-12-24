//
// Created by lilelr on 12/21/17.
//

#include "ResourceRecord.h"
#include "collection_helper.h"
namespace AliSim{
    ResourceRecord::ResourceRecord(){

    }

    unordered_map<int32_t, ResourceStatus>* ResourceRecord::GetServerMap() {
        return &server_map_;
    }

    void ResourceRecord::UpdateServerResourceStatus(BatchInstance* batchInstance,float avg_memory){
        // get the reference then update the reference
        ResourceStatus& resource_status = server_map_.at(batchInstance->machine_ID_);
        resource_status.used_mem_ += avg_memory;
        resource_status.used_cpu_ += batchInstance->avg_real_cpu_num_;

    }

    void ResourceRecord::UpdateServerInstanceStatus(int32_t machine_ID, int64_t end_ts, uint64_t task_id, int32_t seq_no) {
        BatchInstanceIdentifier batch_instance_identifier;
        batch_instance_identifier.machine_id_ = machine_ID;
        batch_instance_identifier.end_ts_ = end_ts;
        batch_instance_identifier.task_id_ = task_id;
        batch_instance_identifier.seq_no_ = seq_no;
        vector<BatchInstanceIdentifier> new_instance_vector;

        auto& instance_list = machine_instance_map_[machine_ID];
        instance_list.push_back(batch_instance_identifier);
    }
}