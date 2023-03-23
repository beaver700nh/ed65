#include <regex>
#include <string>
#include <vector>

#include "common.hpp"

#include "highlight.hpp"

#define TOKEN_TYPE(color, attrs, pattern) {COLOR_##color, attrs, std::regex {pattern}}

Highlighter::TokenType const Highlighter::token_types[] {
  TOKEN_TYPE(WHITE,   A_DIM,    R"~((;(.*))$)~"                       ), // comment
  TOKEN_TYPE(GREEN,   A_NORMAL, R"~(^[^']*(?:'[^']*'[^']*)*("(.*)"))~"), // literal string
  TOKEN_TYPE(GREEN,   A_NORMAL, R"~(^[^"]*(?:"[^"]*"[^"]*)*('(.*)'))~"), // literal char
  TOKEN_TYPE(RED,     A_NORMAL, R"~(^\s+(\.(\w+))(?:$|\s+))~"         ), // directive
  TOKEN_TYPE(RED,     A_NORMAL, R"~(^\s+((\w+))(?:$|\s+))~"           ), // instruction
  TOKEN_TYPE(BLUE,    A_NORMAL, R"~(^((\w+))\s*=)~"                   ), // alias
  TOKEN_TYPE(BLUE,    A_NORMAL, R"~(^((\w+):))~"                      ), // label
  TOKEN_TYPE(YELLOW,  A_NORMAL, R"~(((#)))~"                          ), // immediate
  TOKEN_TYPE(CYAN,    A_NORMAL, R"~(((\$)))~"                         ), // number hex
  TOKEN_TYPE(CYAN,    A_NORMAL, R"~(((%)))~"                          ), // number bin
  TOKEN_TYPE(MAGENTA, A_NORMAL, R"~((,(x|y)))~"                       ), // register indexing
  TOKEN_TYPE(BLUE,    A_NORMAL, R"~(((\d+)))~"                        ), // literal number
};

void Highlighter::highlight(std::vector<std::string> lines, Highlights &highlights) {
  highlights.clear();

  for (unsigned int line_no = 0; line_no < lines.size(); ++line_no) {
    highlight_line(lines.at(line_no), line_no, highlights);
  }
}

void Highlighter::highlight_line(std::string line, unsigned int line_no, Highlights &highlights) {
  for (auto const &token_type : token_types) {
    std::smatch match;

    if (std::regex_search(line, match, token_type.regex)) {
      highlights[line_no].emplace_back(
        match.position(1), match.length(1), token_type.color, token_type.attrs
      );
    }
  }
}
