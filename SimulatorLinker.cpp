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

    void SimulatorLinker::LoadTraceData(AliTraceLoader *trace_loader) {
        trace_loader->LoadServerEvents(&server_events_map_);
        trace_loader->LoadTaskEvent(&task_events_map_);

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

    ResourceStatus* SimulatorLinker::AddServer(int32_t server_id, ServerEvent& server_event) {
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
        return &resource_status;
    }
}