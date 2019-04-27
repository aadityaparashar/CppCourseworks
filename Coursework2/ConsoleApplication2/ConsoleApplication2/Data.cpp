#include "Data.h"
#include <iostream>
#include <algorithm>


int count(pair<char, list<Item>> pr, int counter) {
	counter += pr.second.size();
	return counter;
}

struct prt_pairs
{
	void operator()(pair<char, list<Item>> pr) {
		auto list = pr.second;
		//std::for_each(list.begin(), list.end(), );
		for (auto& s : list) {
			std::cout << s.getName() << " has parameters: Date - " << s.getDate().ToString() << " Group - " << s.getGroup() << " Subgroup " << s.getSubGroup() << "\n";

		}
		return;
	}
}printPairs;


struct nameComparator {
	bool operator()(Item& first, Item& second) {
		if (first.getSubGroup() == second.getSubGroup())return first.getName() < second.getName();
		return first.getSubGroup() < second.getSubGroup();
	}
};

struct dateComparator {
	bool operator()(Item& first, Item& second) {
		return first.getDate() < second.getDate();
	}
};



//constructs the object and fills the container with n random items
//every list<Item> is ordered by subgroup
Data::Data(int n) {
	for (int i = 0; i < n; i++) {
		Item a = Item();
		//if key with item.getgroup does not exist create new one
		auto iterator = dataSet->find(a.getGroup());
		if (iterator == dataSet->end()) {
			list<Item> groupedList = list<Item>();
			groupedList.push_front(a);

			//std::sort(groupedList.begin(), groupedList.end(),[](Item& first, Item& second)->bool {return (first.getSubGroup() < second.getSubGroup()); });
			dataSet->insert({ a.getGroup(), groupedList });
		}
		else {
			iterator->second.push_back(a);
			//iterator->second.sort();
			iterator->second.sort(nameComparator());
		}
	}
	this->objectList = list<Item>(n);
}

//Destructs the object and releases all the memory occupied by the container and the items in it
Data::~Data() {
	delete(dataSet);
}



//Prints all the items stored in the container in command prompt window in easily readable
//format.Items from the same group and subgroup must be ordered by their names
void Data::printAll() {
	//prt_pairs printPairs();
	std::for_each(dataSet->begin(), dataSet->end(), printPairs);


	//for (auto s : this->objectList) {
	//	std::cout << s.getName() << " has parameters: Date - " << s.getDate().ToString() << " Group - " << s.getGroup() << " Subgroup " << s.getSubGroup() << "\n";
//	}
}

//Returns the total number of items in the container. 
//using lambda expression
int Data::countAll() {
	int counter = 0;

	int(*fp)(pair<char, list<Item>>, int) = &count;
	std::for_each(dataSet->begin(), dataSet->end(), [&counter](pair<char, list<Item>> pr) {counter += pr.second.size(); });
	//return this->objectList.size();
	return counter;
}

//returns pointer to container if in original container Items with char group are present
//nullptr otherwise
//using find algorithm
list<Item>* Data::getGroup(char group) {

	if (group == NULL) return nullptr;
	auto it = dataSet->find(group);
	if (it != dataSet->end()) {
		return &(it->second);
	}
	else return nullptr;


	//list<Item>* toReturn = new list<Item>();
	/*
	for (auto s : this->objectList) {
		if (s.getGroup() == group) {
			toReturn->push_front(s);
		}
	}
	if (toReturn->size() > 0) {
		return toReturn;
	}
	return nullptr;
	*/
}


//TODO - assuming each list already ordered by subGroup - Done !

//prints items from container if group matches and returns true
//returns false if such group items were not found
bool Data::pringGroup(char group) {
	if (group == NULL)return false;
	auto it = dataSet->find(group);
	if (it != dataSet->end())std::for_each(it->second.begin(), it->second.end(), [](Item s) {std::cout << s.getName() << " has parameters: Date - " << s.getDate().ToString() << " Group - " << s.getGroup() << " Subgroup " << s.getSubGroup() << "\n"; });
	else return false;

	//list<Item>* grList;
	//if(it != dataSet->end())grList = &it->second;
	//else return false;

	//multimap<int, Item>* sbgrMap = new multimap<int,Item>();
	//std::for_each(grList->begin(), grList->end(), [sbgrMap](Item* dat) {
	//	auto it = sbgrMap->find(dat->getSubGroup());
	//	if (it == sbgrMap->end())sbgrMap->
	//});

	/*
	bool toReturn = false;
	for (auto s : this->objectList) {
		if (s.getGroup() == group) {
			toReturn = true;
			std::cout << s.getName() << " has parameters: Date - " << s.getDate().ToString() << " Group - " << s.getGroup() << " Subgroup " << s.getSubGroup() << "\n";
		}
	}
	return toReturn;
	*/
}

//returns number of Items in container with matching group
int Data::countGroup(char group) {
	auto it = dataSet->find(group);
	if (it != dataSet->end())return it->second.size();
	else return 0;
	/*
	Item it = Item();
	it.setGroup(group);
	int test = count(this->objectList.begin(), this->objectList.end(), it);
	int counter = 0;
	//for (auto s : this->objectList) {
	//	if (s.getGroup() == group) {
	//		counter++;
	//	}
	//}
	return test;*/
}


//Returns a pointer to container of all the items from group g and subgroupsg
list<Item>* Data::getSubGroup(char group, int subGroup) {
	if (group == NULL || subGroup == NULL)return nullptr;
	list<Item>* toReturn = new list<Item>;
	auto it = dataSet->find(group);
	if (it != dataSet->end()) {
		list<Item> grp = it->second;
		std::for_each(grp.begin(), grp.end(), [subGroup, &toReturn](Item dat) {
			if (&dat != nullptr)if (dat.getSubGroup() == subGroup) toReturn->push_back(dat);

			});
	}
	else return nullptr;
	/*
	for (auto s : this->objectList) {
		if (s.getGroup() == group && s.getSubGroup() == subGroup) {
			toReturn->push_front(s);
		}
	}*/
	if (toReturn->size() > 0) {
		return toReturn;

	}
	return nullptr;
}

