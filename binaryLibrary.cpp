#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;


const string PASSWORD = "admin00";

struct Library{
    string code;
    string title;
    string author;
    string genre;
    string publicationYear;
};

//Todas las funciones
vector<Library> csvData(const string &bookslist);
void showBooks(const vector<Library> &books);
bool adminAccess(string &password);
void addBook(vector<Library> &books);
void editBook(vector<Library> &books);
void deleteBook(vector<Library> &books);
void exportBooks(vector<Library>& books, const string& criterion, const string& value);
void binarySearch(vector<Library>& books, const string& criterion, const string& value);
void sortBooks(vector<Library>& books, const string& criterion);
void validateInput();

int main(){
    string filename ="bookslist.csv", password;
    vector<Library> books = csvData(filename);
    string value,criterion;
    int option;

    do{
        cout << "\n**************Welcome to your library***************" << endl;
        cout << "\n1. Login as a user\n2. Login as an admin\n3. Exit" << endl;
        cout << "\nChoose your option: ";
        cin >> option;
        cin.ignore();

        validateInput();

        switch (option){
        case 1: {
            int optionUsers;
            bool back = true;
            
            while(back){
                cout << "\nUsers menu\n1. Show all books\n2. Search book\n3. Return\n\nChoose an option: ";
                cin >> optionUsers;
                cin.ignore();

                validateInput();

                switch (optionUsers){
                case 1:
                    showBooks(books);
                    break;
                case 2: {
                    int searchOption;
                    bool searchBack = true;

                    while(searchBack){
                        cout << "\nSearch by:\n1. Code\n2. Title\n3. Return\n\nChoose an option: ";
                        cin >> searchOption;
                        cin.ignore();

                        validateInput();

                        switch(searchOption){
                            case 1:
                                criterion = "code";
                                searchBack = false;
                                break;
                            case 2:
                                criterion = "title";
                                searchBack = false;
                                break;
                            case 3:
                                cout << "Returning..." << endl;
                                searchBack = false;
                                criterion = "";
                                system("cls");
                                break;
                            default:
                                cout << "Only options from 1 to 3 are accepted" << endl;
                                break;
                        }
                    }
                    if (!criterion.empty()){
                        cout << "Enter the value to search for: ";
                        getline(cin, value);
                        binarySearch(books, criterion, value);
                    }
                    break;
                }
                case 3:
                    cout << "Returning..." << endl;
                    back = false;
                    system("cls");
                    break;
                default:
                    cout << "Only options from 1 to 3 are accepted" << endl;
                    break;
                }
            }
        }
            break;
        case 2:{
            if(adminAccess(password)){
                int optionAdmin;
                bool back = true;
                
                while(back){
                    cout << "\nAdmin menu\n1. Show all books\n2. Search book\n3. Add books\n4. Edit information\n5. Delete information\n6. Export books\n7. Return \nChoose an option: " << endl;
                    cin >> optionAdmin;
                    cin.ignore();

                    validateInput();

                    switch (optionAdmin){
                    case 1:
                        showBooks(books);
                        break;
                    case 2:
                        cout << "Enter the criterion to search by (code, title): ";
                        cin >> criterion;
                        cin.ignore();
                        cout << "Enter the value to search for: ";
                        getline(cin, value);
                        binarySearch(books, criterion, value);
                        break;
                    case 3:
                        addBook(books);
                        break;
                    case 4:
                        editBook(books);
                        break;
                    case 5:
                        deleteBook(books);
                        break;
                    case 6: {
                        int exportOption;
                        bool exportBack = true;

                        while(exportBack){
                            cout << "\nExport by:\n1. Genre\n2. Author\n3. All Books\n4. Return\n\nChoose an option: ";
                            cin >> exportOption;
                            cin.ignore();

                            validateInput();

                            switch(exportOption){
                                case 1:
                                    criterion = "genre";
                                    exportBack = false;
                                    break;
                                case 2:
                                    criterion = "author";
                                    exportBack = false;
                                    break;
                                case 3:
                                    criterion = "all";
                                    exportBack = false;
                                    value = "all"; //Por modificar (Pedro)
                                    break;
                                case 4:
                                    cout << "Returning to previous menu..." << endl;
                                    exportBack = false;
                                    criterion = "";
                                    system("cls");
                                    break;
                                default:
                                    cout << "Only options from 1 to 4 are accepted" << endl;
                                    break;
                            }
                        }
                        if(!criterion.empty() && criterion != "all"){
                            cout << "Enter the value to export: ";
                            getline(cin, value);
                        }
                        if(!criterion.empty()){
                            exportBooks(books, criterion, value);
                        }
                        break;
                    }
                    case 7:
                        cout << "Returning..." << endl;
                        back = false;
                        system("cls");
                        break;
                    default:
                        cout << "Only options from 1 to 3 are accepted" << endl;
                        break;
                    }
                }
            }
        }
        break;
        case 3:
            cout << "Goodbye and thanks for reading books :)" << endl;
            break;
        default:
            cout << "Only options from 1 - 3 are accepted" << endl;
            break;
        }
    } while (option != 3);

return 0;
}

vector<Library> csvData(const string &bookslist){
    vector<Library> books;
    ifstream file(bookslist);
    string line;

    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        Library book;

        getline(ss, book.code, ',');
        getline(ss, book.title, ',');
        getline(ss, book.author, ',');
        getline(ss, book.genre, ',');
        getline(ss, book.publicationYear, ',');

        books.push_back(book);  
    }
    file.close();
    return books;
}

void showBooks(const vector<Library> &books){
    cout << left;
    cout << "\n" << setw(10) << "Code" << setw(85) << "Title" << endl;
    cout << string(95, '-') << endl; // Línea de separación

    for (const auto &book : books) {
        cout << setw(10) << book.code
             << setw(85) << book.title
             << endl;
    }
}

