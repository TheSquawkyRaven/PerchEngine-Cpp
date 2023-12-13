

#include "../../Squawk/Log.h"
#include "Branch2D.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

Vector2 Branch2D::GetGlobalPosition()
{
	Branch* parent = GetParent();
	Branch2D* branch2D = dynamic_cast<Branch2D*>(parent);
	if (branch2D == nullptr)
	{
		return position;
	}
	return branch2D->GetGlobalPosition() + position;
}

Vector2 Branch2D::GetGlobalScale()
{
	Branch* parent = GetParent();
	Branch2D* branch2D = dynamic_cast<Branch2D*>(parent);
	if (branch2D == nullptr)
	{
		return scale;
	}
	return branch2D->GetGlobalScale() * scale;
}
