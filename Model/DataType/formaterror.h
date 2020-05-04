#ifndef FORMATERROR_H
#define FORMATERROR_H

#include <stdexcept>

class FormatError : public std::runtime_error
{
public:
    FormatError(const std::string &);
};


#endif // FORMATERROR_H
