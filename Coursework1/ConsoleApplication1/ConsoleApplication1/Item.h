#pragma once
#include "Date.h"
#include <string>
#include <vector>

class Item {
public:
	Item();
	Item(char Group, int SubGroup, std::string Name, Date TimeStamp);
	~Item();
	const char getGroup();
	int getSubGroup();
	std::string getName();
	void setGroup(char group);
	const bool operator==(const Item& two);
	const bool operator<(const Item& two);
	Date getDate();

private:
	std::vector<std::string> vec = { "Lona","Shantell","Ted","Maira","Renaldo","Tandy","Kimberly","Jeanne","Bibi","Richelle","Raquel","Eusebia","Rana","Takako","Cyndi","Marie","Annett","Steven","Broderick","Olive","Wai","Divina","Erick","Toshia","Hilma","Jovan","Dell","Velda","Bebe","Akiko" };
	char Group = NULL;
	int SubGroup = NULL;
	std::string Name;
	Date TimeStamp;

};