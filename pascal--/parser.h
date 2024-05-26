#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "lexer.h"
#include "simple_hash_table.h"

using namespace std;

// Структура для хранения иерархического списка
struct Node {
    string name;
    vector<Node> children;
};

// Парсер
class Parser {
public:
    Parser(Lexer& lexer);
    void program();
    Node get_hierarchical_structure();

private:
    Lexer& lexer;
    Token current_token;
    SimpleHashTable<string, double> variables;
    SimpleHashTable<string, double> constants;
    Node root;

    void eat(const string& token_type);
    Node block();
    Node const_declarations();
    Node var_declarations();
    void type_spec();
    Node compound_statement();
    Node statement_list();
    Node statement();
    Node assignment_statement();
    Node if_statement();
    Node write_statement();
    Node read_statement();
    double expr();
    double simple_expr();
    double term();
    double factor();
};

void print_hierarchy(const Node& node, const string& prefix = "", bool isLast = true);
