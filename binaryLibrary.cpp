#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
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

int main(){
    string filename = "bookslist.csv", password;
    vector<Library> books = csvData(filename);

    int option;

    do{
        cout << "\n**************Welcome to your library***************" << endl;
        cout << "\n1. Login as a user\n2. Login as an admin\n3. Exit" << endl;
        cout << "\nChoose your option: ";
        cin >> option;
        cin.ignore();

        if(cin.fail()){
            cout << "Fail, try an accepted option" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (option){
        case 1: {
            int optionUsers;
            bool back = true;
            
            while(back){
                cout << "\nUsers menu\n1. Show all books\n2. Search book by its code\n3. Return\nChoose an option: " << endl;
                cin >> optionUsers;
                cin.ignore();

                if(cin.fail()){
                    cout << "Fail, try an accepted option" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                switch (optionUsers){
                case 1:
                    showBooks(books);
                    break;
                case 2:
                    //funcion Pedro
                    break;
                case 3:
                    cout << "Returning..." << endl;
                    back = false;
                    break;
                default:
                    cout << "Only options from 1 to 3 are accepted" << endl;
                    break;
                }
            }
        }
            break;
        case 2:{
            adminAccess(password);
            int optionAdmin;
            bool back = true;
            
            while(back){
                cout << "\nAdmin menu\n1. Show all books\n2. Search book by its code\n3. Add books\n4. Edit information\n5. Delete information\n6. Export books\n7. Return \nChoose an option: " << endl;
                cin >> optionAdmin;
                cin.ignore();

                if(cin.fail()){
                    cout << "Error al leer los datos" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                switch (optionAdmin){
                case 1:
                    showBooks(books);
                    break;
                case 2:
                    //funcion Pedro
                    break;
                case 3:
                    //funcion Valeria
                    break;
                case 4:
                    //funcion Valeria
                    break;
                case 5:
                    //funcion Valeria
                    break;
                case 6:
                    //funcion Pedro
                    break;    
                case 7:
                    cout << "Returning..." << endl;
                    back = false;
                    break;
                default:
                    cout << "Only options from 1 to 3 are accepted" << endl;
                    break;
                }
            }
        }
        break;
        case 3:
            cout << "Goodbye and thank you for reading books :)" << endl;
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
    for(const auto &book : books){
        cout << "\n--------------------------------------------------------------------------------------" 
             << "\nCode's book: " << book.code << "\nTitle: " << book.title 
             << "\n--------------------------------------------------------------------------------------" << endl; 
    }
}

bool adminAccess(string &password){
    cout << "Enter password (or enter 'r' to return): ";
    cin >> password;

    while (password != PASSWORD) { 
        if (password == "R" || password == "r") { 
            cout << "R" << endl; 
            return false;
        } 
        cout << "Incorrect password, please try again (or enter 'r' to cancel): "; 
        cin >> password; 
    }
    return true;
}

void addBook(vector<Library> &books){
    Library newBook;

    cout<<"Enter the coide of the book: ";
    cin>>newBook.code;

    cout<<"Enter the title of the book: ";
    cin.ignore();
    getline(cin, newBook.title);

    cout<<"Enter the author of the book: ";
    cin.ignore();
    getline(cin, newBook.author);

    cout<<"Enter the genre of the book: ";
    cin.ignore();
    getline(cin, newBook.genre);

    cout<<"Enter the publication year of the book: ";
    cin >> newBook.publicationYear;

    books.push_back(newBook);
    cout<<"Book added successfully!"<<endl;

}


void editBook(vector<Library> &books);
void deleteBook(vector<Library> &books);