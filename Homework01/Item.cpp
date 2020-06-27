#include <string>
#include <chrono>
#include <random> 
#include "Date.h"
#include "Item.h"
#include <iostream>
#include <fstream>

using namespace std;

Item::Item() {  
	
	// random seed
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	// generator
	minstd_rand0 generator(seed);
	
	//character code 'A' -> 65 character 'Z'-> code 90
	// so we get a number between 0 and 25 and we add 65
	Group =  generator() % 26 + 65;

	// subgroup between 0 and 99
	Subgroup = generator() % 100;
	
	// we open file for reading
	std::ifstream file("Birds.txt");
	std::string str;
	int i = 0;
	
	// there are 942 record in file
	// we create a random number corespunding to random name
	int n = generator() % 942;
	
	// we get one random name
	while (std::getline(file, str) && i<=n)
	{
		i++;
	}
	
	// we initialize name with choosen random name
	Name = str;

	// we create random date
	Timestamp = Date::CreateRandomDate(Date(1,1,2019),Date(31,12,2020));
}

// contrustor with parameters
Item::Item(char c, int s, string n, Date d) {
	Group = c;
	Subgroup = s;
	Name = n;
	Timestamp = d;
}

// copy constructor
Item::Item(const Item& item) {
	Group = item.Group;
	Subgroup = item.Subgroup;
	Name = item.Name;
	Timestamp = item.Timestamp;
}

// destructor
Item::~Item() {
}