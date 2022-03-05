#ifndef LOGIN_H
#define LOGIN_H

#include "User.h"

   ////   Log In Class Definition    ////
class Log_In : public User_Management
{
public:
   int User_login_Search(string,int); // User log in search
   int Admin_login_Search(string,int); // Admin log in search
   int Input_Prompt(int); // Prompt user to enter Name and ID
};

#endif