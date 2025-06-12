#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Expense {
    string description;
    double amount;
    string category;
    string date;
};

vector <Expense> expenses;

bool isValidDate(const string& date) {
    if (date.size() != 10 || date[2] != '-' || date[5] != '-') return false;

    string month = date.substr(0, 2);
    string day = date.substr(3 , 2);
    string year = date.substr(6, 4);

    for (char c : month + day + year) {
        if (!isdigit(c)) return false;
    }

    int m = stoi(month), d = stoi(day), y = stoi(year);
    if (m < 1 || m > 12 || d < 1 || d > 31 || y < 0) return false;

    return true;
}

void addExpense() {
    Expense expense;
    cout << "Enter description: ";
    cin.ignore();
    getline(cin, expense.description);

    cout << "Enter amount: ";
    cin >> expense.amount;

    cout << "Enter category: ";
    cin.ignore();
    getline(cin, expense.category);

    cout << "Enter date (MM-DD-YYYY): ";
    getline(cin, expense.date);

    while (!isValidDate(expense.date)) {
        cout << "Invalid date format. Please enter again (MM-DD-YYYY) : ";
        getline(cin, expense.date);
    }

    expenses.push_back(expense);
    cout << "Expenses added successfully!\n";
}

void viewExpenses() {
    if (expenses.empty()) {
        cout << "No expenses recorded yet\n";
        return;
    }

    cout << left << setw(20) << "Description" << setw(10) << "Amount"
         << setw(15) << "Category" << setw(12) << "Date" << endl;
    cout << string(60, '-') << endl;

    for (const auto& expense : expenses) {
        cout << left << setw(20) << expense.description
             << setw(10) << expense.amount
             << setw(15) << expense.category
             << setw(12) << expense.date << endl;
    }
}

void viewSummary() {
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }

    double total = 0.0;
    for (const auto& expense : expenses) {
        total += expense.amount;
    }

    cout << "Total Expenses: $" << fixed << setprecision(2) << total << endl;
}

void saveToFile() {
    ofstream file ("expenses.txt");
    if (!file) {
        cout << "Error saving data to file.\n";
        return;
    }

    for (const auto& expense : expenses) {
        file << expense.description << "," << expense.amount << ","
             << expense.category << "," << expense.date << endl;
    }

    file.close();
    cout << "Expenses saved to expenses.txt\n";
}

void loadFromFile() {
    ifstream file ("expenses.txt");
    if (!file) {
        cout << "No saved expenses found.\n";
        return;
    }

    expenses.clear();
    Expense expense;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        expense.description = line.substr(0, pos1);
        expense.amount = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        expense.category = line.substr(pos2 + 1, pos3 - pos2 - 1);
        expense.date = line.substr(pos3 + 1);

        expenses.push_back(expense);
    }

    file.close();
    cout << "Expenses loaded from expenses.txt\n";
}

void showMenu() {
    cout << "\nExpense Tracker\n";
    cout << "1. Add Expense\n";
    cout << "2. View Expenses\n";
    cout << "3. View Summary\n";
    cout << "4. Save to File\n";
    cout << "5. Load from File\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                viewSummary();
                break;

            case 4:
                saveToFile();
                break;

            case 5:
                loadFromFile;
                break;

            case 6:
                cout << "Exiting... Goodbye!\n";
            
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice!= 6);

    return 0;
}