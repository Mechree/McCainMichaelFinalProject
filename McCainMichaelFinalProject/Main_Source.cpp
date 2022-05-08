#define _CRT_SECURE_NO_WARNINGS

#include "Employee_C.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>

// Globals

// Templates

// Prototypes
Employee_C Fill_Array(int, int&);
void Extract_ID(string, Employee_C [], int& , int );
int Find_Employee(string , int, int& );

int main()
{
	// Initializers
	const int SZ = 100;
	string fName;
	int empCount = 0;

	// Ask user to enter binary file name
	cout << "\nEnter the desired file name>";
	//cin.ignore();
	cin >> fName;

	// Call Functions 1,2
	Employee_C employees[] = { Fill_Array(SZ,empCount) };
	Extract_ID(fName, employees, empCount, SZ);

	// Repeatedly ask for user to search and call function 3
	bool again = true;
	int id = -1;

	while (again)
	{
		// Get ID from user
		cout << "\nEnter a employee ID to search for>";
		cin.ignore();
		cin >> id;

		int pos = 0;
		int *pos_P = nullptr;
		pos_P = &pos;

		// Get position of ID in binary file
		Find_Employee(fName,id, pos);
		if (pos == -1)
		{
			cout << "\nEmployee ID does not exist!";
		}
		else
		{
			// use position to display Employee info
			cout << "\nName: " << employees[pos].Get_Name();
			cout << "\nID : " << employees[pos].Get_ID();
			cout << "\nSalary: $" << employees[pos].Get_Sal();
			cout << "\nGender: " << employees[pos].Get_Gend() << endl;
		}
		// Ask user to continue or end program
		cout << "\nEnter 1 to search for another ID, else enter 0>";
		cin >> again;
	}

	// END PROGRAM
	cout << "\nTerminating program" << endl << endl;
	system("pause");
	return 0;
}

// Definitions

Employee_C Fill_Array(int SZ, int& numEmp)
{
	int count = 0;

	// Dynamically allocated Employee object array of size 100
	Employee_C *employee = nullptr;
	employee = new Employee_C[SZ];
	//unique_ptr<Employee_C[]> employee(new Employee_C[SZ]);

	bool again = true;
	
	// Ask user for data to fill object
	for (int i = 0; i < SZ && again; i++)
	{
		char cstr[NM_SZ] = " ";
		//char* cptr = nullptr;
		//cptr = &cstr[NM_SZ];

		cout << "\nEnter the name of employee>";
		cin.ignore();
		cin.get(cstr, NM_SZ);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << cstr << endl;

		int id = -1;
		cout << "\nEnter employees ID>";
		cin >> id;

		double sal = 0;
		cout << "\nEnter employees salary>";
		cin >> sal;

		char gend = ' ';
		cout << "\nEnter employees gender (M,F,O)>";
		cin >> gend;

		// Fill object with user input
		employee[i].Set_Name(cstr);
		employee[i].Set_ID(id);
		employee[i].Set_Sal(sal);
		employee[i].Set_Gend(gend);

		// Output for verification
		cout << "\nName: " << employee[i].Get_Name();
		cout << "\nID : " << employee[i].Get_ID();
		cout << "\nSalary: $" << employee[i].Get_Sal();
		cout << "\nGender: " << employee[i].Get_Gend() << endl;

		numEmp++;
		//allSal += employee[i].Get_Sal();

		cout << "\nEnter 1 to enter another employees data, else enter 0>";
		cin >> again;

	}
	cout << "\n---------------------------------------------------------";
	
	return *employee;
}

void Extract_ID(string fName, Employee_C employees[], int &numEmp, int SZ)
{
	// Use file name from user to create binary file
	string fTitle = fName.substr(0, fName.find_last_of('.')) + ".dat"; // use name from user and add .dat to file extension
	fstream file;
	file.open(fTitle, ios::out | ios::binary);	// Open file in binary/out mode

	if (file.fail())
	{
		cout << "\nFile failed to open. Program terminating" << endl;
		exit(0);
	}
	else {
		cout << "\nFile " << fTitle << " created successfully!";
		cout << "\nPopulating file...." << endl;
		int id = -1;

		// write employee IDs to binary file
		for (int i = 0; i < numEmp; i++)
		{
			id = employees[i].Get_ID();
			file.write(reinterpret_cast<char*>(&id), sizeof(id));
		}
		cout << "\nTask Completed!";
	}
	file.close();
}

int Find_Employee(string fName, int id, int& pos)
{
	ifstream file;
	string fTitle = fName.substr(0, fName.find_last_of('.')) + ".dat"; // use name from user and add .dat to file extension
	string line;
	unsigned char fID;

	file.open(fTitle, ios::in | ios::binary);
	if (file.fail())
	{
		cout << "\nFile failed to open. Program terminating" << endl;
		exit(0);
	}
	else 
	{

		cout << "\nFile opened successfully." << endl;
		int size = 0;
		file.clear();

		// go to the end of binary file, get and save the size, and reset read position to the beginning
		file.seekg(0L, ios::end);
		size = (int)file.tellg();
		file.seekg(0L, ios::beg);

		// read file to the end while comparing positions to the ID enterted by the user.
		//file.read(reinterpret_cast<char*>(&employeeID), sizeof(employeeID));

		// While the byte position in the file is less than the byte size, read the file position ...
		// and then return that position to main, else return -1.
		while (file.tellg()< size)
		{
			// search binary file for entered ID
			file.read(reinterpret_cast<char*>(&fID), sizeof(fID));
			if (id == static_cast<int>(fID))
			{
				// return position to main
				cout << "\n" << file.tellg();
				pos = file.tellg();
			}
			else
			{
				// if ID isnt found, return -1
				pos = -1;
			}
		}
	}
	// else return -1 using a pointer in function  param list

	file.close();
}