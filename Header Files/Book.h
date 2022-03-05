#pragma once
#include "Head.h"

////   Book Management Class Definition    ////
class Book_Management
{
public:
    Book_Management();
    // Memeber Function Prototyping
    void add_Book(); // Add book
    void get_Book();
    void get_Book_Id();
    void display_Book(); // Display Books
    void list_Books();
    void delete_Book(int); // Delete book
    void modify_Book(); // Update book record
    void modify_Book_Record(int);

    // Searching Functions
    void search_By_Book_Name(); // Search for Book by Name
    void search_By_Book_Id(); // Search for Book by I.D
    void search_By_Year(); // Search for Book by year
    void search_By_Author_Name(); // Search for Book by Author name
    void search_By_Category(); // Search Category book
    void search_Reserch_Paper(); // Search Recerch Papers

protected:
    // Data Menbers
    int book_Id;
    int Year;
    int Available;

    string Title;
    string Author;
    string Category;
};
