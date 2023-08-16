#include "BBCodeStateManager.h"

// The initial state is defined as "TextInsertion"
BBCodeStateManager::BBCodeStateManager() : state(StateMachine::TextInsertion) {}

void BBCodeStateManager::handlerRouter(char ch) {
  switch (this->state) {
  case StateMachine::TextInsertion:
    this->textInsertionScopeHandler();
    return;

  case StateMachine::LeftBracket:
    this->textLeftBracketHandler();
    return;

  default:
    break;
  }
}

StateMachine BBCodeStateManager::currentState() const { return this->state; }

bool BBCodeStateManager::compareStrings(std::optional<std::string_view> s1,
                                        std::optional<std::string_view> s2) {

  bool bad_compare = !(s1.has_value() && s2.has_value());
  switch (this->state) {

  // A closing tag symbol has been passed
  case StateMachine::ClosingTagAwaitRightBracket:
  case StateMachine::ClosingTagRightBracket:
    if (bad_compare || (s1.value() != s2.value())) {
      this->state = StateMachine::ClosingTagBadSymbolName;
      return false;
    }

    this->state = StateMachine::TextInsertion;
    return true;

  // Unreachable
  default:
    return false;
  }
}
