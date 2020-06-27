#include "Data.h"
using namespace std;


// comparator for 2 names
bool compare1(Item* i1, Item* i2)
{
	unsigned int i = 0;
	string first = i1->getName();
	string second = i2->getName();

	while ((i < first.length()) && (i < second.length()))
	{
		if (tolower(first[i]) < tolower(second[i])) return true;
		else if (tolower(first[i]) > tolower(second[i])) return false;
		++i;
	}
	return (first.length() < second.length());
}


// comparator for 2 dates
bool compare2(Item* i1, Item* i2)
{
	return (i1->getTimestamp() < i2->getTimestamp());
}


// constructor for n random items grouped automatically
Data::Data(int n) {
	
	// for each item to be generated
	for (int i = 0; i < n; i++) {
		
		// we create random item
		Item* myitem = new Item();
		
		// we declare list
		list<Item*>* mylist;

		// if the subgroup does not exists
		// we create one 
		if (GetSubgroup(myitem->getGroup(), myitem->getSubgroup()) == nullptr) {
			mylist = new list<Item*>();
			mylist->push_front(myitem);
		}

		// else we are adding to existing subgroup
		else {
			mylist = GetSubgroup(myitem->getGroup(), myitem->getSubgroup());
			mylist->push_front(myitem);
		}

		map<int, list<Item*>*>* mymap;


		// if the group does not exists
		// we create one 		
		if (GetGroup(myitem->getGroup()) == nullptr) {
			mymap = new map<int, list<Item*>*>();
			mymap->insert(std::pair<int, list<Item*>*>(myitem->getSubgroup(), mylist));
		}
		// else we are adding to existing group
		else {
			mymap = GetGroup(myitem->getGroup());
			mymap->insert(std::pair<int, list<Item*>*>(myitem->getSubgroup(), mylist));
		}

		// we update the Data Structure
		DataStructure[myitem->getGroup()] = mymap;
	}
}

// empty contrucotor
Data::Data() {

}

// destructor
Data::~Data() {
	// iterator for groups
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	
	// iterator for subgroups
	map<int, list<Item*>*>::iterator itr2;

	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		cout << itr1->first << ":" << endl;;
		map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
		
		// for each subgroup
		for (itr2 = mymap.begin();
			itr2 != mymap.end();
			++itr2)
		{
			cout << itr2->first << ": ";
			list<Item*>* mylist = itr2->second;
			
			// we clear the items subgroup
			mylist->clear();
		}
		// we clear the subgroups in the group
		mymap.clear();
		cout << endl;
	}
	// we clear the groups in the DataStructure
	DataStructure.clear();
}

// we print all items in all groups/subgroups
void Data::PrintAll() {

	// iterator for groups
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	
	// iterator for subgroups
	map<int, list<Item*>*>::iterator itr2;

	// iterator for items
	list<Item*>::iterator itr3;

	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		cout << itr1->first << ":" << endl;;
		map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
		for (itr2 = mymap.begin();
			itr2 != mymap.end();
			++itr2)
		{
			cout << itr2->first << ": ";

			list<Item*>* mylist = itr2->second;
			for (itr3 = mylist->begin();
				itr3 != mylist->end();
				++itr3) {
				cout << ((Item*)* itr3)->getName() << " ";
				cout << ((Item*)* itr3)->getTimestamp().GetDay() << " "
					<< ((Item*)* itr3)->getTimestamp().GetMonth() << " "
					<< ((Item*)* itr3)->getTimestamp().GetYear() << " "
					<< endl;
			}
		}
		cout << endl;
	}
}

// function that counts all items in the Data Structure
int Data::CountItems() {
	
	// we set nr items to 0
	int n = 0;
	
	// iterator for groups
	map<char, map<int, list<Item*>*>*>::iterator itr1;

	// iterator for subgroups
	map<int, list<Item*>*>::iterator itr2;

	// iterator for items
	list<Item*>::iterator itr3;

	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
		
		// for each subgroup
		for (itr2 = mymap.begin();
			itr2 != mymap.end();
			++itr2)
		{
			list<Item*>* mylist = itr2->second;

			// for each item
			for (itr3 = mylist->begin();
				itr3 != mylist->end();
				++itr3) {
				
				// we count the item
				n++;
			}
		}
	}
	return n;
}

