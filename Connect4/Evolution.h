#pragma once
#include "Player.h"

class Evolution
{
public:
	Evolution() = default;
	~Evolution() = default;

	Player combinePlayers(Player& firstParent, Player& secondParent);
};