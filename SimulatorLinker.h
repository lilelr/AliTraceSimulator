//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_SIMULATORLINKER_H
#define ALISIMULATOR_SIMULATORLINKER_H

#include <map>

#include "EventHandler.h"
#include "SimulatedWallTime.h"
#include "AliSimulator.h"
#include "AliTracePreProcessor.h"
#include "ResourceRecord.h"
#include "ResourceStatus.h"
#include "AliTraceLoader.h"

using  namespace std;

namespace AliSim{
    class EventHandler;

    class SimulatorLinker {

    private:
        EventHandler* event_handler_;
        SimulatedWallTime* simulated_time_;
        multimap<uint64_t,ServerEvent> server_events_map_;
        multimap<uint64_t, TaskIdentifier> task_events_map_;
        multimap<uint64_t, BatchInstance> batch_instance_events_map_;

        ResourceRecord resource_record_;

    public:
        explicit SimulatorLinker(EventHandler* eventHandler,SimulatedWallTime* simulatedWallTime);

        virtual ~SimulatorLinker();

//        void LoadTraceData(AliTraceLoader* trace_loader);


        ResourceStatus* AddServer(uint64_t server_id);
        void RemoveServer(uint64_t server_id);
        void AddServerSnapShot(uint64_t current_time);
        void AddTask(uint64_t& task_id, TaskIdentifier& task_identifier);

        void onJobFinished(uint64_t job_id);
        void onJobFailure(uint64_t job_id);

        void onTaskFinished(uint64_t task_id);
        void onTaskFailure(uint64_t task_id);

        void onBatchInstanceReady(TaskIdentifier* task_identifier);
        void onBatchInstanceWaiting(TaskIdentifier* task_identifier);
        void onBatchInstanceRunning(TaskIdentifier* task_identifier);
        void onBatchInstanceTerminated(TaskIdentifier* task_identifier);
        void onBatchInstanceFailed(TaskIdentifier* task_identifier);
        void onBatchInstanceCancelled(TaskIdentifier* task_identifier);


    };
}



#endif //ALISIMULATOR_SIMULATORLINKER_H
