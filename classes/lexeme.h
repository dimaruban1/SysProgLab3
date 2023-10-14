//
// Created by serg on 06.10.23.
//

#ifndef SYSPROGLAB3_LEXEM_H
#define SYSPROGLAB3_LEXEM_H

#include <string>
#include <vector>
/**/
enum lexemeType{
    //ordered by priority descending
    comment_t, //regex /\/\/.+
    multiline_comment_t, //regex /\*([^*]|(\*+[^*/]))*\*+/
    rune_t, //regex '[^'\\]'|'\\.'
    string_t, //regex \"(?:\\.|[^\"])+\"|`(?:\\.|[^`]+)`|""|``
    keyword_t, //identifier that belongs to keywords list
    identifier_t, //regex /\b[a-zA-Z]\w+\b/gm

    integer_t, //regex /[+-]?\b[1-9][0-9]*\b|[+-]?\b0+\b
    decimal_t, //regex  [+-]?[1-9][0-9]*\.[0-9]+\b|-?0\.[0-9]+\b
    hexadecimal_t, //regex \b0[xX][0-9a-fA-F]+\b
    complex_t, //regex ([+-]?\d+(\.\d+)?)\s*([+-]\s*\d+(\.\d+)?)i

    operator_t, //regex (with punctuation) \+|&|\+=|&=|&&|==|!=|-|-=|=|\|<|<=|\*|\^|\*=|\^=|<-|>|>=|\/|<<\/=|<<=|\+\+|=|:=|,|;|%|>>|%=|>>=|--|!|\.\.\.|\.|:|&\^|&\^=|~
    punctuation_t, //regex [.,:;]
};

class Lexeme {
public:
    lexemeType type;
    std::string value;
    int position;
};
class Parser{
private:
    std::string code;
    bool *processedCode;
    void parseLexeme(lexemeType t);
public:
    Parser(std::string code);
    void printResult();
    ~Parser();
    void parseCode();
};

#endif //SYSPROGLAB3_LEXEM_H
