#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Book {
public:
    std::string title;
    std::string author;

    Book(std::string title, std::string author) : title(title), author(author) {}

    void displayBook() const {
        std::cout << "Title: " << title << ", Author: " << author << std::endl;
    }
};

class BookManager {
private:
    std::vector<Book> books;

public:
    void addBook(std::string title, std::string author) {
        books.emplace_back(title, author);
        std::cout << "Book '" << title << "' by " << author << " added." << std::endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library." << std::endl;
            return;
        }
        std::cout << "\n--- All Books ---" << std::endl;
        for (const auto& book : books) {
            book.displayBook();
        }
        std::cout << "-----------------" << std::endl;
    }

    void searchByTitle(std::string title) const {
        std::cout << "\n--- Search by Title: '" << title << "' ---" << std::endl;
        bool found = false;
        for (const auto& book : books) {
            if (book.title == title) {
                book.displayBook();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Book with title '" << title << "' not found." << std::endl;
        }
        std::cout << "---------------------------------" << std::endl;
    }

    void searchByAuthor(std::string author) const {
        std::cout << "\n--- Search by Author: '" << author << "' ---" << std::endl;
        bool found = false;
        for (const auto& book : books) {
            if (book.author == author) {
                book.displayBook();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No books found by author '" << author << "'." << std::endl;
        }
        std::cout << "-----------------------------------" << std::endl;
    }

    Book* getBookByTitle(std::string title) {
        for (auto& book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;
    }

    Book* getBookByAuthor(std::string author) {
        for (auto& book : books) {
            if (book.author == author) {
                return &book;
            }
        }
        return nullptr;
    }
};

class BorrowManager {
private:
    std::unordered_map<std::string, int> stock;

public:
    void initializeStock(const Book& book, int quantity = 3) {
        stock[book.title] = quantity;
        std::cout << "Stock for '" << book.title << "' initialized to " << quantity << " copies." << std::endl;
    }

    void borrowBook(std::string title) {
        if (stock.count(title)) {
            if (stock[title] > 0) {
                stock[title]--;
                std::cout << "Book '" << title << "' successfully borrowed. Remaining stock: " << stock[title] << std::endl;
            }
            else {
                std::cout << "Book '" << title << "' is currently out of stock." << std::endl;
            }
        }
        else {
            std::cout << "Book '" << title << "' not found in stock management." << std::endl;
        }
    }

    void returnBook(std::string title) {
        if (stock.count(title)) {
            stock[title]++;
            std::cout << "Book '" << title << "' successfully returned. Current stock: " << stock[title] << std::endl;
        }
        else {
            std::cout << "Book '" << title << "' not found in stock management." << std::endl;
        }
    }

    void displayStock() const {
        if (stock.empty()) {
            std::cout << "Stock management is empty." << std::endl;
            return;
        }
        std::cout << "\n--- Current Stock ---" << std::endl;
        for (const auto& pair : stock) {
            std::cout << "Title: " << pair.first << ", Stock: " << pair.second << std::endl;
        }
        std::cout << "---------------------" << std::endl;
    }

    bool isBookAvailable(std::string title) const {
        auto it = stock.find(title);
        if (it != stock.end()) {
            return it->second > 0;
        }
        return false;
    }
};

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    bookManager.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    bookManager.addBook("1984", "George Orwell");
    bookManager.addBook("To Kill a Mockingbird", "Harper Lee");
    bookManager.addBook("Animal Farm", "George Orwell");

    bookManager.displayAllBooks();

    Book* book1 = bookManager.getBookByTitle("The Great Gatsby");
    if (book1) borrowManager.initializeStock(*book1);

    Book* book2 = bookManager.getBookByTitle("1984");
    if (book2) borrowManager.initializeStock(*book2);

    Book* book3 = bookManager.getBookByTitle("To Kill a Mockingbird");
    if (book3) borrowManager.initializeStock(*book3);

    Book* book4 = bookManager.getBookByTitle("Animal Farm");
    if (book4) borrowManager.initializeStock(*book4);


    borrowManager.displayStock();

    std::cout << "\n--- Testing Search Functions ---" << std::endl;
    bookManager.searchByTitle("1984");
    bookManager.searchByTitle("Non Existent Book");
    bookManager.searchByAuthor("George Orwell");
    bookManager.searchByAuthor("Jane Austen");
    std::cout << "--------------------------------" << std::endl;

    std::cout << "\n--- Testing Borrow/Return Functions ---" << std::endl;

    std::string borrowTitle1 = "The Great Gatsby";
    std::string borrowTitle2 = "1984";
    std::string borrowTitle3 = "Non Existent Book";
    std::string borrowTitle4 = "Animal Farm";

    std::cout << "\nChecking availability for '" << borrowTitle1 << "': "
        << (borrowManager.isBookAvailable(borrowTitle1) ? "Available" : "Not Available") << std::endl;
    borrowManager.borrowBook(borrowTitle1);
    borrowManager.borrowBook(borrowTitle1);
    borrowManager.borrowBook(borrowTitle1);
    borrowManager.borrowBook(borrowTitle1);

    std::cout << "\nChecking availability for '" << borrowTitle1 << "': "
        << (borrowManager.isBookAvailable(borrowTitle1) ? "Available" : "Not Available") << std::endl;

    borrowManager.borrowBook(borrowTitle2);

    std::cout << "\nChecking availability for '" << borrowTitle3 << "': "
        << (borrowManager.isBookAvailable(borrowTitle3) ? "Available" : "Not Available") << std::endl;
    borrowManager.borrowBook(borrowTitle3);

    Book* bookByAuthor = bookManager.getBookByAuthor("George Orwell");
    if (bookByAuthor) {
        std::cout << "\nFound book by George Orwell: '" << bookByAuthor->title << "'" << std::endl;
        std::cout << "Checking availability for '" << bookByAuthor->title << "': "
            << (borrowManager.isBookAvailable(bookByAuthor->title) ? "Available" : "Not Available") << std::endl;
        borrowManager.borrowBook(bookByAuthor->title);
    }
    else {
        std::cout << "\nNo book found by George Orwell (for borrow test)." << std::endl;
    }

    borrowManager.borrowBook(borrowTitle4);

    borrowManager.displayStock();

    borrowManager.returnBook(borrowTitle1);
    borrowManager.returnBook(borrowTitle2);
    borrowManager.returnBook(borrowTitle3);

    borrowManager.displayStock();

    std::cout << "-------------------------------------" << std::endl;

    return 0;
}
