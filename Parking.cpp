/*------------------------------------------------------
Final Project Milestone 6
Module: Parking
Filename: Parking.cpp
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Parking.h"

using namespace std;

namespace sdds 
{
	Parking::Parking() 
	{
		this->setEmpty();
	}
	
	Parking::Parking(const char* file, int numberOfSpots) 
	{
		this->setEmpty();
		setFileName(file);	

		if (numberOfSpots >= 10 && numberOfSpots <= MAXSPOTS) 
		{
			m_numberOfSpots = numberOfSpots;
		}
		else 
		{
			m_numberOfSpots = 0;
		}

		if (loadFile())
		{
			m_parkingMenu = Menu("Parking Menu, select an action:", 0);
			m_parkingMenu << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Close Parking (End of day)" << "Exit Program";
			m_vehicleMenu = Menu("Select type of the vehicle:", 1);
			m_vehicleMenu << "Car" << "Motorcycle" << "Cancel";
		}
		else
		{
			cout << "Error in data file" << endl;
			this->setEmpty();
		}		
	}

	void Parking::setFileName(const char* file) 
	{
		if (file != nullptr && file[0] != '\0')
		{
			m_fileName = new char[strlen(file) + 1];
			strcpy(m_fileName, file);
		}
		else 
		{
			m_fileName = nullptr;
		}
	}

	void Parking::setEmpty() 
	{
		setFileName(nullptr);

		m_parkingMenu = Menu();
		m_vehicleMenu = Menu();
		m_numberOfSpots = 0;

		for (int i = 0; i < MAXSPOTS; i++) {
			m_spots[i] = nullptr;
		}
		m_numOfParked = 0;
	}

	bool Parking::isEmpty() const 
	{
		return m_fileName == nullptr;
	}


	void Parking::parkingStatus() const {
		cout << "****** Seneca Valet Parking ******" << endl;
		cout << "*****  Available spots: ";
		cout.width(4);
		cout.setf(ios::left);
		cout << m_numberOfSpots - m_numOfParked << " *****" << endl;
		cout.unsetf(ios::left);
	}

	void Parking::parkVehicle() 
	{
		if (m_numberOfSpots == m_numOfParked) 
		{
			cout << "Parking is full" << endl;
		}
		else
		{
			int choice = m_vehicleMenu.run();
			if (choice == 3) 
			{
				cout << "Parking cancelled" << endl;
			}
			else 
			{
				Vehicle* vehicle = nullptr;
				if (choice == 1) 
				{
					vehicle = new Car();
				}
				else if (choice == 2)
				{
					vehicle = new Motorcycle();
				}

				vehicle->setCsv(false);
				cin >> *vehicle;
	
				bool valid = true;

				for (int i = 0; i < m_numberOfSpots && valid; i++) 
				{
					if (m_spots[i] != nullptr && *m_spots[i] == *vehicle) 
					{
						cout << "\nCan not park; license plate already in the system!" << endl;
						cout << *vehicle;
						cout << endl;
						valid = false;
					}
				}
				if (valid && m_numOfParked < m_numberOfSpots) 
				{
					for (int i = 0; i < m_numberOfSpots && valid; i++)
					{
						if (m_spots[i] == nullptr) 
						{
							m_spots[i] = vehicle;
							m_spots[i]->setParkingSpot(i + 1);

							cout << "\nParking Ticket" << endl;
							cout << *m_spots[i]; 
							cout << endl;

							m_numOfParked++;
							valid = false;
						}
					}
				}
			}
		}		
	}

	void Parking::returnVehicle() 
	{
		cout << "Return Vehicle" << endl;

		char licensePlate[MAX_PLATE + 1] = { '\0' };
		bool valid;

		cout << "Enter Licence Plate Number: ";
		do {
			valid = false;
			cin >> licensePlate;
			cin.ignore();
			if (strlen(licensePlate) < 1 || strlen(licensePlate) > MAX_PLATE)
			{
				cout << "Invalid Licence Plate, try again: ";
				valid = true;
			}
		} while (valid);

		toUpper(licensePlate);

		bool flag = true;
		for (int i = 0; i < m_numberOfSpots && flag; i++) 
		{
			if (m_spots[i] != nullptr && *m_spots[i] == licensePlate) 
			{
				cout << "\nReturning: " << endl;
				m_spots[i]->setCsv(false);

				cout << *m_spots[i];
				cout << endl;

				delete m_spots[i];
				m_spots[i] = nullptr;

				m_numOfParked--;
				flag = false;
			}
		}

		if (flag)
		{
			cout << "\nLicense plate " << licensePlate << " Not found\n" << endl;
		}
	}

	void Parking::vehicleList() const
	{
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < m_numberOfSpots; i++) 
		{
			if (m_spots[i] != nullptr)
			{
				m_spots[i]->setCsv(false);
				cout << *m_spots[i];
				cout << "-------------------------------" << endl;
			}
		}
	}
	
	bool Parking::parkingClose() 
	{
		bool valid = false;

		if (m_numOfParked == 0) 
		{
			cout << "Closing Parking" << endl;
			valid = true;
		}
		else 
		{
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";

			if (yes()) 
			{
				cout << "Closing Parking" << endl;
				for (int i = 0; i < m_numberOfSpots; i++) 
				{
					if (m_spots[i] != nullptr) 
					{
						cout << endl << "Towing request" << endl;
						cout << "*********************" << endl;
						cout << *m_spots[i];
						delete m_spots[i];
						m_spots[i] = nullptr;
						m_numOfParked--;
					}
				}
				saveFile();
				valid = true;
			}
			else
			{
				cout << "Aborted!" << endl;
				valid = false;
			}
		}

		return valid;
	}

	bool Parking::exitApp() const 
	{		
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		bool choice = yes();
		if (choice) {
			saveFile();
		}

		return choice;
	}

	bool Parking::loadFile() 
	{
		bool flag = true;
		ifstream fileIn;

		if (!isEmpty()) 
		{
			fileIn.open(m_fileName);
		}

		char vType;
		Vehicle* vehicle;
		m_numOfParked = 0;

		while (m_numOfParked < m_numberOfSpots && flag && fileIn) 
		{
			vType = 'x';
			vehicle = nullptr;

			fileIn >> vType;
			fileIn.ignore();

			if (vType == 'C') 
			{
				vehicle = new Car();
			}
			else if (vType == 'M') 
			{
				vehicle = new Motorcycle();
			}

			if (vehicle) 
			{
				vehicle->setCsv(true);
				fileIn >> *vehicle;
				if (fileIn)
				{
					m_spots[vehicle->getParkingSpot() - 1] = vehicle;
					m_numOfParked++;
				}			
				else 
				{
					delete vehicle;
					vehicle = nullptr;
					flag = false;
				}
			}
		}

		return flag;
	}

	void Parking::saveFile() const
	{
		if (!isEmpty()) 
		{
			ofstream fileOut(m_fileName);

			if (fileOut) 
			{
				for (int i = 0; i < m_numberOfSpots; i++) 
				{
					if (m_spots[i] != nullptr) 
					{
						m_spots[i]->setCsv(true);
						fileOut << *m_spots[i];
					}
				}
			}
		}
	}

	int Parking::run() 
	{
		int choice = 1;

		if (!isEmpty()) 
		{	
			choice = 0;
			int option, flag;

			do
			{
				parkingStatus();
				flag = 1;
				option = m_parkingMenu.run();
				
				switch (option)
				{
				case 1:
					parkVehicle();
					break;
				case 2:
					returnVehicle();
					break;
				case 3:
					vehicleList();
					break;
				case 4:
					if (parkingClose()) 
					{
						flag = 0;
					}
					break;
				default:
					if (exitApp()) 
					{
						cout << "Exiting program!" << endl;
						flag = 0;
					}
					break;
				}
			} while (flag);
		}
		return choice;
	}

	Parking::~Parking() 
	{
		saveFile();
		delete[] m_fileName;
		m_fileName = nullptr;

		for (int i = 0; i < MAXSPOTS; i++) {
			delete m_spots[i];
			m_spots[i] = nullptr;
		}
	}
}