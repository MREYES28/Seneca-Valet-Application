/*------------------------------------------------------
Final Project Milestone 6
Module: Menu
Filename: Menu.h
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>

const int MAX_NO_OF_ITEMS = 10;

namespace sdds {

	class MenuItem 
	{
		char* m_menuItemString;
		friend class Menu;

		MenuItem();
		MenuItem(const char*);
		void setItem(const char*);
		MenuItem(const MenuItem& src) = delete;
		MenuItem& operator=(const MenuItem& src) = delete;
		std::ostream& display() const;
		~MenuItem();
	};

	class Menu 
	{
		char* m_title;
		MenuItem* m_itemsOfMenu[MAX_NO_OF_ITEMS];
		int m_numOfItems;
		int m_indent;

	public:
		Menu();
		Menu(const char*, int = 0);
		Menu(const Menu&);
		virtual ~Menu();
		Menu& operator=(const Menu&);
		void setEmpty();
		void setTitle(const char*);
		void setItems(MenuItem* const[], int);
		void setIdentation(int );
		operator bool() const;
		bool isEmpty() const;
		std::ostream& display() const;
		Menu& operator=(const char*);
		void add(const char*);
		Menu& operator<<(const char*);		
		int run() const;
		operator int() const;
	};		
}
#endif