//
// Created by YuXiao on 12/19/17.
//

#include "string_helper.h"

namespace AliSimulator {
    // sprintf-like string formatter
    void spf(string* s, const std::string fmt, ...) {
        int64_t n, size = 100;
        bool b = false;
        va_list marker;

        while (!b) {
            s->resize(static_cast<size_t>(size));
            va_start(marker, fmt);
            // N.B. the below relies on a slightly dodgy cast via c_str()!
            n = vsnprintf((char*)s->c_str(), size, fmt.c_str(), marker);  // NOLINT -- deconstify
            va_end(marker);
            if ((n > 0) && ((b = (n < size)) == true))
                s->resize(static_cast<size_t>(n));
            else
                size *= 2;
        }
    }
}
