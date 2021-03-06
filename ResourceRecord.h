//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_RESOURCERECORD_H
#define ALISIMULATOR_RESOURCERECORD_H


#include <cstdint>
#include <iostream>
#include <map>
#include <unordered_map>

#include "ResourceStatus.h"
#include "AliTracePreProcessor.h"
#include "SimulatedWallTime.h"

using namespace std;
namespace AliSim {

    class ResourceRecord {

    private:
        unordered_map<int32_t, ResourceStatus> server_map_;
        unordered_map<int32_t , vector<BatchInstanceIdentifier> > machine_instance_map_;
        SimulatedWallTime* simulated_time_;


    public:
        explicit ResourceRecord( SimulatedWallTime* simulated_time);

        void UpdateServerResourceStatus(const int32_t& action, BatchInstance* batchInstance, float avg_memory, uint64_t ts);
        unordered_map<int32_t, ResourceStatus>* GetServerMap();

        void UpdateServerInstanceStatus(const int32_t& action,int32_t machine_ID, int64_t end_ts, uint64_t task_id, int32_t seq_no, uint64_t ts);



    };
}

#endif //ALISIMULATOR_RESOURCERECORD_H
