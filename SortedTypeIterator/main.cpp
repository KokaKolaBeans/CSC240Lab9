#include <iostream>

#include "SortedType.h"

using namespace std;

int main()
{

	SortedType<int> list1;
	list1.PutItem(99);
	list1.PutItem(12);
	list1.PutItem(10);
	list1.PutItem(9);
	list1.PutItem(8);
	list1.PutItem(7);
	list1.PutItem(6);
	list1.PutItem(5);
	list1.PutItem(-1);

	SortedType<int> list11;
	list11.PutItem(99);
	list11.PutItem(12);
	list11.PutItem(10);
	list11.PutItem(900);
	list11.PutItem(8);
	list11.PutItem(7);
	list11.PutItem(6);
	list11.PutItem(5);
	list11.PutItem(-1);

  SortedTypeIterator<int> runner1 = list1.begin();
  SortedTypeIterator<int> runner2 = list11.begin();
  if(runner1 == runner2){
	  cout << "The iterators are the same." << endl;
  }
  else{
	  cout << "The iterators are NOT the same." <<
			  "\nlist1 item: " << *runner1 << "\nlist11 item: " << *runner2 <<  endl;
  }
  ++runner1;
  if(runner1 == runner2){
  	  cout << "The iterators are the same." << endl;
  }
  else{
	  cout << "The iterators are NOT the same." << endl;
  }

  runner1 = list1.begin();
   runner2 = list1.begin();
   if(runner1 == runner2){
 	  cout << "The iterators are the same." << endl;
   }
   else{
 	  cout << "The iterators are NOT the same." <<
 			  "\nlist1 item: " << *runner1 << "\nlist11 item: " << *runner2 <<  endl;
   }
   ++runner1;
   if(runner1 == runner2){
   	  cout << "The iterators are the same." << endl;
   }
   else{
 	  cout << "The iterators are NOT the same." << endl;
   }


  ++runner2;
  //Compare the running lists and stop when the list items aren't the same.
  while(runner1 != list1.end()){
	  cout << "Item at list1: " << *runner1 << endl;
	  cout << "Item at list11: " << *runner2 << endl;
	  ++runner1;
	  ++runner2;
  }

  cout << "List 1 Example (implicit)" << endl;
  SortedType<int> list;
  list.PutItem(99);
  list.PutItem(12);
  list.PutItem(10);
  list.PutItem(9);
  list.PutItem(8);
  list.PutItem(7);
  list.PutItem(6);
  list.PutItem(5);
  list.PutItem(-1);

  for (auto x : list) {
    cout << x << endl;
  }

  cout << "List 1 Example (explicit)" << endl;
  for(SortedTypeIterator<int> it = list.begin(); it != list.end(); ++it){
	  cout << *it << endl;
  }


  cout << "List 2 Example" << endl;
  SortedType<int*> list2;
  int x = 10;
  int y = 1;
  list2.PutItem(&x);
  list2.PutItem(&y);

  for (int* v : list2) {
    cout << *v << endl;
  }

  return 0;
}
