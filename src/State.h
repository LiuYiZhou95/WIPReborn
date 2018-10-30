#pragma once

class State
{
public:
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
	StateController();
	virtual void set_state(State* s);
	State* get_current_state() const;
	virtual void update(float dt);
protected:
	State* _current_state;
};

