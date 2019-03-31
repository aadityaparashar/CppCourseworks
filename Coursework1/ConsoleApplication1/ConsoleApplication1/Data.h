#pragma once
#include <list>
#include "Item.h"
#include <Map>
using namespace std;
class Data {
public:
	Data(int n);
	~Data();
	void printAll();
	int countAll();
	list<Item>* getGroup(char group);
	bool pringGroup(char group);
	int countGroup(char group);
	list<Item>* getSubGroup(char group, int subGroup);
	bool printSubGroupByNames(char group, int subGroup);
	bool printSubGroupByDates(char group, int subGroup);
	int countSubGroup(char group, int subGroup);
	Item* GetItem(char g, int sg, string n);
	Item* GetItem(char g, int sg, Date d);
	bool PrintItem(char g, int sg, string n);
	bool PrintItem(char g, int sg, Date d);
	bool RemoveGroup(char g);
	bool RemoveSubgroup(char g, int sg);
	bool RemoveItem(char g, int sg, string n);
	bool RemoveItem(char g, int sg, Date d);
private:
	map<char, list<Item>>* dataSet = new map<char, list<Item>>();
	list<Item> objectList;
	struct prt_pairs;
};