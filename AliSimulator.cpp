//
// Created by lilelr on 12/21/17.
//

#include "AliSimulator.h"
#include "EventHandler.h"
#include "SimulatorLinker.h"

using namespace std;

namespace AliSim{
    AliSimulator::AliSimulator(SimulatedWallTime simulatedWallTime_,AliTraceLoader aliTraceLoader) : simulatedWallTime_(simulatedWallTime_),ali_trace_loader_(aliTraceLoader) {
        event_handler_= new EventHandler(&simulatedWallTime_);
        linker_ = new SimulatorLinker(event_handler_, &simulatedWallTime_);
        run_cnt_ = 0;
    }

    AliSimulator::~AliSimulator() {
          delete linker_;
        delete event_handler_;
    }

    void AliSimulator::Run() {
        ReplaySimulation();
    }

    void AliSimulator::ReplaySimulation() {
//        while (!simulatedWallTime_.IsStop()){
//        }
        linker_->LoadTraceData(&ali_trace_loader_);

    }


}