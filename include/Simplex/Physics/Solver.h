/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/07
----------------------------------------------*/
#ifndef __SOLVER_H_
#define __SOLVER_H_

#include "Simplex\Physics\RigidBody.h"

namespace Simplex
{

class SimplexDLL Solver
{
	vector3 m_v3Acceleration = ZERO_V3; //Acceleration of the Solver
	vector3 m_v3Position = ZERO_V3; //Position of the Solver
	vector3 m_v3Velocity = ZERO_V3; //Velocity of the Solver
	float m_fMass = 1.0f; //Mass of the solver
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: object instance
	*/
	Solver(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: object to copy
	OUTPUT: object instance
	*/
	Solver(Solver const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: object to copy
	OUTPUT: this instance
	*/
	Solver& operator=(Solver const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Solver(void);
	/*
	USAGE: Content Swap
	ARGUMENTS: object to swap content with
	OUTPUT: ---
	*/
	void Swap(Solver& other);

	/*
	USAGE: Sets the position of the solver
	ARGUMENTS: vector3 a_v3Position -> position to set
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position);
	/*
	USAGE: Gets the position of the solver
	ARGUMENTS: ---
	OUTPUT: position of the solver
	*/
	vector3 GetPosition(void);

	/*
	USAGE: Sets the velocity of the solver
	ARGUMENTS: vector3 a_v3Velocity -> velocity to set
	OUTPUT: ---
	*/
	void SetVelocity(vector3 a_v3Velocity);
	/*
	USAGE: Gets the velocity of the solver
	ARGUMENTS: ---
	OUTPUT: velocity of the solver
	*/
	vector3 GetVelocity(void);

	/*
	USAGE: Sets the mass of the solver
	ARGUMENTS: float a_fMass -> mass to set
	OUTPUT: ---
	*/
	void SetMass(float a_fMass);
	/*
	USAGE: Gets mass of the solver
	ARGUMENTS: ---
	OUTPUT: mass of the object
	*/
	float GetMass(void);

	/*
	USAGE: Applies friction to the movement
	ARGUMENTS: float a_fFriction = 0.1f -> friction to apply negative friction gets minimized to 0.01f
	OUTPUT: ---
	*/
	void ApplyFriction(float a_fFriction = 0.1f);
	/*
	USAGE: Applies a force to the solver
	ARGUMENTS: vector3 a_v3Force -> Force to apply
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force);
	/*
	USAGE: Updates the Solver
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Resolve the collision between two solvers
	ARGUMENTS: Solver* a_pOther -> other solver to resolve collision with
	OUTPUT: ---
	*/
	void ResolveCollision(Solver* a_pOther);
private:
	/*
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};//class

EXPIMP_TEMPLATE template class SimplexDLL std::vector<Solver>;
EXPIMP_TEMPLATE template class SimplexDLL std::vector<Solver*>;

} //namespace Simplex

#endif //__SOLVER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/