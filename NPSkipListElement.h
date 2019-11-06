// Copyright 2019 Ursu Dan-Andrei

#ifndef __NPSKIPLISTELEMENT_H__
#define __NPSKIPLISTELEMENT_H__

/* structura template NPSkipListElement a fost facuta pentru a manipula vectorul
cuts din clasa SkipListElement, deoarece consuma mai putina memorie pe obiect
decat aceasta, avand toate functionalitatile necesare */

#include <iostream>
#include "SkipListElement.h"

template<typename T>
class SkipListElement;

template<typename T>
struct NPSkipListElement {
	SkipListElement<T>* next;
	SkipListElement<T>* prev;

	NPSkipListElement() {
		this->next = nullptr;
		this->prev = nullptr;
	}

	// copy-constructor
	explicit NPSkipListElement(const NPSkipListElement* other) {
		this->next = other.next;
		this->prev = other.prev;
	}

	// assigment operator
	NPSkipListElement<T>& operator=(const NPSkipListElement* other) {
		this->next = other.next;
		this->prev = other.prev;
		return *this;
	}

	~NPSkipListElement() {
	}
};

#endif  // __NPSKIPLISTELEMENT_H__
