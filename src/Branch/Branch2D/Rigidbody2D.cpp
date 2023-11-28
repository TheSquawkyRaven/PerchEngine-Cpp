#include "pch.h"

#include "Rigidbody2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Rigidbody2D::PhysicsUpdate()
{
	Vector2 vel = Vector2(0, gravity) * engine->deltaTime;
	velocity = velocity + vel;
	if (!forceApplied)
	{
		velocity = velocity + applyingForce;
		forceApplied = true;
	}
	position = position + velocity;
}

void Rigidbody2D::AddForce(Vector2 force)
{
	applyingForce = force;
	forceApplied = false;
}