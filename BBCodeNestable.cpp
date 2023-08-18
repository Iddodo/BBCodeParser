#include "BBCodeNestable.h"

const entity_list &BBCodeNestable::content() const { return this->m_content; }

ent_ptr &BBCodeNestable::appendEntity(std::unique_ptr<BBCodeEntity> &e) {
  this->m_content.push_back(std::move(e));

  return this->m_content.back();
}

std::unique_ptr<BBCodeEntity> &BBCodeNestable::lastEntity() {
  return this->m_content.back();
}
