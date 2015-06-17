#ifndef LIGHT_H
#define LIGHT_H

#include "../lightinterface.h"

#include "../global.h"

#include <entityx/Entity.h>
#include <glm/glm.hpp>

class ENGINE_EXPORT LightComponent :
    public entityx::Component<LightComponent>
{
public:
	LightComponent();

    ~LightComponent();

	LightType type() const;
	void setType(LightType t);

	glm::vec4 position() const;
	void setPosition(const glm::vec4 &pos);

    glm::vec4 color() const;
    void setColor(const glm::vec4& c);

    float intensity() const;
    void setIntensity(float i);

	glm::vec4 direction() const;
	void setDirection(const glm::vec4 &dir);

	glm::float_t angle() const;
	void setAngle(glm::float_t angle);

	glm::float_t shadowPower() const;
	void setShadowPower(glm::float_t shadowPower);

	void setLightInterface(LightInterface *lightInterface);
private:
    LightType _type;
	LightInterface *_lightInterface;

};

#endif // !LIGHT_H