//printing Items from same group and subgroup ordered by their names
//if not found return false;
bool Data::printSubGroupByNames(char group, int subGroup) {
	auto it = dataSet->find(group);
	int counter = 0;
	if (it != dataSet->end()) {
		list<Item> grp = it->second;
		std::for_each(grp.begin(), grp.end(), [subGroup, &counter](Item& s) {if (s.getSubGroup() == subGroup) { std::cout << s.getName() << " has parameters: Date - " << s.getDate().ToString() << " Group - " << s.getGroup() << " Subgroup " << s.getSubGroup() << "\n"; counter++; } });
		if (counter != 0)return true;
		return false;
	}
	return false;
}


bool Data::printSubGroupByDates(char group, int subGroup) {
	if (group == NULL || subGroup == NULL)return false;
	list<Item>* byDates = this->getSubGroup(group, subGroup);
	if (byDates == nullptr)return false;
	byDates->sort(dateComparator());
	std::for_each(byDates->begin(), byDates->end(), [](Item& s) {std::cout << s.getName() << " has parameters: Date - " << s.getDate().ToString() << " Group - " << s.getGroup() << " Subgroup " << s.getSubGroup() << "\n"; });
	return true;
}

int Data::countSubGroup(char group, int subGroup) {
	list<Item>* toReturn = this->getSubGroup(group, subGroup);
	if (toReturn == nullptr)return 0;
	else return toReturn->size();

}


Item* Data::GetItem(char g, int sg, string n) {
	list<Item>* grSbgrSet = this->getSubGroup(g, sg);

	if (grSbgrSet != nullptr) {
		auto toReturn = std::find_if(grSbgrSet->begin(), grSbgrSet->end(), [n](Item& it)->bool {if (n == it.
			getName()) return true; else return false; });
		if (toReturn != grSbgrSet->end()) return toReturn.operator->();


	}
	return nullptr;
}

Item* Data::GetItem(char g, int sg, Date d) {
	list<Item>* grSbgrSet = this->getSubGroup(g, sg);
	if (grSbgrSet != nullptr) {
		auto toReturn = std::find_if(grSbgrSet->begin(), grSbgrSet->end(), [d](Item& it)->bool {if (d == it.
			getDate()) return true; else return false; });
		if (toReturn != grSbgrSet->end()) return toReturn.operator->();


	}
	return nullptr;
}

bool Data::PrintItem(char g, int sg, string n) {
	Item* toPrint = this->GetItem(g, sg, n);
	if (toPrint != nullptr) {
		std::cout << toPrint->getName() << " has parameters: Date - " << toPrint->getDate().ToString() << " Group - " << toPrint->getGroup() << " Subgroup " << toPrint->getSubGroup() << "\n";
		return true;
	}
	return false;
}

bool Data::PrintItem(char g, int sg, Date d) {
	Item* toPrint = this->GetItem(g, sg, d);
	if (toPrint != nullptr) {
		std::cout << toPrint->getName() << " has parameters: Date - " << toPrint->getDate().ToString() << " Group - " << toPrint->getGroup() << " Subgroup " << toPrint->getSubGroup() << "\n";
		return true;
	}
	return false;
}

bool Data::RemoveGroup(char g) {
	if (g == NULL)return false;
	if (dataSet->find(g) != dataSet->end()) { dataSet->erase(g); return true; }
	return false;
}

bool Data::RemoveSubgroup(char g, int sg) {
	if (g == NULL || sg == NULL)return false;
	auto it = dataSet->find(g);
	if (it != dataSet->end()) {
		auto toRemove = std::find_if(it->second.begin(), it->second.end(), [sg](Item& itm) {if (sg == itm.getSubGroup())return true; else return false; });
		if (toRemove != it->second.end())it->second.erase(toRemove); return true;
		//std::remove_if(it->second.begin(), it->second.end(), [sg](Item& itm) {if (sg == itm.getSubGroup())return true; else return false; });
	}
	return false;
}


bool Data::RemoveItem(char g, int sg, string n) {
	if (g == NULL || sg == NULL || n.size() == 0)return false;
	auto it = dataSet->find(g);
	if (it != dataSet->end()) {
		if (it != dataSet->end()) {
			auto toRemove = std::find_if(it->second.begin(), it->second.end(), [sg, n](Item& itm) {if (sg == itm.getSubGroup() && n == itm.getName())return true; else return false; });
			if (toRemove != it->second.end())it->second.erase(toRemove); return true;

		}
		//std::remove_if(it->second.begin(), it->second.end(), [sg,n](Item& itm) {if (sg == itm.getSubGroup() && n ==itm.getName())return true; else return false; });
	}
	return false;
}

bool Data::RemoveItem(char g, int sg, Date d) {
	if (g == NULL || sg == NULL)return false;
	auto it = dataSet->find(g);
	if (it != dataSet->end()) {
		if (it != dataSet->end()) {
			auto toRemove = std::find_if(it->second.begin(), it->second.end(), [sg, d](Item& itm) {if (sg == itm.getSubGroup() && d == itm.getDate())return true; else return false; });
			if (toRemove != it->second.end())it->second.erase(toRemove); return true;

		}
		//std::remove_if(it->second.begin(), it->second.end(), [sg, d](Item& itm) {if (sg == itm.getSubGroup() && d == itm.getDate()) { std::cout << "yes" << endl << endl; return true; } else return false; });
	}
	return false;
}