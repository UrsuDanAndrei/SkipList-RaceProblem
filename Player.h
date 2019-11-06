// Copyright 2019 Ursu Dan-Andrei

#ifndef PLAYER_H_
#define PLAYER_H_

// clasa Player defineste caracteristicile unui participant la cursa

#include <iostream>
#include <limits>

// valori maxime pt numarul de jucatori si numarul de curse
#define MAX_N 1000
#define MAX_M 1000

class Player {
 public:
	int id;
	int points;
	int pos;

	// constructor default, pentru a defini un obiect null
	Player() {
	}

	Player(int id, int points, int pos) {
		this->id = id;
		this->points = points;
		this->pos = pos;
	}

	Player(int id, int points) {
		this->id = id;
		this->points = points;
		this->pos = id;
	}

	explicit Player(int id) {
		this->id = id;
		this->points = 0;
		this->pos = id;
	}

	// copy-constructor
	Player(const Player& other) {
		this->id = other.id;
		this->points = other.points;
		this->pos = other.pos;
	}

	// assigment operator
	Player& operator=(const Player& other) {
		this->id = other.id;
		this->points = other.points;
		this->pos = other.pos;
		return *this;
	}

	/* se stabileste o ordine a jucatorilor, acestia vor fi sortati descrescator
	 * dupa punctaj, iar in caz de egalitate crescator dupa id */

	bool operator<(const Player& other) const {
		if (this->points == other.points) {
			return this->id < other.id;
		} else {
			return this->points > other.points;
		}
	}

	bool operator>(const Player& other) const {
		if (this->points == other.points) {
			return this->id > other.id;
		} else {
			return this->points < other.points;
		}
	}

	// 2 jucatori sunt "==" daca au acelasi id
	bool operator==(const Player& other) const {
		if (this->id == other.id) {
			return 1;
		} else {
			return 0;
		}
	}

	// definirea operatorului >= si <= pe baza celor de mai sus
	bool operator >=(const Player& other) const {
		return ((*this == other) || (*this > other));
	}

	bool operator <=(const Player& other) const {
		return ((*this == other) || (*this < other));
	}

	// destructor
	~Player() {
	}
};

// clasa std::numeric_limits<Player> defineste minimul si maximul clasei Player
namespace std {
template<> class numeric_limits<Player> {
 public:
static Player max() {
return Player(MAX_N, -MAX_M * MAX_N / 2, MAX_N);
}

static Player min() {
return Player(-1, MAX_M * MAX_N / 2, -1);
}
};
}  // namespace std

#endif  // PLAYER_H_
