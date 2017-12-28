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
        unordered_map<uint64_t ,TaskIdentifier> tasks_map_;

        multimap<uint64_t, TaskIdentifier> current_tasks_map_;
        multimap<uint64_t ,BatchInstance> current_batch_instance_map_;

        ResourceRecord resource_record_;

        void onBatchInstanceReady(BatchInstance* batchInstance);
        void onBatchInstanceWaiting(BatchInstance* batchInstance);
        void onBatchInstanceRunning(BatchInstance* batchInstance);
        void onBatchInstanceTerminated(BatchInstance* batchInstance);
        void onBatchInstanceFailed(BatchInstance* batchInstance);
        void onBatchInstanceCancelled(BatchInstance* batchInstance);
        void onBatchInstanceInterrupted(BatchInstance* batchInstance);

        void onBatchInstanceFinished(uint64_t ts);


    public:
        explicit SimulatorLinker(EventHandler* eventHandler,SimulatedWallTime* simulatedWallTime, ResourceRecord& resourceRecord);

         ~SimulatorLinker();

        void LoadTraceData(AliTraceLoader* trace_loader);

        void ConstructTasksMap();

        void HandleEventsOfCurrentTimeStamp();
        void AddServer(int32_t server_id, ServerEvent& server_event);
        void RemoveServer(uint64_t server_id);
        void AddServerSnapShot(uint64_t current_time);
        void AddTask(TaskIdentifier& task_identifier);


        void onJobFinished(uint64_t job_id);
        void onJobFailure(uint64_t job_id);

        void onTaskFinished(uint64_t ts);
        void onTaskFailure(uint64_t task_id);

        void AddBatchInstance(BatchInstance& batchInstance, uint64_t ts);



    };
}



#endif //ALISIMULATOR_SIMULATORLINKER_H
