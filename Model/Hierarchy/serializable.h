#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

class Serializable {
public:
    virtual void serialize() const = 0;
    static Serializable* parse() = 0;
};

#endif // SERIALIZABLE_H
