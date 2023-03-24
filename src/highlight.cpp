#include <cctype>
#include <cstdio>
#include <string>
#include <vector>

#include <curses.h>

#include "common.hpp"

#include "highlight.hpp"

#define TOKEN_TYPE(name, color, attrs) TokenType const TokenTypes::name {COLOR_##color, attrs}

TOKEN_TYPE(INDENT,      BLACK,   A_UNDERLINE);
TOKEN_TYPE(COMMENT,     WHITE,   A_DIM      );
TOKEN_TYPE(ALIAS,       YELLOW,  A_NORMAL   );
TOKEN_TYPE(LABEL,       GREEN,   A_NORMAL   );
TOKEN_TYPE(DIRECTIVE,   RED,     A_NORMAL   );
TOKEN_TYPE(INSTRUCTION, RED,     A_NORMAL   );
TOKEN_TYPE(REG_INDEX,   MAGENTA, A_NORMAL   );
TOKEN_TYPE(LIT_STR,     BLUE,    A_NORMAL   );
TOKEN_TYPE(LIT_CHAR,    BLUE,    A_NORMAL   );
TOKEN_TYPE(LIT_NUM,     BLUE,    A_NORMAL   );
TOKEN_TYPE(IMMEDIATE,   YELLOW,  A_NORMAL   );
TOKEN_TYPE(NUM_HEX,     CYAN,    A_NORMAL   );
TOKEN_TYPE(NUM_BIN,     CYAN,    A_NORMAL   );

#define HIGHLIGHTER(name) TokenType const *_highlight_##name(TokenType const **current_type, char ch, unsigned int index, unsigned int *start, unsigned int *end)

#define iswordch(ch) isalpha(ch) || ch == '_'

void Highlighter::highlight(std::vector<std::string> lines, Highlights &highlights) {
  highlights.clear();

  for (unsigned int line_no = 0; line_no < lines.size(); ++line_no) {
    // printf("Line #%d: '%s'\n", line_no, lines.at(line_no).c_str());
    highlight_line(lines.at(line_no), highlights[line_no]);
  }
}

