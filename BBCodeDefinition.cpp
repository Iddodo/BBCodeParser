#include "BBCodeDefinition.h"

BBCodeDefinition::BBCodeDefinition() {}

BBCodeDefinition::BBCodeDefinition(
    std::unordered_map<std::string, BBCodeDefinition::Entry> &defs)
    : definitions(defs) {}

void BBCodeDefinition::define(
    std::unordered_map<std::string, BBCodeDefinition::Entry> &&defs) {
  this->definitions.insert(defs.begin(), defs.end());
}

std::optional<BBCodeDefinition::Entry>
BBCodeDefinition::entry(const std::string &symbol) {
  auto result = this->definitions.find(symbol);
  if (result == this->definitions.end()) {
    return {};
  }
  return result->second;
}
