#include "User.h"

// + +  User Management Class Function  + + // 

                                                         ////////////    Default Constructor
User_Management::User_Management()
{
    user_Id = 0;
    user_Name = "";
    department = "";
}

void User_Management::get_User()
{
    cout << "\tEnter User Name : ";
    cin.clear();
    getline(cin, user_Name);

    cout << "\tEnter Department Name : ";
    cin.clear();
    getline(cin, department);

    cout << "\n";
}

////////////    Add User to file Function
void User_Management::add_User()
{
    ofstream fout;
    get_User_Id();
    get_User(); // Getting User  information

    fout.open("User.dat", ios::app | ios::binary);
    fout.write((char*)this, sizeof(User_Management));
    cout << "User data saved in file...\n";
    fout.close();
}

////////////    Display User from file Function
void User_Management::display_User()
{
    int rec = 0;
    ifstream fin;
    fin.open("User.dat", ios::in | ios::binary);

    if (!fin)
        cout << "File not found" << endl;

    else
    {
        user_Header();
        while (fin.read((char*)this, sizeof(User_Management))) // Reading User data from file) 
        {
            list_Users(); // Displaying User inforamtion
            rec++;
        }

        fin.close();
        cout << "\nTotal " << rec << " Records in file...\n";
    }
}

////////////    Display Users Information Function
void User_Management::list_Users()
{
    cout.setf(ios::left);
    cout << setw(8) << user_Id
        << setw(20) << user_Name
        << setw(20) << department
        << "\n";
}

////////////    Deleting User Function
void User_Management::delete_User(int t)
{
    char option;
    int flag = 0;
    ifstream fin;
    ofstream fout;

    fout.open("tempUser.dat", ios::out | ios::binary); // Creating a temporary file
    fin.open("User.dat", ios::in | ios::binary);

    if (!fin)
        cout << "File not found" << "\n";

    else
    {
        while (fin.read((char*)this, sizeof(User_Management))) // Reading User data file 
        {
            if (t == user_Id)
            {
                flag++;
                do
                {
                    cout << "Following data will be edited...\n\n"; // Showing the current data
                    user_Header();
                    list_Users();
                    cout << "\n\nWARNING! Following record will be deleted\n";
                Tryagain:
                    cout << " Do you want to delete? (y/n): ";
                    getChoice(option);

                    switch (option)
                    {
                    case 'y':
                        fin.close();
                        fin.open("User.dat", ios::in | ios::binary);
                        while (fin.read((char*)this, sizeof(User_Management)))
                        {
                            if (t != user_Id)
                                fout.write((char*)this, sizeof(User_Management));
                        }
                        fout.close();
                        fin.close();

                        remove("User.dat");
                        rename("tempUser.dat", "User.dat");

                        cout << "\nDeleted successfully! \n";
                        option = 'n';
                        break;

                    case 'n':
                        cout << "\nRequest Reverted\n";
                        fin.close();
                        fout.close();
                        remove("tempUser.dat");
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
        cout << "User with ID:" << t << " not available...\n";
        _getch();
    }
}

////////////    Deleting User Function
void User_Management::modify_User_Record(int t)
{
    ifstream fin;
    ofstream fout;

    fout.open("tempUser.dat", ios::out | ios::binary); // Creating a temporary file
    fin.open("User.dat", ios::in | ios::binary); // Opening User file

    if (!fin)
        cout << "File not found" << endl;

    else
    {
        fin.read((char*)this, sizeof(User_Management));
        while (!fin.eof()) // Reading User data file 
        {
            if (t != user_Id)
                fout.write((char*)this, sizeof(User_Management));
            fin.read((char*)this, sizeof(User_Management));
        }
        fout.close();
        fin.close();

        remove("User.dat");
        rename("tempUser.dat", "User.dat");
    }
}

////////////    Modifying User Function
void User_Management::modify_User()
{
    int n, flag = 0, pos, temp;
    char choice;
    fstream fin, fou;
    fin.open("User.dat", ios::in | ios::binary); // Opening User data file
    cout << "Enter User ID ";
    getChoice(n);

    fin.read((char*)this, sizeof(User_Management));
    while (!fin.eof())
    {
        if (n == user_Id) // Searching with student I.D
        {
            pos = fin.tellg();
            pos = pos - sizeof(User_Management);
            flag++;

            do
            {
                cout << "Following data will be edited...\n\n"; // Showing the current data
                user_Header();
                list_Users();
                fin.close();
            Tryagain:
                cout << "\n\n Want to edit User? (y/n)";
                getChoice(choice);

                switch (choice)
                {
                case 'y':
                    modify_User_Record(n);

                    fin.open("User.dat", ios::in | ios::binary); // Opening User data file
                    fou.open("tempUser.dat", ios::in | ios::app | ios::binary); // Opening User data file

                    fin.read((char*)this, sizeof(User_Management));
                    while (!fin.eof())
                    {
                        temp = fin.tellg();
                        fou.write((char*)this, sizeof(User_Management)); // writing the new data
                        if (pos == temp)
                        {
                            fou.seekp(temp - sizeof(User_Management));
                            get_User_Id();
                            get_User();
                            fou.write((char*)this, sizeof(User_Management)); // writing the new data
                        }
                        fin.read((char*)this, sizeof(User_Management));
                    }
                    fin.close();
                    fou.close();
                    remove("User.dat");
                    rename("tempUser.dat", "User.dat");
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
        fin.read((char*)this, sizeof(User_Management));
    }

    if (flag == 0)
        cout << "User with ID:" << n << " not available...\n";
    _getch();
}

////////////    Searh by Id Function
void User_Management::search_By_User_Id()
{
    int flag = 0, n;
    ifstream fin("User.dat");
    cout << "Enter User I.D "; // Input for User Id
    getChoice(n);
    user_Header();

    while (fin.read((char*)this, sizeof(User_Management)))
    {
        if (n == user_Id) // Comparing will all User records
        {
            list_Users();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "User with I.D : " << n << " not available...\n";
    _getch();
}

////////////    Searh by Name Function
void User_Management::search_By_User_Name()
{
    int flag = 0;
    string n;
    ifstream fin("User.dat");
    cout << "Enter User Name : "; // Input for User name
    cin.clear();
    getline(cin, n);
    user_Header();

    while (fin.read((char*)this, sizeof(User_Management)))
    {
        if (n == user_Name) // Comparing will all User records
        {
            list_Users();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "User with Name : " << n << " not available...\n";
    _getch();
}

////////////    Searh by Reserch Paper Function
void User_Management::search_By_Department()
{
    int flag = 0;
    string n;
    ifstream fin("User.dat");
    cout << "Enter Department Name : "; // Input for Category
    cin.clear();
    getline(cin, n);
    user_Header();

    while (fin.read((char*)this, sizeof(User_Management)))
    {
        if (n == department) // Comparing will all User records
        {
            list_Users();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "User of Department : " << n << " not available...\n";
    _getch();
}

////////////    Unique I.D check Function
void User_Management::get_User_Id()
{
    int id;
    ifstream fin;
    fin.open("User.dat");

EnterAgain:
    try
    {
        cout << "\tEnter User Id";
        getChoice(id);

        fin.seekg(ios::beg);
        while (fin.read((char*)this, sizeof(User_Management)))
        {
            if (id == user_Id)
                throw 'E';
        }
        user_Id = id;
        fin.close();
    }
    catch (...)
    {
        cout << "\tERROR: I.D exist already! Try Again...\n\n";
        goto EnterAgain;
    }
}