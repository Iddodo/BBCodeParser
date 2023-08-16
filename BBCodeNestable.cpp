#include "BBCodeNestable.h"

const entity_list &BBCodeNestable::content() const { return this->m_content; }

void BBCodeNestable::appendEntity(std::unique_ptr<BBCodeEntity> &e) {
  this->m_content.push_back(std::move(e));
}

void BBCodeNestable::appendEntity(std::unique_ptr<BBCodeEntity> &&e) {
  this->m_content.push_back(std::move(e));
}

std::unique_ptr<BBCodeEntity> &BBCodeNestable::lastEntity() {
  return this->m_content.back();
}
