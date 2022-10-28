#ifndef BBCODEPARSER_H_
#define BBCODEPARSER_H_

#include "BBCodeTag.h"


#include <string>
#include <stack>
#include <memory>


using std::string;
using std::stack;
using std::shared_ptr;

#define LBRACKET '['
#define RBRACKET ']'


class BBCodeParser {

    shared_ptr<BBCodeTag> root;
    stack< shared_ptr<BBCodeTag> > tag_stack;

public:

    BBCodeParser(string text) : root(make_shared<BBCodeTag>()) {
        root->setRoot();
        tag_stack.push(root);

        // Iterate over text characters individually.

        for (unsigned int i = 0; i < text.length(); i++) {

            this->insertChar(text[i]);
        }
    }

private:

    void insertChar(char c) {

        shared_ptr<BBCodeTag> controller = this->controllerTag();

        // Handle the beginning of a new BBCode tag
        if (c == LBRACKET) {

            shared_ptr<BBCodeTag> new_tag = make_shared<BBCodeTag>(controller->getParent());
            this->controllerTag()->pushContent(new_tag);
            this->pushController(new_tag);

            return;
        }

        // Handle the ending of a BBCode tag
        if (c == RBRACKET) {

            if (controller->isClosingTag()) {

                shared_ptr<BBCodeTag> parent = controller->getParent();

                /* Tag mismatch with parents
                 * Current approach: simply deem mismatched closing tag invalid */
                if (!controller->matches(parent)) {

                    controller->setInvalid(BBCODE_OUT_OF_PLACE_CLOSING_TAG);
                }

                // Otherwise, pop back BBCode content, as a valid closing tag
                // should not be nested inside.

               this->popController();
               this->popController();

               return;

            }

            if (controller->emptyTag()) {

                this->popController();
                return;
            }

            // Not a closing tag, exit param mode

            controller->exitParamMode();
            return;
        }

        controller->insertChar(c);

    }

private:

    shared_ptr<BBCodeTag> controllerTag() { return this->tag_stack.top(); }

    void pushController(shared_ptr<BBCodeTag> tag) { this->tag_stack.push(tag); }
    void popController() {this->tag_stack.pop(); }

// Render
public:
    string render() const {
        return this->root->render();
    }


};

#endif // BBCODEPARSER_H_
