#include "invalidinterval.h"

InvalidInterval::InvalidInterval(const std::string& msg)
    : std::logic_error(msg) {}
