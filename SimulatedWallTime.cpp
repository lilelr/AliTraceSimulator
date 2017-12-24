//
// Created by lilelr on 12/21/17.
//

#include "SimulatedWallTime.h"
#include <cstdint>

namespace AliSim{
    SimulatedWallTime::SimulatedWallTime(uint64_t stop_time) {
        // set beginning time at 0
        this->current_simulation_ts_=6458;
        this->stop_time_ = stop_time;
    }

    bool SimulatedWallTime::IsStop() {
        if (current_simulation_ts_> this->stop_time_){
            return true;
        }
        return false;
    }

    uint64_t SimulatedWallTime::GetCurrentTimeStamp() {
        return current_simulation_ts_;
    }

    uint64_t SimulatedWallTime::IncreaseCurrentTimeStampByOneSec() {
        current_simulation_ts_++;
        return current_simulation_ts_;
    }
}