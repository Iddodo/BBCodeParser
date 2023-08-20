#include "BBCodeStateManager.h"
#include <cctype>

// The initial state is defined as "TextInsertion"
BBCodeStateManager::BBCodeStateManager() : state(StateMachine::TextInsertion) {}

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

void BBCodeStateManager::feedCharacter(char ch) {
  switch (this->state) {

  case StateMachine::OpeningTagRightBracket:
  case StateMachine::ClosingTagRightBracket:
  case StateMachine::TagClosedWithNoParameters:
  case StateMachine::LeftBracketDuplicate:
  case StateMachine::TextInsertion: {
    if (ch == '[') {
      this->state = StateMachine::LeftBracket;
    }
  } break;
  case StateMachine::LeftBracket: {
    if (std::isspace(ch)) {
      this->state = StateMachine::LeftBracketAwaitTagDefinition;

    } else if (std::isalnum(ch)) {
      this->state = StateMachine::ParameterKey;

    } else if (ch == '[') {
      this->state = StateMachine::LeftBracketDuplicate;

    } else if (ch == ']') {
      this->state = StateMachine::EmptyBracketPair;
    } else {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    }
    break;
  }
  case StateMachine::LeftBracketAwaitTagDefinition: {
    if (std::isalnum(ch)) {
      this->state = StateMachine::TagDefinition;

    } else if (std::isspace(ch)) {
      this->state = StateMachine::LeftBracketAwaitTagDefinition;

    } else if (ch == '/') {
      this->state = StateMachine::ClosingTagAwaitSymbol;
    } else {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    }
    break;
  }
  case StateMachine::TagDefinition: {
    if (std::isspace(ch)) {
      this->state = StateMachine::TagAwaitParameters;

    } else if (std::isalnum(ch)) {
      this->state = StateMachine::TagDefinition;

    } else {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    }
    break;
  }
  case StateMachine::TagAwaitParameters: {
    if (std::isspace(ch)) {
      // ...
    } else if (std::isalnum(ch)) {
      this->state = StateMachine::ParameterKey;

    } else {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    }
    break;
  }
  case StateMachine::ParameterKey: {
    if (std::isspace(ch)) {
      this->state = StateMachine::ParameterAwaitEqualSign;

    } else if (ch == '=') {
      this->state = StateMachine::ParameterAwaitValue;

    } else if (std::isalnum(ch)) {
      this->state = StateMachine::ParameterKey;

    } else {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    }
    break;
  }
  case StateMachine::ParameterAwaitEqualSign: {
    if (std::isspace(ch)) {
      this->state = StateMachine::ParameterAwaitEqualSign;

    } else if (ch == '=') {
      this->state = StateMachine::ParameterEqualSign;

    } else {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    }
    break;
  }
  case StateMachine::ParameterAwaitValue:
  case StateMachine::ParameterEqualSign: {
    if (std::isspace(ch)) {
      this->state = StateMachine::ParameterAwaitValue;

    } else if (std::isalnum(ch)) {
      this->state = StateMachine::ParameterUnquotedValue;

    } else if (ch == '"') {
      this->state = StateMachine::ParameterDoubleQuotedValue;
    } else {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    }
    break;
  }
  case StateMachine::ParameterUnquotedValue: {
    if (ch == '[') {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;

    } else if (ch == ']') {
      this->state = StateMachine::OpeningTagPairEndRightBracket;
    } else if (ch == '"' || ch == '\'') {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    } else if (std::isspace(ch)) {
      this->state = StateMachine::ParameterPairEnd;
    } else {
      this->state = StateMachine::ParameterUnquotedValue;
    }
    break;
  }
  case StateMachine::ParameterDoubleQuotedValue: {
    if (ch == '"') {
      this->state = StateMachine::ParameterPairEnd;

    } else {
      this->state = StateMachine::ParameterDoubleQuotedValue;
    }
    break;
  }
  case StateMachine::ParameterPairEnd: {
    if (std::isspace(ch)) {
      this->state = StateMachine::TagAwaitParameters;

    } else if (std::isalnum(ch)) {
      this->state = StateMachine::ParameterKey;

    } else {
      this->state = StateMachine::OpeningTagBadAdditionalLiterals;
    }
    break;
  }

  case StateMachine::OpeningTagPairEndRightBracket: {
    if (ch == '[') {
      this->state = StateMachine::LeftBracket;

    } else if (ch == ']') {
      this->state = StateMachine::RightBracketDuplicate;

    } else {
      this->state = StateMachine::TextInsertion;
    }
    break;
  }
  case StateMachine::ClosingTagDefinition: {
    if (ch == ']') {
      this->state = StateMachine::ClosingTagRightBracket;

    } else if (std::isspace(ch)) {
      this->state = StateMachine::ClosingTagAwaitRightBracket;

    } else if (std::isalnum(ch)) {
      this->state = StateMachine::ClosingTagDefinition;

    } else {
      this->state = StateMachine::ClosingTagBadAdditionalLiterals;
    }
  }
  case StateMachine::ClosingTagAwaitSymbol: {
    if (ch == '[') {
      this->state = StateMachine::ClosingTagBadAdditionalLiterals;

    } else if (ch == ']') {
      this->state = StateMachine::EmptyBracketPair;

    } else if (std::isalnum(ch)) {
      this->state = StateMachine::ClosingTagDefinition;

    } else {
      this->state = StateMachine::ClosingTagBadAdditionalLiterals;
    }
  }

  case StateMachine::ClosingTagAwaitRightBracket: {
    if (ch == '[') {
      this->state = StateMachine::ClosingTagBadAdditionalLiterals;

    } else if (ch == ']') {
      this->state = StateMachine::ClosingTagRightBracket;

    } else if (std::isspace(ch)) {
      this->state = StateMachine::ClosingTagAwaitRightBracket;

    } else {
      this->state = StateMachine::ClosingTagBadAdditionalLiterals;
    }
  }
  case StateMachine::ClosingTagBadSymbolName: {
  }
  case StateMachine::OpeningTagBadAdditionalLiterals: {
  }
  case StateMachine::ClosingTagBadAdditionalLiterals: {
  }
  case StateMachine::TagParameterIllegalValue: {
  }
  case StateMachine::TagParameterEmptyValue: {
  }
  case StateMachine::EmptyBracketPair: {
  }
  case StateMachine::TagBadQuoteSign: {
  }
  case StateMachine::RightBracketDuplicate: {
    break;
  }
  }
}
