// Exercises for Chapter 10

#include <iostream>

class Employee
{
	public:
		int getAge() const;
		int getYearsOfService() const;
		long int getSalary() const;
		void setAge(int age);
		void setYearsOfService(int years);
		void setSalary(long int salary);
		
	private:
		int itsAge;
		int itsYearsOfService;
		long int itsSalary;
};

void printInfo(Employee name);

int  Employee::getAge() const
{
	return itsAge;
}

int Employee::getYearsOfService() const
{
	return itsYearsOfService;
}

long int Employee::getSalary() const
{
	return itsSalary;
}

void Employee::setAge(int age)
{
	itsAge=age;
}

void Employee::setYearsOfService(int years)
{
	itsYearsOfService=years;
}

void Employee::setSalary(long int salary)
{
	itsSalary=salary;
}

using namespace std;

int main()
{
	//Setting up two employees, Dave and Tom
	
	Employee Dave;
	Employee Tom;
	
	Dave.setAge(30);
	Dave.setYearsOfService(5);
	Dave.setSalary(35000);
	
	Tom.setAge(65);
	Tom.setYearsOfService(40);
	Tom.setSalary(6677000);
	

	//Printing their information
	
	cout << "Dave's Information" << endl;
	cout << "Here is the info for the employee: " << endl;
	printInfo(Dave);
	
	cout << endl << "Tom's Information" << endl;
	cout << "Here is the info for the employee: " << endl;
	printInfo(Tom);	
	
	
	return 0;
	
}
	
void printInfo(Employee name)
{
	cout << "Age: " << name.getAge() << endl;
	cout << "Years of Service: " << name.getYearsOfService() << endl;
	cout << "Salary: $" << name.getSalary() << endl;
}
	
	
	