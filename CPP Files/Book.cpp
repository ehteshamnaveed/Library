#include "Book.h"

// + +  Book Management Class Function  + + // 

                                                         ////////////    Default Constructor
Book_Management::Book_Management()
{
    book_Id = 0;
    Year = 0;
    Available = 0;

    Title = "";
    Author = "";
    Category = "";
}

void Book_Management::get_Book()
{
    cout << "\tEnter Book Title : ";
    cin.clear();
    getline(cin, Title);

    cout << "\tEnter Book Author : ";
    cin.clear();  getline(cin, Author);

    cout << "\tEnter Book Category : ";
    cin.clear();
    getline(cin, Category);

    cout << "\tEnter Book Year";
    getChoice(Year);

    cout << "\tEnter Book Quantity";
    getChoice(Available);

    cout << endl;
}

////////////    Add User to file Function
void Book_Management::add_Book()
{
    ofstream fout;
    get_Book_Id();
    get_Book(); // Getting user  information

    fout.open("Book.dat", ios::app | ios::binary);
    fout.write((char*)this, sizeof(Book_Management));
    cout << "Book data saved in file...\n";
    fout.close();
}

////////////    Display Book from file Function
void Book_Management::display_Book()
{
    int rec = 0;
    ifstream fin;
    fin.open("Book.dat", ios::in | ios::binary);

    if (!fin)
        cout << "File not found" << endl;

    else
    {
        book_Header();
        while (fin.read((char*)this, sizeof(Book_Management))) // Reading Book data from file) 
        {
            list_Books(); // Displaying Book inforamtion
            rec++;
        }

        fin.close();
        cout << "\nTotal " << rec << " Records in file...\n";
    }
}

////////////    Display Books Information Function
void Book_Management::list_Books()
{
    cout.setf(ios::left);
    cout << setw(8) << book_Id
        << setw(20) << Title
        << setw(20) << Author
        << setw(15) << Category
        << setw(8) << Year
        << setw(8) << Available
        << endl;
}

////////////    Deleting Book Function
void Book_Management::delete_Book(int t)
{
    char option;
    int flag = 0;
    ifstream fin;
    ofstream fout;

    fout.open("tempBook.dat", ios::out | ios::binary); // Creating a temporary file
    fin.open("Book.dat", ios::in | ios::binary);

    if (!fin)
        cout << "File not found" << endl;

    else
    {
        while (fin.read((char*)this, sizeof(Book_Management))) // Reading Book data file 
        {
            if (t == book_Id)
            {
                flag++;
                do
                {
                    cout << "Following data will be edited...\n\n"; // Showing the current data
                    book_Header();
                    list_Books();
                    cout << "\n\nWARNING! Following record will be deleted\n";
                Tryagain:
                    cout << " Do you want to delete? (y/n): ";
                    getChoice(option);

                    switch (option)
                    {
                    case 'y':
                        fin.close();
                        fin.open("Book.dat", ios::in | ios::binary);
                        while (fin.read((char*)this, sizeof(Book_Management)))
                        {
                            if (t != book_Id)
                                fout.write((char*)this, sizeof(Book_Management));
                        }
                        fout.close();
                        fin.close();

                        remove("Book.dat");
                        rename("tempBook.dat", "Book.dat");

                        cout << "\nDeleted successfully! \n";
                        option = 'n';
                        break;

                    case 'n':
                        cout << "\nRequest Reverted\n";
                        fin.close();
                        fout.close();
                        remove("tempBook.dat");
                        _getch();
                        break;

                    default:
                        cout << "Error: choose (y/n)\n\n";
                        goto Tryagain;

                    }
                } while (option != 'n');
            }
        }
    }
    if (flag == 0)
    {
        cout << "Book Number with ID:" << t << " not available...\n";
        _getch();
    }
}

////////////    Deleting Book Function
void Book_Management::modify_Book_Record(int t)
{
    ifstream fin;
    ofstream fout;

    fout.open("tempBook.dat", ios::out | ios::binary); // Creating a temporary file
    fin.open("Book.dat", ios::in | ios::binary); // Opening Book file

    if (!fin)
        cout << "File not found" << endl;

    else
    {
        fin.read((char*)this, sizeof(Book_Management));
        while (!fin.eof()) // Reading Book data file 
        {
            if (t != book_Id)
                fout.write((char*)this, sizeof(Book_Management));
            fin.read((char*)this, sizeof(Book_Management));
        }
        fout.close();
        fin.close();

        remove("Book.dat");
        rename("tempBook.dat", "Book.dat");
    }
}

