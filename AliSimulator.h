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


namespace AliSim{

    class SimulatorLinker;
    class EventHandler;
    class AliSimulator {

    private:
        SimulatorLinker* linker_;
        EventHandler* event_handler_;
        SimulatedWallTime simulatedWallTime_;
        uint64_t run_cnt_;

        void ReplaySimulation();
    public:
        explicit AliSimulator(SimulatedWallTime simulatedWallTime_);
        virtual ~AliSimulator();
        void Run();


    };
}


#endif //ALISIMULATOR_ALISIMULATOR_H
