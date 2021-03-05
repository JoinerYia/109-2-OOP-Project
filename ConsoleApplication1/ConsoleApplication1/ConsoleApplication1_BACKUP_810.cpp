#include "stdafx.h" 
#include <string> 
#include <iostream> 
 
using namespace System; 
 
bool Guess(int number) { 
<<<<<<< HEAD
=======
	static int target = -1;

	if(target == -1){
		Random r;
		target = r.Next() % 100 + 1;
	}
	
	if(number == target) return true;
	return false; 
>>>>>>> a168f49af69983cbf126cf119703c3330fb0498d
} 
 
int main(array<System::String ^> ^args) 
{ 
	int guess; 
	do { 
		std::cout << "Choose a number between 1 - 100 :"; 
		std::cin >> guess; 
	} while (!Guess(guess)); 
	return 0; 
}  