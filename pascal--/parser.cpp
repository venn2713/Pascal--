#include "parser.h"

Parser::Parser(Lexer& lexer) : lexer(lexer) {
    current_token = lexer.next_token();
}

void Parser::program() {
    root.name = "program";
    eat("PROGRAM");
    Node program_node = { "ID", {} };
    program_node.children.push_back({ "ID: " + current_token.value, {} });
    root.children.push_back(program_node);
    eat("ID");
    eat("SEMI");
    root.children.push_back(block());
    eat("END");
    if (current_token.type == "END_BLOCK")
        eat("END_BLOCK");
}

Node Parser::get_hierarchical_structure() {
    return root;
}

void Parser::eat(const string& token_type) {
    if (current_token.type == token_type)
        current_token = lexer.next_token();
    else
        throw runtime_error("Unexpected token: " + current_token.type);
}

Node Parser::block() {
    Node block_node = { "block", {} };
    while (current_token.type == "CONST" || current_token.type == "VAR" || current_token.type == "BEGIN") {
        if (current_token.type == "CONST")
            block_node.children.push_back(const_declarations());
        else if (current_token.type == "VAR")
            block_node.children.push_back(var_declarations());
        else if (current_token.type == "BEGIN")
            block_node.children.push_back(compound_statement());
    }
    return block_node;
}

Node Parser::const_declarations() {
    Node const_decl_node = { "const_declarations", {} };
    eat("CONST");
    while (current_token.type == "ID") {
        string const_name = current_token.value;
        eat("ID");
        eat("EQUALS");
        double const_value = stod(current_token.value);
        eat("NUMBER");
        constants.insert(const_name, const_value);
        const_decl_node.children.push_back({ "CONST: " + const_name + " = " + to_string(const_value), {} });
        eat("SEMI");
    }
    return const_decl_node;
}

Node Parser::var_declarations() {
    Node var_decl_node = { "var_declarations", {} };
    eat("VAR");
    while (current_token.type == "ID") {
        vector<string> var_names;
        var_names.push_back(current_token.value);
        eat("ID");
        while (current_token.type == "COMMA") {
            eat("COMMA");
            var_names.push_back(current_token.value);
            eat("ID");
        }
        eat("COLON");
        type_spec();
        for (const auto& var_name : var_names) {
            variables.insert(var_name, 0);
            var_decl_node.children.push_back({ "VAR: " + var_name, {} });
        }
        eat("SEMI");
    }
    return var_decl_node;
}

void Parser::type_spec() {
    if (current_token.type == "INTEGER")
        eat("INTEGER");
    else if (current_token.type == "DOUBLE")
        eat("DOUBLE");
    else
        throw runtime_error("Unexpected type: " + current_token.type);
}

Node Parser::compound_statement() {
    Node comp_stmt_node = { "compound_statement", {} };
    eat("BEGIN");
    comp_stmt_node.children.push_back(statement_list());
    eat("END_BLOCK");
    return comp_stmt_node;
}

Node Parser::statement_list() {
    Node stmt_list_node = { "statement_list", {} };
    stmt_list_node.children.push_back(statement());
    while (current_token.type == "SEMI") {
        eat("SEMI");
        stmt_list_node.children.push_back(statement());
    }
    return stmt_list_node;
}

Node Parser::statement() {
    Node stmt_node = { "statement", {} };
    if (current_token.type == "BEGIN")
        stmt_node.children.push_back(compound_statement());
    else if (current_token.type == "ID")
        stmt_node.children.push_back(assignment_statement());
    else if (current_token.type == "IF")
        stmt_node.children.push_back(if_statement());
    else if (current_token.type == "WRITE")
        stmt_node.children.push_back(write_statement());
    else if (current_token.type == "READ")
        stmt_node.children.push_back(read_statement());
    return stmt_node;
}

Node Parser::assignment_statement() {
    Node assign_stmt_node = { "assignment_statement", {} };
    string var_name = current_token.value;
    eat("ID");
    eat("ASSIGN");
    double var_value = expr();
    if (!variables.insert(var_name, var_value)) {
        throw runtime_error("Variable " + var_name + " not declared");
    }
    assign_stmt_node.children.push_back({ "ID: " + var_name, {} });
    assign_stmt_node.children.push_back({ "VALUE: " + to_string(var_value), {} });
    return assign_stmt_node;
}

Node Parser::if_statement() {
    Node if_stmt_node = { "if_statement", {} };
    eat("IF");
    double condition = expr();
    if_stmt_node.children.push_back({ "condition", {} });
    eat("THEN");
    if (condition) {
        if_stmt_node.children.push_back(statement());
        if (current_token.type == "ELSE") {
            eat("ELSE");
            while (current_token.type != "SEMI")
                eat(current_token.type);
        }
    }
    else {
        while (current_token.type != "END_BLOCK")
            eat(current_token.type);
        eat("END_BLOCK");
        if (current_token.type == "ELSE") {
            eat("ELSE");
            if_stmt_node.children.push_back(statement());
        }
    }
    if (current_token.type == "SEMI")
        eat("SEMI");
    return if_stmt_node;
}