////////////    Modifying Book Function
void Book_Management::modify_Book()
{
    int n, flag = 0, pos, temp;
    char choice;
    fstream fin, fou;
    fin.open("Book.dat", ios::in | ios::binary); // Opening Book data file
    cout << "Enter Book ID ";
    getChoice(n);

    fin.read((char*)this, sizeof(Book_Management));
    while (!fin.eof())
    {
        if (n == book_Id) // Searching with student I.D
        {
            pos = fin.tellg();
            pos = pos - sizeof(Book_Management);
            flag++;

            do
            {
                cout << "Following data will be edited...\n\n"; // Showing the current data
                book_Header();
                list_Books();
                fin.close();
            Tryagain:
                cout << "\n\n Want to edit user? (y/n): ";
                getChoice(choice);

                switch (choice)
                {
                case 'y':
                    modify_Book_Record(n);

                    fin.open("Book.dat", ios::in | ios::binary); // Opening Book data file
                    fou.open("tempBook.dat", ios::in | ios::app | ios::binary); // Opening Book data file

                    fin.read((char*)this, sizeof(Book_Management));
                    while (!fin.eof())
                    {
                        temp = fin.tellg();
                        fou.write((char*)this, sizeof(Book_Management)); // writing the new data
                        if (pos == temp)
                        {
                            fou.seekp(temp - sizeof(Book_Management));
                            get_Book_Id();
                            get_Book();
                            fou.write((char*)this, sizeof(Book_Management)); // writing the new data
                        }
                        fin.read((char*)this, sizeof(Book_Management));
                    }
                    fin.close();
                    fou.close();
                    remove("Book.dat");
                    rename("tempBook.dat", "Book.dat");
                    cout << "\nData Modified successfully...\n";
                    choice = 'n';
                    break;

                case 'n':
                    cout << "\nRequest Reverted\n";
                    break;

                default:
                    cout << "Error: Answer in (y/n)\n";
                    goto Tryagain;
                }
            } while (choice != 'n');

        }
        fin.read((char*)this, sizeof(Book_Management));
    }

    if (flag == 0)
        cout << "Book Number with ID:" << n << " not available...\n";
    _getch();
}

////////////    Searh by Id Function
void Book_Management::search_By_Book_Id()
{
    int flag = 0, n;
    ifstream fin("Book.dat");
    cout << "Enter Book I.D "; // Input for Book Id
    getChoice(n);
    book_Header();

    while (fin.read((char*)this, sizeof(Book_Management)))
    {
        if (n == book_Id) // Comparing will all Book records
        {
            list_Books();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with I.D : " << n << " not available...\n";
    _getch();
}

////////////    Searh by year Function
void Book_Management::search_By_Year()
{
    int flag = 0, n;
    ifstream fin("Book.dat");
    cout << "Enter Publishing year "; // Input for Book year
    getChoice(n);
    book_Header();

    while (fin.read((char*)this, sizeof(Book_Management)))
    {
        if (n == Year) // Comparing will all Book records
        {
            list_Books();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book of Year : " << n << " not available...\n";
    _getch();
}

////////////    Searh by Name Function
void Book_Management::search_By_Book_Name()
{
    int flag = 0;
    string n;
    ifstream fin("Book.dat");
    cout << "Enter Book Name : "; // Input for Book name
    cin.clear();
    getline(cin, n);
    book_Header();

    while (fin.read((char*)this, sizeof(Book_Management)))
    {
        if (n == Title) // Comparing will all Book records
        {
            list_Books();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Name : " << n << " not available...\n";
    _getch();
}

////////////    Searh by Name Function
void Book_Management::search_By_Author_Name()
{
    int flag = 0;
    string n;
    ifstream fin("Book.dat");
    cout << "Enter Author Name : "; // Input for Author name
    cin.clear();
    getline(cin, n);
    book_Header();

    while (fin.read((char*)this, sizeof(Book_Management)))
    {
        if (n == Author) // Comparing will all Book records
        {
            list_Books();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Author Name : " << n << " not available...\n";
    _getch();
}

////////////    Searh by Category Function
void Book_Management::search_By_Category()
{
    int flag = 0;
    string n;
    ifstream fin("Book.dat");
    cout << "Enter Category Name : ";
    cin.clear();  cin.ignore(INT_MAX, '\n'); // Input for Category
    getline(cin, n);
    book_Header();

    while (fin.read((char*)this, sizeof(Book_Management)))
    {
        if (n == Category) // Comparing will all Book records
        {
            list_Books();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book of Category : " << n << " not available...\n";
    _getch();
}

////////////    Searh by Reserch Paper Function
void Book_Management::search_Reserch_Paper()
{
    int flag = 0, y;
    string n;
    ifstream fin("Book.dat");
    cout << "Enter Category Name : ";
    cin.clear();  cin.ignore(INT_MAX, '\n'); // Input for Category
    getline(cin, n);
    cout << "Enter Publishing Year : "; // Input for Publishing year
    getChoice(y);
    book_Header();

    while (fin.read((char*)this, sizeof(Book_Management)))
    {
        if (n == Category && y == Year) // Comparing will all Book records
        {
            list_Books();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book of Category : " << n << " not available...\n";
    _getch();
}

////////////    Unique I.D check Function
void Book_Management::get_Book_Id()
{
    int id;
    ifstream fin;
    fin.open("Book.dat");

EnterAgain:
    try
    {
        cout << "\tEnter Book Id";
        getChoice(id);

        fin.seekg(ios::beg);
        while (fin.read((char*)this, sizeof(Book_Management)))
        {
            if (id == book_Id)
                throw 'E';
        }
        book_Id = id;
        fin.close();
    }
    catch (...)
    {
        cout << "\tERROR: I.D exist already! Try Again...\n\n";
        goto EnterAgain;
    }
}