//
// Created by lilelr on 12/21/17.
//

#include "EventHandler.h"

namespace AliSim{
  EventHandler::EventHandler(SimulatedWallTime *simulated_time) {
      simulated_time_ = simulated_time;
  }

    void EventHandler::LoadInitialMachineEvents(multimap<uint64_t,ServerEvent>* server_events_map) {

    }

    void EventHandler::AddEvent(uint64_t timestamp) {

    }

}
