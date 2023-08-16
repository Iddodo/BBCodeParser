#ifndef BBCODEPARSERSTATE_H
#define BBCODEPARSERSTATE_H

#include "BBCodeBuffer.h"
#include <optional>
#include <string>

enum class StateMachine {
  TextInsertion,

  // Instance of some left bracket appearing
  // Should handle case of bracket sequence ('[[[...')
  LeftBracket,
  LeftBracketAwaitTagDefinition,

  TagDefinition,
  TagAwaitParameters,
  TagClosedWithNoParameters,

  ParameterKey,
  ParameterAwaitEqualSign,
  ParameterEqualSign,
  ParameterAwaitValue,

  // This ends the tag definition
  TagParameterEmptyValue,

  TagParameterIllegalValue,
  ParameterUnquotedValue,
  ParameterDoubleQuotedValue,
  // ParameterDoubleQuotedBackslash,

  // A bad quote sign eliminates the tag definition
  TagBadQuoteSign,

  ClosingTagDefinition,
  ClosingTagAwaitSymbol,
  ClosingTagBadSymbolName,
  ClosingTagAwaitRightBracket,
  ClosingTagRightBracket,
  ClosingTagBadAdditionalLiterals,

  EmptyBracketPair
};

class BBCodeStateManager {

  StateMachine state;

public:
  BBCodeStateManager();
  void feedCharacter(char ch);
  bool compareStrings(std::optional<std::string_view> sv1,
                      std::optional<std::string_view> sv2);

  StateMachine currentState() const;

private:
  void handlerRouter(char ch);

private:
  void textInsertionScopeHandler();
  void textLeftBracketHandler();
  void tagDefinitionHandler();
  void tagAwaitParametersHandler();
  void parameterKeyHandler();
  void parameterValueHandler();
};

#endif
