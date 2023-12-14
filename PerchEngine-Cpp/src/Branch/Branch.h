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
	/// Branch
	/// <para>An object that can be attached as a parent of, or/and as a child of another branch object.</para>
	/// <para>Anything that requires a behaviour needs to be extended from a Branch</para>
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

		/// <summary>
		/// Sets the name of the branch.
		/// </summary>
		/// <param name="name"></param>
		PERCH_API inline void SetName(std::string name) { this->name = name; }
		/// <summary>
		/// Returns the name of the branch.
		/// </summary>
		/// <param name="name">Branch name</param>
		PERCH_API inline std::string GetName() const { return name; }
		/// <summary>
		/// Activate or deactivate the branch. Stops many default behaviour from being executed. Affects its children
		/// </summary>
		/// <param name="active">Do activate or not</param>
		PERCH_API inline void SetActive(bool active) { this->active = active; }
		/// <summary>
		/// Returns if the branch is active.
		/// </summary>
		/// <returns>Branch is active</returns>
		PERCH_API inline bool IsActive() const { return active; }
		/// <summary>
		/// Returns if the branch is globally active, by recursively checking the parent up to its root if any are not active
		/// </summary>
		/// <returns>Branch is globally active</returns>
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

		/// <summary>
		/// Should inherit parent's draw layer. Will ignore self's draw layer if true
		/// </summary>
		bool inheritDrawLayer = true;
		/// <summary>
		/// Should the draw order be relative. Only works if inheritDrawLayer is true. This draw order will be added to parent's draw order.
		/// </summary>
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

		/// <summary>
		/// Creates a branch.
		/// </summary>
		/// <param name="engine">Engine reference</param>
		/// <returns>Branch</returns>
		PERCH_API Branch(Engine* engine);

		/// <summary>
		/// Attaches a child to this branch.
		/// <para>Will own the branch using unique_ptr.</para>
		/// </summary>
		/// <param name="branch">The child branch to attach</param>
		PERCH_API void AttachChild(std::unique_ptr<Branch> branch);
		/// <summary>
		/// Attaches a child to this branch.
		/// <para>Shorthand function to implicitly convert the branch to a unique_ptr.</para>
		/// </summary>
		/// <param name="branch">The child branch to attach</param>
		PERCH_API void AttachChildu(Branch* branch);

		/// <summary>
		/// Attaches a script to this branch.
		/// <para>Will own the script using unique_ptr.</para>
		/// </summary>
		/// <param name="script">The script to attach.</param>
		PERCH_API void AttachScript(std::unique_ptr<Script> script);
		/// <summary>
		/// Attaches a script to this branch.
		/// <para>Shorthand function to implicitly convert the script to a unique_ptr.</para>
		/// </summary>
		/// <param name="script">The script to attach</param>
		PERCH_API void AttachScriptu(Script* script);

		/// <summary>
		/// Ready - Called upon attaching to a branch of the main tree or when the tree is run. Only called once.
		/// <para>Unaffected by the branch's active state.</para>
		/// <para>Preorder call order to its children.</para>
		/// <para>Currently broken. Currently only executes the first time after OnRootCreate on the first run of the engine.</para>
		/// </summary>
		PERCH_API virtual void Ready();

		/// <summary>
		/// Update - Called every frame.
		/// <para>Affected by the branch's active state.</para>
		/// <para>Preorder call to its children.</para>
		/// </summary>
		PERCH_API virtual void Update();
		/// <summary>
		/// UpdateOut - Called every frame after updating all children.
		/// <para>Affected by the branch's active state.</para>
		/// <para>Postorder call to its children.</para>
		/// </summary>
		PERCH_API virtual void UpdateOut();

		/// <summary>
		/// PhysicsUpdate - Called every frame after update for physics purposes.
		/// <para>Affected by the branch's active state.</para>
		/// <para>Preorder call to its children.</para>
		/// </summary>
		PERCH_API virtual void PhysicsUpdate();
		/// <summary>
		/// CollisionUpdate - Called every frame after physics update.
		/// <para>Affected by the branch's active state.</para>
		/// <para>Preorder call to its children.</para>
		/// </summary>
		PERCH_API virtual void CollisionUpdate();

		/// <summary>
		/// A default draw order behaviour.
		/// </summary>
		/// <param name="renderer">Renderer reference.</param>
		PERCH_API void SetupDefaultDrawOrder(Renderer* renderer);
		/// <summary>
		/// SetupDraw - Called every frame after collision update. Setups the draw order of the branch
		/// <para>Affected by the branch's active state</para>
		/// <para>Preorder call to its children</para>
		/// </summary>
		/// <param name="renderer">Renderer reference</param>
		PERCH_API virtual void SetupDraw(Renderer* renderer);
		/// <summary>
		/// Returns the global draw layer of this branch.
		/// <para>Returns the parent's draw layer if inheritDrawLayer is true.</para>
		/// </summary>
		/// <returns>Draw Layer</returns>
		PERCH_API virtual int GetDrawLayer();
		// 

		/// <summary>
		/// Returns the global draw order of this branch.
		/// <para>Returns this draw order's + parent's draw order if relativeDrawOrder is false, otherwise returns this draw order.</para>
		/// </summary>
		/// <returns></returns>
		PERCH_API virtual int GetDrawOrder();		
		/// <summary>
		/// Sets the draw layer of the branch.
		/// <para>Will set inheritDrawLayer to false if is not the same as the parent's.</para>
		/// </summary>
		/// <param name="drawLayer">Draw Layer</param>
		PERCH_API virtual void SetDrawLayer(int drawLayer);
		/// <summary>
		/// Sets the draw layer of the branch.
		/// </summary>
		/// <param name="drawOrder">Draw Order</param>
		PERCH_API virtual void SetDrawOrder(int drawOrder);

		void _Draw(Renderer* renderer);
		/// <summary>
		/// Draw - Called after setup draw by the Renderer.
		/// <para>Draw anything here, that respects the draw layer and draw order.</para>
		/// <para>Call order depends on Setup Draw</para>
		/// </summary>
		/// <param name="renderer">Renderer reference</param>
		PERCH_API virtual void Draw(Renderer* renderer);
		//void _DrawOut(Renderer* renderer);
		// DrawOut - Called every frame right after Drawing all children. Active dependent
		//PERCH_API virtual void DrawOut(Renderer* renderer);

		/// <summary>
		/// Destroy - Mark this branch and its children for destruction after an update loop has completed.
		/// <para>Don't use or move any of the children of this after calling Destroy on this branch.</para>
		/// </summary>
		PERCH_API void Destroy();

		/// <summary>
		/// OnDestroy - Executes when the branch is being destroyed.
		/// <para>Uninitialize manual pointers here</para>
		/// <para>Postorder call to its children.</para>
		/// </summary>
		/// <returns></returns>
		PERCH_API virtual void OnDestroy();

		// ###

	};


}
