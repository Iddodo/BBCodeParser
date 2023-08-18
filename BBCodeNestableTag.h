#ifndef BBCODENESTABLETAG_H
#define BBCODENESTABLETAG_H

#include "BBCodeNestable.h"
#include "BBCodeTag.h"

class BBCodeNestableTag : public BBCodeTag, public BBCodeNestable {
public:
  BBCodeNestableTag(std::unique_ptr<BBCodeTag> &tag_ptr);
  BBCodeNestableTag(BBCodeTag &&definition_tag);
  virtual bool isNestable() const override;
  std::optional<std::string_view> nestableSymbol() const override;
};

#endif
