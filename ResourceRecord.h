//
// Created by lilelr on 12/21/17.
//

#ifndef ALISIMULATOR_RESOURCERECORD_H
#define ALISIMULATOR_RESOURCERECORD_H


#include <cstdint>
#include <iostream>
#include <map>
#include <unordered_map>

#include "ResourceStatus.h"

using namespace std;
namespace AliSim {

    class ResourceRecord {

    private:
        unordered_map<int32_t, ResourceStatus> server_map_;


    public:
        explicit ResourceRecord();

        void UpdateServerResourceStatus();


    };
}

#endif //ALISIMULATOR_RESOURCERECORD_H
