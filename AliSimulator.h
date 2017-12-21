//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_ALISIMULATOR_H
#define ALISIMULATOR_ALISIMULATOR_H

#include <cstdint>
#include <string>
#include <vector>

#include "SimulatedWallTime.h"
#include "SimulatorLinker.h"
#include "EventHandler.h"

using namespace std;

namespace AliSim{

    enum SERVER_EVENT_TYPE{
        ADD,
        SFOT_ERROR,
        HARD_ERROR
    };

    struct ServerEvent{
        uint64_t ts_;
        int32_t machine_id;
        SERVER_EVENT_TYPE event_type_;
        string event_detail_;
        vector<int> cpus_;
        float norm_cpu_;
        float norm_mem_;
        float norm_disk_;

    };

    class AliSimulator {
    private:
        SimulatorLinker* linker_;
        EventHandler* eventHandler_;
        SimulatedWallTime simulatedWallTime_;
        uint64_t run_cnt_;

        void ReplaySimulation();
    public:
        AliSimulator();

        void Run();


    };
}


#endif //ALISIMULATOR_ALISIMULATOR_H
