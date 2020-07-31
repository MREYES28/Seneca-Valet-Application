/*------------------------------------------------------
Final Project Milestone 6
Module: Menu
Filename: Menu.cpp
Author	Melvyn Reyes
-----------------------------------------------------------
Had help from my friends Billy, George, Visa, and Isaac
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "Utils.h"
#include "Menu.h"

using namespace std;

namespace sdds {

	MenuItem::MenuItem()
	{
		setItem(nullptr);
	}

	MenuItem::MenuItem(const char* menuItemString) 
	{
		setItem(menuItemString);
	}

	void MenuItem::setItem(const char* menuItemString) 
	{
		if (menuItemString != nullptr && menuItemString[0] != '\0') 
		{
			m_menuItemString = new char[strlen(menuItemString) + 1];
			strcpy(m_menuItemString, menuItemString);
		}
		else
		{
			m_menuItemString = nullptr;
		}
	}

	ostream& MenuItem::display() const
	{
		if (m_menuItemString != nullptr && m_menuItemString[0] != '\0') {
			cout << m_menuItemString << endl;
		}
		return cout;
	}

	MenuItem::~MenuItem() 
	{
		delete[] m_menuItemString;
		m_menuItemString = nullptr;
	}

	Menu::Menu() 
	{
		setEmpty();
	}

	Menu::Menu(const char* title, int indent) 
	{
		setTitle(title);
		setItems({nullptr}, 0);
		setIdentation(indent);
	}

	Menu::Menu(const Menu& src)
	{
		setTitle(src.m_title);
		setItems(src.m_itemsOfMenu, src.m_numOfItems);
		setIdentation(src.m_indent);
	}

	Menu& Menu::operator=(const Menu& src) 
	{
		if (this != &src) 
		{
			delete[] m_title;
            for (int i = 0; i < m_numOfItems; i++) 
				{
                delete m_itemsOfMenu[i];
                m_itemsOfMenu[i] = nullptr;
            }
			setTitle(src.m_title);
			setItems(src.m_itemsOfMenu, src.m_numOfItems);
			setIdentation(src.m_indent);
		}

		return *this;
	}

	void Menu::setEmpty() 
	{
		setTitle(nullptr);
		setItems({nullptr}, 0);
		setIdentation(0);
	}

	void Menu::setTitle(const char* title) 
	{
		if (title != nullptr && title[0] != '\0')
		{
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
		}
		else 
		{
			m_title = nullptr;
		}
	}

	void Menu::setItems(MenuItem* const itemsOfMenu[], int numOfItems) 
	{
		if (numOfItems > 0) 
		{
			m_numOfItems = numOfItems <= MAX_NO_OF_ITEMS ? numOfItems : MAX_NO_OF_ITEMS;

			for (int i = 0; i < m_numOfItems; i++) 
			{
				m_itemsOfMenu[i] = new MenuItem(itemsOfMenu[i]->m_menuItemString);
			}
		}
		else 
		{
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++)
			{
				m_itemsOfMenu[i] = nullptr;
			}
			m_numOfItems = 0;
		}
	}

	void Menu::setIdentation(int indent) 
	{
		if (indent > 0) 
		{
			m_indent = indent;
		}
		else 
		{
			m_indent = 0;
		}
	}

	Menu::operator bool() const 
	{
		return !isEmpty();
	}

	bool Menu::isEmpty() const 
	{
		return m_title == nullptr;
	}

	ostream& Menu::display() const 
	{
		if (isEmpty()) 
		{
			cout << "Invalid Menu!" << endl;
		}
		else 
		{
			int indent = m_indent * 4;

			cout.width(indent);
			cout << "";
			cout << m_title << endl;

			if (m_itemsOfMenu[0] == nullptr) 
			{
				cout << "No Items to display!" << endl;
			}
			else 
			{
				for (int i = 0; i < m_numOfItems; i++) 
				{
					cout.width(indent);
					cout << "";
					cout << i + 1 << "- ";
					m_itemsOfMenu[i]->display();
				}
				cout.width(indent);
				cout << "";
				cout << "> ";
			}
		}
		return cout;
	}

	Menu& Menu::operator=(const char* title) 
	{
		delete[] m_title;
		setTitle(title);

		return *this;
	}	

	void Menu::add(const char* itemsOfMenu) 
	{
		if (!isEmpty()) 
		{
			if (m_numOfItems < MAX_NO_OF_ITEMS) 
			{
				if (itemsOfMenu != nullptr && itemsOfMenu[0] != '\0')
				{
					m_itemsOfMenu[m_numOfItems] = new MenuItem(itemsOfMenu);
					m_numOfItems++;
				}
				else
				{
					delete[] m_title;
					m_title = nullptr;
					for (int i = 0; i < m_numOfItems; i++) {
						delete m_itemsOfMenu[i];
						m_itemsOfMenu[i] = nullptr;
					}
					setEmpty();
				}
			}
		}
	}

	Menu& Menu::operator<<(const char* itemsOfMenu) 
	{
		add(itemsOfMenu);
		return *this;
	}

	int Menu::run() const 
	{
		int choice = 0;

		display();

		if (m_itemsOfMenu[0] != nullptr) 
		{
			int valid;
			do {
				valid = 0;
				cin >> choice;

				if (cin.fail()) 
				{
					cout << "Invalid Integer, try again: ";
					valid = 1;
				}
				else
				{
					if (choice < 1 || choice > m_numOfItems) 
					{
						cout << "Invalid selection, try again: ";
						valid = 1;
					}
				}
				cin.clear();
				cin.get();
			} while (valid);
		}

		return choice;
	}

	Menu::operator int() const
	{
		return run();
	}

	Menu::~Menu() 
	{
		delete[] m_title;
		m_title = nullptr;
		for (int i = 0; i < m_numOfItems; i++) 
		{
			delete m_itemsOfMenu[i];
			m_itemsOfMenu[i] = nullptr;
		}
	}
}