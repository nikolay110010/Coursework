#include "Theory.h"
#include "Calculator.h"
#include "Testing.h"

#include <iostream>		// для работы с вводом и выводом данных

using namespace std;

// выводит информацию о программе
void Program_Information()
{
	cout << "Учебно-демонстрационная программа на тему: <Булевы функции. Операции: дизъюнкции, конъюкции, отрицания>" << endl;
	cout << "Выполнил: обучающийся группы ДИНРб-11/2 Карячкин Н.В." << endl;


	// хочет ли пользователь вернуться в меню
	int user_Choice;
	cout << "\n1) Продолжить \nВаш выбор: ";
	while (cin >> user_Choice && user_Choice != 1) {
		cout << "Вы решили остаться: ";
	}

	system("cls");	// очистка экрана консоли
}

// ввод и проверка выбора пользователя
int User_Choice()
{
	int user_Choice;
	cout << "Выберите пункт меню: \n1) Теория \n2) Калькулятор \n3) Тестирование \n0) Выход из программы \nВаш выбор: ";
	while (cin >> user_Choice && (user_Choice < 0 || user_Choice > 3)) {
		cout << "ОШИБКА" << endl;
		cout << "Выберите существующий пунк меню: ";
	}

	system("cls");	// очистка экрана консоли

	return user_Choice;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	// выводит информацию о программе
	Program_Information();

	int user_Choice = -1;
	while (user_Choice != 0) {
		// выбор пользователем пунка меню с проверкой
		user_Choice = User_Choice();

		// пункты меню
		switch (user_Choice)
		{
		case 1: Theory();     break;	// теория

		case 2: Calculator(); break;	// калькулятор

		case 3: Testing();    break;	// тест
			
		}

		system("cls");	// очистка экрана консоли
	}
	cout << "Программа завершена" << endl;

	return 0;
}