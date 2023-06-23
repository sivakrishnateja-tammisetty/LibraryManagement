#include <iostream>
#include <vector>
#include <algorithm>
#include<ctime>
#include<sstream>
#include<iomanip>
using namespace std;
class Book {
public:
string title;
string author;
string ISBN;
bool available;
time_t borrowed_date;
time_t returned_date;
Book(string userGivenTitle, string userGivenAuthor, string userGivenISBN): title{userGivenTitle}, author{userGivenAuthor}, ISBN{userGivenISBN}, available{true}, borrowed_date{0}, returned_date{0} {}

string getTitle() const {
        return title;
}

string getAuthor() const {
        return author;
}

string getISBN() const {
        return ISBN;
}

 bool isAvailable() const {
        return available;
}

void setAvailable(bool status) {
        available = status;
}

void set_BorrowedDate() {
        borrowed_date = time(0);
}

void set_ReturnedDate() {
        returned_date = time(0);
}

string get_FormattedDate(time_t date) const {
        tm* dt = localtime(&date);
        stringstream stream;
        stream << put_time(dt, "%Y-%m-%d %H:%M:%S");
        return stream.str();
}

string get_BorrowedDate() const {
        return get_FormattedDate(borrowed_date);
}

string get_ReturnedDate() const {
        return get_FormattedDate(returned_date);
}
};
class Borrower {
public:
string name;
string contactInfo;
Borrower(string userName, string  userContactInfo): name{userName}, contactInfo{userContactInfo} {}
string getName()const {
        return name;
}

string getContactInfo()const {
        return contactInfo;
}
};
class Library {
private:
vector<Book> books;
vector<Borrower> borrowers;
public:
void addBook(string title,string author,string ISBN) {
        books.push_back(Book(title, author, ISBN));
        cout<<"["<<title<<" Book] was  added successfully "<<endl;
}

void updateBook(string ISBN,string title,string author) {
        auto it =find_if(books.begin(), books.end(), [&ISBN](const Book& book) { return book.getISBN() == ISBN; });
        if (it != books.end()) {
            it->title = title;
            it->author = author;
            cout << "Book updated successfully.\n";
        }
       	else
       	{
           cout << "Book not found.\n";
        }
}

void removeBook(string ISBN) {
        auto it = find_if(books.begin(), books.end(), [&ISBN](const Book& book) { return book.getISBN() == ISBN; });
        if (it != books.end()) {
            books.erase(it);
            cout << "Book removed successfully.\n";
        }
       	else
       	{
            cout << "Book not found.\n";
        }
}
void searchBooksByTitle( string title) {
        cout << "Search Results:\n";
        bool found=false;
        for (const Book& book : books) {
            if (book.getTitle() == title) {
                cout<<"Book was found with provided title\n";
                cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << "\n";
                found=true;
            }
  }
       if(!found)
        {
            cout<<"No books found with that title\n";
        }
    }
void searchBooksByAuthor(string author) {
        cout << "Search Results:\n";
        bool found=false;
        for (const Book& book : books) {
            if (book.getAuthor() == author) {
                cout<<"Book was found with provided Author name\n";
                cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << "\n";
                found=true;
            }
        }
        if(!found)
        {
            cout<<"Book was not found with given Author name\n";
        }
}

void searchBooksByISBN(string ISBN) {
        cout << "Search Results:\n";
	bool found=false;
        for ( Book book : books) {
            if (book.getISBN() == ISBN) {
		    found=true;
                cout<<"Book was found with provided ISBN"<<endl;
               cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << "\n";
               break;
              
            }
	}
	if(!found)
            {
                 cout<<"Book was not found with provided ISBN number\n";
            }
}

void addBorrower(string name,string contactInfo) {
  borrowers.emplace_back(Borrower(name, contactInfo));
  cout << "Borrower added successfully.\n";
}

void updateBorrower(string name,  string contactInfo) {
        auto it = find_if(borrowers.begin(), borrowers.end(), [&name](Borrower borrower) { return borrower.getName() == name; });
        if (it != borrowers.end()) 
	{
            it->contactInfo = contactInfo;
           cout << "Borrower updated successfully.\n";
        }
       	else
       	{
           cout << "Borrower not found.\n";
        }
}
void removeBorrower( string name) {
        auto it = find_if(borrowers.begin(), borrowers.end(), [&name](Borrower borrower) { return borrower.getName() == name; });
        if (it != borrowers.end())
       	{
            borrowers.erase(it);
            cout << "Borrower removed successfully.\n";
        }
       	else
       	{
            cout << "Borrower not found.\n";
        }
}

void searchBorrowersByName( const string& name)
{
        bool found=false;
        cout << "Search Results:\n";
        for ( const Borrower &borrower : borrowers)
       	{
            if (borrower.getName() == name)
	    {
                cout << "Name: " << borrower.getName() << ", Contact Info: " << borrower.getContactInfo() << "\n";
                found=true;
            }
        }
        if(!found)
        {
            cout << "No borrowers found with the given name.\n";
        }
}

void borrowBook(string title, string name) {
        auto bookIt = find_if(books.begin(), books.end(), [&title](Book& book) { return book.getTitle() == title && book.isAvailable(); });

        if (bookIt != books.end())
       	{
            auto borrowerIt = find_if(borrowers.begin(), borrowers.end(), [&name](const Borrower& borrower) { return borrower.getName() == name; });

            if (borrowerIt != borrowers.end())
	    {
                bookIt->setAvailable(false);
                bookIt->set_BorrowedDate();
                cout << "Book borrowed successfully.\n";
                cout << "Borrowed Date: " << bookIt->get_BorrowedDate() << "\n";
            }
	    else
	    {
                cout << "Borrower not found.\n";
            }
        }
       	else
       	{
            cout << "Book not available.\n";
        }
}

void returnBook(string title)
{
        auto it = find_if(books.begin(), books.end(), [&title](Book& book) { return book.getTitle() == title && !book.isAvailable(); });
        if (it != books.end())
       	{
            it->setAvailable(true);
            it->set_ReturnedDate();
            cout << "Book returned successfully.\n";
            cout << "Returned Date: " << it->get_ReturnedDate() << "\n";
        }
       	else
       	{
            cout << "Invalid book or book is already available.\n";
        }
}
void generateReportAllBooks()
{
        if(books.empty())
        {
            cout<<"No Books Available"<<endl;
        }
        else
        {
        cout << "All Books:\n";
        for (Book book : books)
       	{
            cout<<"-------------------------------------------------\n";
            cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << "\n";
            if (!book.isAvailable()) {
                cout << "Borrowed Date: " << book.get_BorrowedDate() << "\n";
                cout << "Returned Date: " << book.get_ReturnedDate() << "\n";
            }
        }
        cout<<"----------------------------------------------------\n";
        }
}
 
void generateReportAvailableBooks()
{
        cout << "Available Books:\n";
        for (Book book : books)
       	{
            if (book.isAvailable())
	    {
                cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << "\n";
            }
        }
}

void generateReportBorrowedBooks()
{
        bool found=false;
        cout << "Borrowed Books:\n";
        for (Book book : books)
       	{
            if (book.isAvailable())
	    {
               cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << "\n";
               found=true;
            }
        }
        if(!found)
	{
                cout<<"No borrowed books\n";
        }

    }
};
int main()
{
Library library;
int choice = 0;

while (choice != 20)
{
        cout <<"------Library Management System-------\n";
        cout << "1. Add Book\n";
        cout << "2. Update Book\n";
        cout << "3. Remove Book\n";
        cout << "4. Generate Report Available Books\n";
        cout << "5. Generate Report All Books\n";
        cout<<"6. Search Books By Title\n";
        cout<<"7. Search Book By Author\n";
        cout<<"8. Search Book By ISBN\n";
        cout<<"9. Add Borrower\n";
        cout<<"10. Update Borrower\n";
        cout<<"11. Generate Report Borrowed Books\n";
        cout<<"12. Remove Borrower\n";
        cout<<"13. Search Borrower By Name\n";
        cout<<"14. Borrow Book\n";
        cout<<"15. Return Book\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
       	{
            case 1:
		    {
                cout<<"You selcted to add a book\n";
                cout<<"-------------------------\n";
                string title, author, isbn;
                cout <<"\nEnter Title:";
                getline(cin, title);
                cout << "Enter Author:";
                getline(cin, author);
                cout << "Enter ISBN: ";
                getline(cin, isbn);
                library.addBook(title, author, isbn);
                break;
            }
            case 2:
		    {
                cout<<"You selected to update book based on ISBN:\n";
                cout<<"------------------------------------------\n";
                string searchISBN, newTitle, newAuthor;
                cout << "Enter the ISBN of the book you want to update: ";
                getline(cin, searchISBN);
                cout << "Enter the new details of the book to modify:\n";
                cout << "New Title: ";
                getline(cin, newTitle);
                cout << "New Author: ";
                getline(cin, newAuthor);
                library.updateBook(searchISBN, newTitle, newAuthor);
                break;
            }
            case 3:
		    {
                cout<<"You selected to remove book based on ISBN\n";
                cout<<"------------------------------------------\n";
                string removeISBN;
                cout << "Enter the ISBN of the book you want to remove: ";
                getline(cin, removeISBN);
                library.removeBook(removeISBN);
                break;
            }
            case 4:
		    {
                cout<<"You selected to generate to report all books\n";
                cout<<"--------------------------------------------\n";
                library.generateReportAllBooks();
                break;
            }
            case 5:
		    {
                cout << "You selected to Generate all available books\n";
                cout<<"----------------------------------------------\n";
                library.generateReportAllBooks();
                break;
            }
            case 6:
            {
                cout<<"you selected to search a book by Title\n";
                cout<<"--------------------------------------\n";
                string title;
                cout<<"Enter title:";
                getline(cin,title);
                library.searchBooksByTitle(title);
                break;
            }
            case 7:
            {
                cout<<"You selected to search a book by Author Name\n";
                cout<<"--------------------------------------------\n";
                string author_name;
                cout<<"Enter Author name:";
                cin>>author_name;
                library.searchBooksByAuthor(author_name);
                break;
            }
            case 8:
            {
                cout<<"You selected to search a book by ISBN\n";
                cout<<"-------------------------------------\n";
                string num;
                cout<<"Enter an ISBN NUmber:";
                getline(cin,num);
                library.searchBooksByISBN(num);
                break;
                
            }
            case 9:
            {
                cout<<"You selected to add brower information:\n";
                cout<<"---------------------------------------\n";
                string name,contact;
                cout<<"Enter your name:";
                getline(cin,name);
                cout<<"Enter your contact info:";
                getline(cin,contact);
                library.addBorrower(name,contact);
                break;
            }
            case 10:
            {
            cout<<"You selected to update borrower information based on name:\n";
            cout<<"-------------------------------------------------------------\n";
            string updated_name,newContactInfo;
            cout<<"Enter updated name:";
            getline(cin,updated_name);
            cout<<"Enter updated contact info:";
            getline(cin,newContactInfo);
            library.updateBorrower(updated_name,newContactInfo);
            break;
            }
            case 11:
            {
                cout<<"You selected to Generate Report of Borrowed Books\n";
                cout<<"-------------------------------------------------\n";
                library.generateReportBorrowedBooks();
                break;
            }
            case 12:
            {
                cout<<"You selected to remove borrower:\n";
                cout<<"--------------------------------\n";
                string name;
                cout<<"Enter name:";
                getline(cin,name);
                library.removeBorrower(name);
                break;
            }
            case 13:
            {
                cout<<"You selected to search Borrower by his name:\n";
                cout<<"--------------------------------------------\n";
                string name;
                cout<<"Enter name you want to search in borrowers list:";
                getline(cin,name);
                library.searchBorrowersByName(name);
                break;
            }
            case 14:
            {
                cout<<"You selected to borrow a book\n";
                cout<<"-----------------------------\n";
                string book_title,borrower_name;
                cout<<"Enter which book you want to borrow:";
                getline(cin,book_title);
                cout<<"Enter person name who taking book:";
                getline(cin,borrower_name);
                library.borrowBook(book_title,borrower_name);
                break;
            }
            case 15:
            {
                cout<<"You selected to return a book\n";
                cout<<"-----------------------------\n";
                string book_title;
                cout<<"Enter which book you want to return:";
                getline(cin,book_title);
                library.returnBook(book_title);
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
        cout << "\n";
    }
    return 0;
}


       


