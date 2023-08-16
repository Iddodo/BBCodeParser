#ifndef BBCODEHTMLRENDERER_H
#define BBCODEHTMLRENDERER_H

#include "BBCodeRenderer.h"

#include <array>
#include <utility>

class BBCodeHTMLRenderer : public BBCodeRenderer {
  std::unordered_map<std::string_view, tag_renderer const> tag_renderers;

public:
  BBCodeHTMLRenderer();

private:
  std::string transformTagToHTMLNoParams(const BBCodeTag *tag) const;
  std::string renderSelfClosingTagNoParams(const BBCodeTag *tag) const;
  virtual std::string renderTag(const BBCodeTag *tag) const override;

private:
  static constexpr std::array html_regular_tags_no_params{"b", "u"};
  static constexpr std::array html_self_enclosing_tags_no_params{"hr"};
};

#endif
