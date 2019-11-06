// Copyright 2019 Ursu Dan-Andrei

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "SkipList.h"
#include "Player.h"
#include "Ranking.h"

int main() {
	// streamuri catre fisiere
	std::ifstream in("races.in");
	std::ofstream out("races.out");

	// apel necesar pentru fucntia random()
	srand(time(NULL));

	int n, m, k;
	in >> n >> m >> k;
	Ranking r(n);
	int* v = new int[n + 1];

	for (int i = 1; i <= m + k; i++) {
		char c;
		in >> c;

		if (c == 'p') {
			std::string s;
			in >> s;

			// se afiseaza clasamentul
			r.print(out);
		} else {
			// se deplaseaza cursorul un caracter in spate
			in.seekg(-1, std::ios_base::cur);

			// se citesc timpii jucatorilor
			for (int j = 0; j < n; j++) {
				in >> v[j];
			}

			// se simuleaza cursa
			r.race(v);
		}
	}

	in.close();
	out.close();
	delete[] v;

	return 0;
}
