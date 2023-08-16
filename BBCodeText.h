#ifndef BBCODESTRING_H_
#define BBCODESTRING_H_

#include "BBCodeEntity.h"

// An object for a simple std::string inside a BBCode tag
class BBCodeText : public BBCodeEntity {
  std::string m_text;

public:
  BBCodeText();
  BBCodeText(std::string_view init_sv);
  void appendCharacter(char c);
  void appendText(std::string_view sv);
  std::string_view text() const;
  virtual std::optional<std::string_view> peek_text() const override;
};

#endif // BBCODESTRING_H_
