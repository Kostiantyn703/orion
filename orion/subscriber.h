#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

class vector2f;

class subscriber {
public:
	virtual ~subscriber() {}
	virtual void on_notify(const vector2f &in_position, const vector2f &in_forward_vector) = 0;
};
#endif // SUBSCRIBER_H
