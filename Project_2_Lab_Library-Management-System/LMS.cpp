#include<iostream>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include<iomanip>

using namespace std;

void display_menu_admin(int& op)
{
	system("cls");
	cout << "1)Add a new member." << endl;
	cout << "2)Remove an existing member." << endl;
	cout << "3)Add a book to library." << endl;
	cout << "4)Remove a book from library." << endl;
	cout << "5)Check the list of members." << endl;
	cout << "6)Check the list of books." << endl;
	cout << "7)To log out and exit from the program." << endl;
	cout << "8)Save the Data." << endl;
	cout << "Enter your option : ";
	cin >> op;
}

void display_menu_member(int& op)
{
	cout << endl << "1)Check Your Personal Details : " << endl;
	cout << "2)Get a book" << endl;
	cout << "Enter your option : ";
	cin >> op;
}

void data_mem_input(vector<string>& mem_name, vector<string>& mem_id)
{
	ifstream fn;
	char name[100], id[15];
	fn.open("memberdata.txt");
	if (fn.is_open())
	{
		//cout << "Good Hu gaya.";
		for (int i = 0; !(fn.eof()); i++)
		{
			fn.getline(name, 100);
			mem_name.push_back(name);
			//cout<<mem_name[i];
			fn.getline(id, 15);
			mem_id.push_back(id);
			// cout<<mem_id[i];
		}
	}
	else
	{
		cout << "File is Missing.";
	}
	fn.close();
}

void data_mem_output(vector<string>& mem_name, vector<string>& mem_id)
{
	ofstream fn;
	fn.open("memberdata.txt");
	//cout << "Good Hu gaya.";
	for (int i = 0; i < mem_name.size(); i++)
	{
		fn << mem_name[i] << endl;
		fn << mem_id[i];
		if (i == mem_name.size() - 1)
		{
			continue;
		}
		else
		{
			fn << endl;
		}
	}
	fn.close();
}

void data_book_input(vector<string>& book_name, vector<string>& book_id, vector<int>& book_quantity)
{
	ifstream fn;
	char name[100], id[15];
	int quantity;
	fn.open("bookdata.txt");
	if (fn.is_open())
	{
		//cout << "Good Hu gaya.";
		for (int i = 0; !(fn.eof()); i++)
		{
			fn.getline(name, 100);
			book_name.push_back(name);
			//cout << book_name[0];
			fn >> id;
			book_id.push_back(id);
			//cout << book_id[0];
			fn >> quantity;
			fn.ignore();
			book_quantity.push_back(quantity);
			//cout << book_quantity[0];
		}
	}
	else
	{
		cout << "File is Missing.";
	}
	fn.close();
}

void data_book_output(vector<string>& book_name, vector<string>& book_id, vector<int>& book_quantity)
{
	ofstream fn;
	fn.open("bookdata.txt");
	//cout << "Good Hu gaya.";
	for (int i = 0; i < book_name.size(); i++)
	{
		fn << book_name[i] << endl;
		fn << book_id[i] << " " << book_quantity[i];
		if (i == book_name.size() - 1)
		{
			continue;
		}
		else
		{
			fn << endl;
		}
	}
	fn.close();
}

void adduser(vector<string>& mem_name, vector<string>& mem_id, vector<string>& book_id)
{
	string name, id;
	char op = 'Y';
	while (op != 'N' && op != 'n')
	{
		cin.ignore();
		cout << "Enter the user name : ";
		getline(cin, name);
		cout << "Enter the user id : ";
		getline(cin, id);
		for (int i = 0; i < mem_id.size(); i++)
		{
			if (id == mem_id[i])
			{
				cout << "ID matches with the other member.It must be unique.Kindly enter again:";
				//cin.ignore();
				i = 0;
				getline(cin, id);
			}
		}
		for (int i = 0; i < book_id.size(); i++)
		{
			if (id == book_id[i])
			{
				cout << "ID matches with one book id.It must be unique.Kindly enter again:";
				//cin.ignore();
				i = 0;
				getline(cin, id);
			}
		}
		mem_name.push_back(name);
		mem_id.push_back(id);
		cout << endl << "You have entered name as " << name << " and ID as " << id << endl;
		cout << "Do you want to enter data again? (Y/N): ";
		cin >> op;
	}

}

