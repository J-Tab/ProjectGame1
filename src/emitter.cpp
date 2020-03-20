#include "emitter.h"

glm::vec3 emitter::missleDown()
{
	return glm::vec3(location.loc.position.x, 10000, 0);
}