Node Parser::write_statement() {
    Node write_stmt_node = { "write_statement", {} };
    eat("WRITE");
    eat("LPAREN");
    vector<string> values;
    while (current_token.type != "RPAREN") {
        if (current_token.type == "STRING") {
            values.push_back(current_token.value.substr(1, current_token.value.length() - 2));
            write_stmt_node.children.push_back({ "STRING: " + values.back(), {} });
            eat("STRING");
        }
        else {
            double value = expr();
            values.push_back(to_string(value));
            write_stmt_node.children.push_back({ "VALUE: " + to_string(value), {} });
        }
        if (current_token.type == "COMMA")
            eat("COMMA");
    }
    eat("RPAREN");
    for (const auto& value : values)
        cout << value << " ";
    return write_stmt_node;
}

Node Parser::read_statement() {
    Node read_stmt_node = { "read_statement", {} };
    eat("READ");
    eat("LPAREN");
    string var_name = current_token.value;
    eat("ID");
    eat("RPAREN");
    string value;
    cin >> value;
    if (!variables.exists(var_name)) {
        throw runtime_error("Variable " + var_name + " not declared");
    }
    variables.insert(var_name, stod(value));
    read_stmt_node.children.push_back({ "ID: " + var_name, {} });
    read_stmt_node.children.push_back({ "VALUE: " + value, {} });
    return read_stmt_node;
}

double Parser::expr() {
    double result = simple_expr();
    while (current_token.type == "EQUALS" || current_token.type == "NOTEQUALS" || current_token.type == "LESS" ||
        current_token.type == "LESSEQUALS" || current_token.type == "GREATER" || current_token.type == "GREATEREQUALS") {
        string op = current_token.type;
        eat(current_token.type);
        double right = simple_expr();
        if (op == "EQUALS")
            result = (result == right);
        else if (op == "NOTEQUALS")
            result = (result != right);
        else if (op == "LESS")
            result = (result < right);
        else if (op == "LESSEQUALS")
            result = (result <= right);
        else if (op == "GREATER")
            result = (result > right);
        else if (op == "GREATEREQUALS")
            result = (result >= right);
    }
    return result;
}

double Parser::simple_expr() {
    double result = term();
    while (current_token.type == "PLUS" || current_token.type == "MINUS") {
        if (current_token.type == "PLUS") {
            eat("PLUS");
            result += term();
        }
        else if (current_token.type == "MINUS") {
            eat("MINUS");
            result -= term();
        }
    }
    return result;
}

double Parser::term() {
    double result = factor();
    while (current_token.type == "MULT" || current_token.type == "DIVISION" || current_token.type == "MOD" || current_token.type == "DIV") {
        if (current_token.type == "MULT") {
            eat("MULT");
            result *= factor();
        }
        else if (current_token.type == "DIVISION") {
            eat("DIVISION");
            double divisor = factor();
            if (divisor == 0)
                throw runtime_error("Division by zero error.");
            result /= divisor;
        }
        else if (current_token.type == "MOD") {
            eat("MOD");
            double divisor = factor();
            if (divisor == 0)
                throw runtime_error("Modulo by zero error.");
            result = fmod(result, divisor);
        }
        else if (current_token.type == "DIV") {
            eat("DIV");
            double divisor = factor();
            if (divisor == 0)
                throw runtime_error("Integer division by zero error.");
            result = static_cast<int>(result) / static_cast<int>(divisor);
        }
    }
    return result;
}

double Parser::factor() {
    double result;
    if (current_token.type == "LPAREN") {
        eat("LPAREN");
        result = expr();
        eat("RPAREN");
    }
    else if (current_token.type == "NUMBER") {
        result = stod(current_token.value);
        eat("NUMBER");
    }
    else if (current_token.type == "ID") {
        string var_name = current_token.value;
        eat("ID");
        if (!variables.get(var_name, result) && !constants.get(var_name, result)) {
            throw runtime_error("Variable " + var_name + " not declared");
        }
    }
    else if (current_token.type == "STRING") {
        result = 0;
        eat("STRING");
    }
    else {
        throw runtime_error("Unexpected token: " + current_token.type);
    }
    return result;
}

void print_hierarchy(const Node& node, const string& prefix, bool isLast) {
    cout << prefix;

    if (isLast) {
        cout << "+-";
    }
    else {
        cout << "|-";
    }

    cout << node.name << endl;

    for (size_t i = 0; i < node.children.size(); i++) {
        string newPrefix = prefix + (isLast ? "  " : "| ");
        print_hierarchy(node.children[i], newPrefix, i == node.children.size() - 1);
    }
}

