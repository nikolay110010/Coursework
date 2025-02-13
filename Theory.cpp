#include "Theory.h"

#include <iostream>     // ��� ������ � ������ � ������� ������
#include <fstream>      // ��� ������ � �������
#include <string>       // ��� ������ � ��������

using namespace std;

void Theory()
{
    // ��� (����) �����
    string file_Name = "Theory.txt";

    // �������� �������� ���������� � ��� ��������� ���������� ��� ������
    ifstream file(file_Name);

    // ��������, ������� �� ������ ����
    if (!file.is_open()) {  // ���� ���� �� ��� ������
        cerr << "������ ��� �������� �����: " << file_Name << "\n���������� � ��������� ��� ������� ������ ��������" << endl;
        return; // Exit the function if unable to open the file
    }

    // ���������� ������ ����� � ����� �� �������
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();   // �������� �����


    // ����� �� ������������ ��������� � ����
    int user_Choice;
    cout << "\n0) ��������� � ���� \n��� �����: ";
    while (cin >> user_Choice && user_Choice != 0) {
        cout << "�� ������ ��������: ";
    }
}