#include "Calculator.h"

#include <iostream>     // ��� ������ � ������ � ������� ������
#include <stack>        // ��� ������ � ������
#include <string>       // ��� ������ � ��������
#include <cctype>       // ��� ������������� � �������������� ��������
#include <stdexcept>    // ��������� ������ ����� ����������

using namespace std;

// ���������� ���������� ��������
bool Solve_Operation(char op, bool a, bool b)
{
    switch (op)
    {
    case '&': return a && b;

    case '|': return a || b;

    default: throw invalid_argument("����������� ��������");
    }
}

// ������� ���������� �������� ���������
bool Solve_Expression(const string& expr)
{
    stack<bool> values;     // ���� ������� (0 ��� 1)
    stack<char> symbols;    // ���� �������� (|, &, !, (. )

    // 
    for (size_t i = 0; i < expr.length(); i++) {
        // ���� ������� ������ - ������, ��������� � ��������� �������
        if (isspace(expr[i])) {
            continue;
        }

        // ���� ������� ������ - 0 ��� 1, �� ���������� � ���� values
        if (expr[i] == '0' || expr[i] == '1') {
            values.push(expr[i] - '0'); // � ������� �������������� ������� � ������� ��������
        }
        // ���� ������� ������ - (, �� ���������� � ���� symbols
        else if (expr[i] == '(') {
            symbols.push(expr[i]);
        }
        // ���� ������� ������ - ), ����������� �������� ������ ������
        else if (expr[i] == ')') {
            while (!symbols.empty() && symbols.top() != '(') {
                char ch = symbols.top();
                symbols.pop();

                // ���������� �������� !
                if (ch == '!') {
                    // ���� � ��������� (!) ��� ��������� (��� �����, ��� � ������)
                    if (values.empty()) {
                        throw invalid_argument("������������ ���������");
                    }
                    bool val = values.top();
                    values.pop();
                    values.push(!val);
                }       
                // ���������� �������� | ��� &
                else {
                    // ���� � ��������� (|, &) ���� �������
                    if (values.size() < 2) {
                        throw invalid_argument("������������ ���������");
                    }
                    bool val2 = values.top(); values.pop();
                    bool val1 = values.top(); values.pop();
                    values.push(Solve_Operation(ch, val1, val2));
                }
            }
            // �������� ( ����� ���������� ���� ��������� � �������
            if (!symbols.empty() && symbols.top() == '(') {
                symbols.pop();
            }
            else {
                throw invalid_argument("�������������� ������");
            }
        }
        // ���������� �������� | ��� & ���
        else if (expr[i] == '|' || expr[i] == '&') {
            // ���������� ������ (������) ��� ��������� (���������) �����
            while (!symbols.empty() && symbols.top() != '(' && symbols.top() != '!') {
                char ch = symbols.top();
                symbols.pop();

                // ���� � ��������� (|, &) ���� �������
                if (values.size() < 2) {
                    throw invalid_argument("������������ ���������");
                }
                bool val2 = values.top(); values.pop();
                bool val1 = values.top(); values.pop();
                values.push(Solve_Operation(ch, val1, val2));
            }
            symbols.push(expr[i]);
        }
        // ���� ������� ������ - !, �� ���������� � ���� symbols
        else if (expr[i] == '!') {
            symbols.push(expr[i]);
        }
        // ���� ������ �� �������� ���������� ��������
        else {
            throw invalid_argument("������������ ������ � ���������");
        }
    }

    // ���������� ���������� �������� � ����� symbols
    while (!symbols.empty()) {
        char ch = symbols.top();
        symbols.pop();

        // ���������� �������� !
        if (ch == '!') {
            // ���� � ��������� (!) ��� ��������� (��� �����, ��� � ������)
            if (values.empty()) {
                throw invalid_argument("������������ ���������");
            }
            bool val = values.top();
            values.pop();
            values.push(!val);
        }
        // ���������� �������� | ��� &
        else {
            // ���� � ��������� (|, &) ���� �������
            if (values.size() < 2) {
                throw invalid_argument("������������ ���������");
            }
            bool val2 = values.top(); values.pop();
            bool val1 = values.top(); values.pop();
            values.push(Solve_Operation(ch, val1, val2));
        }
    }

    // �������� ����� values:
        // ���� �������� ��������� - ����������
    if (values.size() != 1) {
        throw invalid_argument("������������ ���������");
    }

        // ���� 1 �������� - ��� � ���� �����
    return values.top();
}

void Calculator()
{
    int user_Choice = -1;
    while (user_Choice != 0) {
        string expr;

        cout << "������� ������� ��������� (��������: 1&!(1|0).): ";
        cin >> expr;

        // ��������� ����������
        try {   // ������
            bool result = Solve_Expression(expr);

            cout << "���������: " << result << endl;
        }
        catch (const exception& e) {    // ��������
            cerr << "������ ��� ���������� ���������: " << e.what() << endl;
        }

        // ����� �� ������������ ��������� � ����
        cout << "\n0) ��������� � ���� \n1) ��������� ��� ���� ��������� \n��� �����: ";
        while (cin >> user_Choice && (user_Choice != 0 && user_Choice != 1)) {
            cout << "������" << endl;
            cout << "�������� ������������ ���� ����: ";
        }
        cout << endl;
    }
}