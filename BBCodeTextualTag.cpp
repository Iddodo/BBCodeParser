#include "BBCodeTextualTag.h"
#include "BBCodeNestable.h"
#include "BBCodeNestableTag.h"

ent_ptr &BBCodeTextualTag::appendEntity(std::unique_ptr<BBCodeEntity> &e) {
  if (e->type() != BBCodeEntityType::Text) {
    throw "Attempted to append a non-textual entity to a BBCodeTextualTag.";
  }

  return this->BBCodeNestable::appendEntity(e);
}

BBCodeTextualTag::BBCodeTextualTag(BBCodeTag &&tag_definition)
    : BBCodeNestableTag(std::move(tag_definition)) {}

BBCodeTextualTag::BBCodeTextualTag(std::unique_ptr<BBCodeTag> &tag_ptr)
    : BBCodeNestableTag(tag_ptr) {}
