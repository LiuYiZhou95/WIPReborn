#pragma once
#include "MemoryManager.h"

class State
{
public:
	WIP_MEM(State);
	State(class StateController* sc);
	virtual void begin() = 0;
	virtual void end() = 0;
	virtual bool update(float dt) = 0;

protected:
	class StateController* _controller;
};

class StateController
{
public:
	WIP_MEM(StateController);
	StateController();
	virtual void set_state(State* s);
	State* get_current_state() const;
	virtual void update(float dt);
protected:
	State* _current_state;
};

