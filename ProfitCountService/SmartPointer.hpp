#pragma once
#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

#include <iostream>

using namespace std;

template<class T>
struct Status {
	T* ptr;
	int counter = 0;
};

template<class T>
class SmartPointer {
	Status<T>* smartPtr;
public:
	SmartPointer(T* ptr = 0);
	SmartPointer(const SmartPointer&);
	~SmartPointer();
	SmartPointer& operator=(const SmartPointer&);
	T* operator->() const;
	void showCounter() { cout << smartPtr->counter; }
};
#endif