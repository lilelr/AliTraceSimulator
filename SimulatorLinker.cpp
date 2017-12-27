//
// Created by lilelr on 12/21/17.
//

#include "SimulatorLinker.h"
#include "ResourceRecord.h"
#include "glog/logging.h"

namespace AliSim {
    SimulatorLinker::SimulatorLinker(EventHandler *eventHandler, SimulatedWallTime *simulatedWallTime) {
        event_handler_ = eventHandler;
        simulated_time_ = simulatedWallTime;
    }

    SimulatorLinker::~SimulatorLinker() {
        delete event_handler_;
//        delete simulated_time_;
    }

    void SimulatorLinker::LoadTraceData(AliTraceLoader *trace_loader) {
        trace_loader->LoadServerEvents(&server_events_map_);
        trace_loader->LoadTaskEvent(&task_events_map_);
        ConstructTasksMap();
        trace_loader->LoadBatchInstanceEvent(&batch_instance_events_map_);

        // loads the initialized machine resources and then erases it from server_events_map_ because we don't need it anymore
        auto zero_sever_events = server_events_map_.count(0);
        auto iter = server_events_map_.find(0);
        while (zero_sever_events) {
            AddServer(iter->second.machine_id_, iter->second);
            ++iter;
            --zero_sever_events;
        }
        server_events_map_.erase(0);
    }

    void SimulatorLinker::ConstructTasksMap() {
        for (auto it = task_events_map_.begin(); it != task_events_map_.end(); ++it) {
            tasks_map_.insert({it->second.task_id_, it->second});
        }
    }

    void SimulatorLinker::HandleEventsOfCurrentTimeStamp() {
        uint64_t cur_sim_ts = simulated_time_->GetCurrentTimeStamp();

        LOG(INFO) << "the cluster has " << current_tasks_map_.size() << " tasks at " << cur_sim_ts << endl;
        auto tasks_count_current_ts = task_events_map_.count(cur_sim_ts);
        auto task_events_map_iter = task_events_map_.find(cur_sim_ts);
        while (tasks_count_current_ts) {
            AddTask(task_events_map_iter->second);
            tasks_count_current_ts--;
        }

        onTaskFinished(cur_sim_ts);

        // load batch instance events
        auto count_batch_instance_cur_ts = batch_instance_events_map_.count(cur_sim_ts);
        if (count_batch_instance_cur_ts) {
            auto batch_instance_map_iter = batch_instance_events_map_.find(cur_sim_ts);
            while (count_batch_instance_cur_ts) {
                AddBatchInstance(batch_instance_map_iter->second);
                string instance_status = batch_instance_map_iter->second.status_;
//                if(instance_status == "Ready"){
//                    onBatchInstanceReady(&batch_instance_map_iter->second);
//                }else if(instance_status == "Waiting"){
//                    onBatchInstanceWaiting(&batch_instance_map_iter->second);
//                }else if(instance_status == "Running"){
//                    onBatchInstanceRunning(&batch_instance_map_iter->second);
//                }else if(instance_status == "Terminated"){
//                    onBatchInstanceTerminated(&batch_instance_map_iter->second);
//                }else if(instance_status == "Failed"){
//                    onBatchInstanceFailed(&batch_instance_map_iter->second);
//                }else if(instance_status == "Cancelled"){
//                    onBatchInstanceCancelled(&batch_instance_map_iter->second);
//                }else{
//                    //"Interupted"
//                    onBatchInstanceInterrupted(&batch_instance_map_iter->second);
//                }

                count_batch_instance_cur_ts--;
            }
        }

        onBatchInstanceFinished(cur_sim_ts);

    }

    void SimulatorLinker::AddBatchInstance(BatchInstance &batchInstance) {
        current_batch_instance_map_.insert({batchInstance.end_timestamp_, batchInstance});

        // updates the resource status  of the machine specified by the batchInstance
//        CHECK(tasks_map_.count(batchInstance.task_id_) == 1);
        if(tasks_map_.count(batchInstance.task_id_) == 0){
            return;
        }
        auto &task_ref = tasks_map_.at(batchInstance.task_id_);
        float avg_memory = task_ref.plan_men_;
        resource_record_.UpdateServerResourceStatus(1, &batchInstance, avg_memory);
        resource_record_.UpdateServerInstanceStatus(1, batchInstance.machine_ID_, batchInstance.end_timestamp_,
                                                    batchInstance.task_id_, batchInstance.seq_no_);

    }

