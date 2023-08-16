#ifndef BBCODEPARSER_H
#define BBCODEPARSER_H

#include "BBCodeEntity.h"
#include "BBCodeRenderer.h"
#include "BBCodeRoot.h"
#include "BBCodeStateManager.h"
#include "BBCodeTag.h"

#include <memory>
#include <stack>

class BBCodeParser {
  BBCodeStateManager fsm;
  BBCodeRenderer &renderer;
  std::stack<std::unique_ptr<BBCodeNestable>> stack_nestables;
  std::string buffer;
  std::unique_ptr<BBCodeTag> active_tag;
  std::string active_param_key;
  std::string active_param_value;

public:
  BBCodeParser(std::string_view src_text, BBCodeRenderer &&rend);

private:
  void appendTextToCurrentNestable(std::string_view text);
  std::unique_ptr<BBCodeNestable> &currentNestable();
};

#endif