// returns the group passed as parameter
map<int, list<Item*>*>* Data::GetGroup(char c) {
	// iterator for groups
	map<char, map<int, list<Item*>*>*>::iterator itr1;

	// iterator for subgroups
	map<int, list<Item*>*>::iterator itr2;
	
	// for each group
	for (itr1 = DataStructure.begin(); itr1 != DataStructure.end(); itr1++) {
		
		//if we find the element, we return the group
		if (itr1->first == c) {
			return itr1->second;
		}
	}
	return nullptr;
}

// prints the group passed as parameter
void Data::PrintGroup(char c) {
	// iterator for groups
	map<char, map<int, list<Item*>*>*>::iterator itr1;

	// iterator for subgroups
	map<int, list<Item*>*>::iterator itr2;

	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		
		// if we find the group, we print its contests
		if (itr1->first == c) {
			cout << itr1->first << ":" << endl;
			map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
			for (itr2 = mymap.begin();
				itr2 != mymap.end();
				++itr2)
			{
				cout << itr2->first << ": ";
				for (std::list<Item*>::iterator it = itr2->second->begin(); it != itr2->second->end(); ++it)
					cout << (*it)->getName() << " "
					<< (*it)->getTimestamp().GetDay() << " "
					<< (*it)->getTimestamp().GetMonth() << " "
					<< (*it)->getTimestamp().GetYear() << endl;
			}
		}
	}
}


// function that returns the nr of items in a group
int Data::CountGroupItems(char c) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;
	list<Item*>::iterator itr3;

	int n = 0;
	
	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		if (itr1->first == c) {
			map<int, list<Item*>*>* mymap = itr1->second;
			
			// for each subgroup
			for (itr2 = mymap->begin();
				itr2 != mymap->end();
				++itr2) {

				// for each item
				for (itr3 = itr2->second->begin();
					itr3 != itr2->second->end();
					++itr3) {
					// we count the item
					n++;
				}
			}
		}
	}
	return n;
}


// function that returns a subgroup
list<Item*>* Data::GetSubgroup(char c, int i) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;

	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		if (itr1->first == c) {
			for (itr2 = itr1->second->begin();
				itr2 != itr1->second->end();
				++itr2)
			{
				if (itr2->first == i) {
					return itr2->second;
				}
			}
		}
	}
	return nullptr;
}


// function that prints the subgroup ordered by names
void Data::PrintSubgroupByNames(char c, int i) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;

	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		cout << itr1->first <<":"<< endl;
		if (itr1->first == c) {
			map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
			for (itr2 = mymap.begin();
				itr2 != mymap.end();
				++itr2)
			{
				if (itr2->first == i) {
					std::cout << "By Names:" << endl;
					cout << itr2->first<<": ";
					
					// we sort the lists by names
					itr2->second->sort(compare1);
					for (std::list<Item*>::iterator it = itr2->second->begin(); it != itr2->second->end(); ++it)
						cout << (*it)->getName() << " "
						<< (*it)->getTimestamp().GetDay() << " "
						<< (*it)->getTimestamp().GetMonth() << " "
						<< (*it)->getTimestamp().GetYear() << endl;
				}
			}
		}
	}
}

// function that prints the subgroup ordered by dates
void Data::PrintSubgroupByDates(char c, int i) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;

	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		if (itr1->first == c) {
			cout << itr1->first << ": " << endl;
			map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
			
			// for each subgroup
			for (itr2 = mymap.begin();
				itr2 != mymap.end();
				++itr2)
			{
				if (itr2->first == i) {
					std::cout << "By Dates:" << endl;
					cout << itr2->first << ": ";
					
					// we sort the lists by dates
					itr2->second->sort(compare2);
					
					// for each item
					for (std::list<Item*>::iterator it = itr2->second->begin(); it != itr2->second->end(); ++it)
						cout << (*it)->getName() << " "
						<< (*it)->getTimestamp().GetDay() << " "
						<< (*it)->getTimestamp().GetMonth() << " "
						<< (*it)->getTimestamp().GetYear() << endl;
				}
			}
		}
	}
}

