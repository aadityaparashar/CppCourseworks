#include <iostream>
#include "Item.h"
#include <random>
#include <exception>

Item::Item() {

	this->Group = (char)(rand() % 26 + 65);
	this->SubGroup = (int)rand() % 99;
	this->Name = vec.at((int)rand() % vec.size());
	int day, month, year;
	day = (int)rand() % 25 + 1;
	month = (int)rand() % 11 + 1;
	year = (int)rand() % 20 + 1998;

	this->TimeStamp = Date(day, month, year);



}

Item::Item(char Group, int SubGroup, std::string Name, Date TimeStamp) {
	this->Group = Group;
	this->SubGroup = SubGroup;
	this->Name = Name;
	this->TimeStamp = TimeStamp;
}


Item::~Item() {

}

const char Item::getGroup() {
	return this->Group;
}

int Item::getSubGroup() {
	return this->SubGroup;
}

std::string Item::getName() {
	return this->Name;
}

void Item::setGroup(char group)
{
	this->Group = group;
}



Date Item::getDate() {
	return this->TimeStamp;
}


const bool Item::operator==(const Item& two) {
	Item test = two;
	if (this->Group == test.getGroup())return true;
	return false;
}

const bool Item::operator<(const Item& two) {
	Item test = two;
	if (this->SubGroup < test.getSubGroup())return true;
	return false;
}