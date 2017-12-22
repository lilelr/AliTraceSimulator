//
// Created by lilelr on 12/21/17.
//

#include "SimulatedWallTime.h"
#include <cstdint>

namespace AliSim{
    SimulatedWallTime::SimulatedWallTime(uint64_t stop_time) {
        this->stop_time_ = stop_time;
    }

    bool SimulatedWallTime::IsStop() {
        if (current_simulation_ts_> this->stop_time_){
            return true;
        }
        return false;
    }
}