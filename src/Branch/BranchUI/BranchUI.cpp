#include "pch.h"

#include "../../Squawk/Log.h"
#include "BranchUI.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


Vector2 BranchUI::GetGlobalPosition()
{
	Branch* parent = GetParent();
	BranchUI* branchUI = dynamic_cast<BranchUI*>(parent);
	if (branchUI == nullptr)
	{
		return position;
	}
	return branchUI->GetGlobalPosition() + position;
}

Vector2 BranchUI::GetGlobalScale()
{
	Branch* parent = GetParent();
	BranchUI* branchUI = dynamic_cast<BranchUI*>(parent);
	if (branchUI == nullptr)
	{
		return scale;
	}
	return branchUI->GetGlobalScale() * scale;
}
