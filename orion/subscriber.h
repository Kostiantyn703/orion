#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

class game_object;

class subscriber {
public:
	virtual ~subscriber() {}
	virtual void on_notify(game_object *in_object) = 0;
};
#endif // SUBSCRIBER_H
