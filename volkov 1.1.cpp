#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <clocale>
#include <limits>

using namespace std;

struct monitors {
    char name[20];//название монитора
    int diagonal;//диагональ монитора
    int frequency;//Частота обновления монитора
    char permission[20];//разрешение монитора
    char aspectRatio[20];//соотношение сторон
}monitors;

void PrintMonitorsRow(string name, int diagonal, int frequency, char permission[20], char aspectRatio[20]) {
    cout << left << setw(10) << name << "|" << left << setw(10)
        << diagonal << "|"
        << left << setw(10) << frequency << "|" << left << setw(10) <<
        permission
        << "|" << left
        << setw(10) << aspectRatio << " |" << endl;
}

void PrintMonitorsRowHeader() {
    cout << left << setw(10) << "Название" << "|" << left << setw(10) << "Диагональ" << "|"
        << left << setw(10)
        << "Частота" << "|" << left << setw(10) << "Разрешение" << "|" << left <<
        setw(10) << "Соотношение" << setw(10) << "|"
        << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");
    string path = "file.bin";
    char choice = '0';
    do {
        ofstream fout;
        ifstream fin;
        cout << endl << "1-Добавить запись" << endl << "2-Посмотреть записи" << endl
            << "3-Поиск" << endl << "4-Выход"
            << endl;
        cin >> choice;
        switch (choice) {
        case '1':
            cout << "Название монитора: ";
            cin >> monitors.name;
            cout << endl << "диагональ монитора: ";
            while (!(cin >> monitors.diagonal)) {
                cout << "Некорректное значение, попробуй еще раз";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << endl << "Частота обновления монитора: ";
            while (!(cin >> monitors.frequency)) {
                cout << "Некорректное значение, попробуй еще раз";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << endl << "разрешение монитора: ";
            cin >> monitors.permission;
            cout << endl << "соотношение сторон: ";
            cin >> monitors.aspectRatio;
            fout.open(path, ios::binary | ios::app);//запись в конец файла
            if (!fout.is_open()) cout << "Ошибка при открытии файла!\n";
            else {
                fout.write((char*)&monitors, sizeof(monitors));
            }
            fout.close();
            cout << "Готово";
            break;

        case '2':
            PrintMonitorsRowHeader();
            fin.open(path, ios::binary);
            if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
            else {
                while (fin.read((char*)&monitors, sizeof(monitors))) {
                    PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                }
            }
            fin.close();
            break;

        case '3':
            do {
                cout << "\n1-Поиск по названию\n";
                cout << "2-Поиск по диагональ\n";
                cout << "3-Поиск по частоте\n";
                cout << "4-Поиск по разрешение\n";
                cout << "5-Поиск по соотношение сторон\n";
                cout << "6-Назад\n";
                cin >> choice;
                string input_data;
                switch (choice) {
                case '1':
                    cout << "Введи название ";
                    cin >> input_data;
                    fin.open(path, ios::binary);
                    if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
                    else {
                        int cc = 0;
                        PrintMonitorsRowHeader();
                        while (fin.read((char*)&monitors, sizeof(monitors))) {
                            if ((string(monitors.name)).find(input_data) != string::npos) {
                                cc++;
                                PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                            }
                        }
                        if (cc == 0) {
                            cout << "ничего не найдено";
                        }
                        fin.close();
                    }
                    break;

                case '2':

                    do {
                        cout << "Как будем искать? \n1 - >\n2 - <\n3 - =\n4 - назад\n";
                        cin >> choice;
                        int count = 0;
                        switch (choice) {
                        case '1':
                            cout << "Введи диагональ монитора ";
                            cin >> input_data;
                            fin.open(path, ios::binary);
                            if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
                            PrintMonitorsRowHeader();
                            while (fin.read((char*)&monitors, sizeof(monitors))) {
                                if (monitors.diagonal > stoi(input_data)) {
                                    count++;
                                    PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                                }
                            }
                            if (count == 0) {
                                cout << "ничего не найдено";
                            }
                            fin.close();
                            break;

                        case '2':
                            cout << "Введи диагональ монитора ";
                            cin >> input_data;
                            fin.open(path, ios::binary);
                            if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
                            PrintMonitorsRowHeader();
                            while (fin.read((char*)&monitors, sizeof(monitors))) {

                                if (monitors.diagonal < stoi(input_data)) {
                                    count++;
                                    PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                                }
                            }
                            if (count == 0) {
                                cout << "ничего не найдено";
                            }
                            fin.close();
                            break;

                        case '3':
                            cout << "Введи диагональ монитора ";
                            cin >> input_data;
                            fin.open(path, ios::binary);
                            if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
                            PrintMonitorsRowHeader();
                            while (fin.read((char*)&monitors, sizeof(monitors))) {
                                if (monitors.diagonal == stoi(input_data)) {
                                    count++;
                                    PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                                }
                            }
                            if (count == 0) {
                                cout << "ничего не найдено";
                            }
                            fin.close();
                            break;

                        default:
                            cout << "Ошибка, следуй инструкциям";
                            break;
                        }

                    } while (choice != '4');
                    break;
                case '3':
                    do {
                        do {
                            cout << "Как будем искать? \n1 - >\n2 - <\n3 - =\n4 - назад\n";
                            cin >> choice;
                            int count = 0;
                            switch (choice) {
                                case '1':
                                    cout << "Введи частоту обновления монитора ";
                                    cin >> input_data;
                                    fin.open(path, ios::binary);
                                    if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
                                    PrintMonitorsRowHeader();
                                    while (fin.read((char*)&monitors, sizeof(monitors))) {
                                        if (monitors.frequency > stoi(input_data)) {
                                            count++;
                                            PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                                        }
                                    }
                                    if (count == 0) {
                                        cout << "ничего не найдено";
                                    }
                                    fin.close();
                                    break;
                                case '2':
                                    cout << "Введи частоту обновления монитора";
                                    cin >> input_data;
                                    fin.open(path, ios::binary);
                                    if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
                                    PrintMonitorsRowHeader();
                                    while (fin.read((char*)&monitors, sizeof(monitors))) {
                                        if (monitors.frequency < stoi(input_data)) {
                                            count++;
                                            PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                                        }
                                    }
                                    if (count == 0) {
                                        cout << "ничего не найдено";
                                    }
                                    fin.close();
                                    break;
                                case '3':
                                    cout << "Введи частоту обновления монитора ";
                                    cin >> input_data;
                                    fin.open(path, ios::binary);
                                    if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
                                    PrintMonitorsRowHeader();
                                    while (fin.read((char*)&monitors, sizeof(monitors))) {

                                        if (monitors.frequency == stoi(input_data)) {
                                            count++;
                                            PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                                        }
                                    }
                                    if (count == 0) {
                                        cout << "ничего не найдено";
                                    }
                                    fin.close();
                                    break;
                                default:
                                    cout << "Ошибка, следуй инструкциям";
                                    break;
                                }
                            } while (choice != '4');
                        } while (choice != '4');
                        break;

                case '4':
                    cout << "Введи разрешение монитора ";
                    cin >> input_data;
                    fin.open(path, ios::binary);
                    if (!fin.is_open())
                        cout << "Ошибка при открытии файла!\n";
                    else {
                        int count = 0;
                        PrintMonitorsRowHeader();
                        while (fin.read((char*)&monitors, sizeof(monitors))) {
                            if ((string(monitors.permission)).find(input_data) != string::npos) {
                                count++;
                                PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                            }
                        }
                        if (count == 0) {
                            cout << "ничего не найдено";
                        }
                        fin.close();
                    }
                    break;

                case '5':
                    cout << "Введи соотношение сторон ";
                    cin >> input_data;
                    fin.open(path, ios::binary);
                    if (!fin.is_open()) cout << "Ошибка при открытии файла!\n";
                    else {
                        int count = 0;
                        PrintMonitorsRowHeader();
                        while (fin.read((char*)&monitors, sizeof(monitors))) {
                            if ((string(monitors.permission)).find(input_data) != string::npos) {
                                count++;
                                PrintMonitorsRow(string(monitors.name), monitors.diagonal, monitors.frequency, monitors.permission, monitors.aspectRatio);
                            }
                        }
                        if (count == 0) {
                            cout << "ничего не найдено";
                        }
                        fin.close();
                    }
                    break;
                default:
                    cout << "Ошибка, следуй инструкциям";
                    break;
                }
            } while (choice != '6');

        default:
            cout << "Ошибка, следуй инструкциям";
            break;
        }
    } while (choice != '4');
    return 0; 
}

