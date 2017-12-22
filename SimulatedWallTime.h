//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_SIMULATEDWALLTIME_H
#define ALISIMULATOR_SIMULATEDWALLTIME_H

#include <cstdint>

namespace AliSim{
    class SimulatedWallTime {
    private:
        uint64_t current_simulation_ts_;
        uint64_t stop_time_;

    public:
        explicit SimulatedWallTime(uint64_t stop_time);

        uint64_t GetCurrentTimeStamp();
        // // update the current wall time because it is earlier than the timestamp of next event

        uint64_t UpdateCurrentTimeStamp(uint64_t event_timestamp);

        bool IsStop();

    };
}



#endif //ALISIMULATOR_SIMULATEDWALLTIME_H
