#pragma once
#include "XeEngineLV1.h"

struct BLKHeader
{
	short count;
	short destination;
};
class BLK
{
private:
protected:
	void *data;
	XeEngine::File file;
	BLKHeader header;
public:
	BLK();
	~BLK();

	bool Load(char *filename);
	bool Save(char *filename);

	short Count();
	void Count(short);
	short Destination();
	void Destination(short);

	void SetData(void*);
};