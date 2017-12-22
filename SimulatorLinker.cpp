//
// Created by lilelr on 12/21/17.
//

#include "SimulatorLinker.h"
#include "ResourceRecord.h"


namespace AliSim{
    SimulatorLinker::SimulatorLinker(EventHandler* eventHandler,SimulatedWallTime* simulatedWallTime){

    }

    SimulatorLinker::~SimulatorLinker() {
        delete event_handler_;
        delete simulated_time_;
    }
}