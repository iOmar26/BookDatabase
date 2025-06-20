#include <iostream>
#include <string>
using namespace std;

// Constants for maximum counts
const int MAX_BOOKS = 100;
const int MAX_AUTHORS = 100;
const int MAX_RELATIONS = 10; // Max authors per book / books per author

// Structure to hold book information
struct Book {
    int id;
    int pages;
    char title[100];
    char subject[100];
    char date[20];
    int authors[MAX_RELATIONS]; // IDs of assigned authors
    int authorCount;
};

// Structure to hold author information
struct Author {
    int id;
    char name[100];
    char phone[20];
    char address[200];
    char job[100];
    int books[MAX_RELATIONS]; // IDs of written books
    int bookCount;
};

Book books[MAX_BOOKS];
Author authors[MAX_AUTHORS];
int bookCount = 0;
int authorCount = 0;
int nextBookId = 1;
int nextAuthorId = 1;

// Find book index by ID
int findBook(int id) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].id == id)
            return i;
    }
    return -1;
}

// Find author index by ID
int findAuthor(int id) {
    for (int i = 0; i < authorCount; ++i) {
        if (authors[i].id == id)
            return i;
    }
    return -1;
}

// Add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        cout << "Book list is full.\n";
        return;
    }
    Book &b = books[bookCount];
    b.id = nextBookId++;
    cout << "Title? ";
    cin.getline(b.title, sizeof(b.title));
    cout << "Pages? ";
    cin >> b.pages;
    cin.ignore();
    cout << "Subject? ";
    cin.getline(b.subject, sizeof(b.subject));
    cout << "Date? ";
    cin.getline(b.date, sizeof(b.date));
    b.authorCount = 0;
    bookCount++;
    cout << "Book #" << b.id << " added.\n";
}

// Add a new author
void addAuthor() {
    if (authorCount >= MAX_AUTHORS) {
        cout << "Author list is full.\n";
        return;
    }
    Author &a = authors[authorCount];
    a.id = nextAuthorId++;
    cout << "Name? ";
    cin.getline(a.name, sizeof(a.name));
    cout << "Phone? ";
    cin.getline(a.phone, sizeof(a.phone));
    cout << "Address? ";
    cin.getline(a.address, sizeof(a.address));
    cout << "Job? ";
    cin.getline(a.job, sizeof(a.job));
    a.bookCount = 0;
    authorCount++;
    cout << "Author #" << a.id << " added.\n";
}

// Assign book to author
void assignBook() {
    int bid, aid;
    cout << "Book ID? "; cin >> bid;
    cout << "Author ID? "; cin >> aid;
    cin.ignore();
    int bi = findBook(bid);
    int ai = findAuthor(aid);
    if (bi >= 0 && ai >= 0) {
        Book &b = books[bi];
        Author &a = authors[ai];
        if (b.authorCount < MAX_RELATIONS && a.bookCount < MAX_RELATIONS) {
            b.authors[b.authorCount++] = aid;
            a.books[a.bookCount++] = bid;
            cout << "Assigned.\n";
        } else {
            cout << "Cannot assign: relation limit reached.\n";
        }
    } else {
        cout << "Invalid ID.\n";
    }
}

// Remove assignment
void removeAssign() {
    int bid, aid;
    cout << "Book ID? "; cin >> bid;
    cout << "Author ID? "; cin >> aid;
    cin.ignore();
    int bi = findBook(bid);
    int ai = findAuthor(aid);
    if (bi >= 0 && ai >= 0) {
        Book &b = books[bi];
        Author &a = authors[ai];
        // Remove from book
        for (int i = 0; i < b.authorCount; ++i) {
            if (b.authors[i] == aid) {
                for (int j = i; j < b.authorCount - 1; ++j)
                    b.authors[j] = b.authors[j+1];
                b.authorCount--;
                break;
            }
        }
        // Remove from author
        for (int i = 0; i < a.bookCount; ++i) {
            if (a.books[i] == bid) {
                for (int j = i; j < a.bookCount - 1; ++j)
                    a.books[j] = a.books[j+1];
                a.bookCount--;
                break;
            }
        }
        cout << "Removed.\n";
    } else {
        cout << "Invalid ID.\n";
    }
}

// List all books
void listBooks() {
    for (int i = 0; i < bookCount; ++i) {
        Book &b = books[i];
        cout << b.id << ": " << b.title << " (Authors: ";
        for (int j = 0; j < b.authorCount; ++j) {
            cout << b.authors[j];
            if (j < b.authorCount - 1) cout << ",";
        }
        cout << ")\n";
    }
}

// List all authors
void listAuthors() {
    for (int i = 0; i < authorCount; ++i) {
        Author &a = authors[i];
        cout << a.id << ": " << a.name << " (Books: ";
        for (int j = 0; j < a.bookCount; ++j) {
            cout << a.books[j];
            if (j < a.bookCount - 1) cout << ",";
        }
        cout << ")\n";
    }
}

// Search book
void searchBook() {
    int id;
    cout << "Book ID? "; cin >> id;
    cin.ignore();
    int idx = findBook(id);
    if (idx < 0) {
        cout << "Not found.\n";
    } else {
        Book &b = books[idx];
        cout << b.title << ", " << b.pages << "p, " << b.subject << ", " << b.date << "\n";
    }
}

// Search author
void searchAuthor() {
    int id;
    cout << "Author ID? "; cin >> id;
    cin.ignore();
    int idx = findAuthor(id);
    if (idx < 0) {
        cout << "Not found.\n";
    } else {
        Author &a = authors[idx];
        cout << a.name << ", " << a.phone << ", " << a.address << ", " << a.job << "\n";
    }
}

// Main menu
int main() {
    while (true) {
        int c;
        cout << "1.Add Book\n2.Add Author\n3.Assign Book\n4.Remove Assign\n5.List Books\n6.List Authors\n7.Search Books\n8.Search Authors\n0.Exit:\n ";
        cin >> c;
        cin.ignore();
        if (c == 0) break;
        switch (c) {
            case 1: addBook(); break;
            case 2: addAuthor(); break;
            case 3: assignBook(); break;
            case 4: removeAssign(); break;
            case 5: listBooks(); break;
            case 6: listAuthors(); break;
            case 7: searchBook(); break;
            case 8: searchAuthor(); break;
            default: cout << "?\n"; break;
        }
    }
    return 0;
}

