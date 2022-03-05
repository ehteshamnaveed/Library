#pragma once
#pragma warning(disable: 4996)
#include "Head.h"
#include "Issue.h"

////////////    Function to Issued Book
void Issue_Book::issue_Book()
{
	int flag=0, req_Id;
	long int pos; char option;
	fstream fin("Book.dat",ios::in|ios::out|ios::binary);
	ofstream fou("Issued_Books.dat",ios::app|ios::binary);
	ifstream curr_Profile("Profile.dat",ios::in);

	cout << "Enter Book I.D";
	getChoice(req_Id);

	while(fin.read((char*)this,sizeof(Book_Management)))
 	{
  		if(req_Id==book_Id)
  		{
  			flag++;
  			pos=fin.tellg();
  			if(Available>0)
  			{
                book_Header();
  				list_Books();

  				do
  				{
	  				cout << "Is this the Book? (y/n)";
	  				getChoice(option);

	  				switch(option)
	  				{
	  					case 'y':
	  					case 'Y':
	  						fin.seekp(pos - sizeof(Book_Management));
	  						Available--; // Remove one copy of book from "Book.dat" file
	  						fin.write((char*)this,sizeof(Book_Management)); 

	  						curr_Profile.read((char*)this,sizeof(User_Management));

	  						// cout << "Enter User I.D";
	  						// getChoice(user_Id);
							
	  						// cout << "\tEnter User Name : ";
						   //  cin.clear(); //cin.ignore(INT_MAX,'\n');
						   //  getline(cin,user_Name);

						   //  cout << "\tEnter Department Name : ";
						   //  cin.clear(); 
						   //  getline(cin,department);

						    time_It(); // Time stamp of when is book being issued and due date

	  						fou.write((char*)this,sizeof(Issue_Book)); // write the user and book information in "Issued_books.dat" file

	  						fin.close();
	  						fou.close();
	  						curr_Profile.close();
	  						option='n';
	  						break;

						case 'n':
						case 'N':
							fin.close();
	  						fou.close();
	  						break;

						default:
							cout << "Answer in (y/n)\n\n";
	  				}
  				}while(option!='n');
  			}
  			else 
  			{
  				cout << "No Copies of Book are Available\n";
  				fin.close();
				fou.close();
  				break;
  			}
  		}
  	}
  	if(flag == 0)
     {
        cout<<"Book Number with ID:"<<req_Id<<" not available...\n";
        _getch();
     }
     fin.close();
	 fou.close();
}

////////////    Function to Return Book
void Issue_Book::return_Book()
{
}

////////////    Function to time the Issue and Return date
void Issue_Book::time_It()
{
	// Issued Book Time Stamp
	time_t t ;
	struct tm *tmp ;
	time( &t );
	tmp = localtime( &t );
	strftime(issue_Time, sizeof(issue_Time), "%d %B, %Y - %I:%M %p", tmp);

	// Returned Day Time Stamp
	time_t t2 ;
	struct tm *tmp2 ;
	time( &t2 );
	t2 += 1800000;
	tmp2 = localtime( &t2 );
	strftime(due_Time, sizeof(due_Time), "%d %B, %Y - %I:%M %p", tmp2);
}

void Issue_Book::list_Issued_Books()
{
	cout.setf(ios::left);
     cout << setw(15) << user_Id
          << setw(20) << user_Name
          << setw(20) << department
          << setw(15) << book_Id
          << setw(20) << Title
          << setw(20) << Author
          << setw(15) << Category
          << setw(35) << issue_Time
          << setw(35) << due_Time
          << "\n";
}

////////////    Function display all the issued books with user information
void Issue_Book::display_Issued_Books()
{
     int rec=0;
     ifstream fin;
     fin.open("Issued_Books.dat", ios::in | ios::binary);

     if (!fin)
            cout << "File not found" << endl;

     else
     {
       issued_Header();
       while(fin.read((char*)this,sizeof(Issue_Book))) // Reading Book data from file) 
       {
          list_Issued_Books(); // Displaying Book inforamtion
          cout << "\n\n";
          rec++;
        }

       fin.close();
       cout<<"\nTotal "<<rec<<" Records in file...\n";
      }
}

void Issue_Book::issued_Header()
{
	cout.setf(ios::left);
     cout << setw(15) << "User I.D."
          << setw(20) << "User Name"
          << setw(20) << "Department"
          << setw(15) << "Book ID"
          << setw(20) << "Book Name"
          << setw(20) << "Author Name"
          << setw(15) << "Category"
          << setw(35) << "Issued Date"
          << setw(35) << "Due Date"
          << "\n";

     for(int i=1;i<=190;i++)
      cout<<"=";

     cout<<"\n";
}