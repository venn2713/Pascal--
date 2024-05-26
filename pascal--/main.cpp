#include <windows.h>
#include <locale.h>

#include "lexer.h"
#include "parser.h"

void test_lexer(const string& source_code) {
    Lexer lexer(source_code);
    const vector<Token>& tokens = lexer.get_tokens();

    for (const auto& token : tokens)
        cout << "Token: {" << token.type << ", " << token.value << "}" << endl;
}

void test_parser(const string& source_code) {
    Lexer lexer(source_code);
    Parser parser(lexer);
    try {
        parser.program();
        cout << "\nParsing completed successfully.\nHere is hierarchial structure" << endl;
        Node root = parser.get_hierarchical_structure();
        print_hierarchy(root);
    }
    catch (const exception& err) {
        cout << "Error: " << err.what() << endl;
    }
}

int main() {
    // Устанавливаем кодовую страницу 1251 для консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Устанавливаем локаль на русский
    setlocale(LC_ALL, "Russian");

    string source_code = R"(
    program Example;
    const Pi = 3.1415926;
    var num1, num2: integer;
    var res, d: double;
    begin
        num1 := 5;
        Write("Введите четное целое число: ");
        Read(num2);
        Write("Введите вещественное число: ");
        Read(d);
        if (num2 mod 2 = 0) then
        begin
            res := (num1 - num2 * 5 div 2) / (d * 2);
            Write("Результат = ", res);
        end
        else
            Write("Неверный ввод");
        end.
    )";

    // Тестирование работы лексера
    cout << "Testing lexer:" << endl;
    test_lexer(source_code);
    cout << "\nTesting parser:" << endl;
    // Тестирование работы парсера
    test_parser(source_code);

    return 0;
}
