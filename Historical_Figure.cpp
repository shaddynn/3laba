#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

struct HistoricalFigure {
    int id;
    string name;
    int birthYear;
    int deathYear;
    string country;
    string occupation;
    string famousWork;
    double score;
};

string center(const string& text, int width) {
    int padding = width - text.size();
    int padLeft = padding / 2;
    int padRight = padding - padLeft;
    return (string(padLeft, ' ') + text + string(padRight, ' '));
}

HistoricalFigure* figures = nullptr; // динамический массив
int arraySize = 0;                   // текущее количество элементов
int arrayCapacity = 0;               // ёмкость массива

void push_back(HistoricalFigure figure) {
    // Увеличиваем ёмкость, если массив полон или ещё не инициализирован
    if (arraySize >= arrayCapacity) {
        arrayCapacity = (arrayCapacity == 0) ? 1 : arrayCapacity * 2;
        HistoricalFigure* newFigures = new HistoricalFigure[arrayCapacity];
        for (int i = 0; i < arraySize; i++) {
            newFigures[i] = figures[i];
        }
        delete[] figures;
        figures = newFigures;
    }
    figures[arraySize++] = figure;
}

void freeMemory() {
    delete[] figures;
    figures = nullptr;
    arraySize = 0;
    arrayCapacity = 0;
}

// Функция для чтения данных из файла
bool readDataFromFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        do {
            cout << '\n' << "Press the Enter key to continue.";
        } while (cin.get() != '\n');
        return false;
    }

    HistoricalFigure figure;
    while (file >> figure.id) {
        file.ignore();
        getline(file, figure.name);
        file >> figure.birthYear >> figure.deathYear;
        file.ignore();
        getline(file, figure.country);
        getline(file, figure.occupation);
        getline(file, figure.famousWork);
        file >> figure.score;
        push_back(figure);
    }
    file.close();
    return true;
}

// Функция для отображения данных
void displayData() {
    system("clear");
    int widths[8] = {5, 50, 25, 25, 25, 25, 50, 15};
    cout << "+";
    for (const auto& width : widths) {
        cout << setfill('-') << setw(width) << "" << "+";
    }
    cout << setfill(' ') << "\n";
    string headers[8] = {"ID", "Name", "Birth Year", "Death Year", "Country", "Occupation", "Famous Work", "Score"};
    cout << "|";
    for (size_t i = 0; i < 8; i++) {
        cout << center(headers[i], widths[i]) << "|";
    }
    cout << "\n";

    cout << "+";
    for (const auto& width : widths) {
        cout << setfill('-') << setw(width) << "" << "+";
    }
    cout << setfill(' ') << "\n";
    for (int i = 0; i < arraySize; i++) {
        const auto& figure = figures[i];
        cout << "|";
        cout << center(to_string(figure.id), widths[0]) << "|"
             << center(figure.name, widths[1]) << "|"
             << center(to_string(figure.birthYear), widths[2]) << "|"
             << center(to_string(figure.deathYear), widths[3]) << "|"
             << center(figure.country, widths[4]) << "|"
             << center(figure.occupation, widths[5]) << "|"
             << center(figure.famousWork, widths[6]) << "|"
             << center(to_string(figure.score), widths[7]) << "|\n";
        cout << "+";
        for (const auto& width : widths) {
            cout << setfill('-') << setw(width) << "" << "+";
        }
        cout << setfill(' ') << "\n";
    }

    do {

    } while (cin.get() != '\n');
}

