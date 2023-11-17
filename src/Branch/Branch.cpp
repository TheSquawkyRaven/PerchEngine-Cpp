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
    auto iterator = std::find(Children.begin(), Children.end(), std::shared_ptr<Branch>(child));
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
    // Preorder ready order (Parent ready first)
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
            std::shared_ptr<Branch> child = Children[i];
            child->_Ready();
        }
    }
}

void Branch::_Update()
{
    // Preorder update order (Parent update first)
    Update();
    if (!Children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            std::shared_ptr<Branch> child = Children[i];
            child->_Update();
        }
    }
}

void Branch::_Draw(SDL_Renderer* renderer)
{
    // Preorder draw order (Parent draw first)
    Draw(renderer);
    if (!Children.empty())
    {
        // Draw through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            std::shared_ptr<Branch> child = Children[i];
            child->_Draw(renderer);
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
            std::shared_ptr<Branch> child = Children[i];
            child->_Destroy(true);

            Children[i] = NULL;
        }
        Children.clear();
    }
    // Postorder destruction order (Innermost child destroy first)
    OnDestroy();

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

void Perch::Branch::AttachChild(std::shared_ptr<Branch> branch)
{
    Children.push_back(branch);
}

void Perch::Branch::Init()
{}

void Perch::Branch::Ready()
{}

void Perch::Branch::Update()
{}

void Perch::Branch::Draw(SDL_Renderer* renderer)
{}

void Branch::Destroy()
{
    _Destroy(false);
}

void Perch::Branch::OnDestroy()
{
}
