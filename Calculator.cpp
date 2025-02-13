#include "Calculator.h"

#include <iostream>     // для работы с вводом и выводом данных
#include <stack>        // для работы с стеком
#include <string>       // для работы с строками
#include <cctype>       // для классификации и преобразования символов
#include <stdexcept>    // обработка ошибок через исключения

using namespace std;

// вычисление результата операции
bool Solve_Operation(char op, bool a, bool b)
{
    switch (op)
    {
    case '&': return a && b;

    case '|': return a || b;

    default: throw invalid_argument("Неизвестный оператор");
    }
}

// функция вычисления булевого выражения
bool Solve_Expression(const string& expr)
{
    stack<bool> values;     // стек булевых (0 или 1)
    stack<char> symbols;    // стек символов (|, &, !, (. )

    // 
    for (size_t i = 0; i < expr.length(); i++) {
        // если текущий символ - пробел, переходим к следущему символу
        if (isspace(expr[i])) {
            continue;
        }

        // если текущий символ - 0 или 1, он помещается в стек values
        if (expr[i] == '0' || expr[i] == '1') {
            values.push(expr[i] - '0'); // в скобках преобразование символа в булевое значение
        }
        // если текущий символ - (, он помещается в стек symbols
        else if (expr[i] == '(') {
            symbols.push(expr[i]);
        }
        // если тукущий символ - ), вычисляются операции внутри скобок
        else if (expr[i] == ')') {
            while (!symbols.empty() && symbols.top() != '(') {
                char ch = symbols.top();
                symbols.pop();

                // выполнение операции !
                if (ch == '!') {
                    // если у оператора (!) нет операндов (как слева, так и справа)
                    if (values.empty()) {
                        throw invalid_argument("Неправильное выражение");
                    }
                    bool val = values.top();
                    values.pop();
                    values.push(!val);
                }       
                // выполнение операции | или &
                else {
                    // если у оператора (|, &) один операнд
                    if (values.size() < 2) {
                        throw invalid_argument("Неправильное выражение");
                    }
                    bool val2 = values.top(); values.pop();
                    bool val1 = values.top(); values.pop();
                    values.push(Solve_Operation(ch, val1, val2));
                }
            }
            // удаление ( после завершение всех дейвствий в скобках
            if (!symbols.empty() && symbols.top() == '(') {
                symbols.pop();
            }
            else {
                throw invalid_argument("Несоответствие скобок");
            }
        }
        // выполнение операции | или & при
        else if (expr[i] == '|' || expr[i] == '&') {
            // отсутствии скобки (скобок) или отрицания (отрицаний) слева
            while (!symbols.empty() && symbols.top() != '(' && symbols.top() != '!') {
                char ch = symbols.top();
                symbols.pop();

                // если у оператора (|, &) один операнд
                if (values.size() < 2) {
                    throw invalid_argument("Неправильное выражение");
                }
                bool val2 = values.top(); values.pop();
                bool val1 = values.top(); values.pop();
                values.push(Solve_Operation(ch, val1, val2));
            }
            symbols.push(expr[i]);
        }
        // если текущий символ - !, он помещается в стек symbols
        else if (expr[i] == '!') {
            symbols.push(expr[i]);
        }
        // если символ не является допустимым символом
        else {
            throw invalid_argument("Неправильный символ в выражении");
        }
    }

    // выполнение оставшихся операций в стеке symbols
    while (!symbols.empty()) {
        char ch = symbols.top();
        symbols.pop();

        // выполнение операции !
        if (ch == '!') {
            // если у оператора (!) нет операндов (как слева, так и справа)
            if (values.empty()) {
                throw invalid_argument("Неправильное выражение");
            }
            bool val = values.top();
            values.pop();
            values.push(!val);
        }
        // выполнение операции | или &
        else {
            // если у оператора (|, &) один операнд
            if (values.size() < 2) {
                throw invalid_argument("Неправильное выражение");
            }
            bool val2 = values.top(); values.pop();
            bool val1 = values.top(); values.pop();
            values.push(Solve_Operation(ch, val1, val2));
        }
    }

    // проверка стека values:
        // если значений несколько - исключение
    if (values.size() != 1) {
        throw invalid_argument("Неправильное выражение");
    }

        // если 1 значение - это и есть ответ
    return values.top();
}

void Calculator()
{
    int user_Choice = -1;
    while (user_Choice != 0) {
        string expr;

        cout << "Введите булевое выражение (например: 1&!(1|0).): ";
        cin >> expr;

        // обработка исключений
        try {   // удачно
            bool result = Solve_Expression(expr);

            cout << "Результат: " << result << endl;
        }
        catch (const exception& e) {    // неудачно
            cerr << "Ошибка при вычислении выражения: " << e.what() << endl;
        }

        // хочет ли пользователь вернуться в меню
        cout << "\n0) Вернуться в меню \n1) Посчитать еще одно выражение \nВаш выбор: ";
        while (cin >> user_Choice && (user_Choice != 0 && user_Choice != 1)) {
            cout << "ОШИБКА" << endl;
            cout << "Выберите существующий пунк меню: ";
        }
        cout << endl;
    }
}