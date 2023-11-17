#include "Branch.h"

#include "../Log.h"

using namespace Perch;
using namespace Squawk;


void Branch::SetName(std::string name)
{
    Name = name;
}

Branch::Branch()
{

}

int Branch::GetChildIndex(Branch* child)
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

void Branch::_Init()
{
    Init();
}

void Branch::_Ready()
{
    if (!ReadyCalled)
    {
        Ready();
        ReadyCalled = true;
    }
    if (!Children.empty())
    {
        // Ready through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            Branch* child = Children[i];
            child->_Ready();
        }
    }
}

void Branch::_Update()
{
    Update();
    if (!Children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            Branch* child = Children[i];
            child->_Update();
        }
    }
}

void Branch::_Draw(SDL_Surface* MainSurface)
{
    Draw(MainSurface);
    if (!Children.empty())
    {
        // Draw through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            Branch* child = Children[i];
            child->_Draw(MainSurface);
        }
    }
}

void Branch::_Destroy(bool isChainedDestroy)
{
    if (!Children.empty())
    {
        // Destroys all children through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            Branch* child = Children[i];
            child->_Destroy(true);

            delete child;
            Children[i] = NULL;
        }
        Children.clear();
    }

    // If this is chained, no need to remove this(child) from parent
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

void Perch::Branch::AttachChild(Branch* Branch)
{
    Children.push_back(Branch);
}

void Perch::Branch::Init()
{}

void Perch::Branch::Ready()
{}

void Perch::Branch::Update()
{}

void Perch::Branch::Draw(SDL_Surface* MainSurface)
{}

void Branch::Destroy()
{
    _Destroy(false);
}