// Функция для редактирования данных
void editData(int id) {
    bool isEnd1 = false;
    bool isEnd2 = false;
    bool isEnd3 = false;
    int countSuccess = 0;

    system("clear");
    for (int i = 0; i < arraySize; i++) {
        countSuccess = 0;
            if (figures[i].id == id) {
                system("clear");
                cout << "Введите новое имя: ";
                getline(cin, figures[i].name);
                system("clear");
                cout << "Введите новую страну: ";
                getline(cin, figures[i].country);
                system("clear");
                cout << "Введите новую профессию: ";
                system("clear");
                getline(cin, figures[i].occupation);
                cout << "Введите новое весомое достижение: ";
                getline(cin, figures[i].famousWork);
                system("clear");
                while(!isEnd1) {
                    system("clear");
                   cout << "Введите новую оценку значимости";
                    cin >> figures[i].score;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("clear");
                        cout << "Некорректный ввод." << endl;
                        do {
                            cout << '\n' << "Press the Enter key to continue.";
                        } while (cin.get() != '\n');
                    } else {
                        countSuccess++;
                        isEnd1 = true;
                    }
                }
                while(!isEnd2) {
                    system("clear");
                    cout << "Введите новый год рождения: ";
                    cin >> figures[i].birthYear;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("clear");
                        cout << "Некорректный ввод." << endl;
                        do {
                            cout << '\n' << "Press the Enter key to continue.";
                        } while (cin.get() != '\n');
                    } else {
                        countSuccess++;
                        isEnd2 = true;
                    }
                }
                while(!isEnd3) {
                    system("clear");
                  cout << "Введите новый год смерти: ";
                cin >> figures[i].deathYear;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("clear");
                    cout << "Некорректный ввод." << endl;
                    do {
                        cout << '\n' << "Press the Enter key to continue.";
                    } while (cin.get() != '\n');
                } else {
                    countSuccess++;
                    isEnd3 = true;
                }
                }
                cin.ignore();
                if (countSuccess == 3) {
                    return;
                }
            }
    }
    cout << "Запись с ID " << id << " не найдена." << endl;
    do {
        cout << '\n' << "Press the Enter key to continue.";
    } while (cin.get() != '\n');
}


// Функция для сохранения данных в новый файл
void saveDataToFile(const string &filename) {
    ofstream file(filename);
    if (!file) {
        system("clear");
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
        do {
            cout << '\n' << "Press the Enter key to continue.";
        } while (cin.get() != '\n');
        return;
    }

    for (int i = 0; i < arraySize; i++) {
        const auto& figure = figures[i];
        file << figure.id << endl << figure.name << endl
             << figure.birthYear << endl << figure.deathYear << endl
             << figure.country << endl << figure.occupation << endl
             << figure.famousWork << endl << figure.score << endl;
    }
    file.close();
}

double calculateAverageAge() {
    if (arraySize == 0) {
        return 0.0;
    }
       int currentYear = time(nullptr) / (60*60*24*365) + 1970;
       double totalAge = 0.0;

       for (int i=0; i < arraySize; i++) {
        int deathYear = figures[i].deathYear > 0 ? figures[i].deathYear : currentYear;
        int age = deathYear - figures[i].birthYear;
        totalAge += age;
       }
       do {
            } while (cin.get() != '\n');
       return totalAge/arraySize;
    }

int main() {
    system("clear");
    string filename;
    bool isFile = false;
    while (!isFile) {
        cout << "Введите имя файла для чтения данных: ";
        cin >> filename;
        cin.ignore(); // очищаем буфер
        cout << filename << endl;
        if (readDataFromFile(filename)) {
            isFile = true;
        }
        system("clear");
    }

    int choice;


    while (true) {
        system("clear");
        cout << "\nМеню:\n";
        cout << "1. Просмотр данных\n";
        cout << "2. Редактирование данных\n";
        cout << "3. Сохранение данных в новый файл\n";
        cout << "4. Average Age calculation\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("clear");
            cout << "Некорректный ввод." << endl;
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
            continue;
        }
        if (choice == 1) {
            displayData();
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 2) {
            int id;
            system("clear");
            cout << "Введите ID исторической личности для редактирования: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("clear");
                cout << "Некорректный ввод." << endl;
                do {
                    cout << '\n' << "Press the Enter key to continue.";
                } while (cin.get() != '\n');
                continue;
            }
            cin.ignore(); // очищаем буфер
            editData(id);
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 3) {
                string newFilename;
                system("clear");
                cout << "Введите имя нового файла: ";
                cin >> newFilename;
                cin.ignore();
                saveDataToFile(newFilename);
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 4) {
            double averageAge = calculateAverageAge();
            cout << "Average Age: " << averageAge << endl;
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 0) {
            system("clear");
            cout << "Выход из программы." << endl;
            freeMemory(); // освобождаем память перед завершением
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
            return 0;
            } else {
            cout << "Некорректный выбор. Пожалуйста, попробуйте еще раз." << endl;
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        }
    }
    return 0;
}