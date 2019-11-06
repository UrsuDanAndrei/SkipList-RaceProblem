// Copyright 2019 Ursu Dan-Andrei

#ifndef RLG_H_
#define RLG_H_

#include <iostream>
#include <cstdlib>
#include <ctime>

// random level generator, primeste un maxLevel si returneaza un nivel mai mic

int rlg(int maxLevel) {
	// cu cat nivelul este mai mare cu atat este mai putin probabil
	int n = 0;
	while (random() % 2 == 0 && n < maxLevel) {
		n++;
	}

	return n;
}

#endif  // RLG_H_
