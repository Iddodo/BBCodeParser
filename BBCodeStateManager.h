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
  LeftBracketDuplicate,
  LeftBracketAwaitTagDefinition,

  TagDefinition,
  TagAwaitParameters,
  TagClosedWithNoParameters,
  OpeningTagBadAdditionalLiterals,
  OpeningTagRightBracket,
  OpeningTagPairEndRightBracket,

  ParameterKey,
  ParameterAwaitEqualSign,
  ParameterEqualSign,
  ParameterAwaitValue,

  // This ends the tag definition
  TagParameterEmptyValue,

  TagParameterIllegalValue,
  ParameterUnquotedValue,
  ParameterDoubleQuotedValue,
  ParameterPairEnd,
  // ParameterDoubleQuotedBackslash,

  // A bad quote sign eliminates the tag definition
  TagBadQuoteSign,

  ClosingTagDefinition,
  ClosingTagAwaitSymbol,
  ClosingTagBadSymbolName,
  ClosingTagAwaitRightBracket,
  ClosingTagRightBracket,
  ClosingTagBadAdditionalLiterals,

  EmptyBracketPair,
  RightBracketDuplicate
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
};

#endif
