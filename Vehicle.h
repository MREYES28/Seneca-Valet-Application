/*------------------------------------------------------
Final Project Milestone 6
Module: Vehicle
Filename: Vehicle.h
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/

#ifndef SDDS_VEHICLE_H__
#define SDDS_VEHICLE_H__

#include "ReadWritable.h"

const int MAX_PLATE = 8;
const int MIN_LENGTH = 2;
const int MAX_LENGTH = 60;

namespace sdds {
	class Vehicle : public ReadWritable {
		char m_licensePlate[MAX_PLATE + 1];
		char* m_makeModel;
		int m_parkingSpotNumber;
	protected:
		void setEmpty();
		bool isEmpty() const;
		const char* getLicensePlate();
		const char* getMakeModel();
		void setMakeModel(const char*);
	public:
		Vehicle();
		Vehicle(const char*, const char*, int = 0);
		Vehicle(const Vehicle& v) = delete;
		Vehicle& operator=(const Vehicle& v) = delete;
		int getParkingSpot() const;
		void setParkingSpot(int);
		virtual std::istream& read(std::istream& is = std::cin);
		virtual std::ostream& write(std::ostream& os = std::cout) const;
		friend bool operator==(const Vehicle&, const char*);
		friend bool operator==(const Vehicle&, const Vehicle&);
		virtual ~Vehicle();
	};
	char* toUpper(char*);
	bool strCmp(const char*, const char*);
	bool yes();
	
}
#endif //!SDDS_VEHICLE_H__