#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>
using namespace std;

enum Specialty { KN, PZ, IP, CB, PI };
string specialtyNames[] = { "КН", "ПЗ", "ІР", "КБ", "РІ" };

union ProfileGrade {
    int programming;
    int numericalMethods;
    int pedagogy;
};

struct Student {
    string surname;
    int course;
    Specialty specialty;
    int physics;
    int math;
    ProfileGrade profile;
};

void PrintTable(Student* students, int size) {
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "| № | Прізвище       | Курс  | Спеціальність  | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < size; i++) {
        cout << "| " << setw(1) << i + 1 << " | "
            << setw(15) << left << students[i].surname
            << "| " << setw(6) << students[i].course
            << "| " << setw(15) << specialtyNames[students[i].specialty]
            << "| " << setw(7) << students[i].physics
            << "| " << setw(11) << students[i].math;

        // Display the relevant profile grade based on specialty
        if (students[i].specialty == KN) {
            cout << "| " << setw(14) << students[i].profile.programming << "| " << setw(16) << "-" << "| " << setw(10) << "-" << " |" << endl;
        }
        else if (students[i].specialty == IP) {
            cout << "| " << setw(14) << "-" << "| " << setw(16) << students[i].profile.numericalMethods << "| " << setw(10) << "-" << " |" << endl;
        }
        else {
            cout << "| " << setw(14) << "-" << "| " << setw(16) << "-" << "| " << setw(10) << students[i].profile.pedagogy << " |" << endl;
        }
    }
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
}

void InputData(Student* students, int& size) {
    cout << "Введіть кількість студентів: ";
    cin >> size;
    for (int i = 0; i < size; i++) {
        cout << "Студент #" << (i + 1) << ":" << endl;
        cout << "Прізвище: ";
        cin >> students[i].surname;
        cout << "Курс (1-4): ";
        cin >> students[i].course;

        int specialtyInput;
        cout << "Спеціальність (0 - КН, 1 - ПЗ, 2 - ІР, 3 - КБ, 4 - РІ): ";
        cin >> specialtyInput;
        students[i].specialty = Specialty(specialtyInput);

        cout << "Оцінка з фізики: ";
        cin >> students[i].physics;
        cout << "Оцінка з математики: ";
        cin >> students[i].math;

        if (students[i].specialty == KN) {
            cout << "Оцінка з програмування: ";
            cin >> students[i].profile.programming;
        }
        else if (students[i].specialty == IP) {
            cout << "Оцінка з чисельних методів: ";
            cin >> students[i].profile.numericalMethods;
        }
        else {
            cout << "Оцінка з педагогіки: ";
            cin >> students[i].profile.pedagogy;
        }
    }
}

int GetProfileGrade(const Student& student) {
    if (student.specialty == KN) return student.profile.programming;
    else if (student.specialty == IP) return student.profile.numericalMethods;
    else return student.profile.pedagogy;
}

void SortByGrade(Student* students, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            bool swapNeeded = false;

            if (GetProfileGrade(students[j]) > GetProfileGrade(students[j + 1])) {
                swapNeeded = true;
            }
            else if (GetProfileGrade(students[j]) == GetProfileGrade(students[j + 1])) {
                if (students[j].specialty > students[j + 1].specialty) {
                    swapNeeded = true;
                }
                else if (students[j].specialty == students[j + 1].specialty) {
                    if (students[j].surname > students[j + 1].surname) {
                        swapNeeded = true;
                    }
                }
            }
            if (swapNeeded) {
                swap(students[j], students[j + 1]);
            }
        }
    }
    cout << "Студенти сортовані за профільною оцінкою, спеціальністю та прізвищем." << endl;
    PrintTable(students, size);
}

void BinarySearchBySpecialtyAndGrade(Student* students, int size, Specialty specialty, int grade, string surname) {
    int left = 0, right = size - 1;
    bool found = false;
    while (left <= right) {
        int mid = (left + right) / 2;
        int profileGrade = GetProfileGrade(students[mid]);

        if (students[mid].specialty == specialty && profileGrade == grade && students[mid].surname == surname) {
            found = true;
            cout << "Студент знайдений за індексом " << mid + 1 << ":" << endl;
            cout << "Прізвище: " << students[mid].surname << ", Курс: " << students[mid].course
                << ", Спеціальність: " << specialtyNames[students[mid].specialty]
                << ", Оцінка з профільного предмету: " << profileGrade << endl;
            break;
        }
        else if (profileGrade < grade || (profileGrade == grade && students[mid].specialty < specialty)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    if (!found) {
        cout << "Не знайдено такого/их студентів." << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int size;
    Student students[100];

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Ввести значення\n";
        cout << "2. Вивести таблицю\n";
        cout << "3. Сортувати за оцінкою з профільного предмету\n";
        cout << "4. Бінарний пошук за спеціальністю, прізвищем та оцінкою з профільного предмету\n";
        cout << "0. Вихід\n";
        cout << "Введіть вибір: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            InputData(students, size);
            break;
        case 2:
            PrintTable(students, size);
            break;
        case 3:
            SortByGrade(students, size);
            break;
        case 4: {
            int specialtyInput, grade;
            string surname;
            cout << "Вибрати спеціальність (0 - КН, 1 - ПЗ, 2 - ІР, 3 - КБ, 4 - РІ): ";
            cin >> specialtyInput;
            cout << "Ввести прізвище для пошуку: ";
            cin >> surname;
            cout << "Ввести оцінку з профільного предмету для пошуку: ";
            cin >> grade;
            BinarySearchBySpecialtyAndGrade(students, size, Specialty(specialtyInput), grade, surname);
            break;
        }
        case 0:
            cout << "Вихід." << endl;
            return 0;
        default:
            cout << "Введіть значення знову." << endl;
        }
    }
}
