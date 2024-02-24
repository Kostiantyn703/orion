#ifndef GAME_STATE_H
#define GAME_STATE_H
//#include "application.h"

class application;

class game_state {
public:
	virtual ~game_state() {}

	virtual void process(application &in_game, float delta_time) = 0;
	virtual void on_transition(application &in_game) = 0;

};

class start_state : public game_state {
public:
	virtual ~start_state() {}

	virtual void process(application &in_game, float delta_time) override;
	virtual void on_transition(application &in_game) override;
};

class active_state : public game_state {
public:
	virtual ~active_state() {}

	virtual void process(application &in_game, float delta_time) override;
	virtual void on_transition(application &in_game) override;
};

#endif // GAME_STATE_H