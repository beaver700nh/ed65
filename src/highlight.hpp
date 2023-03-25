#ifndef HIGHLIGHT_HPP
#define HIGHLIGHT_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <curses.h>

#include "common.hpp"

/*
 * HIGHLIGHT RULES
 * ===============
 *
 * ALIAS = $FFFF
 *
 *   .directive $FFFF
 *
 * label:
 *   instr           ; A i
 *   instr #$FF      ; #
 *   instr $FFFF     ; a
 *   instr $FF       ; zp r
 *   instr ($FFFF)   ; (a)
 *   instr $FFFF,r   ; a,x a,y
 *   instr $FF,r     ; zp,x zp,y
 *   instr ($FF,x)   ; (zp,x)
 *   instr ($FF),y   ; (zp),y
 *
 * ---------------
 *
 * COLOR_RED:     .directive instr
 * COLOR_YELLOW:  #immediate
 * COLOR_GREEN:   char, string
 * COLOR_CYAN:    $hex, %bin
 * COLOR_BLUE:    alias label number
 * COLOR_MAGENTA: ,x ,y
 *
 * Comments are COLOR_WHITE A_DIM
 * All else are COLOR_WHITE A_NORMAL
 */

struct Highlight {
  unsigned int start;
  unsigned int num;
  unsigned int color;
  unsigned int attrs;
};

// line number : highlights
using Highlights = std::unordered_map<unsigned int, std::vector<Highlight>>;

class Highlighter {
public:
  Highlighter() = delete;

  static void highlight(std::vector<std::string> lines, Highlights &highlights);
  static void highlight_line(std::string line, std::vector<Highlight> &highlight);
};

struct TokenType {
  unsigned int color;
  unsigned int attrs;
  char const *const name;
};

class TokenTypes {
public:
  static TokenType const
    INDENT, COMMENT, ALIAS, LABEL,
    DIRECTIVE, INSTRUCTION, REG_INDEX,
    LIT_STR, LIT_CHAR, LIT_NUM,
    IMMEDIATE, NUM_HEX, NUM_BIN;
};

#endif
