/*------------------------------------------------------
Final Project Milestone 6
Module: Parking
Filename: Parking.h
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__

#include "Menu.h"
#include "Car.h"
#include "Motorcycle.h"

const int MAXSPOTS = 100;

namespace sdds 
{
	class Parking : public Menu 
	{
	private:
		char* m_fileName;
		Menu m_parkingMenu;
		Menu m_vehicleMenu;
		int m_numberOfSpots;
		Vehicle* m_spots[MAXSPOTS];
		int m_numOfParked;

		void setEmpty();
		bool isEmpty() const;
		void parkingStatus() const;
		void parkVehicle();
		void returnVehicle();
		void vehicleList() const;
		bool parkingClose();
		bool exitApp() const;
		bool loadFile();
		void saveFile() const;

	public:
		using Menu::Menu;

		Parking();
		Parking(const char*, int);
		Parking(const Parking& pCopy) = delete;
		Parking& operator=(const Parking& p) = delete;
		void setFileName(const char*);
		int run(); 
		~Parking();		
	};
}
#endif