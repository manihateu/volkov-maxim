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
} monitorss;

void PrintMonitorsRowHeader() {
    cout << left << setw(10) << "Название" << "|" << left << setw(10) << "Диагональ" << "|" << left << setw(10)
        << "Частота" << "|" << left << setw(10) << "Разрешение" << "|" << left << setw(10) << "Соотношение" << "|"
        << endl;
}

void PrintMonitorsNewRow(string name, int diagonal, int frequency, char permission[20], char aspectRatio[20]) {
    cout << left << setw(10) << name << "|" << left << setw(10)
        << diagonal << "|" << left << setw(10) << frequency << "|"
        << left
        << setw(10) << permission << "|" << left << setw(10)
        << aspectRatio << " |"
        << endl;
}



int main() {
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");
    string path = "file.bin";
    char choice = '0';

    ofstream fout;
    ifstream fin;
    monitors* proc = new monitors; // Создаем указатель на структуру
    ofstream* ofs = &fout; // Создаем указатель на ofstream
    ifstream* ifs = &fin; // Создаем указатель на ifstream

    do {
        cout << endl << "1-Добавить запись" << endl << "2-Посмотреть записи" << endl << "3-Поиск" << endl << "4-Выход" << endl;
        cin >> choice;
        switch (choice) {
        case '1':
            cout << "название монитора: ";
            cin >> proc->name;
            cout << endl << "диагональ монитора: ";
            while (!(cin >> proc->diagonal)) {
                cout << "Некорректное значение, попробуй еще раз";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << endl << "Частота обновления монитора: ";
            while (!(cin >> proc->frequency)) {
                cout << "Некорректное значение, попробуй еще раз";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << endl << "разрешение монитора: ";
            cin >> proc->permission;
            cout << endl << "соотношение сторон: ";
            cin >> proc->aspectRatio;
            ofs->open(path, ios::binary | ios::app);//запись в конец файла
            if (!ofs->is_open()) cout << "Ошибка при открытии файла!\n";
            else {
                ofs->write((char*)proc, sizeof(monitors));
            }
            ofs->close();
            cout << "Готово";
            break;

        case '2':
            PrintMonitorsRowHeader();
            ifs->open(path, ios::binary);
            if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
            else {
                while (ifs->read((char*)proc, sizeof(monitors))) {
                    PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                }
            }
            ifs->close();
            break;

        case '3':
            do {
                cout << "\n1-Поиск по названию\n";
                cout << "2-Поиск по частоте\n";
                cout << "3-Поиск по тепловыделению\n";
                cout << "4-Поиск по модели\n";
                cout << "5-Поиск по сокету\n";
                cout << "6-Назад\n";
                cin >> choice;
                string fff;
                switch (choice) {
                case '1':
                    cout << "Введи название ";
                    cin >> fff;
                    ifs->open(path, ios::binary);
                    if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
                    else {
                        int cc = 0;
                        PrintMonitorsRowHeader();
                        while (ifs->read((char*)proc, sizeof(monitors))) {
                            if ((string(proc->name)).find(fff) != string::npos) {
                                cc++;
                                PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                            }
                        }
                        if (cc == 0) {
                            cout << "ничего не найдено";
                        }
                        ifs->close();
                    }
                    break;

                case '2':
                    do {
                        cout << "Как будем искать? \n1 - >\n2 - <\n3 - =\n4 - назад\n";
                        cin >> choice;
                        int ccc = 0;
                        switch (choice) {
                        case '1':
                            cout << "Введи диагональ монитора ";
                            cin >> fff;
                            ifs->open(path, ios::binary);
                            if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
                            PrintMonitorsRowHeader();
                            while (ifs->read((char*)proc, sizeof(monitors))) {
                                if (proc->diagonal > stoi(fff)) {
                                    ccc++;
                                    PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                                }
                            }
                            if (ccc == 0) {
                                cout << "ничего не найдено";
                            }
                            ifs->close();
                            break;

                        case '2':
                            cout << "Введи диагональ монитора ";
                            cin >> fff;
                            ifs->open(path, ios::binary);
                            if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
                            PrintMonitorsRowHeader();
                            while (ifs->read((char*)proc, sizeof(monitors))) {

                                if (proc->diagonal < stoi(fff)) {
                                    ccc++;
                                    PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                                }
                            }
                            if (ccc == 0) {
                                cout << "ничего не найдено";
                            }
                            ifs->close();
                            break;

                        case '3':
                            cout << "Введи диагональ монитора ";
                            cin >> fff;
                            ifs->open(path, ios::binary);
                            if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
                            PrintMonitorsRowHeader();
                            while (ifs->read((char*)proc, sizeof(monitors))) {
                                if (proc->diagonal == stoi(fff)) {
                                    ccc++;
                                    PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                                }
                            }
                            if (ccc == 0) {
                                cout << "ничего не найдено";
                            }
                            ifs->close();
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
                            int ccc = 0;
                            switch (choice) {
                            case '1':
                                cout << "Введи частоту обновления монитора ";
                                cin >> fff;
                                ifs->open(path, ios::binary);
                                if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
                                PrintMonitorsRowHeader();
                                while (ifs->read((char*)proc, sizeof(monitors))) {
                                    if (proc->frequency > stoi(fff)) {
                                        ccc++;
                                        PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                                    }
                                }
                                if (ccc == 0) {
                                    cout << "ничего не найдено";
                                }
                                ifs->close();
                                break;

                            case '2':
                                cout << "Введи частоту обновления монитора ";
                                cin >> fff;
                                ifs->open(path, ios::binary);
                                if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
                                PrintMonitorsRowHeader();
                                while (ifs->read((char*)proc, sizeof(monitors))) {
                                    if (proc->frequency < stoi(fff)) {
                                        ccc++;
                                        PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                                    }
                                }
                                if (ccc == 0) {
                                    cout << "ничего не найдено";
                                }
                                ifs->close();
                                break;

                            case '3':
                                cout << "Введи частоту обновления монитора ";
                                cin >> fff;
                                ifs->open(path, ios::binary);
                                if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
                                PrintMonitorsRowHeader();
                                while (ifs->read((char*)proc, sizeof(monitors))) {

                                    if (proc->frequency == stoi(fff)) {
                                        ccc++;
                                        PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                                    }
                                }
                                if (ccc == 0) {
                                    cout << "ничего не найдено";
                                }
                                ifs->close();
                                break;

                            default:
                                cout << "Ошибка, следуй инструкциям";
                                break;
                            }

                        } while (choice != '4');
                    } while (choice != '4');
                    break;
                case '4':
                    cout << "разрешение монитора ";
                    cin >> fff;
                    ifs->open(path, ios::binary);
                    if (!ifs->is_open())
                        cout << "Ошибка при открытии файла!\n";
                    else {
                        int cc = 0;
                        PrintMonitorsRowHeader();
                        while (ifs->read((char*)proc, sizeof(monitors))) {
                            if ((string(proc->permission)).find(fff) != string::npos) {
                                cc++;
                                PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                            }
                        }
                        if (cc == 0) {
                            cout << "ничего не найдено";
                        }
                        ifs->close();
                    }
                    break;

                case '5':
                    cout << "соотношение сторон ";
                    cin >> fff;
                    ifs->open(path, ios::binary);
                    if (!ifs->is_open()) cout << "Ошибка при открытии файла!\n";
                    else {
                        int cc = 0;
                        PrintMonitorsRowHeader();
                        while (ifs->read((char*)proc, sizeof(monitors))) {
                            if ((string(proc->aspectRatio)).find(fff) != string::npos) {
                                cc++;
                                PrintMonitorsNewRow(string(proc->name), proc->diagonal, proc->frequency, proc->permission, proc->aspectRatio);
                            }
                        }
                        if (cc == 0) {
                            cout << "ничего не найдено";
                        }
                        ifs->close();
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
    delete proc, ofs, ifs;
}