    void SimulatorLinker::onBatchInstanceReady(BatchInstance *batchInstance) {

    }

    void SimulatorLinker::onBatchInstanceWaiting(BatchInstance *batchInstance) {

    }

    void SimulatorLinker::onBatchInstanceRunning(BatchInstance *batchInstance) {

    }

    void SimulatorLinker::onBatchInstanceTerminated(BatchInstance *batchInstance) {


    }

    void SimulatorLinker::onBatchInstanceFailed(BatchInstance *batchInstance) {

    }

    void SimulatorLinker::onBatchInstanceCancelled(BatchInstance *batchInstance) {

    }

    void SimulatorLinker::onBatchInstanceInterrupted(BatchInstance *batchInstance) {
        // TODO
    }

    void SimulatorLinker::onBatchInstanceFinished(uint64_t ts) {
        auto count_current_instance_ts = current_batch_instance_map_.count(ts);
        if (count_current_instance_ts > 0) {
            auto current_instance_iter = current_batch_instance_map_.find(ts);
            while (count_current_instance_ts ) {
                if (current_instance_iter->second.status_ == "Terminated" ||
                    current_instance_iter->second.status_ == "Failed" ||
                    current_instance_iter->second.status_ == "Cancelled" ||
                    current_instance_iter->second.status_ == "Interrupted") {
//                    auto previous_iter = current_tasks_iter;
//                    previous_iter--;
                    // updates the resource status  of the machine specified by the batchInstance
                    CHECK(tasks_map_.count(current_instance_iter->second.task_id_) == 1);
                    auto &task_ref = tasks_map_.at(current_instance_iter->second.task_id_);
                    float avg_memory = task_ref.plan_men_;
                    resource_record_.UpdateServerResourceStatus(2,&current_instance_iter->second, avg_memory);
                    resource_record_.UpdateServerInstanceStatus(2, current_instance_iter->second.machine_ID_, current_instance_iter->second.end_timestamp_, current_instance_iter->second.task_id_, current_instance_iter->second.seq_no_);


                    current_batch_instance_map_.erase(current_instance_iter);
                    current_instance_iter = current_batch_instance_map_.find(ts);
//                    current_tasks_iter = previous_iter;
                    LOG(INFO) << "remove " << current_instance_iter->second.task_id_ << " tasks at " << ts << endl;

                } else {
                    ++current_instance_iter;
                }

                --count_current_instance_ts;
            }
        }
    }


    void SimulatorLinker::AddServer(int32_t server_id, ServerEvent &server_event) {
        ResourceStatus resource_status;
        resource_status.ts_ = server_event.ts_;
        resource_status.machine_id_ = server_event.machine_id_;
        resource_status.norm_cpu_ = server_event.norm_cpu_;
        resource_status.norm_mem_ = server_event.norm_mem_;
        resource_status.norm_disk_ = server_event.norm_disk_;
        resource_status.used_cpu_ = 0;
        resource_status.used_disk_ = 0;
        resource_status.used_mem_ = 0;

        resource_record_.GetServerMap()->insert(pair<int32_t, ResourceStatus>(server_id, resource_status));
    }

    void SimulatorLinker::AddTask(TaskIdentifier &task_identifier) {
        // <key, value> (task_end_time, TaskIdentifier
        // TODO: handle different status of the status(waiting, terminated, etc.)
        current_tasks_map_.insert(pair<uint64_t, TaskIdentifier>(task_identifier.modify_timestamp_, task_identifier));
    }

    void SimulatorLinker::onTaskFinished(uint64_t ts) {
        auto count_current_tasks_ts = current_tasks_map_.count(ts);
        if (count_current_tasks_ts > 0) {
            auto current_tasks_iter = current_tasks_map_.find(ts);
            while (count_current_tasks_ts) {
                if (current_tasks_iter->second.status_ == "Terminated" ||
                    current_tasks_iter->second.status_ == "Failed" ||
                    current_tasks_iter->second.status_ == "Cancelled" ||
                    current_tasks_iter->second.status_ == "Interrupted") {
//                    auto previous_iter = current_tasks_iter;
//                    previous_iter--;
                    current_tasks_map_.erase(current_tasks_iter);
                    current_tasks_iter = current_tasks_map_.find(ts);
//                    current_tasks_iter = previous_iter;
                    LOG(INFO) << "remove " << current_tasks_iter->second.task_id_ << " tasks at " << ts << endl;
                } else {
                    ++current_tasks_iter;
                }

                --count_current_tasks_ts;
            }
        }
    }
}