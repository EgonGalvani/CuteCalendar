#ifndef FILE_IO
#define FILE_IO

#include "Container/vector.h"
#include "Hierarchy/serializable.h"
#include "DataType/deepptr.h"
#include "Hierarchy/event.h"
#include "DataType/date.h"

#include <vector>

template<typename T>
class FileIO {
protected:
    std::string _fileName;
public:
    FileIO(std::string fN) : _fileName(fN) {}

    virtual void write(const Container<Date, std::vector<DeepPtr<Event>>>&) const = 0;
    virtual Container<Date, std::vector<DeepPtr<Event>>> read() const = 0;
};

#endif // FILE_IO
