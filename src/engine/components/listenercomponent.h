#ifndef LISTENER_H
#define LISTENER_H

#include "../global.h"
#include <entityx/Entity.h>
#include "../meta/object.h"

class ENGINE_EXPORT ListenerComponent :
	public entityx::Component<ListenerComponent>,
	public Object
{
public:
	ListenerComponent();
	~ListenerComponent();
};
#endif