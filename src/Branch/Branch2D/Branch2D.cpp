#include "pch.h"

#include "../../Squawk/Log.h"
#include "Branch2D.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

Vector2 Branch2D::GetGlobalPosition()
{
	Branch* parent = GetParent();
	Branch2D* branch2D = dynamic_cast<Branch2D*>(parent);
	if (branch2D == NULL)
	{
		return Position;
	}
	return branch2D->GetGlobalPosition() + Position;
}

Vector2 Branch2D::GetGlobalScale()
{
	Branch* parent = GetParent();
	Branch2D* branch2D = dynamic_cast<Branch2D*>(parent);
	if (branch2D == NULL)
	{
		return Scale;
	}
	return branch2D->GetGlobalScale() * Scale;
}
