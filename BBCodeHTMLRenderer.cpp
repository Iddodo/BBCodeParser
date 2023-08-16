
#include "BBCodeHTMLRenderer.h"

#include <__functional/bind.h>
#include <format>
#include <functional>

BBCodeHTMLRenderer::BBCodeHTMLRenderer() {
  for (auto sym_nestable : html_regular_tags_no_params) {
    this->tag_renderers.insert(
        {sym_nestable,
         std::bind(&BBCodeHTMLRenderer::transformTagToHTMLNoParams, this,
                   std::placeholders::_1)});
  }

  for (auto sym_sc : html_self_enclosing_tags_no_params) {
    this->tag_renderers.insert(
        {sym_sc, std::bind(&BBCodeHTMLRenderer::renderSelfClosingTagNoParams,
                           this, std::placeholders::_1)});
  }
}

std::string
BBCodeHTMLRenderer::transformTagToHTMLNoParams(const BBCodeTag *tag) const {
  std::string sym{tag->symbol()};
  std::string inner{this->renderNestable(tag)};
  return std::string("<") + sym + ">" + inner + "</" + sym + ">";
}

std::string
BBCodeHTMLRenderer::renderSelfClosingTagNoParams(const BBCodeTag *tag) const {
  std::string sym{tag->symbol()};
  return std::string("<") + sym + " />";
}

std::string BBCodeHTMLRenderer::renderTag(const BBCodeTag *tag) const {

  // Throw an error if a non-allowed tag is used
  if (!this->tag_renderers.count(tag->symbol())) {
    throw std::string("The tag [") + std::string(tag->symbol()) +
        "] is not allowed by BBCodeHTMLRenderer.";
  }

  return this->tag_renderers.find(tag->symbol())->second(tag);
}
