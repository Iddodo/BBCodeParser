#ifndef BBCODENESTABLE_H
#define BBCODENESTABLE_H

#include <list>
#include <memory>

#include "BBCodeEntity.h"

using entity_list = std::list<std::unique_ptr<BBCodeEntity>>;
using ent_ptr = std::unique_ptr<BBCodeEntity>;

class BBCodeNestable {
  std::list<std::unique_ptr<BBCodeEntity>> m_content;

public:
  virtual ent_ptr &appendEntity(ent_ptr &e);
  virtual std::optional<std::string_view> nestableSymbol() const { return {}; }

  std::unique_ptr<BBCodeEntity> &lastEntity();
  const entity_list &content() const;
};

#endif
