#include "BBCodeRenderer.h"
#include "BBCodeNestable.h"

using root_ptr = std::unique_ptr<BBCodeRoot>;

inline std::string
BBCodeRenderer::renderEntity(const std::unique_ptr<BBCodeEntity> &e) const {
  switch (e->type()) {
  case BBCodeEntityType::Text:
    return this->renderText(e->peek_text().value());

  case BBCodeEntityType::Tag:
    return this->renderTag(dynamic_cast<const BBCodeTag *>(e.get()));

  case BBCodeEntityType::Root:
    return this->renderRoot(dynamic_cast<const BBCodeRoot *>(e.get()));
  }
}

std::string
BBCodeRenderer::renderNestable(const BBCodeNestable *nestable) const {
  std::string result{};
  for (auto &containable : nestable->content()) {
    result += this->renderEntity(containable);
  }
  return result;
}

std::string BBCodeRenderer::renderRoot(const BBCodeRoot *root) const {
  return std::move(
      this->renderNestable(dynamic_cast<const BBCodeNestable *>(root)));
}
