#include "pch.h"

#include "Rigidbody2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Rigidbody2D::PhysicsUpdate()
{
	// Gravity acceleration -> ps-2
	Vector2 gravityVel = Vector2(0, gravity * engine->GetDeltaTime()); // ps-2 * s = ps-1
	// Velocity -> ps-1
	velocity += gravityVel;
	// Position -> p
	position += velocity * engine->timeScale * engine->GetDeltaTime(); // ps-1 * s = p
}

void Rigidbody2D::AddForce(Vector2 force)
{
	velocity += force;
}