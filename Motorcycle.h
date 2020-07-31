/*------------------------------------------------------
Final Project Milestone 6
Module: Motorcycle
Filename: Motorcycle.h
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#ifndef SDDS_MOTORCYCLE_H__
#define SDDS_MOTORCYCLE_H__

#include "Vehicle.h"

namespace sdds 
{
	class Motorcycle : public Vehicle 
	{

		bool m_hasSideCar;

	public:

		Motorcycle();
		Motorcycle(const char* plate, const char* makeModel, int spotNum = 0, bool flag = false);
		virtual ~Motorcycle();
		Motorcycle(const Motorcycle& mCopy) = delete;
		Motorcycle& operator=(const Motorcycle& mCopy) = delete;
		virtual std::istream& read(std::istream& istr = std::cin);
		virtual std::ostream& write(std::ostream& ostr = std::cout) const;
	};
}
#endif