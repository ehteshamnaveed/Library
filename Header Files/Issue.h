#ifndef ISSUE_H
#define ISSUE_H

#include "Head.h"
#include "Book.h"
#include "User.h"

   ////   Issue Book Class Definition    ////
class Issue_Book : public Book_Management, public User_Management
{
public:
	void issue_Book(); // Issues the book with user information 
	void display_Issued_Books(); // Displays all the issued books with user information
	void issued_Header();
	void list_Issued_Books();
	void return_Book(); // Return the book to the Library
	void time_It(); // Function to time the Issued and Reurn date
private:
	char issue_Time[30];
	char due_Time[30];
};

#endif