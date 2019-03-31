#include "Date.h"
#include <iostream>
#include <random>

using namespace std;
Date::Date()
{
	time(&Now);
	struct tm Tm;
	localtime_s(&Tm, &Now);
	Day = Tm.tm_mday; // 1...31
	strcpy_s(Month, MonthNames[Tm.tm_mon]); // 0...11
	iMonth = Tm.tm_mon + 1;
	Year = Tm.tm_year + 1900; // current year - 1900
}

Date::Date(int d, int m, int y)
{
	SetYear(y);
	SetMonth(m);
	SetDay(d);
}

Date::Date(const Date& Original)
{ // copy constructor
	Day = Original.Day;
	Year = Original.Year;
	iMonth = Original.iMonth;
	strcpy_s(Month, Original.Month);
}


Date::~Date()
{
	if (pText)
		delete pText;
	//cout << "destructor called\n";
}

bool Date::IsLeap(int y)
{ // from https://www.programiz.com/c-programming/examples/leap-year
	if (y % 4 == 0)
	{
		if (y % 100 == 0)
		{
			// year is divisible by 400, hence the year is a leap year
			if (y % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

char* Date::ToString() const
{
	(const_cast<Date*>(this))->pText = new char[12];
	sprintf_s(pText, 12, "%02d %s %d", Day, Month, Year);
	return pText;
}

void Date::SetMonth(int m)
{
	if (m < 1 || m > 12)
		throw ("Wrong month");
	strcpy_s(Month, MonthNames[m - 1]);
	iMonth = m;
}

int Date::GetMonth(char* pBuf, int nBuf) const
{
	if (!pBuf || nBuf < 4)
		return iMonth;
	strcpy_s(pBuf, nBuf, Month);
	return iMonth;
}

void Date::SetYear(int y)
{
	if (y < 0)
		throw ("Wrong year");
	Year = y;
}