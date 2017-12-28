//
// Created by lilelr on 12/21/17.
//

#include "AliSimulator.h"
#include "EventHandler.h"
#include "SimulatorLinker.h"
#include "glog/logging.h"

using namespace std;

namespace AliSim{

    AliSimulator::AliSimulator(SimulatedWallTime simulatedWallTime,AliTraceLoader aliTraceLoader) : simulated_wall_time_(simulatedWallTime),ali_trace_loader_(aliTraceLoader) {
        event_handler_= new EventHandler(&simulated_wall_time_);
        ResourceRecord resource_record(&simulatedWallTime);
        linker_ = new SimulatorLinker(event_handler_, &simulated_wall_time_,resource_record);
        run_cnt_ = 0;
    }

    AliSimulator::~AliSimulator() {
          delete linker_;
//        delete event_handler_;
    }

    void AliSimulator::Run() {
        ReplaySimulation();
    }

    void AliSimulator::ReplaySimulation() {
//        while (!simulatedWallTime_.IsStop()){
//        }

        // load trace data
        linker_->LoadTraceData(&ali_trace_loader_);

        // simulation starts
        while (simulated_wall_time_.GetCurrentTimeStamp() < 1000000){
            simulated_wall_time_.IncreaseCurrentTimeStampByOneSec();
            linker_->HandleEventsOfCurrentTimeStamp();

        }
    }


}