bool adminAccess(string &password){
    cout << "Enter password (or enter 'r' to return): ";
    cin >> password;

    while (password != PASSWORD){ 
        if (password == "R" || password == "r"){ 
            cout << "Returning to previous menu" << endl; 
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            return false;
        } 
        cout << "Incorrect password, please try again (or enter 'r' to cancel): "; 
        cin >> password; 
    }
    cout << "Access granted" << endl;
    return true;
}

void addBook(vector<Library> &books){
    Library newBook;

    cout<<"Enter the code of the book: ";
    cin>>newBook.code;
    cin.ignore();

    //validar si el codigo existe ya

    for(const auto &book : books){
        if(newBook.code == book.code){
            cout<<"The code already exists"<<endl;
            return;
        }
    }
    
    cout<<"Enter the title of the book: ";
    getline(cin, newBook.title);

    cout<<"Enter the author of the book: ";
    getline(cin, newBook.author);

    cout<<"Enter the genre of the book: ";
    getline(cin, newBook.genre);

    cout<<"Enter the publication year of the book: ";
    cin >> newBook.publicationYear;

    books.push_back(newBook);
    cout<<"Book added successfully!"<<endl;

}


void editBook(vector<Library> &books){
    string code;
    bool found = false;
    int size = books.size();
    cout<<"Enter the code of the book you want to edit: ";
    cin>>code;

    for(int i=0; i<size; i++){
        if(books[i].code == code){
            cout<<"Editing book: "<<books[i].title<<endl;
            cout<<"Enter the new title: ";
            cin.ignore();
            getline(cin, books[i].title);

            cout<<"Enter the new author (current: "<<books[i].author<<"): ";
            getline(cin, books[i].author);
            
            cout<<"Enter the new genre (current: "<<books[i].genre<<"): ";
            getline(cin, books[i].genre);

            cout<<"Enter the new publication year (current: "<<books[i].publicationYear<<"): ";
            cin>>books[i].publicationYear;

            found = true;
            break;
        }
    }

    if(!found){
        cout<<"Book with code "<<code<<" not found"<<endl;
    }
}



void deleteBook(vector<Library> &books) {
    string code;
    cout << "Enter the code of the book you want to delete: ";
    cin >> code;

    for (auto it = books.begin(); it != books.end(); ) {
        if (it->code == code) { // Accede al código del libro a través del iterador
            string answer;
            cout << "Are you sure you want to delete the book with code " << code << "? (y/n): ";
            cin >> answer;

            if (answer == "y" || answer == "Y") {
                it = books.erase(it);
                cout << "Book deleted successfully!"<<endl;
            } else if(answer == "n" || answer == "N"){
                cout << "Returning..." << endl;
                ++it;
            }else{
                cout << "Invalid option. Returning..." << endl;
                ++it;
            }
            return;
        } else {
            ++it;
        }
    }
        cout << "Book with code " << code << " not found."<<endl;
}


void sortBooks(vector<Library>& books, const string& criterion) {
    if (criterion == "code") {
        sort(books.begin(), books.end(), [](const Library& a, const Library& b) {
            return a.code < b.code;
        });
    } else if (criterion == "title") {
        sort(books.begin(), books.end(), [](const Library& a, const Library& b) {
            return a.title < b.title;
        });
    } else if (criterion == "author") {
        sort(books.begin(), books.end(), [](const Library& a, const Library& b) {
            return a.author < b.author;
        });
    } else if (criterion == "genre") {
        sort(books.begin(), books.end(), [](const Library& a, const Library& b) {
            return a.genre < b.genre;
        });
    }
}

void binarySearch(vector<Library>& books, const string& criterion, const string& value) {
    sortBooks(books, criterion); 

    auto it = lower_bound(books.begin(), books.end(), value, [criterion](const Library& book, const string& value) {
        if (criterion == "code") return book.code < value;
        if (criterion == "title") return book.title < value;
        return false;
    });

    if (it != books.end() && ((criterion == "code" && it->code == value) ||
                              (criterion == "title" && it->title == value))) {
        cout << "Book found:\n";
        cout << "Code: " << it->code << "\n";
        cout << "Title: " << it->title << "\n";
        cout << "Author: " << it->author << "\n";
        cout << "Genre: " << it->genre << "\n";
        cout << "Publication Year: " << it->publicationYear << "\n";
    } else {
        cout << "Book with " << criterion << " " << value << " not found.\n";
    }
}

void exportBooks(vector<Library>& books, const string& criterion, const string& value) {
    sortBooks(books, criterion);

    static int fileCount = 1;
    stringstream filename;
    filename << "exported_books_" << fileCount++ << ".csv";

    ofstream file(filename.str());

    if (!file.is_open()) {
        cout << "Error opening file " << filename.str() << " for writing.\n";
        return;
    }

    file << "Code,Title,Author,Genre,PublicationYear\n";
    bool found = false;

    auto it = lower_bound(books.begin(), books.end(), value, [criterion](const Library& book, const string& value) {
        if (criterion == "genre") return book.genre < value;
        if (criterion == "author") return book.author < value;
        return false;
    });

    while (it != books.end() && ((criterion == "genre" && it->genre == value) ||
                                 (criterion == "author" && it->author == value))) {
        file << it->code << "," << it->title << "," << it->author << ","
             << it->genre << "," << it->publicationYear << "\n";
        found = true;
        ++it;
    }

    file.close();

    if (found) {
        cout << "Books exported successfully to " << filename.str() << "!\n";
    } else {
        cout << "No books found with " << criterion << " " << value << ".\n";
    }
}

void validateInput(){
    if(cin.fail()){
        cout << "Fail, try an accepted option" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}