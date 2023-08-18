#include "BBCodeTag.h"
#include "BBCodeEntity.h"

const auto &BBCodeTag::parameters() const { return this->m_parameters; }

BBCodeTag::BBCodeTag(std::string_view tag_symbol)
    : BBCodeEntity(BBCodeEntityType::Tag) {}

bool BBCodeTag::isNestable() const { return false; }
