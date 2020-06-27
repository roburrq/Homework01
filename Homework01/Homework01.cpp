#include <iostream>
#include "Item.h"
#include "Data.h"
#include <map>
int main()
{
	cout << "======= test1 -- insert test ==========" << endl;

	// we create an empty container
	Data* d = new Data();
	
	// we add 2 items in group A, subgroup 2
	d->InsertItem('A', 2, "A21", Date());
	d->InsertItem('A', 2, "A22", Date());

	//we add 2 items in group B, subgroup 1
	d->InsertSubgroup('B', 1, { new Item('B', 1, "B11", Date(2,10,2018)),
								new Item('B', 1, "B12", Date(1,10,2018)) }

	);

	// we add new group
	d->InsertGroup('C', { 2, 3 }, { {new Item('C',2,"C21",Date())},
	{new Item('C',3,"C31",Date())} });

	// we display the results
	d->PrintAll();


	cout << "======= test2 -- remove test ==========" << endl;
	// we remove group c
	d->RemoveGroup('A');
	d->RemoveSubgroup('C', 2);

	// we again display the results

	// will display B11,B21 and C31
	// rest of them are erased
	d->PrintAll();

	cout << "======= test3 -- print order by names test ==========" << endl;
	// will display first B11, then B12 (order by name)
	d->PrintSubgroupByNames('B', 1);
	
	cout << "======= test4 -- print order by dates test ==========" << endl;
	// will display first B12, then B11 (order by date)
	d->PrintSubgroupByDates('B', 1);

	cout << "======= test5 -- create random groups test ==========" << endl;
	Data * d2 = new Data(200);
	d2->PrintAll();

	cout << "======= test6 -- count test ==========" << endl;
	cout<< "Nr items in d2 is:" << d2->CountItems()<<endl;
	cout << "Nr items for group 'A' in d2 is:" << d2->CountGroupItems('A')<<endl;	
	cout << "Nr items for group 'A' then subgroup 1 in d2 is:" << d2->CountSubgroupItems('A',1)<<endl;

	return 0;
}