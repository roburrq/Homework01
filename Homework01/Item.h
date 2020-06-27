#pragma once
#include <string>
#include "Date.h"
using namespace std;
class Item
{
private:
	char Group; // Any from range 'A'...'Z'
	int Subgroup; // Any from range 0...99
	string Name; // Any, but not empty
	Date Timestamp; // Any
public:
	Item(); // Fills the four fields above with preudo-random values
	Item(char, int, string, Date);
	Item(const Item&); // copy constructor
	~Item();
	char getGroup() {
		return Group;
	}
	int getSubgroup() {
		return Subgroup;
	}
	string getName() {
		return Name;
	}
	Date getTimestamp() {
		return Timestamp;
	}
};