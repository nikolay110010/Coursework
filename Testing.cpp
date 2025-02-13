#include "Testing.h"

#include <iostream>     // для работы с вводом и выводом данных
#include <cstdlib>      // предоставляет функции для генерации случайных чисел
#include <ctime>        // для инициализации генератора случайных чисел текущим временем
#include <vector>       // предоставляет контейнер для хранения списка строковых выражений
#include <string>       // для работы с строками

using namespace std;

// структура для хранения булевого выражения и ответа на него
struct Boolean_Expression {
    string expression;  // выражение
    bool answer;        // правильный ответ на выражение
};

// функция для генерации случайного булева значения (0 или 1)
bool Generate_Random_Bool()
{
    return rand() % 2;
}

// функция структурного типа для генерации случайного булева выражения
Boolean_Expression Generate_Random_Expression()
{
    Boolean_Expression expr;

    // генерация переменных булевого выражения
    bool x = Generate_Random_Bool();
    bool y = Generate_Random_Bool();
    bool z = Generate_Random_Bool();

    // список возможных выражений
    vector<string> expressions = {
        "x & y",
        "x | y",
        "!x",
        "x | (y & z)",
        "x & (y | z)",
        "(x | y) & !z",
        "!(x & y)",
        "x & (!y | z)",
        "(x | !y) & z"
    };

    // выбор случайного выражения из списка
    int i = rand() % expressions.size();
    expr.expression = expressions[i];

    // вычисление правильного ответа для выбранного выражения
    if (i == 0) {
        expr.answer = x && y;
    }
    else if (i == 1) {
        expr.answer = x || y;
    }
    else if (i == 2) {
        expr.answer = !x;
    }
    else if (i == 3) {
        expr.answer = x || (y && z);
    }
    else if (i == 4) {
        expr.answer = x && (y || z);
    }
    else if (i == 5) {
        expr.answer = (x || y) && !z;
    }
    else if (i == 6) {
        expr.answer = !(x && y);
    }
    else if (i == 7) {
        expr.answer = x && (!y || z);
    }
    else if (i == 8) {
        expr.answer = (x || !y) && z;
    }

    // замена переменных x, y, z в выражении на их значения
    for (char& ch : expr.expression) {
        if (ch == 'x') {
            ch = x ? '1' : '0';
        }
        else if (ch == 'y') {
            ch = y ? '1' : '0';
        }
        else if (ch == 'z') {
            ch = z ? '1' : '0';
        }
    }

    return expr;
}

// функция - выводит выражение и варианты ответа для пользователя, принимает и проверяет ответ
bool Expression_for_User(Boolean_Expression expr)
{
    bool options[2] = { 0, 1 };     // возможные варианты ответа

    // перемешивание вариантов ответа
    if (rand() % 2 == 0) {
        swap(options[0], options[1]);
    }

    // вывод выражения и вариантов ответа
    cout << "Выражение: " << expr.expression << endl;
    cout << "Выберите правильный ответ:" << endl;
    for (int i = 0; i < 2; ++i) {
        cout << i + 1 << ") " << options[i] << endl;
    }

    // ввод и проверка ответа пользователя
    int user_Choice;
    cout << "Ваш выбор: ";
    while (cin >> user_Choice && (user_Choice < 1 || user_Choice > 2)) {
        cout << "ОШИБКА" << endl;
        cout << "Выберите существующий вариант ответа: ";
    }

    // проверка ответа пользователя
    if (options[user_Choice - 1] == expr.answer) {
        cout << "Правильно!" << endl << endl;

        return true;
    }
    else {
        cout << "Неправильно. Правильный ответ: " << expr.answer << endl << endl;

        return false;
    }
}

// система оценивания результатов теста
void Rating_System(int num_Questions, int correct_Answers)
{
    int grade;  // оценка

    int incorrect_Answers = num_Questions - correct_Answers;    // неправильных ответов

    // кол-во ошибок = оценка
    if (incorrect_Answers == 0) {
        grade = 5;
    }
    else if (incorrect_Answers <= 2) {
        grade = 4;
    }
    else if (incorrect_Answers <= 4) {
        grade = 3;
    }
    else {
        grade = 2;
    }

    cout << "Вы ответили правильно на " << correct_Answers << " из " << num_Questions << " вопросов" << endl;
    cout << "Ваша оценка: " << grade << endl;
}

void Testing()
{
    srand(static_cast<unsigned int>(time(0)));                  // инициализация генератора случайных чисел

    int num_Questions = 10;     // кол-во выражений за тест
    int correct_Answers = 0;    // кол-во правильных ответов

    int user_Choice = -1;
    while (user_Choice != 0) {
        // каждый круг цикла - одно выражение для пользователя
        for (int i = 0; i < num_Questions; ++i) {
            Boolean_Expression expr = Generate_Random_Expression();     // генерация случайного булева выражения

            // если пользователь отвечает верно - счетчик правильных ответов +1
            if (Expression_for_User(expr)) {
                correct_Answers++;
            }
        }

        // система оценивания
        Rating_System(num_Questions, correct_Answers);


        // хочет ли пользователь вернуться в меню
        cout << "\n0) Вернуться в меню \n1) Решить еще один тест \nВаш выбор: ";
        while (cin >> user_Choice && (user_Choice != 0 && user_Choice != 1)) {
            cout << "ОШИБКА" << endl;
            cout << "Выберите существующий пунк меню: ";
        }
        cout << endl;
    }
}