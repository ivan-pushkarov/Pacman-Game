#include "mathutils.h"

bool operator==(const glm::vec3& v, const glm::vec3& u)
{
	return (abs(v.x - u.x) < Settings::Epsillion &&
		abs(v.y - u.y) < Settings::Epsillion &&
		abs(v.z - u.z) < Settings::Epsillion);
}

bool operator!=(const glm::vec3& v, const glm::vec3& u)
{
	return !(v == u);
}