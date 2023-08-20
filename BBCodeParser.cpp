#include "BBCodeParser.h"
#include "BBCodeEntity.h"
#include "BBCodeRoot.h"
#include "BBCodeStateManager.h"
#include "BBCodeTag.h"
#include "BBCodeText.h"
#include "BBCodeTextualTag.h"

BBCodeParser::BBCodeParser(std::string_view src_text, BBCodeDefinition &&def,
                           BBCodeRenderer &&rend)
    : renderer(rend), definition(def) {

  // Put root at the top of the stack
  this->stack_nestables.push(std::unique_ptr<BBCodeNestable>(new BBCodeRoot()));

  // Iterate over string using the state machine
  for (auto ch : src_text) {
    this->fsm.feedCharacter(ch);
    switch (fsm.currentState()) {

      // Add character to the parser buffer member variable

    case StateMachine::TextInsertion:
    case StateMachine::TagDefinition:
    case StateMachine::ClosingTagDefinition:
    case StateMachine::LeftBracketDuplicate:
    case StateMachine::ParameterKey:
    case StateMachine::ParameterUnquotedValue:
    case StateMachine::ParameterDoubleQuotedValue: {
      this->buffer += ch;
      break;
    }

    // Append any existing text in the buffer to the current nestable
    // Empty buffer and prepare for a possible tag definition
    case StateMachine::LeftBracket: {
      if (!this->buffer.empty()) {
        this->appendTextToCurrentNestable(this->buffer);
        this->buffer.clear();
      }
      break;
    }

    case StateMachine::TagAwaitParameters: {
      this->active_tag = std::make_unique<BBCodeTag>(this->buffer);
      this->buffer.clear();
      break;
    }

    // No need to set the active tag, simply add this nestable to the stack
    case StateMachine::TagClosedWithNoParameters: {
      std::unique_ptr<BBCodeEntity> tag{};
      auto tag_def =
          this->definition.entry(std::string(this->active_tag->symbol()));
      if (!tag_def.has_value()) {
        throw std::string("Undefined tag name"
                          " ") +
            std::string(this->active_tag->symbol());
      }

      switch (tag_def.value().tag_type) {
      case BBCodeTagType::Textual:
        tag = std::unique_ptr<BBCodeEntity>(
            new BBCodeTextualTag(this->active_tag));
        break;
      case BBCodeTagType::Nestable:
        tag = std::unique_ptr<BBCodeEntity>(
            new BBCodeNestableTag(this->active_tag));
        break;
      case BBCodeTagType::SelfClosing:
        tag = std::unique_ptr<BBCodeEntity>(
            new BBCodeNestableTag(this->active_tag));
        break;
      }

      this->active_tag.reset();
      auto &nest = this->currentNestable();

      // Add tag to stack if it's nestable
      if (tag_def.value().tag_type != BBCodeTagType::SelfClosing) {
        this->stack_nestables.push(std::move(tag));

        // Otherwise, the tag needs to be appended to the current nestable
        // immediately.
      } else {
        nest->appendEntity(tag);
      }

      // TODO: Remember to append the created nestable tag to its parent after
      // it has been closed.

      break;
    }

    // A parameter name now exists in the buffer.
    // Save the parameter name and clear the buffer.
    case StateMachine::ParameterAwaitEqualSign:
    case StateMachine::ParameterEqualSign: {
      this->active_param_key = this->buffer;
      this->buffer.clear();
      break;
    }

    case StateMachine::TagParameterEmptyValue: {
      throw std::string("Empty value for parameter: ") + this->active_param_key;
      break;
    }

    // Current behavior: do not allow illegal parameters
    case StateMachine::TagParameterIllegalValue: {
      throw std::string("Illegal parameter: ") + this->active_param_key;
      break;
    }

    // Current behavior: do not allow rogue symbols
    case StateMachine::TagBadQuoteSign: {
      throw std::string("Bad quote sign in tag definition: ") +
          std::string(this->active_tag->symbol());
      break;
    }

    case StateMachine::ClosingTagBadSymbolName:
      throw std::string("Attempted closing tag name '") + this->buffer +
          "' does not match opening tag name '" +
          std::string(this->currentNestable()->nestableSymbol().value_or(
              "root BBCode entity")) +
          "'";
      break;

    case StateMachine::OpeningTagBadAdditionalLiterals: {
      throw std::string("Opening tag contains additional characters: ") +
          this->buffer;
      break;
    }

    case StateMachine::ClosingTagBadAdditionalLiterals: {
      throw std::string("Closing tag contains additional characters: ") +
          this->buffer;
      break;
    }

    case StateMachine::EmptyBracketPair: {
      throw "An illegal empty bracket pair has been identified";
      break;
    }

    // Feed opening and closing tags to the state machine, which will adjust the
    // state accordingy
    case StateMachine::ClosingTagAwaitRightBracket:
    case StateMachine::ClosingTagRightBracket:
      if (!this->fsm.compareStrings(
              this->buffer, this->currentNestable()->nestableSymbol())) {
        // TODO: currently this does nothing. theoretically,
        // this block could be used to (for example)
        // scratch the closing tag attempt all together, as well as clearing the
        // buffer.
        // The current behavior throws an exception.
      }
      break;

    // TODO
    case StateMachine::OpeningTagRightBracket:
    case StateMachine::OpeningTagPairEndRightBracket:
    case StateMachine::ParameterPairEnd:
    case StateMachine::RightBracketDuplicate:

    case StateMachine::LeftBracketAwaitTagDefinition:
    case StateMachine::ParameterAwaitValue:
    case StateMachine::ClosingTagAwaitSymbol:
      break;
    }
  }
}

void BBCodeParser::appendTextToCurrentNestable(std::string_view text) {
  auto &nestable = this->currentNestable();
  auto &last_entity = nestable->lastEntity();

  // Simply append the text to the last entity if it happens to be text
  if (last_entity->type() == BBCodeEntityType::Text) {
    (dynamic_cast<BBCodeText *>(last_entity.get()))->appendText(text);
    return;
  }

  // Otherwise, create a new text entity and append to current nestable.
  auto text_entity =
      std::unique_ptr<BBCodeEntity>(new BBCodeText(this->buffer));
  nestable->appendEntity(text_entity);
}

std::unique_ptr<BBCodeNestable> &BBCodeParser::currentNestable() {
  return this->stack_nestables.top();
}
