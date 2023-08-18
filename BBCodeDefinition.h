#ifndef BBCODEDEFINITION_H
#define BBCODEDEFINITION_H

#include "BBCodeTag.h"

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

class BBCodeDefinition {
public:
  struct Entry {
    explicit Entry(BBCodeTagType tag_type) : tag_type(tag_type) {}
    BBCodeTagType tag_type;
  };

private:
  std::unordered_map<std::string, Entry> definitions;

public:
  BBCodeDefinition();
  BBCodeDefinition(
      std::unordered_map<std::string, BBCodeDefinition::Entry> &defs);
  void define(std::unordered_map<std::string, BBCodeDefinition::Entry> &&defs);
  std::optional<Entry> entry(const std::string &symbol);
};

#endif
