#include "Employee_C.h"

double Employee_C::allSal = 0;

Employee_C::Employee_C()
{
	empName [NM_SZ]= ' ';
	empID = -1;
	empSal = 0.0;
	empGend = ' ';
}

Employee_C::Employee_C(char nm[], int id, double sal, char gend)
{
	empName [NM_SZ] = nm [NM_SZ];
	empID = id;
	empSal = sal;
	empGend = gend;

}

// Getters
char Employee_C::Get_Name() const
{
	return empName[NM_SZ];
}

int Employee_C::Get_ID() const
{
	return empID;
}

double Employee_C::Get_Sal() const
{
	return empSal;
}

char Employee_C::Get_Gend() const
{
	return empGend;
}

double Employee_C::Get_All_Sal() const
{
	return allSal;
}

// Setters
void Employee_C::Set_Name(char nm[])
{
	empName [NM_SZ] = nm [NM_SZ];
}

void Employee_C::Set_ID(int id)
{
	empID = id;
}

void Employee_C::Set_Sal(double sal)
{
	empSal = sal;
}

void Employee_C::Set_Gend(char gend)
{
	empGend = gend;
}

double Employee_C::Calc_Sal(double sal, double prevSal)
{
	allSal -= prevSal;
	allSal += sal;
	return allSal;
}