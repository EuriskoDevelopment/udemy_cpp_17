#include <algorithm>
#include <iostream>
using namespace std;

#define MAX_BOOKS 10
#define MAX_USERS 10

struct User {
    int id;
    string name;

    User()
    {
        id = 0;
        name = "";
    }
};

struct Book {
    int id;
    string name;
    int quantity;
    int nbrOfBorrowed;

    void read()
    {
        cout << "Enter book id, title & quantity: ";
        cin >> id >> name >> quantity;
    }

    void print()
    {
        cout << "id = " << id << " name = " << name << " quantity "
             << quantity << " total_borrowed " << nbrOfBorrowed
             << "\n";
    }
};

bool compareById(Book& a, Book& b)
{
    return a.id < b.id;
}

bool compareByName(Book& a, Book& b)
{
    return a.name < b.name;
}

struct LibrarySystem {
    int nbrOfBooks;
    int nbrOfUsers;
    Book bookList[MAX_BOOKS];
    User userList[MAX_USERS];

    LibrarySystem()
    {
        nbrOfBooks = nbrOfUsers = 0;
    }

    void add_book()
    {
        bookList[nbrOfBooks++].read();
    }

    void print_library_by_id()
    {
        sort(bookList, bookList + nbrOfBooks, compareById);
        for (int i = 0; i < nbrOfBooks; i++) {
            bookList[i].print();
        }
    }

    void print_library_by_name()
    {
        sort(bookList, bookList + nbrOfBooks, compareByName);
        for (int i = 0; i < nbrOfBooks; i++) {
            bookList[i].print();
        }
    }

    void run()
    {
        while (true) {
            int choice = menu();

            if (choice == 1)
                add_book();
            //else if (choice == 2)
            //search_books_by_prefix();
            //else if (choice == 3)
            //print_who_borrowed_book_by_name();
            else if (choice == 4)
                print_library_by_id();
            else if (choice == 5)
                print_library_by_name();
            //else if (choice == 6)
            //add_user();
            //else if (choice == 7)
            //user_borrow_book();
            //else if (choice == 8)
            //user_return_book();
            //else if (choice == 9)
            //print_users();
            else
                break;
        }
    }

    int menu()
    {
        int choice = -1;
        while (choice == -1) {
            if (true) {
                cout << "\nLibrary Menu;\n";
                cout << "1) add_book\n";
                cout << "2) search_books_by_prefix\n";
                cout << "3) print_who_borrowed_book_by_name\n";
                cout << "4) print_library_by_id\n";
                cout << "5) print_library_by_name\n";
                cout << "6) add_user\n";
                cout << "7) user_borrow_book\n";
                cout << "8) user_return_book\n";
                cout << "9) print_users\n";
                cout << "10) Exit\n";
            }

            cout << "\nEnter your menu choice [1 - 10]: ";
            cin >> choice;

            if (!(1 <= choice && choice <= 10)) {
                cout << "Invalid choice. Try again\n";
                choice = -1; // loop keep working
            }
        }
        return choice;
    }
};

int main()
{
    //freopen("c.in", "rt", stdin);
    LibrarySystem library;
    library.run();
    return 0;
}