void addbook(vector<string>& book_name, vector<string>& book_id, vector<int>& book_quantity, vector<string>& mem_id)
{
	string name, id;
	char op = 'Y';
	int quantity;
	while (op != 'N' && op != 'n')
	{
		cin.ignore();
		cout << "Enter the book name : ";
		getline(cin, name);
		//cout << book_name[1] << " " << endl;
		cout << "Enter the book id : ";
		getline(cin, id);
		for (int i = 0; i < book_id.size(); i++)
		{
			if (id == book_id[i])
			{
				cout << "ID matches with the other member.It must be unique.Kindly enter again:";
				//cin.ignore();
				i = 0;
				getline(cin, id);
			}
		}
		for (int i = 0; i < mem_id.size(); i++)
		{
			if (id == mem_id[i])
			{
				cout << "ID matches with one book id.It must be unique.Kindly enter again:";
				//cin.ignore();
				i = 0;
				getline(cin, id);
			}
		}
		book_name.push_back(name);
		book_id.push_back(id);
		//cout << book_id[1] << " " << endl;
		cout << "Enter the book Quantity : ";
		cin >> quantity;

		book_quantity.push_back(quantity);
		//cout << book_quantity[1] << " " << endl;
		cout << endl << "You have entered name as " << name << " book quantity " << quantity << " and ID as " << id << endl;
		cout << "Do you want to enter data again? (Y/N): ";
		cin >> op;
	}

}

void check_member(vector<string>& mem_name, vector<string>& mem_id)
{
	system("cls");
	cout << "\tMember name"<<"\t\t\t\t"<<"Member ID " << endl<<endl<<endl;
	for (int i = 0; i < mem_name.size(); i++)
	{
		cout <<"\t"<<left<<setw(20)<<mem_name[i] << "\t\t\t"<< left << setw(20)<< mem_id[i] << endl;
	}
}

void check_book(vector<string>& book_name, vector<string>& book_id, vector<int>& book_quantity)
{
	system("cls");
	int counter = 0;
	cout << "\tBook name\t\tBook ID\t\tBook Quantity"<<endl<<endl<<endl;
	for (int i = 0; i < book_name.size(); i++)
	{
		cout << "\t" << left << setw(20) << book_name[i] << "\t" << left << setw(10) << book_id[i]<< "\t" << left << setw(20) << book_quantity[i] << endl;
		counter++;
	}
	if (counter == 0)
	{
		cout << endl << "Member does not exists." << endl;
	}
}

void remove_mem(vector<string>& mem_name, vector<string>& mem_id)
{
	int counter = 0;
	string id_rem;
	cin.ignore();
	cout << "Which book do you want to remove? Kindly give its id : ";
	getline(cin, id_rem);
	for (int i = 0; i < mem_name.size(); i++)
	{
		if (mem_id[i] == id_rem)
		{
			mem_name.erase(mem_name.begin() + i);
			mem_id.erase(mem_id.begin() + i);
			cout << "The member entry has been removed.";
			counter++;
		}
	}
	if (counter == 0)
	{
		cout << "Member does not exists.";
	}
}

void remove_book(vector<string>& book_name, vector<string>& book_id, vector<int>& book_quantity)
{
	string id_rem;
	cin.ignore();
	cout << "Which book do you want to remove? Kindly give its id : ";
	getline(cin, id_rem);
	for (int i = 0; i < book_name.size(); i++)
	{
		if (book_id[i] == id_rem)
		{
			book_name.erase(book_name.begin() + i);
			book_id.erase(book_id.begin() + i);
			book_quantity.erase(book_quantity.begin() + i);
			cout << "The book entry has been removed.";
		}
	}
}

void mem_personal(vector<string> mem_name, vector<string> mem_id)
{
	string name, id;
	int op, counter_id = 0;
	cout << endl << "Do you want to see through your 1)id or 2)name : ";
	cin >> op;
	if (op == 1)
	{
		cin.ignore();
		cout << "Kindly enter your ID:";
		getline(cin, id);
		for (int i = 0; i < mem_id.size(); i++)
		{
			if (mem_id[i] == id)
			{
				cout << endl << "Your name is " << mem_name[i] << " and your id is " << mem_id[i] << endl;
				counter_id++;
			}
		}
		if (counter_id == 0)
		{
			cout << "Member against this id does not exists.";
		}
	}
	else if (op == 2)
	{
		cin.ignore();
		cout << "Kindly enter your name:";
		getline(cin, name);
		for (int i = 0; i < mem_name.size(); i++)
		{
			if (mem_name[i] == name)
			{
				cout << endl << "Your name is " << mem_name[i] << " and your id is " << mem_id[i] << endl;
				counter_id++;
			}
		}
		if (counter_id == 0)
		{
			cout << "Member against this name does not exists.";
		}
	}
	else
	{
		cout << "Wrong Option." << endl;
	}
}

void getabook(vector<string>& book_name, vector<int>& book_quantity)
{
	int i = 0;
	cout << "Which book do u want? " << endl;
	for (int i = 0; i < book_name.size(); i++)
	{
		cout << i << ") " << book_name[i] << endl;
	}
	cout << "Enter Option : ";
	cin >> i;
	if (book_quantity[i] > 0)
	{
		cout << endl << "It's available." << endl;
		book_quantity[i] -= 1;
	}
	else
	{
		cout << "It's not available.";
	}
}

