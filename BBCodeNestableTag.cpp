#include "BBCodeNestableTag.h"

std::optional<std::string_view> BBCodeNestableTag::nestableSymbol() const {
  return this->symbol();
}

bool BBCodeNestableTag::isNestable() const { return true; }

BBCodeNestableTag::BBCodeNestableTag(BBCodeTag &&tag_definition)
    : BBCodeTag(tag_definition) {}

BBCodeNestableTag::BBCodeNestableTag(std::unique_ptr<BBCodeTag> &tag_ptr)
    : BBCodeTag(*tag_ptr) {}