// function that counts the items in a subgroup
int Data::CountSubgroupItems(char c, int i) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;

	int n = 0;
	
	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		if (itr1->first == c) {
			cout << itr1->first << ": " << endl;
			map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
			
			// for each subgroup
			for (itr2 = mymap.begin();
				itr2 != mymap.end();
				++itr2)
			{
				if (itr2->first == i) {
					n++;
				}
			}
		}
	}
	return n;
}

// function that returns an item
Item* Data::GetItem(char c, int i, string s) {
	list<Item*>* items = GetSubgroup(c, i);
	list<Item*>::iterator it;
	
	// for each item in the subgroup
	for (it = items->begin(); it != items->end(); it++) {
		// if we find the item, we return it
		if ((*it)->getName() == s) {
			return *it;
		}
	}
	// else we return nullptr
	return nullptr;
}

// function that prints a given item by its name
void Data::PrintItem(char c, int i, string s) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;
	list<Item*>::iterator itr3;

	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		cout << itr1->first << ":" << endl;;
		map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
		
		// for each subgroup
		for (itr2 = mymap.begin();
			itr2 != mymap.end();
			++itr2)
		{
			cout << itr2->first << ": ";

			list<Item*>* mylist = itr2->second;
			
			// for each item
			for (itr3 = mylist->begin();
				itr3 != mylist->end();
				++itr3) {

				// if the item matches
				if (((Item*)* itr3)->getName() == s) {
					
					// we print the item
					cout << ((Item*)* itr3)->getName() << " ";
					cout << ((Item*)* itr3)->getTimestamp().GetDay() << " "
						<< ((Item*)* itr3)->getTimestamp().GetMonth() << " "
						<< ((Item*)* itr3)->getTimestamp().GetYear() << " "
						<< endl;
				}
			}
		}
		cout << endl;
	}
}


// function that inserts an item
Item* Data::InsertItem(char c, int i, string s, Date d) {

	Item* myitem = new Item(c, i, s, d);
	list<Item*>* mylist;

	// if the subgroup does not exists we create it, else we get it
	if (GetSubgroup(myitem->getGroup(), myitem->getSubgroup()) == nullptr) {
		mylist = new list<Item*>();
		mylist->push_front(myitem);
	}
	else {
		mylist = GetSubgroup(myitem->getGroup(), myitem->getSubgroup());
		mylist->push_front(myitem);
	}

	map<int, list<Item*>*>* mymap;

	// if the group does not exists we create it, else we get it
	if (GetGroup(myitem->getGroup()) == nullptr) {
		mymap = new map<int, list<Item*>*>();
		mymap->insert(std::pair<int, list<Item*>*>(myitem->getSubgroup(), mylist));
	}
	else {
		mymap = GetGroup(myitem->getGroup());
		mymap->insert(std::pair<int, list<Item*>*>(myitem->getSubgroup(), mylist));
	}

	// we update the DataStructure entry
	DataStructure[myitem->getGroup()] = mymap;
	
	return myitem;
}


// function that inserts an entire subgroup
list<Item*>* Data::InsertSubgroup(char c, int i,
								  initializer_list<Item*> items) {

	// iterator for items
	initializer_list<Item*>::iterator it;

	// container for groups
	map<int, list<Item*>*>* mymap = new map<int, list<Item*>*>();
	
	// container for items
	list<Item*>* mylist = new list<Item*>();

	for (it = items.begin(); it != items.end(); it++) {
		
		// if the groups does not exists, we create it
		if (GetGroup(c) == nullptr) {
			mymap = new map<int, list<Item*>*>();
		}
		else {
			// if the group exists we get it
			mymap = GetGroup(c);
		}
		// if the subgroup does not exists, we create it
		if (GetSubgroup(c, i) == nullptr) {
			mylist = new list<Item*>();
			mylist->push_back(*it);
			mymap->insert(std::pair<int, list<Item*>*>(i,mylist));
			DataStructure[c]=  mymap;
		}
		else {
			// if the subgroup exists, we get it
			mylist = GetSubgroup(c,i);
			mylist->push_back(*it);
		}
	}
	return mylist;
}

