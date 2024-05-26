#include "lexer.h"

Lexer::Lexer(const string& source_code) : current(0), source_code(source_code) {
    tokenize();
}

Token Lexer::next_token() {
    if (current < tokens.size())
        return tokens[current++];
    return { "", "" };
}

const vector<Token>& Lexer::get_tokens() const {
    return tokens;
}

void Lexer::tokenize() {
    vector<pair<string, string>> token_specification = {
        {"PROGRAM", "program"},
        {"CONST", "const"},
        {"VAR", "var"},
        {"BEGIN", "begin"},
        {"END_BLOCK", "end"},
        {"IF", "if"},
        {"THEN", "then"},
        {"ELSE", "else"},
        {"WRITE", "Write"},
        {"READ", "Read"},
        {"DOUBLE", "double"},
        {"INTEGER", "integer"},
        {"MOD", "mod"},
        {"DIV", "div"},
        {"NUMBER", "\\d+(\\.\\d*)?"},
        {"ASSIGN", ":="},
        {"EQUALS", "="},
        {"NOTEQUALS", "!="},
        {"LESS", "<"},
        {"LESSEQUALS", "<="},
        {"GREATER", ">"},
        {"GREATEREQUALS", ">="},
        {"END", "\\."},
        {"ID", "[A-Za-z][A-Za-z0-9]*"},
        {"STRING", "\"[^\"]*\""},
        {"PLUS", "\\+"},
        {"MINUS", "-"},
        {"MULT", "\\*"},
        {"DIVISION", "/"},
        {"SKIP", "[ \t\n]+"},
        {"LPAREN", "\\("},
        {"RPAREN", "\\)"},
        {"SEMI", ";"},
        {"COMMA", ","},
        {"COLON", ":"},
        {"MISMATCH", "."}
    };

    string tok_regex;
    for (const auto& pair : token_specification)
        tok_regex += "(?:" + pair.second + ")|";
    tok_regex.pop_back();

    regex token_regex(tok_regex);
    auto words_begin = sregex_iterator(source_code.begin(), source_code.end(), token_regex);
    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; i++) {
        smatch match = *i;
        for (const auto& pair : token_specification) {
            if (regex_match(match.str(), regex(pair.second))) {
                string kind = pair.first;
                string value = match.str();
                if (kind == "SKIP")
                    kind = "";
                if (!kind.empty())
                    tokens.push_back({ kind, value });
                break;
            }
        }
    }
}
