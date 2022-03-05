#ifndef User_H
#define User_H
#include "Head.h"

////   User Management Class Definition    ////
class User_Management
{
public:
    User_Management();
    // Memeber Function Prototyping
    void add_User(); // Add User
    void get_User();
    void get_User_Id(); // Check for unique I.D
    void display_User(); // Display user
    void list_Users();
    void delete_User(int); // Delete User
    void modify_User(); // Update User record
    void modify_User_Record(int);

    // Searching Functions
    void search_By_User_Name(); // Search for user by Name
    void search_By_User_Id(); // Search for user by I.D
    void search_By_Department(); // Search Department Students

protected:
    // Data Menbers
    int user_Id;
    string user_Name;
    string department;
};
#endif