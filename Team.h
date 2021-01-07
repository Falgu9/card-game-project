#ifndef __TEAM__H__
#define __TEAM__H__

#include "Player.h"

class Team
{
	friend std::ostream& operator<<(std::ostream& os, Team const& team);
private:
	int points;
	int size;
	Player **team;
public:
	Team(int size);
	~Team();

	Player *getPlayer(int index) const;
	int getSize() const;
	int getPoints() const;
	Player **getTeam() const;

	void setSize(int size);
	void setPoints(int points);
	void setTeam(Player **team);
	void setPlayer(Player *player, int index);

	void add(Player *player);
	void addPoints(int points);
};

#endif

