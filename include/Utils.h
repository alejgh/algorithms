#ifndef ALGORITHMS_UTILS_H
#define ALGORITHMS_UTILS_H

#include "catch.hpp"

namespace utils {

    template <typename DataStructure>
    void CheckString(const DataStructure &ds, const std::string &want){
        std::stringstream want_ss;
        std::stringstream result;
        want_ss << want;
        result << ds;
        want_ss.flush();
        result.flush();
        REQUIRE(want_ss.str() == result.str());
    }
}

#endif //ALGORITHMS_UTILS_H