// function that inserts an entire group
// eg call:     	d->InsertGroup('C', { 2, 3 },
//					  {{new Item('C',2,"C21",Date())},
//					  {new Item('C', 3, "C31", Date())} });
map<int, list<Item*>*>* Data::InsertGroup(char c,
	initializer_list<int> subgroups,
	initializer_list<initializer_list<Item*>> items) {

	initializer_list<int>::iterator it1;
	initializer_list<initializer_list<Item*>>::iterator it2;
	initializer_list<Item*>::iterator it3;

	map<int, list<Item*>*>* mymap = new map<int, list<Item*>*>();
	list<Item*>* mylist = new list<Item*>();

	if (GetGroup(c)==nullptr) {
		mymap = new map<int, list<Item*>*>();
	}
	else {
		mymap = GetGroup(c);
	}
	for (it1 = subgroups.begin(), it2 = items.begin(); it1 != subgroups.end() && it2 != items.end(); ++it1, ++it2) {
		if (GetSubgroup(c,*it1) == nullptr) {
			mylist = new list<Item*>();
			for (it3 = it2->begin(); it3 != it2->end(); it3++) {
				Item* myitem = *it3;
				mylist->push_back(myitem);
			}
			mymap->insert(std::pair<int, list<Item*>*>(*it1, mylist));
		}
		else {
			mylist = GetSubgroup(c,*it1);
			for (it3 = it2->begin(); it3 != it2->end(); ++it3) {
				Item* myitem = *it3;
				mylist->push_back(myitem);
			}
		}
	}
	DataStructure[c] = mymap;
	return mymap;
}


// function that removes an item
bool Data::RemoveItem(char c, int i, string s) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;

	bool found = false;
	
	// for each group
	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		
		// if we find the group
		if (itr1->first == c) {
			map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
			
			// for each subgroup
			for (itr2 = mymap.begin();
				itr2 != mymap.end();
				++itr2)
			{
				// if we find the subgroup
				if (itr2->first == i) {
					
					// for each item
					for (std::list<Item*>::iterator it = itr2->second->begin(); it != itr2->second->end(); ++it)
						if (((Item*)* it)->getGroup() == c
							&& ((Item*)* it)->getSubgroup() == i
							&& ((Item*)* it)->getName() == s) {
								// we remove all list contents
								itr2->second->remove(*it);
								return true;
						}
				}
			}
		}
	}
	return false;
}

// function that removes a entire subgroup
bool Data::RemoveSubgroup(char c, int i) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;

	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {
		if (itr1->first == c) {
			for (itr2 = itr1->second->begin();
				itr2 != itr1->second->end();
				++itr2)
				{
					if (itr2->first == i) {
						// we clear the list 
						// corespunding to subgroup
						itr2->second->clear();
						return true;
					}
				}
		}
	}
	return false;

}

// function that removes a entire group
bool Data::RemoveGroup(char c) {
	map<char, map<int, list<Item*>*>*>::iterator itr1;
	map<int, list<Item*>*>::iterator itr2;

	for (itr1 = DataStructure.begin();
		itr1 != DataStructure.end();
		++itr1) {

		// if we find the group
		if (itr1->first == c) {
			map<int, list<Item*>*> mymap = ((map<int, list<Item*>*>) * (itr1->second));
			for (itr2 = mymap.begin();
				itr2 != mymap.end();
				++itr2)
			{
				// we clear the list
				itr2->second->clear();
			}
			// we empty the subgroup
			itr1->second->empty();
			itr1->second->clear();
		}
	}
	// we delete the group
	DataStructure.erase(c);
	return true;
}