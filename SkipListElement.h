// Copyright 2019 Ursu Dan-Andrei

#ifndef SKIPLISTELEMENT_H_
#define SKIPLISTELEMENT_H_

/* clasa template SkipListElement defineste un nod dintr-un SkipList, care
contine in parametru info datele ce trebuie stocate */

#include <iostream>
#include "./rlg.h"

template <typename T>
class SkipListElement {
 public:
	T info;

	// retine pointeri la alte noduri, din fata, respectiv spatele, celui curent
	SkipListElement<T>** cuts;
	int maxLevel;

	SkipListElement(T info, int maxLevel) {
		// se atribuie random un nivel mai mic decat maxLevel
		this->maxLevel = rlg(maxLevel);

		// initializare cuts
		this->cuts = new SkipListElement<T>*[this->maxLevel + 1];
		for (int i = 0; i <= this->maxLevel; i++) {
			this->cuts[i] = nullptr;
		}

		this->info = info;
	}

	// copy-constructor
	SkipListElement(const SkipListElement& other) {
		this->maxLevel = other.maxLevel;
		this->info = other.info;

		this->cuts = new SkipListElement<T>*[this->maxLevel + 1];
		for (int i = 0; i <= this->maxLevel; i++) {
			this->cuts[i] = nullptr;
		}
	}

	// assigment operator
	SkipListElement& operator=(const SkipListElement& other) {
		this->maxLevel = other.maxLevel;
		this->info = other.info;

		delete[] this->cuts;
		this->cuts = new SkipListElement<T>*[this->maxLevel + 1];
		for (int i = 0; i <= this->maxLevel; i++) {
			this->cuts[i] = nullptr;
		}
		return *this;
	}

	// operatorii nodului sunt definiti dupa operatorii tipului T
	bool operator<(const SkipListElement& other) const {
		return this->info < other.info;
	}

	bool operator>(const SkipListElement& other) const {
		return this->info > other.info;
	}

	bool operator==(const SkipListElement& other) const {
		if (this->info == other.info) {
			return 1;
		} else {
			return 0;
		}
	}

	bool operator >=(const SkipListElement& other) const {
		return ((*this == other) || (*this > other));
	}

	bool operator <=(const SkipListElement& other) const {
		return ((*this == other) || (*this < other));
	}

	// destructor
	~SkipListElement() {
		delete[] this->cuts;
	}
};

#endif  // SKIPLISTELEMENT_H_
