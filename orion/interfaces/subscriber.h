#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

class vector2f;
class game_object;

class subscriber {
public:
	virtual ~subscriber() {}
	virtual void on_notify(const vector2f &position, const vector2f &forward_vector, int type = 0) = 0;
	virtual void on_notify(game_object &object) = 0;
};
#endif // SUBSCRIBER_H
