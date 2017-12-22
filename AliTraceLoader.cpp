//
// Created by lilelr on 12/21/17.
//

#include "AliTraceLoader.h"

namespace AliSim {
    AliTraceLoader::AliTraceLoader(string trace_path) {
        trace_path_ = trace_path;
    }

    void AliTraceLoader::LoadServerEvents(multimap<uint64_t, ServerEvent> *server_events_map) {

    }

    void AliTraceLoader::LoadBatchInstanceEvent(multimap<uint64_t, BatchInstance> *batch_instance_events_map) {

    }

    void AliTraceLoader::LoadTaskEvent(multimap<uint64_t, TaskIdentifier> *task_events_map) {}
}
