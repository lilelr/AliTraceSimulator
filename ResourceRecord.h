//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_RESOURCERECORD_H
#define ALISIMULATOR_RESOURCERECORD_H


#include <cstdint>
#include <map>
#include <bits/unordered_map.h>

#include "ResourceStatus.h"

using namespace std;

class ResourceRecord {

private:
    unordered_map<int32_t,ResourceStatus> server_map_;


  public:
    ResourceRecord();
    void UpdatServerResourceStatus();



};


#endif //ALISIMULATOR_RESOURCERECORD_H
