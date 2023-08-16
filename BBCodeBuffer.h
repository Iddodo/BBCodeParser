#ifndef BBCODEBUFFER_H
#define BBCODEBUFFER_H

#include <string>
#include <string_view>

class BBCodeBuffer {
  std::string buffer;

public:
  std::string_view peek() const;
  void append(char ch);
  void flush();
};

#endif
