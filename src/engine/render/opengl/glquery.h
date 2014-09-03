#ifndef GLQUERY_H
#define GLQUERY_H

class GLQuery
{
public:
	GLQuery(unsigned int target);
	~GLQuery();

	void begin();
	void end();

	bool ready() const;
	int result() const;

private:
	unsigned int _query;
	unsigned int _target;
};

#endif