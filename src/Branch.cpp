#include "Branch.h"

#include "Log.h"

using namespace Perch;
using namespace Squawk;


void Perch::Engine::Branch::SetName(std::string name)
{
    Name = name;
}

int Perch::Engine::Branch::GetChildIndex(Branch* child)
{
    auto iterator = std::find(Children.begin(), Children.end(), child);
    if (iterator == Children.end())
    {
        // Not found!
        Log::Warnf("%s not found as a child in %s!", child->Name, Name);
        return -1;
    }

    int index = iterator - Children.begin();
    return index;
}

void Perch::Engine::Branch::Destroy(bool isChainedDestroy)
{
    if (!Children.empty())
    {
        // Destroys all children through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            Branch* child = Children[i];
            child->Destroy(true);

            delete child;
            Children[i] = NULL;
        }
        Children.clear();
    }

    // This is chained, no need to remove this(child) from parent
    if (!isChainedDestroy)
    {
        if (Parent != NULL)
        {
            int childIndex = Parent->GetChildIndex(this);
            if (childIndex == -1)
            {
                Log::Errorf("Cannot destroy %s as it is not a child of the assigned parent - %s!", Name, Parent->Name);
                return;
            }
            Parent->Children.erase(Parent->Children.begin() + childIndex);
        }

        delete this;
    }
}

void Perch::Engine::Branch::Destroy()
{
    Destroy(false);
}
