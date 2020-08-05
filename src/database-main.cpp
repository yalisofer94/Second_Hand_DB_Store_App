#include "database.h"

int detectUser()
{
	string passManager = "123MANAGER";
	char userType;
	string pass;

	cout << "Are you a manager or employee? [m/e]" << endl;
	cin >> userType;

	if (userType == 'e')
		return 2;

	if (userType == 'm')
	{
		cout << "Enter password: " << endl;
		cin >> pass;

		if (pass == passManager)
			return 1;
		else
		{
			cout << "Wrong password!" << endl;
			return 2;
		}
	}
}

void managerMenu()
{
	cout << "-----------------------Welcome manager------------------------" << endl;
	cout << "Enter the number of the action you'd like to perform:" << endl;
	cout << "1) Find book in inventory" << endl;
	cout << "2) Find oldest customer" << endl;
	cout << "3) Find oldest book" << endl;
	cout << "4) Show current order list" << endl;
	cout << "5) Find number of books sold" << endl;
	cout << "6) Find the most read author between dates" << endl;
	cout << "7) Find top 3 customers according to their purchases" << endl;
	cout << "8) Find the book with the most interpreters" << endl;
	cout << "9) Show purchase history of customer" << endl;
	cout << "10) Show orders history of customer" << endl;
	cout << "11) Find shipping cost" << endl;
	cout << "12) Find if customer splitted his order" << endl;
	cout << "13) Find the current shipping status" << endl;
	cout << "14) Find the shippings number by Xpress" << endl;
	cout << "15) Find total sum of money transfered by Bit" << endl;
	cout << "16) Find transactions with profit above the average in last year" << endl;
	cout << "17) Find number of shippings made by Xpress and Israel post last year" << endl;
	cout << "18) Show details about all shippings that includes 2 or more editions of the same book" << endl;
	cout << "19) Find customers that haven't purchased at the last 24 months" << endl;
	cout << "20) Find all customers that order and didn't arrive to take their books at least 14 days" << endl;
	cout << "21) Find the number of books in the warehouse" << endl;
	cout << "22) Find the number of books the store purchased and the total price paid" << endl;
	cout << "23) Find the profit in a given month" << endl;
	cout << "24) Find the annual average in monthly transactions" << endl;
	cout << "25) Show emplotee's salary " << endl;
	cout << "26) Find The employee with the most transactions per month" << endl;
	cout << "0) Exit" << endl;
}

void generalMenu()
{
	cout << "-----------------------Welcome employee-----------------------" << endl;
	cout << "Enter the number of the action you'd like to perform:" << endl;
	cout << "1) Find book in inventory" << endl;
	cout << "2) Find oldest customer" << endl;
	cout << "3) Find oldest book" << endl;
	cout << "4) Show current order list" << endl;
	cout << "6) Find the most read author between dates" << endl;
	cout << "8) Find the book with the most interpreters" << endl;
	cout << "11) Find shipping cost" << endl;
	cout << "12) Find if customer splitted his order" << endl;
	cout << "13) Find the current shipping status" << endl;
	cout << "14) Find the shippings number by Xpress" << endl;
	cout << "17) Find number of shippings made by Xpress and Israel post last year" << endl;
	cout << "18) Show details about all shippings that includes 2 or more editions of the same book" << endl;
	cout << "20) Find all customers that order and didn't arrive to take their books at least 14 days" << endl;
	cout << "21) Find the number of books in the warehouse" << endl;
	cout << "0) Exit" << endl;
}

int main(void)
{
	int userChoise;
	MySQL Mysql;

	if (detectUser() == 1)
		managerMenu();
	else
		generalMenu();

	while (1)
	{
		cout << ">> ";
		cin >> userChoise;
		switch (userChoise)
		{
		case 0:
			cout << "Have a nice day :)" << endl;
			system("pause");
			return 1;

		case 1:
			Mysql.query_1();
			break;

		case 2:
			Mysql.query_2();
			break;

		case 3:
			Mysql.query_3();
			break;

		case 4:
			Mysql.query_4();
			break;

		case 5:
			Mysql.query_5();
			break;

		case 6:
			Mysql.query_6();
			break;

		case 7:
			Mysql.query_7();
			break;

		case 8:
			Mysql.query_8();
			break;

		case 9:
			Mysql.query_9();
			break;

		case 10:
			Mysql.query_10();
			break;

		case 11:
			Mysql.query_11();
			break;

		case 12:
			Mysql.query_12();
			break;

		case 13:
			Mysql.query_13();
			break;

		case 14:
			Mysql.query_14();
			break;

		case 15:
			Mysql.query_15();
			break;

		case 16:
			Mysql.query_16();
			break;

		case 17:
			Mysql.query_17();
			break;

		case 18:
			Mysql.query_18();
			break;

		case 19:
			Mysql.query_19();
			break;

		case 20:
			Mysql.query_20();
			break;

		case 21:
			Mysql.query_21();
			break;

		case 22:
			Mysql.query_22();
			break;

		case 23:
			Mysql.query_23();
			break;

		case 24:
			Mysql.query_24();
			break;

		case 25:
			Mysql.query_25();
			break;

		case 26:
			Mysql.query_26();
			break;

		default:
			cout << "Invalid input" << endl;
			break;
		}
	}
	return 0;
}
