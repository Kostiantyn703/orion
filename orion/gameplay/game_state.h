#ifndef GAME_STATE_H
#define GAME_STATE_H

class application;

class game_state {
public:
	virtual ~game_state() = default;

	virtual void process(application &game, float delta_time) = 0;
	virtual void on_transition(application &game) = 0;
};

class start_state : public game_state {
public:
	virtual ~start_state() = default;

	virtual void process(application &game, float delta_time) override;
	virtual void on_transition(application &game) override;
};

class active_state : public game_state {
public:
	virtual ~active_state() = default;

	virtual void process(application &game, float delta_time) override;
	virtual void on_transition(application &game) override;
};

#endif // GAME_STATE_H