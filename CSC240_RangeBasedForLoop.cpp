//============================================================================
// CSC 240 - Range-Based For Loops
// Demonstrates iterating a container without an index variable.
//============================================================================

#include <iostream>
#include "Larva.h"
using namespace std;

int main() {
	Larva myLarva[3];
	Larva larva1("blue", slim);
	Larva larva2("red", round);
	Larva larva3("yellow", stinky);
	myLarva[0] = larva1;
	myLarva[1] = larva2;
	myLarva[2] = larva3;

	for(Larva item : myLarva){
		cout << item.getColor() << " " << item.getType() << endl;
	}
	return 0;
}









