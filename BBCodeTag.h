#ifndef BBCODETAG_H_
#define BBCODETAG_H_

#include "BBCodeTagInvalidness.h"
#include "BBCodeContentObject.h"
#include "BBCodeString.h"


#include <vector>
#include <memory>
#include <string>
#include <memory>
#include <cctype>



using std::vector;
using std::shared_ptr;
using std::string;

using std::shared_ptr;
using std::make_shared;

class BBCodeTag : public BBCodeContentObject {
    bool param_mode;

    BBCodeTagInvalidness valid;

    shared_ptr<BBCodeTag> parent;

    vector< shared_ptr<BBCodeContentObject> > inner;
    vector<string> params;

    bool root;

    bool whitespace_sequence;

// Insert into tag
public:
    void insertChar(char c) {

        if (this->paramMode()) {

            this->insertCharParam(c);
            return;
        }

        this->insertCharInner(c);
    }
    
    void pushContent(shared_ptr<BBCodeContentObject> content) {
        this->inner.push_back(content);
    }

private:
    void insertCharParam(char c) {

        if (this->isWhitespace(c)) {
            this->whitespace_sequence = true;
            return;
        }

        // In case of an empty param list or a white sequence
        if (this->params.empty() || this->whitespace_sequence) {
            this->params.push_back("");
        }

        this->whitespace_sequence = false;
        this->params.back() += c;
    }

    void insertCharInner(char c) {

        // If last content object inside tag is not a string,
        // Create a new empty string and push back to inner vector
        if (this->inner.empty() || !(this->inner.back()->isString())) {

            this->inner.push_back(make_shared<BBCodeString>());
        }

        this->inner.back()->insertChar(c);
    }




// Constructors
public:
    BBCodeTag(shared_ptr<BBCodeTag> parent = nullptr)
        : param_mode(true), valid(BBCODE_VALID), parent(parent), root(false), whitespace_sequence(false) {}

// Boolean tests
public:
    bool isValid() const { return this->valid == BBCODE_VALID; }

    bool paramMode() const { return this->param_mode; }

    bool isString() const { return false; }

    bool isClosingTag() const {

        if (this->emptyTag()) return false;

        return this->params[0][0] == '/';
    }



    bool matches(shared_ptr<BBCodeTag> tag2) {

        if (!tag2 || this->emptyTag() || tag2->emptyTag()) return false;

        return this->params[0].compare(tag2->params[0]);
    }


        bool emptyTag() const { return this->params.empty() || this->params[0].empty(); }



// Getters and setters
public:
    shared_ptr<BBCodeTag> getParent() { return this->parent; }

    void setInvalid(BBCodeTagInvalidness s) { this->valid = s; }


    void exitParamMode() { this->param_mode = false; }

    // Make this a friend function
    void setRoot() {

        this->root = true;
        this->exitParamMode();
    }

    string name() {
        // Empty tag
        if (this->root) return "root";
        if (this->emptyTag()) return "";

        return this->params[0];
    }

private:

    bool isWhitespace(char c) const {
        return std::isspace(c);
    }



// Rendering function

public:

    string render() {

        // Return nothing on empty tag
        if(this->emptyTag() && !this->root) return "[]";

        // Return nothing on closing tag
        if (this->isClosingTag()) return "";

        // Return nothing on invalid tags
        if (!this->isValid()) return "";

        string inner = this->renderInner();
        string tag = this->name();

        if (tag == "b")
            return "<b>" + inner + "</b>";

        if (tag == "img")
            return "<img src=\"" + inner + "\" alt=\"\" />";


        if (tag == "u")
            return "<u>" + inner + "</u>";

        if (tag == "center")
            return "<div style=\"text-align: center;\">" + inner + "</div>";


        return inner;

    }

private:

        string renderInner() {

            string result = "";

            for (shared_ptr<BBCodeContentObject> content : this->inner) {
                result += content->render();
            }

            return result;
        }

};

#endif // BBCODETAG_H_
