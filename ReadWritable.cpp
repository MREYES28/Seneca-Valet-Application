/*------------------------------------------------------
Final Project Milestone 6
Module: ReadWritable
Filename: ReadWritable.cpp
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#include <iostream>
#include "ReadWritable.h"

namespace sdds 
{
	ReadWritable::ReadWritable() 
	{
		comma = false;
	}

	bool ReadWritable::isCsv()const 
	{
		return comma;
	}

	void ReadWritable::setCsv(bool value) 
	{
		comma = value;
	}

	ReadWritable::~ReadWritable() 
	{

	}

	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw) 
	{
		rw.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, ReadWritable& rw) 
	{
		rw.read(is);
		return is;
	}
}