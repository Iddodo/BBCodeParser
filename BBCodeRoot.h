#ifndef BBCODEROOT_H
#define BBCODEROOT_H

#include "BBCodeEntity.h"
#include "BBCodeNestable.h"

class BBCodeRoot : public BBCodeEntity, public BBCodeNestable {
public:
  BBCodeRoot() : BBCodeEntity(BBCodeEntityType::Root) {}
};

#endif
