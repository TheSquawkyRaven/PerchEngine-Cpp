

#include "Branch.h"

#include "../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


bool Branch::IsGloballyActive() const
{
    if (!active)
    {
        return false;
    }
    if (parent == nullptr)
    {
        return true;
    }
    return parent->IsGloballyActive();
}

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
    if (markedForDestruction)
    {
        return;
    }

    // Active independent
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
    // Ready through recursion
    for (size_t i = 0; i < children.size(); ++i)
    {
        children[i]->_Ready();
    }
}

void Branch::_Update()
{
    if (!active || markedForDestruction)
    {
        return;
    }

    // Preorder update order (Parent update first)
    Update();
    if (script != nullptr)
    {
        script->Update();
    }
    // Update through recursion
    for (size_t i = 0; i < children.size(); ++i)
    {
        children[i]->_Update();
        children[i]->_UpdateOut();
    }
}

void Branch::_UpdateOut()
{
    if (!active || markedForDestruction)
    {
        return;
    }

    UpdateOut();
}

void Branch::_PhysicsUpdate()
{
    if (!active || markedForDestruction)
    {
        return;
    }

    PhysicsUpdate();
    if (script != nullptr)
    {
        script->PhysicsUpdate();
    }
    // Update through recursion
    for (size_t i = 0; i < children.size(); ++i)
    {
        children[i]->_PhysicsUpdate();
    }
}

void Branch::_CollisionUpdate()
{
    if (!active || markedForDestruction)
    {
        return;
    }

    CollisionUpdate();
    // Update through recursion
    for (size_t i = 0; i < children.size(); ++i)
    {
        children[i]->_CollisionUpdate();
    }
}

void Branch::_SetupDraw(Renderer* renderer)
{
    if (!active || markedForDestruction)
    {
        return;
    }

    // Preorder SetupDraw order (Parent SetupDraw first)
    SetupDraw(renderer);
    // SetupDraw through recursion
    for (size_t i = 0; i < children.size(); ++i)
    {
        children[i]->_SetupDraw(renderer);
    }
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
    script = nullptr;

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

void Branch::MarkForDestruction()
{
    markedForDestruction = true;

    // Mark for destruction through recursion
    for (size_t i = 0; i < children.size(); ++i)
    {
        children[i]->MarkForDestruction();
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

void Branch::AttachChildu(Branch* branch)
{
    AttachChild(unique_ptr<Branch>(branch));
}

void Branch::AttachScript(unique_ptr<Script> script)
{
    this->script = std::move(script);
    this->script->SetAttachedToBranch(this);
}

void Branch::AttachScriptu(Script* script)
{
    AttachScript(unique_ptr<Script>(script));
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

void Branch::SetupDefaultDrawOrder(Renderer * renderer)
{
    renderer->SetDrawOrder(this, GetDrawLayer(), GetDrawOrder());
}

void Branch::SetupDraw(Renderer* renderer)
{

}

int Branch::GetDrawLayer()
{
    if (parent == nullptr)
    {
        return drawLayer;
    }
    if (inheritDrawLayer)
    {
        return parent->GetDrawLayer();
    }
    return drawLayer;
}

int Branch::GetDrawOrder()
{
    if (!inheritDrawLayer)
    {
        return drawOrder;
    }
    if (!relativeDrawOrder)
    {
        return drawOrder;
    }
    if (parent == nullptr)
    {
        return drawOrder;
    }
    return drawOrder + parent->GetDrawOrder();
}

void Branch::SetDrawLayer(int drawLayer)
{
    this->drawLayer = drawLayer;
    if (parent != nullptr)
    {
        if (parent->GetDrawLayer() == drawLayer)
        {
            inheritDrawLayer = true;
            return;
        }
    }
    inheritDrawLayer = false;
}

void Branch::SetDrawOrder(int drawOrder)
{
    this->drawOrder = drawOrder;
}

void Branch::_Draw(Renderer* renderer)
{
    if (!active || markedForDestruction)
    {
        return;
    }

    // Preorder draw order (Parent draw first)
    Draw(renderer);
    if (script != nullptr)
    {
        script->Draw(renderer);
    }
    //// Draw through recursion
    //for (size_t i = 0; i < children.size(); ++i)
    //{
    //    children[i]->_Draw(renderer);
    //    children[i]->_DrawOut(renderer);
    //}
}

void Branch::Draw(Renderer* renderer)
{}

void Branch::_DrawOut(Renderer* renderer)
{
    if (!active || markedForDestruction)
    {
        return;
    }

    DrawOut(renderer);
}

void Branch::DrawOut(Renderer* renderer)
{}

void Branch::Destroy()
{
    MarkForDestruction();
    engine->AddBranchToDestructionQueue(this);
}

void Branch::OnDestroy()
{}
