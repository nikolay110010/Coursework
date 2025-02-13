#include "Theory.h"

#include <iostream>     // для работы с вводом и выводом данных
#include <fstream>      // для работы с файлами
#include <string>       // для работы с строками

using namespace std;

void Theory()
{
    // имя (путь) файла
    string file_Name = "Theory.txt";

    // создание файловой переменной и вкл обработки исключений для файлов
    ifstream file(file_Name);

    // проверка, успешно ли открыт файл
    if (!file.is_open()) {  // если файл не был открыт
        cerr << "Ошибка при открытии файла: " << file_Name << "\nОбратитесь в поддержку для решения данной проблемы" << endl;
        return; // Exit the function if unable to open the file
    }

    // построчное чтение файла и вывод на консоль
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();   // закрытие файла


    // хочет ли пользователь вернуться в меню
    int user_Choice;
    cout << "\n0) Вернуться в меню \nВаш выбор: ";
    while (cin >> user_Choice && user_Choice != 0) {
        cout << "Вы решили остаться: ";
    }
}