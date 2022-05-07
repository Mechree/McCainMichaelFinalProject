#include <string>
#include <cstring>
#include <cstdlib>

#ifndef Employee_C_
#define Employee_C_

using namespace std;

const int NM_SZ = 41;

class Employee_C
{
private:
	char empName[NM_SZ];
	int empID;
	double empSal;
	char empGend;
	static double allSal;

public:
	Employee_C();
	Employee_C(char nm[], int id, double sal, char gend);

	//Getters
	char Get_Name() const;
	int Get_ID() const;
	double Get_Sal() const;
	char Get_Gend() const;
	double Get_All_Sal() const;

	//Setters
	void Set_Name(char[]);
	void Set_ID(int);
	void Set_Sal(double);
	void Set_Gend(char);
	double Calc_Sal(double sal, double prevSal);
};

#endif

