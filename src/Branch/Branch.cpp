#include "pch.h"

#include "Branch.h"

#include "../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Branch::SetName(string name)
{
    Name = name;
}

int Branch::GetChildIndex(Branch* child)
{
    for (int i = 0; i < Children.size(); i++)
    {
        if (Children[i].get() == child)
        {
            return i;
        }
    }
    // Not found!
    Log::Warnf("%s not found as a child in %s!", child->Name, Name);
    return -1;
}

void Branch::_Ready()
{
    // Preorder ready order (Parent ready first)
    if (!ReadyCalled)
    {
        Ready();
        if (ScriptRef != NULL)
        {
            ScriptRef->Ready(EngineRef);
        }
        ReadyCalled = true;
    }
    if (!Children.empty())
    {
        // Ready through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_Ready();
        }
    }
}

void Branch::_Update()
{
    // Preorder update order (Parent update first)
    if (Updated)
    {
        return;
    }
    // Updated problem! Update Out is not tracked properly as intended!
    Update();
    if (ScriptRef != NULL)
    {
        ScriptRef->Update(EngineRef);
    }
    Updated = true;
    if (!Children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_Update();
            child->_UpdateOut();
        }
    }
}

void Branch::_UpdateOut()
{
    if (!Updated)
    {
        return;
    }
    UpdateOut();
    Updated = false;
}

void Branch::_PhysicsUpdate()
{
    /*if (PhysicsUpdated)
    {
        return;
    }*/
    PhysicsUpdate();
    if (ScriptRef != NULL)
    {
        ScriptRef->PhysicsUpdate(EngineRef);
    }
    PhysicsUpdated = true;
    PhysicsUpdated = false;
    if (!Children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_PhysicsUpdate();
        }
    }
}

void Branch::_CollisionUpdate()
{
    /*if (PhysicsUpdated)
    {
        return;
    }*/
    CollisionUpdate();
    if (!Children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_CollisionUpdate();
        }
    }
}

void Branch::_Draw(SDL_Renderer* renderer)
{
    // Preorder draw order (Parent draw first)
    if (Drawn)
    {
        return;
    }
    Draw(renderer);
    if (ScriptRef != NULL)
    {
        ScriptRef->Draw(EngineRef, renderer);
    }
    Drawn = true;
    if (!Children.empty())
    {
        // Draw through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_Draw(renderer);
            child->_DrawOut(renderer);
        }
    }
}

void Branch::_DrawOut(SDL_Renderer* renderer)
{
    if (!Drawn)
    {
        return;
    }
    DrawOut(renderer);
    Drawn = false;
}

void Branch::_Destroy(bool isChainedDestroy)
{
    if (!Children.empty())
    {
        // Destroys all children through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_Destroy(true);

            Children[i] = NULL;
        }
        Children.clear();
    }
    // Postorder destruction order (Innermost child destroy first)
    if (ScriptRef != NULL)
    {
        ScriptRef->OnDestroy(EngineRef); // Script destroys first
    }
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
    }
}

Branch::Branch(Engine* engine)
{
    EngineRef = engine;
}

void Branch::AttachChild(shared_ptr<Branch> branch)
{
    Children.push_back(branch);
    branch->Parent = this;
}

void Branch::Ready()
{}

void Branch::Update()
{}

void Branch::UpdateOut()
{}

void Branch::PhysicsUpdate()
{}

void Branch::CollisionUpdate()
{}

void Branch::Draw(SDL_Renderer* renderer)
{}

void Branch::DrawOut(SDL_Renderer* renderer)
{}

void Branch::Destroy()
{
    _Destroy(false);
}

void Branch::OnDestroy()
{
}
