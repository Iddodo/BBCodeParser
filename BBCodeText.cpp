#include "BBCodeText.h"
#include "BBCodeEntity.h"

BBCodeText::BBCodeText(std::string_view init_sv)
    : BBCodeEntity(BBCodeEntityType::Text), m_text(init_sv) {}

BBCodeText::BBCodeText() : BBCodeText("") {}

void BBCodeText::appendCharacter(char c) { this->m_text += c; }
void BBCodeText::appendText(std::string_view sv) { this->m_text += sv; }

std::string_view BBCodeText::text() const { return this->m_text; }

std::optional<std::string_view> BBCodeText::peek_text() const {
  return this->m_text;
}
