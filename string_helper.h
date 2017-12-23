//
// Created by YuXiao on 12/19/17.
//

#ifndef ALISIMULATOR_STRING_HELPER_H
#define ALISIMULATOR_STRING_HELPER_H

#include <string>
#include <cstdarg>

using std::string;

namespace AliSim{
    // sprintf-like string formatter
    void spf(string* s, const string fmt, ...);
}



#endif //ALISIMULATOR_STRING_HELPER_H
