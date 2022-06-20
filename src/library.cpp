#include <algorithm>
#include <iostream>
using namespace std;

#define MAX_BOOKS 10
#define MAX_USERS 10

struct User {
    int id;
    string name;
    int borrowedBookIds[MAX_BOOKS];
    int nbrBorrowedBooks;

    User()
    {
        id = 0;
        name = "";
        nbrBorrowedBooks = 0;
    }

    void borrowBook(int bookId)
    {
        borrowedBookIds[nbrBorrowedBooks++] = bookId;
    }

    void returnBook(int bookId)
    {

        int* index = find(borrowedBookIds, borrowedBookIds + nbrBorrowedBooks, bookId) - nbrBorrowedBooks;
        cout << "Returning book id: " << bookId << " index: " << *index << endl;

        if (*index >= nbrBorrowedBooks) {
            cout << "Not a borrowed book" << endl;
            return;
        }
        for (int i = *index; i <= nbrBorrowedBooks; i++) {
            borrowedBookIds[i] = borrowedBookIds[i + 1];
        }

        nbrBorrowedBooks--;
    }

    bool is_borrowed(int book_id)
    {
        for (int i = 0; i < nbrBorrowedBooks; ++i) {
            if (book_id == borrowedBookIds[i])
                return true;
        }
        return false;
    }

    void read()
    {
        cout << "Enter user name and id: ";
        cin >> name >> id;
    }

    void print()
    {
        // sort what he borrowed
        sort(borrowedBookIds, borrowedBookIds + nbrBorrowedBooks);

        cout << "user " << name << " id " << id << " borrowed books ids: ";
        for (int i = 0; i < nbrBorrowedBooks; ++i)
            cout << borrowedBookIds[i] << " ";
        cout << "\n";
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
        nbrOfBorrowed = 0;
    }

    void print()
    {
        cout << "id = " << id << " name = " << name << " quantity "
             << quantity << " total_borrowed " << nbrOfBorrowed
             << "\n";
    }

    bool operator()(Book& a) const
    {
        return a.id == id;
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

const int isSameBook(Book& a, Book& b)
{
    return a.name == b.name;
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

    void add_user()
    {
        userList[nbrOfUsers++].read();
    }

    int find_book_idx_by_name(string name)
    {
        for (int i = 0; i < nbrOfBooks; ++i) {
            if (name == bookList[i].name)
                return i;
        }
        return -1;
    }

    void user_borrow_book()
    {
        string name;
        int bookId;
        cout << "Enter name and book id to borrow: ";
        cin >> name >> bookId;

        // Use lambda function here.
        //[id = bookId](const Book& book) -> bool {return book.id == id};
        //int i = find(bookList, bookList + nbrOfBooks, [id = bookId](const Book& book) -> bool {return book.id == id;});

        for (auto& book : bookList) {
            if (book.id == bookId) {
                book.nbrOfBorrowed++;
            }
        }

        for (auto& user : userList) {
            if (user.name == name) {
                user.borrowBook(bookId);
            }
        }
    }

    void user_return_book()
    {
        string name;
        int bookId;
        cout << "Enter name and book id to return: ";
        cin >> name >> bookId;

        for (auto& book : bookList) {
            if (book.id == bookId) {
                book.nbrOfBorrowed--;
            }
        }

        for (auto& user : userList) {
            if (user.name == name) {
                user.returnBook(bookId);
            }
        }
    }

    void print_users()
    {
        cout << "\n";
        for (int i = 0; i < nbrOfUsers; ++i)
            userList[i].print();
    }

    void print_who_borrowed_book_by_name()
    {
        string book_name;
        cout << "Enter book name: ";
        cin >> book_name;

        int book_idx = find_book_idx_by_name(book_name);

        if (book_idx == -1) {
            cout << "Invalid book name.\n";
            return;
        }
        int book_id = bookList[book_idx].id;

        if (bookList[book_idx].nbrOfBorrowed == 0) {
            cout << "No borrowed copies\n";
            return;
        }

        for (int i = 0; i < nbrOfUsers; ++i) {
            if (userList[i].is_borrowed(book_id))
                cout << userList[i].name << "\n";
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
            else if (choice == 3)
                print_who_borrowed_book_by_name();
            else if (choice == 4)
                print_library_by_id();
            else if (choice == 5)
                print_library_by_name();
            else if (choice == 6)
                add_user();
            else if (choice == 7)
                user_borrow_book();
            else if (choice == 8)
                user_return_book();
            else if (choice == 9)
                print_users();
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