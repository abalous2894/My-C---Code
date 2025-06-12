#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

struct Item {
    string name;
    string category;
    int quantity;
    double price;

    void display() const {
        cout << "Name: " << name << " \nQuantity: " << quantity << " \nPrice: $" << price << endl;
    }
};

void addItem(vector<Item>& inventory);
void removeItem(vector<Item>& inventory);
void displayInventory(const vector<Item>& inventory);
void saveInventoryToFile(const vector<Item>& inventory, const string& filename);
void loadInventoryFromFile(vector<Item>& inventory, const string& filename);
void searchItem(const vector<Item>& inventory);
void updateItemDetails(vector <Item>& inventory);
void filterByCategory(const vector<Item>& inventory);
bool validatePositiveNumber(double& vavlue);
bool validatePositiveInteger(int& value);
bool itemExists(const vector<Item>& inventory, const string& name);

int main() {
    vector<Item> inventory;
    const string filename = "inventory.txt";

    loadInventoryFromFile(inventory, filename);

    int choice;

    do {
        cout << "\nInventory Management System" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Remove Item" << endl;
        cout << "3. Display Inventory" << endl;
        cout << "4. Search for an Item" << endl;
        cout << "5. Update Item Details" << endl;
        cout << "6. Filter by Category" << endl;
        cout << "7. Save and Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
            continue;
        }

        switch(choice) {
            case 1:
                addItem(inventory);
                break;
            
            case 2:
                removeItem(inventory);
                break;

            case 3:
                displayInventory(inventory);
                break;

            case 4:
                searchItem(inventory);
                break;

            case 5:
                updateItemDetails(inventory);
                break;

            case 6:
                filterByCategory(inventory);
                break;

            case 7:
                saveInventoryToFile(inventory, filename);
                cout << "Inventory saved. Exiting the program. Goodbye!" << endl;
                break;
        }
    } while (choice!= 7);

    return 0;
}

bool validatePositiveInteger(int& value) {
    while (true) {
        cin >> value;
        if (!cin.fail() && value > 0) return true;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }
}

bool validatePositiveNumber(double& value) {
    while (true) {
        cin >> value;
        if (!cin.fail() && value > 0) return true;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive number: ";
    }
}

bool itemExists(const vector<Item>& inventory, const string& name) {
    for (const auto& item : inventory) {
        if (item.name == name) {
            return true;
        }
    }

    return false;
}

void addItem(vector<Item>& inventory) {
    Item newItem;

    cout << "Enter item name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newItem.name);

    if (itemExists(inventory, newItem.name)) {
        cout << "Item already exists in inventory. Please use a unique name.\n";
        return;
    }

    cout << "Enter item category: ";
    getline(cin, newItem.category);

    cout << "Enter quantity: ";
    while (!validatePositiveInteger(newItem.quantity));

    cout << "Enter price: ";
    while (!validatePositiveNumber(newItem.price));

    inventory.push_back(newItem);
    cout << "Item added successfully!\n";
}

void removeItem(vector<Item>& inventory) {
    string itemName;
    cout << "Enter the name of the item to remove: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, itemName);

    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ( it->name == itemName) {
            inventory.erase(it);
            cout << "Item removed successfully!" << endl;
            return;
        }
    }

    cout << "Item not found in inventory." << endl;
}

void displayInventory(const vector<Item>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty!" << endl;
        return;
    }

    cout << "\nCurrent Inventory:\n";
    for (const auto& item : inventory) {
        item.display();
    }
}

void searchItem(const vector<Item>& inventory) {
    string itemName;
    cout << "Enter the name of the item to search for: ";
    cin.ignore();
    getline(cin, itemName);

    for (const auto& item : inventory) {
        if (item.name == itemName) {
            cout << "Item found.\n";
            item.display();
            return;
        }
    }

    cout << "Item not found in inventory.\n";
}

void updateItemDetails(vector<Item>& inventory) {
    string itemName;
    cout << "Enter the name of the item to update: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, itemName);

    for (auto& item : inventory) {
        if (item.name == itemName) {
            cout << "Current details:\n";
            item.display();

            int choice;
            cout << "What would you like to update?\n";
            cout << "1. Price\n";
            cout << "2. Quantity\n";
            cout << "3, Category\n";
            cout << "Enter your choice: ";
            cin >> choice;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
                case 1:
                    cout << "Enter the new price: ";
                    while (!validatePositiveNumber(item.price));
                    break;
                
                case 2:
                    cout << "Enter the new quantity: ";
                    while (!validatePositiveInteger(item.quantity));
                    break;

                case 3:
                    cout << "Select new category:\n";
                    getline(cin, item.category);
                    break;

                default: 
                    cout << "Invalid choice. No changes made.\n";
            }

            cout << "Item details updated successfully!\n";
            return;
        }
    }

    cout << "Item not found in inventory.\n";
}

void filterByCategory(const vector<Item>& inventory) {
    string category;
    
    cout << "Enter a category to filter by: ";
    cin.ignore();
    getline(cin, category);

    bool found = false;
    cout << "Items in category \"" << category << "\":\n";
    for (const auto& item : inventory) {
        if (item.category == category) {
            cout << "Name: " << item.name
                             << ", Quantity: " << item.quantity
                             << ", Price: $" << item.price << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No items found in category \"" << category << "\".\n";
    }
}

void saveInventoryToFile(const vector<Item>& inventory, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error; Could not open file for saving." << endl;
        return;
    }

    for (const auto& item : inventory) {
        file << item.name << "," << item.category << "," << item.quantity << "," << item.price << endl;
    }

    file.close();
    cout << "Inventory saved to " << filename << endl;
}

void loadInventoryFromFile(vector<Item>& inventory, const string& filename) {
    ifstream file(filename);
    if(!file) {
        cerr << "No existing inventory file found. Starting with an empty inventory." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) {
            cerr << "Invalid data format in file. Skipping line: " << line << endl;
            continue;
        }

        Item item;
        try {
            item.name = line.substr(0, pos1);
            item.category = line.substr(pos1 + 1, pos2 - pos1 - 1);
            item.quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            item.price = stod(line.substr(pos3 + 1));
        } catch (const exception& e) {
            cerr << "Error parsing line. Skipping line: " << line << endl;
            continue;
        }

        inventory.push_back(item);
    }

    file.close();
    cout << "Inventory loaded from " << filename << endl;
}