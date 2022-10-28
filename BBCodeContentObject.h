#ifndef BBCODECONTENTOBJECT_H_
#define BBCODECONTENTOBJECT_H_

#include <string>

using std::string;

// Abstract-type class for an object inside a BBCode tag
class BBCodeContentObject {



public:
    virtual string render() = 0;

    virtual bool isString() const = 0;

    virtual void insertChar(char c) = 0;
};

#endif // BBCODECONTENTOBJECT_H_
