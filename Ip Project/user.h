#pragma once
#ifndef USER_H
#define USER_H
#include "Run.h"
class user
{
public:
	user();
	~user();
	void Initialise(Run data);
	void user_main();
private:
	Run userData;
};
#endif// !USER_H