void Highlighter::highlight_line(std::string line, std::vector<Highlight> &highlight) {
  HIGHLIGHTER(NULL);
  HIGHLIGHTER(INDENT);
  HIGHLIGHTER(ALIAS);
  HIGHLIGHTER(LABEL);
  HIGHLIGHTER(DIRECTIVE);
  HIGHLIGHTER(INSTRUCTION);
  HIGHLIGHTER(REG_INDEX);
  HIGHLIGHTER(LIT_STR);
  HIGHLIGHTER(LIT_CHAR);
  HIGHLIGHTER(LIT_NUM);
  HIGHLIGHTER(IMMEDIATE);
  HIGHLIGHTER(NUM_HEX);
  HIGHLIGHTER(NUM_BIN);

  TokenType const *current_type = nullptr;
  unsigned int start = 0;
  unsigned int end = 0;

  for (unsigned int index = 0; index < line.size(); ++index) {
    char ch = line.at(index);
    TokenType const *finished_type = nullptr;

    // printf("ch: %c\n", ch);

    if (ch == ';') {
      // Comment takes precedence over all
      finished_type = current_type;
      current_type = &TokenTypes::COMMENT;
    }
    else if (current_type == nullptr) {
      finished_type = _highlight_NULL(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::INDENT) {
      finished_type = _highlight_INDENT(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::ALIAS) {
      finished_type = _highlight_ALIAS(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::LABEL) {
      finished_type = _highlight_LABEL(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::DIRECTIVE) {
      finished_type = _highlight_DIRECTIVE(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::INSTRUCTION) {
      finished_type = _highlight_INSTRUCTION(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::REG_INDEX) {
      finished_type = _highlight_REG_INDEX(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::LIT_STR) {
      finished_type = _highlight_LIT_STR(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::LIT_CHAR) {
      finished_type = _highlight_LIT_CHAR(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::LIT_NUM) {
      finished_type = _highlight_LIT_NUM(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::IMMEDIATE) {
      finished_type = _highlight_IMMEDIATE(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::NUM_HEX) {
      finished_type = _highlight_NUM_HEX(&current_type, ch, index, &start, &end);
    }
    else if (current_type == &TokenTypes::NUM_BIN) {
      finished_type = _highlight_NUM_BIN(&current_type, ch, index, &start, &end);
    }

    // printf("finished: %p, current: %p\n", finished_type, current_type);

    if (finished_type) {
      highlight.emplace_back(start, end - start, finished_type->color, finished_type->attrs);
      start = index;
      end = index + 1;
    }

    if (current_type == &TokenTypes::COMMENT) {
      break;
    }
  }

  if (current_type) {
    highlight.emplace_back(start, line.size() - start, current_type->color, current_type->attrs);
  }
}

HIGHLIGHTER(NULL) {
  if (iswordch(ch)) {
    *current_type = &TokenTypes::ALIAS;
  }
  else if (isdigit(ch)) {
    *current_type = &TokenTypes::LIT_NUM;
  }
  else if (ch == '\'') {
    *current_type = &TokenTypes::LIT_CHAR;
  }
  else if (ch == '"') {
    *current_type = &TokenTypes::LIT_STR;
  }
  else if (ch == '#') {
    *current_type = &TokenTypes::IMMEDIATE;
  }
  else if (ch == '$') {
    *current_type = &TokenTypes::NUM_HEX;
  }
  else if (ch == '%') {
    *current_type = &TokenTypes::NUM_BIN;
  }
  else if (isspace(ch) && index == 0) {
    *current_type = &TokenTypes::INDENT;
  }

  return nullptr;
}

HIGHLIGHTER(INDENT) {
  if (iswordch(ch)) {
    *current_type = &TokenTypes::INSTRUCTION;
  }
  else if (ch == '.') {
    *current_type = &TokenTypes::DIRECTIVE;
  }
  else if (!isspace(ch)) {
    *current_type = nullptr;
  }

  // INDENT never interrupts a token because it can only be started from NULL
  return nullptr;
}

HIGHLIGHTER(ALIAS) {
  if (iswordch(ch) || isdigit(ch)) {
    ++*end;
    return nullptr;
  }
  else if (ch == ',') {
    *current_type = &TokenTypes::REG_INDEX;
  }
  else if (ch == ':') {
    *current_type = &TokenTypes::LABEL;
    return nullptr;
    // We are only modifying the type, not starting a new token
  }
  else {
    *current_type = nullptr;
  }

  return &TokenTypes::ALIAS;
}

// This is only reached the character after a colon
HIGHLIGHTER(LABEL) {
  if (iswordch(ch)) {
    *current_type = &TokenTypes::INSTRUCTION;
  }
  else if (ch == '.') {
    *current_type = &TokenTypes::DIRECTIVE;
  }
  else {
    *current_type = nullptr;
  }

  // The label is always done after the colon
  return &TokenTypes::LABEL;
}

HIGHLIGHTER(DIRECTIVE) {
  if (iswordch(ch) || isdigit(ch)) {
    ++*end;
    return nullptr;
  }
  else {
    *current_type = nullptr;
    return &TokenTypes::DIRECTIVE;
  }
}

HIGHLIGHTER(INSTRUCTION) {
  if (iswordch(ch) || isdigit(ch)) {
    ++*end;
    return nullptr;
  }
  else {
    *current_type = nullptr;
    return &TokenTypes::INSTRUCTION;
  }
}

HIGHLIGHTER(REG_INDEX) {
  if (iswordch(ch)) {
    ++*end;
    return nullptr;
  }
  else {
    *current_type = nullptr;
    return &TokenTypes::REG_INDEX;
  }
}

HIGHLIGHTER(LIT_STR) {
  if (ch == '"') {
    *current_type = nullptr;
    return &TokenTypes::LIT_STR;
  }
  else {
    ++*end;
    return nullptr;
  }
}

HIGHLIGHTER(LIT_CHAR) {
  if (ch == '\'') {
    *current_type = nullptr;
    return &TokenTypes::LIT_CHAR;
  }
  else {
    ++*end;
    return nullptr;
  }
}

HIGHLIGHTER(LIT_NUM) {
  if (isdigit(ch)) {
    ++*end;
    return nullptr;
  }
  else if (ch == ',') {
    *current_type = &TokenTypes::REG_INDEX;
  }
  else {
    *current_type = nullptr;
  }

  return &TokenTypes::LIT_NUM;
}

// Token only lasts one character
HIGHLIGHTER(IMMEDIATE) {
  *current_type = nullptr;
  return &TokenTypes::IMMEDIATE;
}

// Token only lasts one character
HIGHLIGHTER(NUM_HEX) {
  *current_type = nullptr;
  return &TokenTypes::NUM_HEX;
}

// Token only lasts one character
HIGHLIGHTER(NUM_BIN) {
  *current_type = nullptr;
  return &TokenTypes::NUM_BIN;
}
