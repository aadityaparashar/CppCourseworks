// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Data.h"
#include <algorithm>

void testCreateAndPrint() {
	Data dat = Data(100);
	dat.printAll();
	cout << endl;
	int count = dat.countAll();
	cout << count << endl;
}

void testGetGroup() {
	Data dat = Data(1000);

	list<Item>* it = dat.getGroup('A');

	cout << it->size() << endl;

	list<Item>* itSub = dat.getSubGroup('Q', 98);

	if (itSub != nullptr) {
		std::for_each(itSub->begin(), itSub->end(), [](Item& s) {std::cout << s.getName() << " has parameters: Date - " << s.getDate().ToString() << " Group - " << s.getGroup() << " Subgroup " << s.getSubGroup() << "\n";
			});
		cout << itSub->size() << endl;
	}


}

void printSubgroup() {
	Data dat = Data(1000);
	dat.printSubGroupByNames('Q', 98);
	cout << endl;
	cout << endl;
	dat.printSubGroupByDates('Q', 98);
}

void testPrintandGetItem() {
	Data dat = Data(1000);
	Date dt = Date(24, 2, 1999);
	Item* testItemSearchDate = dat.GetItem('Q', 98, dt);
	std::cout << testItemSearchDate->getName() << " has parameters: Date - " << testItemSearchDate->getDate().ToString() << " Group - " << testItemSearchDate->getGroup() << " Subgroup " << testItemSearchDate->getSubGroup() << "\n";
	dat.PrintItem('Q', 98, "Teena");
	dat.PrintItem('Q', 98, dt);
	cout << endl;
}

void testRemoves() {

	Data dat = Data(100);
	dat.printAll();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	dat.RemoveGroup('A');
	dat.pringGroup('A');
	dat.RemoveSubgroup('C', 16);
	Date dt = Date(11, 10, 2005);
	dat.RemoveItem('B', 44, dt);
	dat.printAll();
}

int main()
{
	testRemoves();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
