#ifndef BBCODERENDERER_H
#define BBCODERENDERER_H

#include "BBCodeEntity.h"
#include "BBCodeNestable.h"
#include "BBCodeRoot.h"
#include "BBCodeTag.h"

#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

using tag_renderer = std::function<std::string(const BBCodeTag *)>;

class BBCodeRenderer {
public:
  virtual std::string renderRoot(const BBCodeRoot *root) const;
  virtual std::string renderText(const std::string_view &text) const;
  virtual std::string renderTag(const BBCodeTag *tag) const = 0;

protected:
  std::string renderNestable(const BBCodeNestable *nestable) const;
  std::string renderEntity(const std::unique_ptr<BBCodeEntity> &e) const;
};

#endif
