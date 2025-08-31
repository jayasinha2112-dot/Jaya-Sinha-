#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int quantity;

    Book() {}
    Book(int id, string title, string author, int quantity) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->quantity = quantity;
    }
};

vector<Book> library;

// Function to save books to file
void saveToFile() {
    ofstream file("library_data.txt");
    for (auto &b : library) {
        file << b.id << "|" << b.title << "|" << b.author << "|" << b.quantity << "\n";
    }
    file.close();
}

// Function to load books from file
void loadFromFile() {
    ifstream file("library_data.txt");
    if (!file.is_open()) return;

    library.clear();
    string line;
    while (getline(file, line)) {
        int id, qty;
        string title, author;
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        size_t pos3 = line.find("|", pos2 + 1);

        id = stoi(line.substr(0, pos1));
        title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        qty = stoi(line.substr(pos3 + 1));

        library.push_back(Book(id, title, author, qty));
    }
    file.close();
}

void addBook() {
    int id, qty;
    string title, author;

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Quantity: ";
    cin >> qty;

    library.push_back(Book(id, title, author, qty));
    saveToFile();
    cout << "Book added successfully!\n";
}

void viewBooks() {
    if (library.empty()) {
        cout << "No books in library.\n";
        return;
    }
    cout << "\n--- Library Books ---\n";
    for (auto &b : library) {
        cout << "ID: " << b.id << " | Title: " << b.title
             << " | Author: " << b.author
             << " | Quantity: " << b.quantity << "\n";
    }
}

void searchBook() {
    int choice;
    cout << "\nSearch by: 1) ID  2) Title  3) Author\nChoice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        int id;
        cout << "Enter Book ID: ";
        cin >> id;
        for (auto &b : library) {
            if (b.id == id) {
                cout << "Found: " << b.title << " by " << b.author << " | Qty: " << b.quantity << "\n";
                return;
            }
        }
    } else if (choice == 2) {
        string title;
        cout << "Enter Title: ";
        getline(cin, title);
        for (auto &b : library) {
            if (b.title == title) {
                cout << "Found: " << b.title << " by " << b.author << " | Qty: " << b.quantity << "\n";
                return;
            }
        }
    } else if (choice == 3) {
        string author;
        cout << "Enter Author: ";
        getline(cin, author);
        for (auto &b : library) {
            if (b.author == author) {
                cout << "Found: " << b.title << " by " << b.author << " | Qty: " << b.quantity << "\n";
                return;
            }
        }
    }
    cout << "Book not found!\n";
}

void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;
    for (auto &b : library) {
        if (b.id == id) {
            if (b.quantity > 0) {
                b.quantity--;
                saveToFile();
                cout << "Book issued successfully!\n";
            } else {
                cout << "Out of stock!\n";
            }
            return;
        }
    }
    cout << "Book not found!\n";
}

void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;
    for (auto &b : library) {
        if (b.id == id) {
            b.quantity++;
            saveToFile();
            cout << "Book returned successfully!\n";
            return;
        }
    }
    cout << "Book not found!\n";
}

int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n--- Library Tracker ---\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: saveToFile(); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
