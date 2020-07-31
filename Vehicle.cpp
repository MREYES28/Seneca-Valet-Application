/*------------------------------------------------------
Final Project Milestone 6
Module: Vehicle
Filename: Vehicle.cpp
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>
#include <cctype>
#include <cstring>
#include "Vehicle.h"

using namespace std;

namespace sdds {

	void Vehicle::setEmpty() 
	{
		m_licensePlate[0] = '\0';
		m_makeModel = nullptr;
		m_parkingSpotNumber = 0;
	}

	bool Vehicle::isEmpty() const 
	{
		return m_licensePlate[0] == '\0' || m_makeModel == nullptr;
	}
	
	const char* Vehicle::getLicensePlate() 
	{
		return m_licensePlate;
	}

	const char* Vehicle::getMakeModel() 
	{
		return m_makeModel;
	}

	void Vehicle::setMakeModel(const char* makeModel)
	{
		if (makeModel != nullptr && makeModel[0] != '\0' && strlen(makeModel) >= MIN_LENGTH)
		{

			delete[] m_makeModel;
			m_makeModel = new char[strlen(makeModel) + 1];
			strcpy(m_makeModel, makeModel);
		}
		else 
		{
			delete[] m_makeModel;
			setEmpty();
		}
	}

	Vehicle::Vehicle() : ReadWritable() 
	{
		setEmpty();
	}

	Vehicle::Vehicle(const char* licensePlate, const char* makeModel, int parkingSpotNumber) : ReadWritable() 
	{
		setEmpty();

		if (licensePlate != nullptr && licensePlate[0] != '\0' && strlen(licensePlate) <= MAX_PLATE) 
		{
			strncpy(m_licensePlate, licensePlate, MAX_PLATE);
			m_licensePlate[MAX_PLATE] = '\0';
			toUpper(m_licensePlate);
		}
		else 
		{
			m_licensePlate[0] = '\0';
		}
		setMakeModel(makeModel);
		setParkingSpot(parkingSpotNumber);
	}
	
	int Vehicle::getParkingSpot() const 
	{
		return m_parkingSpotNumber;
	}

	void Vehicle::setParkingSpot(int parkingSpotNumber) 
	{
		if (parkingSpotNumber >= 0) 
		{
			m_parkingSpotNumber = parkingSpotNumber;
		}
		else 
		{
			delete[] m_makeModel;
			setEmpty();
		}
	}

	bool operator==(const Vehicle& v, const char* licensePlate) 
	{
		bool same = false;

		if (!v.isEmpty()) 
		{
			if (licensePlate != nullptr && licensePlate[0] != '\0' 
				&& strlen(licensePlate) <= MAX_PLATE)
			{
				if (strCmp(v.m_licensePlate, licensePlate)) 
				{
					same = true;
				}
			}
		}

		return same;
	}

	bool operator==(const Vehicle& a, const Vehicle& b)
	{
		bool same = false;

		if (!a.isEmpty() && !b.isEmpty()) 
		{
			if (strCmp(a.m_licensePlate, b.m_licensePlate)) 
			{
				same = true;
			}
		}
		
		return same;
	}

	istream& Vehicle::read(istream& is) 
	{
		if (isCsv()) 
		{
			is >> m_parkingSpotNumber;
			is.ignore();
			is.getline(m_licensePlate, MAX_PLATE + 1, ',');
			toUpper(m_licensePlate);	

			char temp[60 + 1] = { '\0' };
			is.getline(temp, 60 + 1, ',');
			setMakeModel(temp);
		}
		else 
		{
			cout << "Enter Licence Plate Number: ";
			char tempLicensePlate[MAX_PLATE + 2];
			int invalid;

			do {
				invalid = 0;
				is.getline(tempLicensePlate, MAX_PLATE + 2);

				if (strlen(tempLicensePlate) == 0 || strlen(tempLicensePlate) > MAX_PLATE) {
					invalid = 1;
					cout << "Invalid Licence Plate, try again: ";			
				}	
				is.clear();
			} while (invalid);

			strncpy(m_licensePlate, tempLicensePlate, MAX_PLATE);
			m_licensePlate[MAX_PLATE] = '\0';
			toUpper(m_licensePlate);
			
			cout << "Enter Make and Model: ";
			char temp[60 + 2] = { '\0' };

			do {
				invalid = 0;				
				is.getline(temp, 60 + 2);

				if (strlen(temp) < 2 || strlen(temp) > 60) {
					invalid = 1;
					cout << "Invalid Make and model, try again: ";
					is.clear();
				}				
			} while (invalid);

			setMakeModel(temp);
			m_parkingSpotNumber = 0;
		}

		if (is.fail()) 
		{
			is.clear();
			setEmpty();
		}
		
		return is;
	}

	ostream& Vehicle::write(ostream& os) const 
	{
		if (isEmpty()) 
		{
			os << "Invalid Vehicle Object" << endl;
		}
		else
		{
			if (isCsv()) 
			{
				os << m_parkingSpotNumber << "," << m_licensePlate << "," << m_makeModel << ",";
			}
			else 
			{
				os << "Parking Spot Number: ";
				if (m_parkingSpotNumber > 0) 
				{
					os << m_parkingSpotNumber << endl;
				}
				else 
				{
					os << "N/A" << endl;
				}
				os << "Licence Plate: " << m_licensePlate << endl;
				os << "Make and Model: " << m_makeModel << endl;
			}
		}

		return os;
	}

	Vehicle::~Vehicle() 
	{
		delete[] m_makeModel;
		m_makeModel = nullptr;
	}

	char* toUpper(char* str) 
	{
		for (int i = 0; str[i] != '\0'; i++) 
		{
			str[i] = toupper(str[i]);
		}

		return str;
	}

	bool strCmp(const char* str1, const char* str2) 
	{
		bool valid = false;

		int sizeOfStr1 = strlen(str1);
		int sizeOfStr2 = strlen(str2);

		if (sizeOfStr1 == sizeOfStr2) 
		{
			char* tempStr1 = new char[sizeOfStr1 + 1];
			strcpy(tempStr1, str1);
			toUpper(tempStr1);

			char* tempStr2 = new char[sizeOfStr1 + 1];
			strcpy(tempStr2, str2);
			toUpper(tempStr2);

			if (strcmp(tempStr1, tempStr2) == 0) 
			{
				valid = true;
			}

			delete[] tempStr1;
			tempStr1 = nullptr;
			delete[] tempStr2;
			tempStr2 = nullptr;
		}

		return valid;
	}

	bool yes() 
	{
		string option;
		bool choice, valid;
		do {
			valid = true;
			cin >> option;
			cin.ignore(1000, '\n');

			if (option == "Y" || option == "y") 
			{
				choice = true;
			}
			else if (option == "N" || option == "n") 
			{
				choice = false;
			}
			else 
			{
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				valid = false;
				cin.clear();
			}
		} while (!valid);

		return choice;
	}
}