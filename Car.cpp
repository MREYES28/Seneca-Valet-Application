/*------------------------------------------------------
Final Project Milestone 6
Module: Car
Filename: Car.cpp
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/

#include <iostream>
#include "Car.h"

using namespace std;

namespace sdds {
	Car::Car()
	{
		Vehicle::setEmpty();
		m_carWash = false;
	}

	Car::Car(const char* licensePlate, const char* makeModel, int ParkingSpotNumber, bool flag) : Vehicle(licensePlate, makeModel, ParkingSpotNumber) 
	{
		m_carWash = flag;
	}

	istream& Car::read(istream& is)
	{

		if (isCsv()) 
		{
			Vehicle::read(is);

			int choice;
			is >>  choice;
			m_carWash = choice;
			is.ignore();
		}
		else
		{
			cout << "\nCar information entry" << endl;
			Vehicle::read(is);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			m_carWash = yes();
		}

		return is;
	}
	
	ostream& Car::write(ostream& os) const
	{
		if (isEmpty()) 
		{
			os << "Invalid Car Object" << endl;
		}
		else 
		{
			if (isCsv()) 
			{
				os << "C,";
				Vehicle::write(os);
				os << int(m_carWash) << endl;
			}
			else {
				os << "Vehicle type: Car" << endl;
				Vehicle::write(os);
				if (m_carWash) {
					os << "With Carwash" << endl;
				}
				else {
					os << "Without Carwash" << endl;
				}
			}
		}

		return os;
	}

	Car::~Car() 
	{

	}
}