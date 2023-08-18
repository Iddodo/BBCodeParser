#ifndef BBCODEEXAMPLEDEFINITION_H
#define BBCODEEXAMPLEDEFINITION_H

#include "BBCodeDefinition.h"
#include "BBCodeTag.h"

#include <unordered_map>

// An example singleton BBCodeDefinition

class BBCodeExampleDefinition : public BBCodeDefinition {
private:
  static inline std::unordered_map<std::string, Entry> basic_definitions{
      {"center", Entry(BBCodeTagType::Nestable)},
      {"b", Entry(BBCodeTagType::Textual)},
      {"u", Entry(BBCodeTagType::Textual)},
      {"img", Entry(BBCodeTagType::Textual)},
      {"hr", Entry(BBCodeTagType::SelfClosing)}};

public:
  BBCodeExampleDefinition()
      : BBCodeDefinition(BBCodeExampleDefinition::basic_definitions){};
};

#endif
