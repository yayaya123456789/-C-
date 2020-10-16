// seekp in
// seekg out
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<cstdlib>
#include<cctype>
#define maxnumber 100
using namespace std;
void initialFile();
void list(void);
void update(void);
void insert(void);
void deleterecords(void);
void sort(void);
int instructions();
int main()
{
	int choice = 0;
	ifstream File("Phones.dat", ios::in);//input
	void(*f[])(void) = { list, update, insert ,deleterecords };

	if (!File)
	{
		cout<< "There is no file: Phones.dat!" <<endl;
		cout << "New file is initialized!" << endl;
		initialFile();
	}
	else
	{
		cout << "Data of Phones.data is loaded!" << endl;
		File.close();
	}

	while ((choice = instructions()) != 5)
	{
		(*f[choice - 1])();
	}
}
void initialFile()
{
	ofstream reFile("Phones.dat", ios::in | ios::binary);//output
	int id ;
	char name[15] = "";
	char number[11] = "";
	for (int i = 0; i < maxnumber; i++)
	{
		reFile.write(reinterpret_cast<char *>(&id), sizeof(id));
		reFile.write(reinterpret_cast<char *>(&name), sizeof(name));
		reFile.write(reinterpret_cast<char *>(&number), sizeof(number));
	}
	reFile.close();
}
int instructions()
{
	int choice = 1;
	cout << "\nEnter a choice:" <<endl; 
	cout << "1  List all phones." << endl;
	cout << "2  Update phone." << endl;
	cout << "3  Insert phone." << endl;
	cout << "4  Delete phone." << endl;
	cout << "5  End program." << endl;
	do
	{
		cout << "?";
		cin >> choice;
	} while (choice < 1 || choice > 5);
	return choice;
}
void list(void)
{
	ifstream reFile("Phones.dat");
	int id;
	char name[15] = "";
	char number[11] = "";
	cout << setw(7) << "Record#" << "    " << left << setw(18) << "Name" << left << setw(13) << "PhoneNumber" << endl;
	for (int count = 1; count <= maxnumber && !reFile.eof(); count++)
	{
		reFile.read(reinterpret_cast<char *>(&id), sizeof(id));
		reFile.read(reinterpret_cast<char *>(&name), sizeof(name));
		reFile.read(reinterpret_cast<char *>(&number), sizeof(number));
		if (id > 0 && id <= maxnumber)
		{
			cout << fixed << showpoint;
			cout << left << setw(7) << id << "    "<< left << setw(18) << name << left << setw(13) << number << endl;
		}
	}
	reFile.close();
}
void update(void)
{
	fstream reFile("Phones.dat", ios::out | ios::in);
	int id;
	char name[15] = "";
	char number[11] = "";
	int count = 0;
	cout << "Update a phone number\nEnter the phone Record# for update: ";
	cin >> count;
	reFile.seekg((count - 1)*(sizeof(id) + sizeof(name) + sizeof(number)));
	reFile.read(reinterpret_cast<char *>(&id), sizeof(id));
	reFile.read(reinterpret_cast<char *>(&name), sizeof(name));
	reFile.read(reinterpret_cast<char *>(&number), sizeof(number));

	if (id != -1)
	{
		cout << setw(7) << "Record#" << "    " << left << setw(18) << "Name" << left << setw(13) << "PhoneNumber" << endl;
		cout << fixed << showpoint;
		cout << setw(7) << id << "    " << left << setw(18) << name << left << setw(13) << number << endl;
		cout << "Enter the name: ";
		cin.ignore();
		cin.getline(name, 15, '\n');
		cout << "Enter the phone number: ";
		cin.getline(number, 11, '\n');
		reFile.seekp((count - 1)*(sizeof(id) + sizeof(name) + sizeof(number)));
		reFile.write(reinterpret_cast<char *>(&id), sizeof(id));
		reFile.write(reinterpret_cast<char *>(&name), sizeof(name));
		reFile.write(reinterpret_cast<char *>(&number), sizeof(number));
		cout << "Phone updated." << endl;
		reFile.close();
		sort();
	}
	else
	{
		cerr << "Cannot update. The record is empty." << endl;
		reFile.close();
	}
}
void insert(void)
{
	fstream reFile("Phones.dat", ios::out | ios::in);
	int id;
	char name[15] = "";
	char number[11] = "";
	int count = 1;
	reFile.read(reinterpret_cast<char *>(&id), (sizeof(id)));

	while ((id != -1) && count < maxnumber)
	{
		count++;
		reFile.seekg((count - 1)*(sizeof(id) + sizeof(name) + sizeof(number)));
		reFile.read(reinterpret_cast<char *>(&id), (sizeof(id)));
	}
	if (count <= maxnumber)
	{
		cout << "Insert a phone number\nEnter the name: ";
		cin.ignore();
		cin.getline(name, 15, '\n');
		cout << "Enter the phone number: ";
		cin.getline(number, 11, '\n');
		reFile.seekp((count - 1) *(sizeof(id) + sizeof(name) + sizeof(number)));
		reFile.write(reinterpret_cast<char *>(&count), sizeof(count));
		reFile.write(reinterpret_cast<char *>(&name), sizeof(name));
		reFile.write(reinterpret_cast<char *>(&number), sizeof(number));
		cout << "Phone inserted." << endl;
		reFile.close();
		sort();
	}
	else
	{
		cerr << "Cannot insert. The file is full." << endl;
		reFile.close();
	}
}
void deleterecords(void)
{
	fstream reFile("Phones.dat", ios::out | ios::in);
	int id;
	char name[15] = "";
	char number[11] = "";
	int count = 1;
	cout << "Delete a phone number" << endl;
	cout << "Enter the phone Record# for deletion: " << endl;
	cin >> count;
	reFile.seekg((count - 1) *(sizeof(id) + sizeof(name) + sizeof(number)));
	reFile.read(reinterpret_cast<char *>(&id), (sizeof(id)));

	if (id != -1)
	{
		reFile.seekp((count - 1)*(sizeof(id) + sizeof(name) + sizeof(number)));
		id = -1;
		strcpy_s(name, "");
		strcpy_s(number, "");
		reFile.write(reinterpret_cast<char *> (&id), (sizeof(id)));
		reFile.write(reinterpret_cast<char *>(&name), sizeof(name));
		reFile.write(reinterpret_cast<char *>(&number), sizeof(number));
		cout << "Phone deleted." << endl;
		reFile.close();
		sort();
	}
	else
	{
		cerr << "Cannot delete. The record is empty." << endl;
		reFile.close();
	}
}
void sort(void)
{
	int id;
	char name[15] = "";
	char number[11] = "";
	char hold[15] = "";
	
	int idArray[maxnumber];
	char nameArray[maxnumber][15];
	char numberArray[maxnumber][11];
	int n = 0;
	fstream reFile("Phones.dat", ios::out | ios::in);
	for (int count = 1; count <= maxnumber && !reFile.eof(); count++)
	{
		reFile.read(reinterpret_cast<char *> (&id), sizeof(id));
		reFile.read(reinterpret_cast<char *>(&name), sizeof(name));
		reFile.read(reinterpret_cast<char *>(&number), sizeof(number));
		if (id > 0 && id <= maxnumber)
		{
			idArray[n] = id;
			strcpy_s(nameArray[n], name);
			strcpy_s(numberArray[n], number);
			n++;
		}
	}
	for (int pass = 0; pass < n - 1; pass++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (strcmp(nameArray[j], nameArray[j + 1]) > 0)
			{
				strcpy_s(hold, nameArray[j]);
				strcpy_s(nameArray[j], nameArray[j + 1]);
				strcpy_s(nameArray[j + 1], hold);
			

				strcpy_s(hold, numberArray[j]);
				strcpy_s(numberArray[j], numberArray[j + 1]);
				strcpy_s(numberArray[j + 1], hold);
			}
		}
	}
	reFile.seekp(0);

	for (int i = 1; i <= n; i++)
	{
		reFile.write(reinterpret_cast<char *>(&i), sizeof(i));
		reFile.write(reinterpret_cast<char *>(&nameArray[i - 1]), sizeof(nameArray[i - 1]));
		reFile.write(reinterpret_cast<char *>(&numberArray[i - 1]), sizeof(numberArray[i - 1]));
	}
	id = -1;
	strcpy_s(name, "");
	strcpy_s(number, "");
	for (; n <= maxnumber; n++)
	{
		reFile.write(reinterpret_cast<char *>(&id), sizeof(id));
		reFile.write(reinterpret_cast<char *>(&name), sizeof(name));
		reFile.write(reinterpret_cast<char *>(&number), sizeof(number));

	}
	cout << "Phones sorted by name." << endl;
	reFile.close();
}