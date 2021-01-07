#include "Team.h"

Team::Team(int size) : team(NULL), size(0), points(0) 
{
	this -> size = size;

	team = new Player*[size];
}

Team::~Team()
{
	delete[] team;
}

Player *Team::getPlayer(int index) const
{
	if(index <= size)
		return team[index];

	return NULL;
}

Player **Team::getTeam() const
{
	return team;
}

int Team::getSize() const
{
	return size;
}

int Team::getPoints() const
{
	return points;
}

void Team::setSize(int size)
{
	this -> size = size;
}

void Team::setPoints(int points)
{
	this -> points = points;
}

void Team::setPlayer(Player *player, int index)
{
	if(index <= size)
		team[index] = player;
}

void Team::setTeam(Player **team)
{
	this -> team = team;
}

void Team::add(Player *player)
{
	for(int i =0; i < size; i++)
	{
		if(team[i] == NULL)
		{
			team[i] = player;
			return;
		}
	}

	std::cout << "Error : capacity has been reached." << std::endl;
}

void Team::addPoints(int points)
{
	this -> points += points;
}

std::ostream& operator<<(std::ostream& os, Team const& team)
{
	os << "Team size : " << team.size << std::endl;

	os << "Team players : " << std::endl;
	for(int i = 0; i < team.size; i++)
		os << *team.getPlayer(i);

	os << "Team points : " << team.points << std::endl;

	return os;
}