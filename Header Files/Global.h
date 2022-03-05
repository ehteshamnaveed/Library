#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

static int logged_ID;

template <typename T>
inline void getChoice(T& choice)
{
    cout << " : ";
    cin >> std::setw(1) >> choice;

    //Error check
    while (!std::cin.good())
    {
        //Report problem
        cout << "ERROR: Faulty input! Try again..." << "\n";

        //Clear stream
        cin.clear();
        std::cin.ignore(INT_MAX, '\n');

        //Get input again..
        cout << " Re-eneter : ";
        cin >> std::setw(1) >> choice;
    }
    //Clear stream
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}


inline void book_Header()
{
    cout.setf(ios::left);
    cout << setw(8) << "I.D."
        << setw(20) << "Book Title"
        << setw(20) << "Book Author"
        << setw(15) << "Category"
        << setw(8) << "Year"
        << setw(8) << "Avl"
        << "\n";

    for (int i = 1; i <= 82; i++)
        cout << "=";

    cout << "\n";
}


inline void user_Header()
{
    cout.setf(ios::left);
    cout << setw(8) << "I.D."
        << setw(20) << "Student Name"
        << setw(20) << "Department"
        << "\n";
    for (int i = 1; i <= 50; i++)
        cout << "=";
    cout << "\n";
}
