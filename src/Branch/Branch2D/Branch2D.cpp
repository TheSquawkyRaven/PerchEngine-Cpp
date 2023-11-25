#include "pch.h"

#include "Branch2D.h"

using namespace std;
using namespace Perch;

Branch2D::Branch2D()
{
	Position.X = 0;
	Position.Y = 0;
	Scale.X = 1;
	Scale.Y = 1;
}

Vector2 Branch2D::_GetGlobalPosition()
{
	shared_ptr<Branch> parent = GetParent();
	Branch2D* branch2D = dynamic_cast<Branch2D*>(parent.get());
	if (branch2D == NULL)
	{
		return Position;
	}
	return branch2D->GetGlobalPosition() + Position;
}

Vector2 Branch2D::_GetGlobalScale()
{
	shared_ptr<Branch> parent = GetParent();
	Branch2D* branch2D = dynamic_cast<Branch2D*>(parent.get());
	if (branch2D == NULL)
	{
		return Scale;
	}
	return branch2D->GetGlobalScale() + Scale;
}

Vector2 Perch::Branch2D::GetGlobalPosition()
{
	return _GetGlobalPosition();
}

Vector2 Perch::Branch2D::GetGlobalScale()
{
	return _GetGlobalScale();
}