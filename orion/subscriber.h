#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

class vector2f;

class subscriber {
public:
	virtual ~subscriber() {}
	virtual void on_notify(vector2f &in_position) = 0;
};
#endif // SUBSCRIBER_H
