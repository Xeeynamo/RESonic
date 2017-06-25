#pragma once

typedef char HBXHitbox[0x10];

class HBX
{
public:
	HBXHitbox hitbox[0x200];
	char angle[0x100];

	HBX();
	~HBX();

	bool Load(char *filename);
	bool Save(char *filename);
};