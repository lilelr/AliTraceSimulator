//
// Created by lilelr on 12/21/17.
//

#include "ResourceRecord.h"
namespace AliSim{
    ResourceRecord::ResourceRecord(){

    }

    unordered_map<int32_t, ResourceStatus>* ResourceRecord::GetServerMap() {
        return &server_map_;
    }
}