/*------------------------------------------------------
Final Project Milestone 6
Module: ReadWritable
Filename: ReadWritable.h
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#ifndef SDDS_READWRITABLE_H__
#define SDDS_READWRITABLE_H__
#include <iostream>

namespace sdds 
{
	class ReadWritable 
	{
		bool comma;

	public:
		ReadWritable();
		virtual ~ReadWritable();
		bool isCsv()const;
		void setCsv(bool value);
		virtual std::ostream& write(std::ostream& os = std::cout) const = 0;
		virtual std::istream& read(std::istream& is = std::cin) = 0;
	};

	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw);
	std::istream& operator>>(std::istream& is, ReadWritable& rw);
}
#endif