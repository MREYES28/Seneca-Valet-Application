/*------------------------------------------------------
Final Project Milestone 6
Module: Motorcycle
Filename: Motorcycle.cpp
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/

#include <iostream>
#include "Motorcycle.h"

using namespace std;

namespace sdds 
{
	Motorcycle::Motorcycle() 
	{
		Vehicle::setEmpty();
		m_hasSideCar = false;
	}

	Motorcycle::Motorcycle(const char* licensePlate, const char* makeModel, int parkingSpotNumber, bool flag) : Vehicle(licensePlate, makeModel, parkingSpotNumber) 
	{
		m_hasSideCar = flag;
	}
	
	istream& Motorcycle::read(istream& is) 
	{
		if (isCsv()) 
		{
			Vehicle::read(is);
			int choice;
			is >> choice;
			m_hasSideCar = bool(choice);
			is.ignore();
		}
		else 
		{
			cout << "\nMotorcycle information entry" << endl;
			Vehicle::read(is);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			m_hasSideCar = yes();
		}

		return is;
	}

	ostream& Motorcycle::write(ostream& os) const
	{
		if (isEmpty()) 
		{
			os << "Invalid Motorcycle Object" << endl;
		}
		else 
		{
			if (isCsv()) 
			{
				os << "M,";
				Vehicle::write(os);
				os << int(m_hasSideCar) << endl;
			}
			else
			{
				os << "Vehicle type: Motorcycle" << endl;
				Vehicle::write(os);
				if (m_hasSideCar) 
				{
					os << "With Sidecar" << endl;
				}
			}
		}

		return os;
	}

	Motorcycle::~Motorcycle() 
	{

	}
}