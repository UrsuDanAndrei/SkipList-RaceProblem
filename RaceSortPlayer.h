#ifndef __RACESORTPLAYER_H__
#define __RACESORTPLAYER_H__

#include "Player.h"

class RaceSortPlayer : Player {
public:

	RaceSortPlayer(int id, int points, int pos) : Player(id, points, pos) {

	}

	bool operator<(const Player& other) const {
		if (this->points == other.points) {
			return this->pos < other.pos;
		} else {
			return this->points > other.points;
		}
	}

	bool operator>(const Player& other) const {
		if (this->points == other.points) {
			return this->pos > other.pos;
		} else {
			return this->points < other.points;
		}
	}
};




#endif