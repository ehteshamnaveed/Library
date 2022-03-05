#include "Head.h"
#include "Issue.h"
#include "Login.h"


int main()
{
	//Issue_Book I;
	Log_In L;
	User_Management U;
	Book_Management B;
	B.add_Book();
	U.add_User();
	B.display_Book();
	U.display_User();
	int p = L.Input_Prompt(2);
	if (p == 1)
		cout << "Good Morning";
	else
		cout << "ERROR : Sleeping";
	//I.issue_Book();

	return 0;
}