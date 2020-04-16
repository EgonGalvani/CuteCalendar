#ifndef INVALIDINTERVAL_H
#define INVALIDINTERVAL_H

#include <stdexcept>

class InvalidInterval : public std::logic_error {
    public:
        InvalidInterval(const std::string&);
};

#endif // INVALIDINTERVAL_H
