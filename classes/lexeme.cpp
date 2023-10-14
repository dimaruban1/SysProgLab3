#include "lexeme.h"
#include "map"
#include <regex>
#include <iostream>
#include <set>
#include <utility>

using namespace  std;
bool lexemeComparator(const Lexeme& lhs, const Lexeme& rhs) {
    return lhs.position < rhs.position;
}

set<string> keywords;
map<lexemeType, regex> regexMap = {
        { integer_t, regex(R"(/[+-]?\b[1-9][0-9]*\b|[+-]?\b0+\b)") },
        { decimal_t, regex(R"([+-]?[1-9][0-9]*\.[0-9]+\b|-?0\.[0-9]+\b)") },
        { hexadecimal_t, regex(R"(\b0[xX][0-9a-fA-F]+\b)") },
        { complex_t, regex(R"(([+-]?\d+(\.\d+)?)\s*([+-]\s*\d+(\.\d+)?)i)") },
        { string_t, regex(R"(".*"|`[^`]*`)") },
        { rune_t, regex(R"('[^'\\]'|'\\.')") },
        { comment_t, regex(R"(\/\/.+)") },
        { multiline_comment_t, regex(R"(/\*([^*]|(\*+[^*/]))*\*+/)")},
        { keyword_t, regex(R"(/\b[a-zA-Z]\w+\b/gm)") },
        { punctuation_t, regex(R"([.,:;])") },
        { operator_t, regex(R"(\+|&|\+=|&=|&&|==|!=|-|-=|=|\|<|<=|\*|\^|\*=|\^=|<-|>|>=|\/|<<\/=|<<=|\+\+|=|:=|,|;|%|>>|%=|>>=|--|!|\.\.\.|\.|:|&\^|&\^=|~)") },
        { identifier_t, regex(R"(\b[a-zA-Z]\w+\b)") }
};

vector<Lexeme> lexemas;
Parser::Parser(std::string code){
    this->code = std::move(code);
    this->processedCode = new bool[this->code.length()];
}
Parser::~Parser() {
    delete [] this->processedCode;
}

void addKeywords();
string getName(enum lexemeType t);

void Parser::parseLexeme(lexemeType t) {
    bool isTypeKeyword = false;
    if (t == keyword_t){
        isTypeKeyword = true;
        t = identifier_t;
    }
    regex regexPattern = regexMap[t];
    sregex_iterator iter(code.begin(), code.end(), regexPattern);
    sregex_iterator end;
    while (iter != end) {
        std::smatch match = *iter;
        if (isTypeKeyword){
            t = keyword_t;
            if (!(keywords.find(match.str()) != keywords.end())){
                ++iter;
                continue;

            }
        }
        bool containsTrue = std::any_of(processedCode + match.position(),
                                        processedCode + match.position() + match.length(),
                                        [](bool value) {
                                            return value;
                                        });
        if (containsTrue){
            iter++;
            continue;
        }
        Lexeme L;
        L.type = t;
        L.value = match.str();
        L.position = match.position();
        std::fill(processedCode + L.position, processedCode + L.position + L.value.length(), true);
        lexemas.push_back(L);
        ++iter;
    }
}

void Parser::parseCode(){
    addKeywords();
    for (int i = comment_t; i <= punctuation_t; i++){
        parseLexeme((lexemeType)i);
    }
}

void Parser::printResult() {
    std::sort(lexemas.begin(),
              lexemas.end(),
              [](const Lexeme& lhs, const Lexeme& rhs) { return lhs.position < rhs.position; });
    for (auto & lexeme : lexemas){
        cout << getName(lexeme.type) << ": " << lexeme.value << endl;
    }
}
string getName(enum lexemeType t) {
    switch (t) {
        case comment_t:
        case multiline_comment_t:
            return "comment";
        case rune_t:
            return "rune";
        case string_t:
            return "string";
        case keyword_t:
            return "keyword";
        case identifier_t:
            return "identifier";
        case integer_t:
            return "integer";
        case decimal_t:
            return "decimal";
        case hexadecimal_t:
            return "hexadecimal";
        case complex_t:
            return "complex";
        case operator_t:
            return "operator";
        case punctuation_t:
            return "punctuation";
        default:
            return "unknown";
    }
}

void addKeywords(){
    keywords.insert("break");
    keywords.insert("default");
    keywords.insert("func");
    keywords.insert("interface");
    keywords.insert("select");
    keywords.insert("case");
    keywords.insert("defer");
    keywords.insert("go");
    keywords.insert("map");
    keywords.insert("struct");
    keywords.insert("chan");
    keywords.insert("else");
    keywords.insert("goto");
    keywords.insert("package");
    keywords.insert("switch");
    keywords.insert("const");
    keywords.insert("fallthrough");
    keywords.insert("if");
    keywords.insert("range");
    keywords.insert("type");
    keywords.insert("continue");
    keywords.insert("for");
    keywords.insert("import");
    keywords.insert("return");
    keywords.insert("var");
}