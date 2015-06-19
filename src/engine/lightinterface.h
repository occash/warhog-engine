#ifndef LIGHT_INTERFACE
#define  LIGHT_INTERFACE


#include <glm/glm.hpp>

enum LightType
{
    Undefined,
    Directional,
    Point,
    Spot
};

struct DirectLight
{
    glm::vec4 color;

    glm::vec4 direction;

    glm::float_t intensity;
    glm::float_t __panding[3];
};

struct PointLight
{
    glm::vec4 color;

    glm::vec4 position;

    glm::float_t intensity;
    glm::float_t __panding[3];
};

struct SpotLight
{
    glm::vec4 position;

    glm::vec4 color;

    glm::vec4 direction;

    glm::float_t angle;
    glm::float_t shadowPower;
    glm::float_t intensity;
    glm::float_t __padding1;
};

class RenderSystem;

class LightInterface
{
public:
    LightInterface(RenderSystem *s);

    void setType(LightType t);

    LightInterface(DirectLight *directLight);
    LightInterface(PointLight *pointLight);
    LightInterface(SpotLight *spotLight);

    glm::vec4 getPosition() const;
    glm::vec4 getColor() const;
    glm::vec4 getDirection() const;
    glm::float_t getAngle() const;
    glm::float_t getShadowPower() const;
    glm::float_t getIntensity() const;

    void setLightStruct(DirectLight *directLight);
    void setLightStruct(PointLight *pointLight);
    void setLightStruct(SpotLight *spotLight);

    void setPosition(glm::vec4 pos);
    void setColor(glm::vec4 color);
    void setDirection(glm::vec4 direction);
    void setAngle(glm::float_t angle);
    void setShadowPower(glm::float_t power);
    void setIntensity(glm::float_t intensity);

private:
    LightType _type;
    RenderSystem *_renderSys;

    void *_light;
};

#endif // !LIGH_INTERFACE