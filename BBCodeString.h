#ifndef BBCODESTRING_H_
#define BBCODESTRING_H_

#include <string>
using std::string;


#include "BBCodeContentObject.h"

// An object for a simple string inside a BBCode tag
class BBCodeString : public BBCodeContentObject {

    string text;


public:
    bool isString() const { return true; }


    void insertChar(char c) { text += c;}

public:
    string render() { return this->text; }
};

#endif // BBCODESTRING_H_
