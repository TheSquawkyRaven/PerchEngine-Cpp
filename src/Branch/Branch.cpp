#include "pch.h"

#include "Branch.h"

#include "../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

int Branch::GetChildIndex(Branch* child)
{
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i].get() == child)
        {
            return i;
        }
    }
    // Not found!
    Log::Warnf("%s not found as a child in %s!", child->name, name);
    return -1;
}

void Branch::_Ready()
{
    // Preorder ready order (Parent ready first)
    if (!readyExecuted)
    {
        Ready();
        if (script != nullptr)
        {
            script->Ready();
        }
        readyExecuted = true;
    }
    if (!children.empty())
    {
        // Ready through recursion
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->_Ready();
        }
    }
}

void Branch::_Update()
{
    // Preorder update order (Parent update first)
    // TODO Updated problem! Update Out is not tracked properly as intended!
    Update();
    if (script != nullptr)
    {
        script->Update();
    }
    if (!children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->_Update();
            children[i]->_UpdateOut();
        }
    }
}

void Branch::_UpdateOut()
{
    UpdateOut();
}

void Branch::_PhysicsUpdate()
{
    PhysicsUpdate();
    if (script != nullptr)
    {
        script->PhysicsUpdate();
    }
    if (!children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->_PhysicsUpdate();
        }
    }
}

void Branch::_CollisionUpdate()
{
    CollisionUpdate();
    if (!children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->_CollisionUpdate();
        }
    }
}

void Branch::_Draw(SDL_Renderer* renderer)
{
    // Preorder draw order (Parent draw first)
    Draw(renderer);
    if (script != nullptr)
    {
        script->Draw(renderer);
    }
    if (!children.empty())
    {
        // Draw through recursion
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->_Draw(renderer);
            children[i]->_DrawOut(renderer);
        }
    }
}

void Branch::_DrawOut(SDL_Renderer* renderer)
{
    DrawOut(renderer);
}

void Branch::_Destroy(bool isChainedDestroy)
{
    if (!children.empty())
    {
        // Destroys all children through recursion
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->_Destroy(true);
            children[i] = nullptr;
        }
        children.clear();
    }
    // Postorder destruction order (Innermost child destroy first)
    if (script != nullptr)
    {
        script->OnDestroy(); // Script destroys first
    }
    OnDestroy();

    // If this is chained, no need to remove this(child) from parent
    if (!isChainedDestroy)
    {
        if (parent != nullptr)
        {
            int childIndex = parent->GetChildIndex(this);
            if (childIndex == -1)
            {
                Log::Errorf("Cannot destroy %s as it is not a child of the assigned parent - %s!", name, parent->name);
                return;
            }
            parent->children.erase(parent->children.begin() + childIndex);
        }
    }
}

Branch::Branch(Engine* engine)
{
    this->engine = engine;
}

void Branch::AttachChild(unique_ptr<Branch> branch)
{
    branch->parent = this;
    children.push_back(move(branch));
}

void Branch::AttachScript(unique_ptr<Script> script)
{
    this->script = std::move(script);
    this->script->SetAttachedToBranch(this);
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
