#pragma once
class MapObject
{
public:

	int type;
	int x, y;

	bool active = true;
	MapObject();
	~MapObject();
};

