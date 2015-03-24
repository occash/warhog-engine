#ifndef SOUNDLISTENER_H
#define SOUNDLISTENER_H
#include <glm/glm.hpp>
class SoundListener
{
private:
	glm::vec3 _pos;
	glm::vec3 _forward;
	glm::vec3 _up;
public:
    SoundListener();
    ~SoundListener();
    void setPos(float x, float y, float z);
    void setForward(float x, float y, float z);
    void setUp(float x, float y, float z);
	void setPos(const glm::vec3& pos);
	void setUp(const glm::vec3& pos);
	void setForward(const glm::vec3& pos);
	glm::vec3 getPos();
	glm::vec3 getForward();
	glm::vec3 getUp();
};
#endif