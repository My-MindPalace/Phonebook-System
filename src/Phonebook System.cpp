/*	Phonebook System.cpp : Defines the entry point for the console application.
	Author - My-MindPalace
	***Phone Book System***

	Features - 
	i)		Add new Contacts 
	ii)		Search for a contact
	iii)	Display the entire phonebook
	iv)		Update an existing phonebook entry
*/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
using namespace std;
fstream file;


//Class for records in the phonebook
class ContactRecord
{
	public:
		string id;
		string name;
		string number;
};

class PhonebookController
{
	vector<ContactRecord> phonebook;	//list of ContactRecords in a vector
	public:
		void createRecord()
		{
			system("CLS");
			file.open("data/records.txt",ios_base::app);
			ContactRecord *contact;
			contact = new ContactRecord();
			cout << "Enter the ID of the new Contact" << endl;
			cin >> contact->id;
			cout << "Enter the name of the new Contact" << endl;
			cin >> contact->name;
			cout << "Enter the phone number" << endl;
			cin >> contact->number;
			phonebook.push_back(*contact);
			makeAnEntry(contact->id, contact->name, contact->number);
			file.close();
		}

		void showPhonebook()
		{
			file.open("data/records.txt", ios::in);
			char ch;
			system("CLS");
			cout << "ID\tNAME\tNUMBER" << endl;
			while (!file.eof())
			{
				file >> ch;
				if (ch == ',')
				{
					cout << "\t";
					continue;
				}
				else if (ch == '.')
				{
					cout << "\n";
					continue;
				}
				cout << ch;
			}
			file.close();
			_getch();
		}

		void search()
		{
			system("CLS");
			string key;
			cout << "Enter the value to be searched" << endl;
			cin >> key;
			int i;
			for (i = 0; i < phonebook.size(); i++)
			{
				if (key.compare(phonebook[i].name) == 0)
				{
					cout << "ID\tNAME\tNUMBER" << endl;
					cout << phonebook[i].id << "\t" << phonebook[i].name << "\t" << phonebook[i].number << endl;
					_getch();
				}
			}
		}
		
		void updatePhonebook()
		{
			int i,ch;
			string name;
			system("CLS");
			cout << "Enter the name of the contact which has to be updated" << endl;
			cin >> name;
			cout << "Update ?\n1. NAME\n2. NUMBER\n choice - ";
			cin >> ch;
			for (i = 0; i < phonebook.size(); i++)
			{
				if (name.compare(phonebook[i].name) == 0)
				{
					system("CLS");
					switch (ch)
					{
						case 1: cout << "Enter the new name of the contact" << endl;
							cin >> phonebook[i].name;
							break;

						case 2: cout << "Enter the new number of the contact" << endl;
							cin >> phonebook[i].number;
							break;
					}
				}
			}
		}
	private:
		void makeAnEntry(string id,string name, string number)
		{
			file << id << "," << name << "," << number << "." <<endl;
			cout << "Entry added" << endl;
		}

};

int main()
{
	int choice=0;
	string key;
	PhonebookController pc;
	while (choice != 5)
	{
		system("CLS");
		cout << "# MAIN MENU #" << endl;
		cout << "1. New Contact" << endl;
		cout << "2. Update Exisiting Contact" << endl;
		cout << "3. Search Contact" << endl;
		cout << "4. Show Phonebook Entries" << endl;
		cout << "5. Exit" << endl;
		cout << "Your Choice - ";
		cin >> choice;
		switch(choice)
		{
			case 1:	pc.createRecord();
					break;

			case 2: pc.updatePhonebook();
					break;

			case 3: pc.search();
					break;

			case 4: pc.showPhonebook();
					break;

			case 5: exit(EXIT_SUCCESS);
		}
	}
	_getch();
    return 0;
}

