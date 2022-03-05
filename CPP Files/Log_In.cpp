
#include "Login.h"

////////////    Function to search the Admin for login validation
int Log_In::Admin_login_Search(const string req_Name, const int req_Id)
{
   int flag=0;
   ifstream read_Admin("Admin.dat",ios::in|ios::binary);
   ofstream curr_Profile("Profile.dat",ios::out);

   while(read_Admin.read((char*)this,sizeof(Log_In)))
   {
      if(req_Name == user_Name && req_Id == user_Id)
      {
         curr_Profile.write((char*)this,sizeof(Log_In));
         logged_ID = user_Id;
         flag++;
         break;
      }
   }
   curr_Profile.close();
   read_Admin.close();
   return flag;
}

////////////    Function to search the User for login validation
int Log_In::User_login_Search(const string req_Name, const int req_Id)
{
   int flag=0;
   ifstream read_User("User.dat",ios::in|ios::binary);
   ofstream curr_Profile("Profile.dat",ios::out);

   while(read_User.read((char*)this,sizeof(Log_In)))
   {
      if(req_Name == user_Name && req_Id == user_Id)
      {
         curr_Profile.write((char*)this,sizeof(Log_In));
         logged_ID = user_Id;
         flag++;
         break;
      }
   }
   curr_Profile.close();
   read_User.close();
   return flag;
}

////////////    Function to prompt user for login
int Log_In::Input_Prompt(const int a)
{
   cin.ignore(INT_MAX,'\n');
   int return_State=0, login_Id;
   string login_Name;

   cout << "\n\n";
   cout << "\t  Name : ";
   cin.clear();
   getline(cin,login_Name);

   cout << "\t  Pass : "; 
   cin >> login_Id;;

   switch(a)
   {
     case 1:
     return_State = Admin_login_Search(login_Name,login_Id);
     break;

     case 2:
     return_State = User_login_Search(login_Name,login_Id);
     break;
    }
   return return_State;
 }