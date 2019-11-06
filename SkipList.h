// Copyright 2019 Ursu Dan-Andrei

#ifndef SKIPLIST_H_
#define SKIPLIST_H_

// clasa template SkipList defineste structura de date cu acelasi nume

#include <iostream>
#include "SkipListElement.h"
#include <limits>
#define DEFAULT_MAX_LEVEL 5

template <typename T>
class SkipList {
 public:
	SkipListElement<T>* head;
	SkipListElement<T>* tail;
	int nrElements;
	int maxLevel;

	explicit SkipList(int maxLevel = DEFAULT_MAX_LEVEL) {
		// se initializeaza nivelul maxim al listei
		this->maxLevel = maxLevel;
		this->nrElements = 0;

		// se initializeaza primul nod din lista cu valoare minima a tipului T
		this->head = new SkipListElement<T>(std::numeric_limits<T>::min(), 0);
		this->head->maxLevel = maxLevel;
		delete[] this->head->cuts;
		this->head->cuts = new SkipListElement<T>*[this->maxLevel + 1];

		// se initializeaza ultimul nod din lista cu valoare maxima a tipului T
		this->tail = new SkipListElement<T>(std::numeric_limits<T>::max(), 0);
		this->tail->maxLevel = maxLevel;
		delete[] this->tail->cuts;
		this->tail->cuts = new SkipListElement<T>*[this->maxLevel + 1];

		// se face legaturile dintre ultimul nod si primul nod
		for (int i = 0; i <= this->maxLevel; i++) {
			this->head->cuts[i] = this->tail;
			this->tail->cuts[i] = nullptr;
		}
	}

	// copy-constructor
	SkipList(const SkipList& other) {
		this->maxLevel = other.maxLevel;
		this->nrElements = other.nrElements;

		this->head = new SkipListElement<T>(std::numeric_limits<T>::min(), 0);
		this->head->maxLevel = maxLevel;
		delete[] this->head->cuts;
		this->head->cuts = new SkipListElement<T>*[this->maxLevel + 1];

		this->tail = new SkipListElement<T>(std::numeric_limits<T>::max(), 0);
		this->tail->maxLevel = maxLevel;
		delete[] this->tail->cuts;
		this->tail->cuts = new SkipListElement<T>*[this->maxLevel + 1];

		for (int i = 0; i <= this->maxLevel; i++) {
			this->head->cuts[i] = other.head->cuts[i];
			this->tail->cuts[i] = other.tail->cuts[i];
		}
	}

	// assigment operator
	SkipList& operator=(const SkipList& other) {
		this->maxLevel = other.maxLevel;
		this->nrElements = other.nrElements;

		delete this->head;
		this->head = new SkipListElement<T>(std::numeric_limits<T>::min(), 0);
		this->head->maxLevel = maxLevel;
		delete[] this->head->cuts;
		this->head->cuts = new SkipListElement<T>*[this->maxLevel + 1];

		delete this->tail;
		this->tail = new SkipListElement<T>(std::numeric_limits<T>::max(), 0);
		this->tail->maxLevel = maxLevel;
		delete[] this->tail->cuts;
		this->tail->cuts = new SkipListElement<T>*[this->maxLevel + 1];

		for (int i = 0; i <= this->maxLevel; i++) {
			this->head->cuts[i] = other.head->cuts[i];
			this->tail->cuts[i] = other.tail->cuts[i];
		}

		return *this;
	}

	// returneaza true daca x se afla in lista, false altfel
	bool search_elem(const T& x) {
		SkipListElement<T>* sle = this->head;
		int level = this->maxLevel;

		// parcurge nivelel de jos in sus pana la nivelul 0
		while (level != -1) {
			// parcurge lista orizontal pana cand intalneste un nod mai mare
			while (x >= sle->cuts[level]->info) {
				sle = sle->cuts[level];
			}
			level--;
		}

		if (sle->info == x) {
			return 1;
		} else {
			return 0;
		}
	}

	// sterge nodul cu informatia x (daca acesta exista)
	void delete_elem(const T& x) {
		// cnt retine posibilele noduri la care trebuie modificate legaturile
		SkipListElement<T>** cnt = new SkipListElement<T>*[this->maxLevel + 1];
		SkipListElement<T>* sle = this->head;
		int level = this->maxLevel;

		// functia search_elem putin modificata
		while (level != -1) {
			while (x > sle->cuts[level]->info) {
				sle = sle->cuts[level];
			}

			cnt[level] = sle;
			level--;
		}

		// se sterge (daca exista) nodul cu informatia x
		sle = sle->cuts[0];
		if (sle->info == x) {
			level = sle->maxLevel;

			// se refac legaturile din skiplist
			for (int i = 0; i <= level; i++) {
				cnt[i]->cuts[i] = sle->cuts[i];
			}

			delete sle;
			nrElements--;
		}

		delete[] cnt;
	}

	// introduce in lista un nod cu informatia x
	void insert_elem(const T& x) {
		// se aloca memorie pentru nod
		SkipListElement<T>* ins = new SkipListElement<T>(x, this->maxLevel);

		// cnt retine posibilele noduri de care trebuie legat nodul introdus
		SkipListElement<T>** cnt = new SkipListElement<T>*[this->maxLevel + 1];
		SkipListElement<T>* sle = this->head;

		int level = this->maxLevel;

		// functia search_elem putin modificata
		while (level != -1) {
			while (x >= sle->cuts[level]->info) {
				sle = sle->cuts[level];
			}

			// se retine nodul de legatura de la nivelul actual
			cnt[level] = sle;
			level--;
		}

		// se refac legaturile din skiplist
		level = ins->maxLevel;
		for (int i = 0; i <= level; i++) {
			ins->cuts[i] = cnt[i]->cuts[i];
			cnt[i]->cuts[i] = ins;
		}

		delete[] cnt;
		nrElements++;
	}

	// intoarce skiplist-ul sub forma de vector
	T* toArray() {
		SkipListElement<T> *sle = this->head->cuts[0];
		T* info = new T[nrElements + 1];

		int i = 0;
		while (sle != this->tail) {
			info[i] = sle->info;
			sle = sle->cuts[0];
			i++;
		}
		return info;
	}

	// destructor
	~SkipList() {
		SkipListElement<T> *sle = this->head;

		// parcurge lista nod cu nod si le elibereaza din memorie
		while (sle != nullptr) {
			SkipListElement<T> *del = sle;
			sle = sle->cuts[0];
			delete del;
		}
	}
};

#endif  // SKIPLIST_H_
