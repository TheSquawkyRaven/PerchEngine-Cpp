#include "Branch.h"

#include "../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Branch::SetName(string name)
{
    Name = name;
}

Branch::Branch()
{

}

int Branch::GetChildIndex(Branch* child)
{
    auto iterator = find(Children.begin(), Children.end(), shared_ptr<Branch>(child));
    if (iterator == Children.end())
    {
        // Not found!
        Log::Warnf("%s not found as a child in %s!", child->Name, Name);
        return -1;
    }

    int index = iterator - Children.begin();
    return index;
}

void Branch::_Init(Engine* engine)
{
    Init(engine);
}

void Branch::_Ready(Engine* engine)
{
    // Preorder ready order (Parent ready first)
    if (!ReadyCalled)
    {
        Ready(engine);
        ReadyCalled = true;
    }
    if (!Children.empty())
    {
        // Ready through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_Ready(engine);
        }
    }
}

void Branch::_Update(Engine* engine)
{
    // Preorder update order (Parent update first)
    Update(engine);
    if (!Children.empty())
    {
        // Update through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_Update(engine);
            OutStack.push(child);
        }
    }
    // Reverse Preorder update out
    while (!OutStack.empty())
    {
        shared_ptr<Branch> child = OutStack.top();
        OutStack.pop();
        child->_UpdateOut(engine);
    }
}

void Branch::_UpdateOut(Engine* engine)
{
    UpdateOut(engine);
}

void Branch::_Draw(Engine* engine, SDL_Renderer* renderer)
{
    // Preorder draw order (Parent draw first)
    Draw(engine, renderer);
    if (!Children.empty())
    {
        // Draw through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_Draw(engine, renderer);
            OutStack.push(child);
        }
    }
    // Reverse Preorder draw out
    while (!OutStack.empty())
    {
        shared_ptr<Branch> child = OutStack.top();
        OutStack.pop();
        child->_DrawOut(engine, renderer);
    }
}

void Branch::_DrawOut(Engine* engine, SDL_Renderer* renderer)
{
    DrawOut(engine, renderer);
}

void Branch::_Destroy(Engine* engine, bool isChainedDestroy)
{
    if (!Children.empty())
    {
        // Destroys all children through recursion
        for (size_t i = 0; i < Children.size(); ++i)
        {
            shared_ptr<Branch> child = Children[i];
            child->_Destroy(engine, true);

            Children[i] = NULL;
        }
        Children.clear();
    }
    // Postorder destruction order (Innermost child destroy first)
    OnDestroy(engine);

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

void Branch::AttachChild(shared_ptr<Branch> branch)
{
    Children.push_back(branch);
}

void Branch::Init(Engine* engine)
{}

void Branch::Ready(Engine* engine)
{}

void Branch::Update(Engine* engine)
{}

void Perch::Branch::UpdateOut(Engine * engine)
{}

void Branch::Draw(Engine* engine, SDL_Renderer* renderer)
{}

void Branch::DrawOut(Engine* engine, SDL_Renderer * renderer)
{}

void Branch::Destroy(Engine* engine)
{
    _Destroy(engine, false);
}

void Branch::OnDestroy(Engine* engine)
{
}
