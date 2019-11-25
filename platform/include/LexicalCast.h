#ifndef LEXICAL_CAST_H_
#define LEXICAL_CAST_H_

#include <cassert>
#include <sstream>
#include <string>

namespace balcony_watering_system {
namespace platform {

template <typename T>
T lexical_cast(const std::string& str)
{
    T var;
    std::istringstream iss;
    iss.str(str);
    iss >> var;

    assert(!iss.fail() && "cast should not fail");

    return var;
}

}
}

#endif // LEXICAL_CAST_H_
