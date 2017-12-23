//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_ALITRACELOADER_H
#define ALISIMULATOR_ALITRACELOADER_H

#include <string>
#include <map>

#include "AliTracePreProcessor.h"

using namespace std;

namespace AliSim{
    class AliTraceLoader {
    private:
        string trace_path_;
    public:
        AliTraceLoader();
        explicit AliTraceLoader(string trace_path);

        void LoadServerEvents(multimap<uint64_t,ServerEvent>* server_events_map);
        void LoadTaskEvent(multimap<uint64_t, TaskIdentifier>* task_events_map);
        void LoadBatchInstanceEvent(multimap<uint64_t, BatchInstance>* batch_instance_events_map);

    };
}



#endif //ALISIMULATOR_ALITRACELOADER_H