//Admin Authorization
int admin_auth()
{
	int counter = 0;
	char username_file[500], passwd_file[100];
	char username[500], passwd[100];
	ifstream fn;
	fn.open("Auth_file.txt");
	fn.getline(username_file, 500);
	fn.getline(passwd_file, 100);
	cin.ignore();
	cout << "Kindly Enter your Username : ";
	cin.getline(username, 500);
	if (fn.is_open())
	{
		if (strcmp(username, username_file) == 0)
		{
			cout << "Kindly Enter your Password : ";
			cin.getline(passwd, 100);
			if (strcmp(passwd, passwd_file) == 0)
			{
				return 0;
			}
			else
			{
				while (strcmp(passwd, passwd_file) != 0)
				{
					cout << endl << "Wrong Password.";
					cout << "Kindly Enter your Password : ";
					cin.getline(passwd, 100);
					counter++;
					if (counter >= 3)
					{
						cout << endl << "Maximum Try Reached.";
						return 1;
					}
				}
				return 0;
			}

		}
		else
		{
			cout << "Username not Found." << endl;
			return 1;
		}
	}
	else
	{
		cout << "Authorization File is Missing." << endl;
		return 2;
	}
	return 0;
}

int mem_auth(vector<string> mem_id)
{
	int counter = 0, max = 0;
	string id;
	cin.ignore();
auth:
	cout << "Kindly enter your ID :";
	getline(cin, id);
	for (int i = 0; i < mem_id.size(); i++)
	{
		if (id == mem_id[i])
		{
			cout << "Hello";
			counter++;
			return 0;
		}
	}
	if (counter == 0)
	{
		cout << "Wrong ID." << endl;
		max++;
		if (max == 3)
		{
			cout << "Maximum Attempt reached.";
			return 1;
		}
		goto auth;
	}
}

int main()
{
	cout << endl << endl;
	cout << "-----------------------------------WELCOME TO LIBRARY MANAGEMENT SYSTEM-----------------------------------" << endl;
	cout << endl << endl;

	vector<string>mem_name;
	vector<string>mem_id;
	vector<string>book_name;
	vector<int>book_quantity;
	vector<string>book_id;
	data_mem_input(mem_name, mem_id);
	data_book_input(book_name, book_id, book_quantity);
	int admin_menu;
	int mem_menu;
	char auth;
authorization:
	cout << "What access level you have? \n A) Admin \n M)Member \n Enter option:";
	cin >> auth;
	if (auth == 'A' || auth == 'a')
	{
		cout << endl << "-----------Welcome to Admin Panel.-------------" << endl;
		if (admin_auth() == 1)
		{
			goto authorization;
		}
		else
		{
			display_menu_admin(admin_menu);
			while (admin_menu != 7)
			{
				if (admin_menu == 1)
				{
					adduser(mem_name, mem_id, book_id);
				}
				else if (admin_menu == 2)
				{
					remove_mem(mem_name, mem_id);
				}
				else if (admin_menu == 3)
				{
					addbook(book_name, book_id, book_quantity, mem_id);
				}
				else if (admin_menu == 4)
				{
					remove_book(book_name, book_id, book_quantity);
				}
				else if (admin_menu == 5)
				{
					check_member(mem_name, mem_id);
				}
				else if (admin_menu == 6)
				{
					check_book(book_name, book_id, book_quantity);
				}
				else if (admin_menu == 8)
				{
					data_mem_output(mem_name, mem_id);
					data_book_output(book_name, book_id, book_quantity);
				}
				else
				{
					cout << "Wrong Option.";
				}
				system("pause");
				system("cls");
				display_menu_admin(admin_menu);
			}
		}
	}
	else if (auth == 'M' || auth == 'm')
	{
		int i;
		i = mem_auth(mem_id);
		if (i == 0)
		{
			cout << endl << "-----------Welcome to Member Panel.-------------" << endl;
			display_menu_member(mem_menu);
			cout << "Hello";
			while (mem_menu != 0)
			{
				if (mem_menu == 1)
				{
					mem_personal(mem_name, mem_id);
				}
				else if (mem_menu == 2)
				{
					getabook(book_name, book_quantity);
				}
				else
				{
					cout << "Wrong Option Selected.";
				}
				display_menu_member(mem_menu);
			}
		}
		else
		{
			cout << "Kindly try again.";
		}
	}
	else
	{
		cout << "Wrong Option Selected.";
	}
	data_mem_output(mem_name, mem_id);
	data_book_output(book_name, book_id, book_quantity);
}

