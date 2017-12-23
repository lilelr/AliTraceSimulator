//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_RESOURCESTATUS_H
#define ALISIMULATOR_RESOURCESTATUS_H
#include <cstdint>

namespace AliSim {

    class ResourceStatus {
    public:
        uint64_t ts_;
        int32_t machine_id_;
        float norm_cpu_;
        float norm_mem_;
        float norm_disk_;
        float used_cpu_;
        float used_mem_;
        float used_disk_;

        ResourceStatus();
    };
}


#endif //ALISIMULATOR_RESOURCESTATUS_H
