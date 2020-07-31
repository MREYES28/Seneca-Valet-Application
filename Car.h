/*------------------------------------------------------
Final Project Milestone 6
Module: Car
Filename: Car.h
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#ifndef SDDS_CAR_H__
#define SDDS_CAR_H__

#include <iostream>
#include "Vehicle.h"

namespace sdds {
	class Car : public Vehicle 
	{
		bool m_carWash;

	public:

		Car();
		Car(const char*, const char*, int = 0, bool = false);
		virtual ~Car();
		Car(const Car& c) = delete;
		Car& operator=(const Car& c) = delete;
		virtual std::istream& read(std::istream& is = std::cin);
		virtual std::ostream& write(std::ostream& os = std::cout) const;
	};
}
#endif