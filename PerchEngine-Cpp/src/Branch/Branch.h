#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "../Engine.h"
#include "Script.h"

#include <string>
#include <vector>
#include <memory>

namespace Perch
{

	/// <summary>
	/// A Branch is a container that can hold data and other branches as children.
	/// This is similar to Godot's Node.
	/// </summary>
	class Branch
	{

		friend class Engine;

		// # Variables + Getters/Setters

	private:

		std::string name = "Branch";
		bool active = true;
		bool markedForDestruction = false;

	public:

		PERCH_API inline void SetName(std::string name) { this->name = name; }
		PERCH_API inline std::string GetName() const { return name; }
		PERCH_API inline void SetActive(bool active) { this->active = active; }
		PERCH_API inline bool IsActive() const { return active; }
		PERCH_API bool IsGloballyActive() const;

	private:

		Branch* parent = nullptr;
		std::vector<std::unique_ptr<Branch>> children;

		bool readyExecuted = false;

		int drawLayer = 0;
		int drawOrder = 0;

	public:

		PERCH_API inline bool IsReady() const { return readyExecuted; }

		PERCH_API inline Branch* GetParent() { return parent; }

	protected:

		Engine* engine = nullptr;
		std::unique_ptr<Script> script = nullptr;

	public:

		// Ignores self's draw layer if true
		bool inheritDrawLayer = true;
		// Only works if inheritDrawLayer is true. This draw order will be added to parent's draw order.
		bool relativeDrawOrder = true;

		// ###


		// # Functions

	private:

		int GetChildIndex(Branch* child);

		// TODO check is attached to engine root when attached to execute this
		// Active independent
		void _Ready();

		// Active dependent
		void _Update();
		void _UpdateOut();
		void _PhysicsUpdate();
		void _CollisionUpdate();
		void _SetupDraw(Renderer* renderer);
		// Active independent
		void _Destroy(bool isChainedDestroy);

		void MarkForDestruction();

	public:

		PERCH_API Branch(Engine* engine);

		PERCH_API void AttachChild(std::unique_ptr<Branch> branch);
		// Implicitly converts branch into a unique_ptr
		PERCH_API void AttachChildu(Branch* branch);

		PERCH_API void AttachScript(std::unique_ptr<Script> script);
		// Implicitly converts script into a unique_ptr
		PERCH_API void AttachScriptu(Script* script);

		// Ready - Preorder, Called upon attaching to a branch of the main tree or when the tree is run. Only called once. Active independent
		PERCH_API virtual void Ready();

		// Update - Preorder, Called every frame. Active dependent
		PERCH_API virtual void Update();
		// UpdateOut - Called every frame after Updating all children. Active dependent
		PERCH_API virtual void UpdateOut();

		// PhysicsUpdate - Preorder, Called every frame after update, before collision update. Active dependent
		PERCH_API virtual void PhysicsUpdate();
		// CollisionUpdate - Preorder, Called every frame after physics update, before draw. Active dependent
		PERCH_API virtual void CollisionUpdate();

		PERCH_API void SetupDefaultDrawOrder(Renderer* renderer);
		// SetupDraw - Preorder, Called every frame. Update first, then SetupDraw. Active dependent
		PERCH_API virtual void SetupDraw(Renderer* renderer);
		// Returns the parent's draw layer if inheritDrawLayer is true
		PERCH_API virtual int GetDrawLayer();
		// Returns this draw order's + parent's draw order relativeDrawOrder is false, otherwise returns this draw order.
		PERCH_API virtual int GetDrawOrder();
		// Sets inheritDrawLayer to true or false if it equals the parent's draw layer
		PERCH_API virtual void SetDrawLayer(int drawLayer);
		PERCH_API virtual void SetDrawOrder(int drawOrder);

		void _Draw(Renderer* renderer);
		// Draw - Order dependent on SetupDraw. SetupDraw must be overriden to setup the draw layer and order.
		PERCH_API virtual void Draw(Renderer* renderer);
		void _DrawOut(Renderer* renderer);
		// DrawOut - Called every frame right after Drawing all children. Active dependent
		PERCH_API virtual void DrawOut(Renderer* renderer);

		// Destroy - Starts the destruction of children and this. Don't use or move any of the children of this after calling Destroy on this branch
		PERCH_API void Destroy();

		// OnDestroy - POSTorder, Called while destroying. Uninitialize pointers here. Active independent
		PERCH_API virtual void OnDestroy();

		// ###

	};


}