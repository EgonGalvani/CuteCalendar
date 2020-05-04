#include "formaterror.h"

FormatError::FormatError(const std::string& what_arg) : std::runtime_error(what_arg) {}
