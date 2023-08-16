#ifndef BBCODETAG_H
#define BBCODETAG_H

#include <list>
#include <memory>
#include <optional>
#include <unordered_map>

#include "BBCodeEntity.h"
#include "BBCodeNestable.h"

class BBCodeTag : public BBCodeEntity, public BBCodeNestable {
  std::unordered_map<std::string_view, std::string_view> m_parameters;
  std::string_view m_symbol;

public:
  BBCodeTag(std::string_view tag_symbol);
  bool hasParams() const;
  std::string_view &symbol() const;

  std::optional<std::string_view &> getParam(const std::string_view &key) const;

  void setParam(const std::string &key, const std::string &val);

  const auto &parameters() const;

  std::optional<std::string_view> nestableSymbol() const override;
};

#endif
