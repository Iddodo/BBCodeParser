#ifndef BBCODEENTITY_H_
#define BBCODEENTITY_H_

#include <optional>
#include <string>
#include <string_view>

enum class BBCodeEntityType { Text, Tag, Root };

// Abstract-type class for an object inside a BBCode tag
class BBCodeEntity {
protected:
  BBCodeEntityType entity_type;

public:
  BBCodeEntity(BBCodeEntityType t) : entity_type(t){};
  virtual BBCodeEntityType type() const { return this->entity_type; }
  virtual std::optional<std::string_view> peek_text() const { return {}; }
};

#endif // BBCODEENTITY_H_
