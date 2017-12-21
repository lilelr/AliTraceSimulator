//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_EVENTHANDLER_H
#define ALISIMULATOR_EVENTHANDLER_H


#include <map>

#include "EventHandler.h"
#include "SimulatedWallTime.h"
#include "AliSimulator.h"
#include "AliTracePreProcessor.h"
#include "ResourceRecord.h"
#include "ResourceStatus.h"
#include "AliTraceLoader.h"

namespace AliSim{
    class EventHandler {
    private:
        SimulatedWallTime* simulated_time_;
        void AddTaskEvent(uint64_t timestamp, TaskIdentifier task_identifier);
        void AddServerEvent(uint64_t timestamp, ServerEvent server_event);
        void AddBatchInstanceEvent(uint64_t timestamp, BatchInstance batch_instance_event);


    public:
        explicit EventHandler(SimulatedWallTime simulated_time);

        void AddEvent(uint64_t timestamp);

        uint64_t  GetTimeOfNextEvent(uint64_t cur_run_time);

        // stop the simulation at the specified time
        void StopSimulationAtSpecifiedTime(uint64_t timestamp);
    };
}



#endif //ALISIMULATOR_EVENTHANDLER_H
