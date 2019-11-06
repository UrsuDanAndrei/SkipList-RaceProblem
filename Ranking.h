// Copyright 2019 Ursu Dan-Andrei

#ifndef RANKING_H_
#define RANKING_H_

// clasa Ranking simuleaza evolutia clasamentului

#include <cmath>
#include <utility>
#include "SkipList.h"
#include "Player.h"

class Ranking {
 public:
	int nrPlayers;

	// jucatorii sunt stocati intr-un skiplist si intr-un vector clasic
	SkipList<Player>* list;
	Player* players;

	// retine pozitia fiecarui jucator dupa un print
	int* posPrint;
	bool firstPrint;

	explicit Ranking(int nrPlayers) {
		this->nrPlayers = nrPlayers;
		firstPrint = true;

		// se aloca un skiplist cu log(n) nivele (motive de eficienta)
		list = new SkipList<Player>((int)(log(nrPlayers) / log(2)));
		players = new Player[nrPlayers + 1];
		posPrint = new int[nrPlayers + 1];

		// se introduc jucatorii in skiplist si in vectorul clasic
		for (int i = 0; i < nrPlayers; i++) {
			list->insert_elem(Player(i, 0, i));
			players[i] = Player(i, 0, i);
			posPrint[i] = i;
		}
	}

	// copy-constructor
	Ranking(const Ranking& other) {
		this->nrPlayers = other.nrPlayers;
		this->firstPrint = other.firstPrint;

		list = new SkipList<Player>((int)log(nrPlayers) / log(2));
		players = new Player[nrPlayers + 1];
		posPrint = new int[nrPlayers + 1];

		this->list = other.list;

		for (int i = 0; i < nrPlayers; i++) {
			this->players[i] = other.players[i];
			this->posPrint[i] = other.posPrint[i];
		}
	}

	// copy assigment
	Ranking& operator=(const Ranking& other) {
		this->nrPlayers = other.nrPlayers;
		this->firstPrint = other.firstPrint;

		delete list;
		delete[] players;
		delete[] posPrint;

		list = new SkipList<Player>((int)log(nrPlayers) / log(2));
		players = new Player[nrPlayers + 1];
		posPrint = new int[nrPlayers + 1];

		this->list = other.list;

		for (int i = 0; i < nrPlayers; i++) {
			this->players[i] = other.players[i];
			this->posPrint[i] = other.posPrint[i];
		}
	}

	// primeste un vector cu timpii jucatorilor si simuleaza o cursa
	void race(const int v[]) {
		// sorteaza jucatorii in functie de timpul de terminare al cursei
		SkipList<Player> sorting((int)(log(nrPlayers) / log(2)));

		int p = 0;
		for (int i = 0; i < nrPlayers; i++) {
			if (v[i] != 0) {
				/*  pozitia si id-ul au fost date invers deoarece clasa Player
				face departajarea in cazul punctajelor egale dupa id, si nu dupa
				pos cum avem nevoie */
				sorting.insert_elem(Player(players[i].pos, -v[i], i));
				p++;
			}
		}

		int points = p / 2;
		int nrPlayersSort = sorting.nrElements;
		Player* sortedPlayers = sorting.toArray();

		// se atribuie punctajele jucatorilor dupa pozitia lor in sort
		for (int i = 0; i < nrPlayersSort; i++) {
			Player info = sortedPlayers[i];

			// se schimba inapoi id-ul cu pos-ul
			std::swap(info.pos, info.id);

			// se sterge jucatorul din lista si se introduce cu noul punctaj
			list->delete_elem(players[info.id]);
			players[info.id].points += points;
			list->insert_elem(players[info.id]);

			points--;
			if (points == 0 && p % 2 == 0) {
				points--;
			}
		}

		delete[] sortedPlayers;

		Player* listPlayers = list->toArray();

		// se actualizeaza pozitiile jucatorilor
		for (int i = 0; i < nrPlayers; i++) {
			players[listPlayers[i].id].pos = i;
		}

		delete[] listPlayers;
	}

	// primeste un ostream catre un fisier si afiseaza clasamentul in el
	void print(std::ostream& out) {
		Player* listPlayers = list->toArray();

		if (firstPrint == true) {
			for (int i = 0; i < nrPlayers; i++) {
				Player info = listPlayers[i];

				out << (info.id  + 1) << " " << info.points
				<< " " << "0" << "\n";

				posPrint[info.id] = players[info.id].pos;
			}
			firstPrint = false;
		} else {
			for (int i = 0; i < nrPlayers; i++) {
				Player info = listPlayers[i];

				out << (info.id  + 1) << " " << info.points
				<< " " << (posPrint[info.id] - players[info.id].pos) << "\n";

				posPrint[info.id] = players[info.id].pos;
			}
		}
		out << "\n";

		delete[] listPlayers;
	}

	// destructor
	~Ranking() {
		delete list;
		delete[] players;
		delete[] posPrint;
	}
};

#endif  // RANKING_H_
