//
// Created by lilelr on 12/21/17.
//

#include "SimulatorLinker.h"
#include "ResourceRecord.h"


namespace AliSim{
    SimulatorLinker::SimulatorLinker(EventHandler* eventHandler,SimulatedWallTime* simulatedWallTime){
       event_handler_ = eventHandler;
        simulated_time_ = simulatedWallTime;
    }

    SimulatorLinker::~SimulatorLinker() {
        delete event_handler_;
        delete simulated_time_;
    }

    void SimulatorLinker::LoadTraceData(AliTraceLoader *trace_loader) {
        trace_loader->LoadServerEvents(&server_events_map_);
        trace_loader->LoadTaskEvent(&task_events_map_);
        trace_loader->LoadBatchInstanceEvent(&batch_instance_events_map_);

        // loads the initialized machine resources and then erases it from server_events_map_ because we don't need it anymore
        auto zero_sever_events = server_events_map_.count(0);
        auto iter = server_events_map_.find(0);
        while (zero_sever_events){
            AddServer(iter->second.machine_id_,iter->second);
            ++iter;
            --zero_sever_events;
        }
        server_events_map_.erase(0);


    }

    void SimulatorLinker::HandleEventsOfCurrentTimeStamp() {
        uint64_t cur_sim_ts = simulated_time_->GetCurrentTimeStamp();

        auto tasks_count_current_ts = task_events_map_.count(cur_sim_ts);
        auto task_events_map_iter = task_events_map_.find(cur_sim_ts);
        while (tasks_count_current_ts){
            AddTask(task_events_map_iter->second);
            tasks_count_current_ts--;
        }

        onTaskFinished(cur_sim_ts);
    }

     void SimulatorLinker::AddServer(int32_t server_id, ServerEvent& server_event) {
        ResourceStatus resource_status;
        resource_status.ts_ = server_event.ts_;
        resource_status.machine_id_ = server_event.machine_id_;
        resource_status.norm_cpu_ = server_event.norm_cpu_;
        resource_status.norm_mem_ = server_event.norm_mem_;
        resource_status.norm_disk_ = server_event.norm_disk_;
        resource_status.used_cpu_ = 0;
        resource_status.used_disk_ = 0;
        resource_status.used_mem_ = 0;

        resource_record_.GetServerMap()->insert(pair<int32_t ,ResourceStatus>(server_id,resource_status));
    }

    void SimulatorLinker::AddTask(TaskIdentifier& task_identifier) {
        // <key, value> (task_end_time, TaskIdentifier
        // TODO: handle different status of the status(waiting, terminated, etc.)
        current_tasks_map_.insert(pair<uint64_t, TaskIdentifier>(task_identifier.modify_timestamp_,task_identifier));
    }

    void SimulatorLinker::onTaskFinished(uint64_t ts) {
        auto count_current_tasks_ts = current_tasks_map_.count(ts);
        if(count_current_tasks_ts > 0){
            auto current_tasks_iter = current_tasks_map_.find(ts);
            while (count_current_tasks_ts){
                if(current_tasks_iter->second.status_ == "Terminated" || current_tasks_iter->second.status_ == "Failed" || current_tasks_iter->second.status_ == "Cancelled" || current_tasks_iter->second.status_ == "Interrupted"){
                    current_tasks_map_.erase(current_tasks_iter);
                }
                current_tasks_iter++;
                count_current_tasks_ts--;
            }
        }
    }
}