#ifndef BBCODETEXTUALTAG_H
#define BBCODETEXTUALTAG_H

#include "BBCodeNestableTag.h"

class BBCodeTextualTag : public BBCodeNestableTag {
public:
  BBCodeTextualTag(std::unique_ptr<BBCodeTag> &tag_ptr);
  BBCodeTextualTag(BBCodeTag &&tag_definition);
  virtual ent_ptr &appendEntity(std::unique_ptr<BBCodeEntity> &e) override;
};

#endif
