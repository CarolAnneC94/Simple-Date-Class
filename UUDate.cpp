/*
* UUDate.cpp
*
* Version information
* Author: TODO - Carol-Anne Campbell
* Date: TODO - 26th October 2019
* Description: This file is the implementation file for the UUDate class and defines (implements) the functions of the class
*
* Copyright notice -
*/

#include "UUDate.h"

using namespace std;

UUDate::UUDate() {
	//Initialises the date to 01/01/2000
	day_ = 01;
	month_ = 01;
	year_ = 2000;
}

UUDate::UUDate(int day, int month, int year) {
	//Validate the constructor arguments, return to the default value of each if they are not valid
	if (day > 31) {
		SetDay(1);
	}
	else if (day < 1) {
		SetDay(1);
	}
	else {
		SetDay(day);
	}

	if (month > 12) {
		SetMonth(1);
	}
	else if (month < 1) {
		SetMonth(1);
	}
	else {
		SetMonth(month);
	}

	if (year < 1) {
		SetYear(2000);
	}
	else {
		SetYear(year);
	}
}

UUDate::UUDate(std::string date) {
	//Extracting date from string input depending on string length (leading zeroes in date)
	if (date.length() > 9){
		//all leading zeroes
		SetDay(std::stoi(date.substr(0, 2)));
		SetMonth(std::stoi(date.substr(3, 5)));
		SetYear(std::stoi(date.substr(6, 9)));
	}
	else if (date.length() == 9) {
		//one leading zero
		SetDay(std::stoi(date.substr(0, 2)));
		SetMonth(std::stoi(date.substr(3, 4)));
		SetYear(std::stoi(date.substr(5, 8)));
	}
	else {
		//no leading zeroes
		SetDay(std::stoi(date.substr(0, 1)));
		SetMonth(std::stoi(date.substr(2, 3)));
		SetYear(std::stoi(date.substr(4, 7)));
	}
		
}

void UUDate::IncrementDate() {
	//increase the day count by one unit
	day_++;
	if (month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) {
		if (day_ > 30)
		{
			//30 day month rolls over to day 1, month increments by one unit when over max days
			day_ = 1;
			month_++;
		}
	}
	if (month_ == 2) {
		if ((year_ % 4) == 0) {
			//February only, day rolls over to 1 and month increments depending on leap year status
			if (day_ > 29) {
				day_ = 1;
				month_++;
			}
		}
		else if(day_ > 28) {
			//non-leap year February rolls over and increments month
			day_ = 1;
			month_++;
		}

	}
	if (month_ == 1 || month_ == 3 || month_ == 5 || month_ == 7 || month_ == 8 || month_ == 10 || month_ == 12) {
		//day rolls over to 1 for all other months if at max days
		if (day_ > 31) {
			day_ = 1;
			month_++;
		}
	}
	//year increments by one if month exceeds 12 units
	if (month_ > 12) {

		month_ = 1;
		year_++;
	}
}

int UUDate::Between(UUDate date) {
	
	int startYear = year_;

	//extracting args for the "second" date
	int endDay = date.GetDay();
	int endMonth = date.GetMonth();
	int endYear = date.GetYear();
	
	//calculates the day difference between original and "second" date and returns the new value

	int endLeapyear;
	int betweenMonth;

	//runs only if measuring between two separate years
	if (endYear > year_) {
		//checking for the number of leap-years between two years
		if ((endYear % 4) != 0) {
			endLeapyear = (endYear - startYear) / 4;
			endDay = endDay + endLeapyear;
			//accounting for starting in a leap-year mount
			if (month_ >= 2) {
				endDay = endDay - 1;
				//and returning the calculated difference
				int startDate = (365 * year_) + (30 * month_) + day_;
				int endDate = (365 * endYear) + (30 * endMonth) + endDay;
				return endDate - startDate;
			}
			else {
				int startDate = (365 * year_) + (30 * month_) + day_;
				int endDate = (365 * endYear) + (30 * endMonth) + endDay;
				return endDate - startDate;
			}
		}
		else {
			int startDate = (365 * year_) + (30 * month_) + day_;
			int endDate = (365 * endYear) + (30 * endMonth) + endDay;
			return endDate - startDate;
		}
	}
	else if (endMonth > month_) {
		//determine the differnce between individual months and adjusting for the number of separate days
		betweenMonth = endMonth - month_;
		endDay = endDay + betweenMonth;
		//returns the value after calculation
		int startDate = (365 * year_) + (30 * month_) + day_;
		int endDate = (365 * endYear) + (30 * endMonth) + endDay;
		return endDate - startDate;
	}
	else {
		//only used if same month and same year, gets the day difference and that's it!
		int startDate = (365 * year_) + (30 * month_) + day_;
		int endDate = (365 * endYear) + (30 * endMonth) + endDay;
		return endDate - startDate;
	}
}

int UUDate::GetDay() const {
	return day_;
}

void UUDate::SetDay(int day) {
	//prevents a non-leap year exceeding its day count for month 2
	if ((year_ % 4) != 0) {
		if (month_ == 2) {
			if (day > 28) {
			day = day_;
			}
		}
	}

	//sets day to previous value if invalid date is detected, returns a valid date
	if (day > 31) {}
	else if (day < 1) {}
	else {
		day_ = day;
	}
}

int UUDate::GetMonth() const {
	return month_;
}

void UUDate::SetMonth(int month) {
	//sets month to previous value if invalid date is detected, returns a valid date
	if (month > 12) {}
	else if (month < 1) {}
	else {
		month_ = month;
	}
}

int UUDate::GetYear() const {
	return year_;
}

void UUDate::SetYear(int year) {
	//sets year to previous if invalid date is detected, returns a valid date
	if (year < 1) {}
	else {
		year_ = year;
	}
}

std::string UUDate::GetDate() {
	//returns the new date as a compiled string
	return std::to_string(GetDay()) + "/" + std::to_string(GetMonth()) + "/" + std::to_string(GetYear());
}