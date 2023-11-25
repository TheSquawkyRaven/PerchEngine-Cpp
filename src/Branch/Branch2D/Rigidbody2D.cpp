#include "pch.h"

#include "Rigidbody2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Rigidbody2D::AddForce(Vector2 force)
{
	ApplyingForce = force;
	ForceApplied = false;
}

void Rigidbody2D::PhysicsUpdate()
{
	Vector2 velocity = Vector2(0, Gravity) * EngineRef->DeltaTime;
	Velocity = Velocity + velocity;
	if (!ForceApplied)
	{
		Velocity = Velocity + ApplyingForce;
		ForceApplied = true;
	}
	Position = Position + Velocity;
}
