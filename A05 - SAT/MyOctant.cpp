#include "MyOctant.h"

Simplex::uint Simplex::MyOctant::m_uLeafNodes;
Simplex::uint Simplex::MyOctant::m_uOctantCount;
Simplex::uint Simplex::MyOctant::m_uMaxLevel;
Simplex::uint Simplex::MyOctant::m_uIdealEntityCount;

Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	//Get instances of mesh and ent manager
	m_pEntityMngr = MyEntityManager::GetInstance();
	m_pMeshMngr = MeshManager::GetInstance();

	//Get min and max points of RB
	m_v3Min = m_pEntityMngr->GetRigidBody()->GetCenterGlobal();
	m_v3Max = m_pEntityMngr->GetRigidBody()->GetCenterGlobal();

	//Fetch ent count
	entityCount = m_pEntityMngr->GetEntityCount();


	m_uID = m_uOctantCount;
	m_uOctantCount += 1;
	m_pRoot = this;
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;


	for (uint i = 0; i < entityCount; ++i)
	{
		m_EntityList.push_back(i);
		//Rigid body min and max
		vector3 rbMin = m_pEntityMngr->GetRigidBody(i)->GetMinGlobal();
		vector3 rbMax = m_pEntityMngr->GetRigidBody(i)->GetMaxGlobal();


		//Set min and max in oct
		if (rbMin.x < m_v3Min.x)
		{
			m_v3Min.x = rbMin.x;
		}
		if (rbMin.y < m_v3Min.y)
		{
			m_v3Min.y = rbMin.y;
		}
		if (rbMin.z < m_v3Min.z)
		{
			m_v3Min.z = rbMin.z;
		}
		if (rbMax.x > m_v3Max.x)
		{
			m_v3Max.x = rbMax.x;
		}
		if (rbMax.y > m_v3Max.y)
		{
			m_v3Max.y = rbMax.y;
		}
		if (rbMax.z > m_v3Max.z)
		{
			m_v3Max.z = rbMax.z;
		}
	}

	//calculate center
	m_v3Center = (m_v3Min + m_v3Max) / 2.f;

	//Calc size
	m_fSize = m_v3Max - m_v3Min;

	//Subdivide and construct tree
	Subdivide();
	ConstructTree();


}

Simplex::MyOctant::MyOctant(vector3 a_v3Center, vector3 a_fSize)
{

	m_pEntityMngr = MyEntityManager::GetInstance();
	m_pMeshMngr = MeshManager::GetInstance();

	m_fSize = a_fSize;
	m_v3Max = (m_fSize / 2.0f) + a_v3Center;
	m_v3Min = a_v3Center - (m_fSize / 2.0f);

	m_uID = m_uOctantCount;
	m_uOctantCount += 1;
	m_v3Center = a_v3Center;

}

Simplex::MyOctant::MyOctant(MyOctant const & other)
{
	m_pEntityMngr = MyEntityManager::GetInstance();
	m_pMeshMngr = MeshManager::GetInstance();

	//Set equal to param oct
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;
	m_v3Center = other.m_v3Center;
	m_fSize = other.m_fSize;
	m_pParent = other.m_pParent;
	m_uLevel = other.m_uLevel;
	entityCount = other.entityCount;
	m_pRoot = other.m_pRoot;
	m_uChildren = other.m_uChildren;

	m_uID = m_uOctantCount;
	m_uOctantCount += 1;


	//Create new children nodes
	for (uint i = 0; i < m_uChildren; ++i)
	{
		m_pChild[i] = new MyOctant(*other.m_pChild[i]);
	}
	//Create new entity list
	for (uint i = 0; i < entityCount; ++i)
	{
		m_EntityList.push_back(other.m_EntityList[i]);
	}

	if (this == m_pRoot)
	{
		float children = other.m_lChild.size();
		for (uint i = 0; i < children; ++i)
		{
			m_lChild.push_back(other.m_lChild[i]);
		}
	}

}

Simplex::MyOctant & Simplex::MyOctant::operator=(MyOctant const & other)
{
	if (&other == this) {
		return *this;
	}

	Release();
	m_pEntityMngr = MyEntityManager::GetInstance();
	m_pMeshMngr = MeshManager::GetInstance();
	m_uID = m_uOctantCount;
	m_uOctantCount += 1;

	// Copy member variables 
	m_fSize = other.m_fSize;
	m_pParent = other.m_pParent;
	m_v3Center = other.m_v3Center;
	m_uLevel = other.m_uLevel;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	// Create the rest of the nodes
	m_uChildren = other.m_uChildren;
	for (uint i = 0; i < m_uChildren; ++i) {
		m_pChild[i] = new MyOctant(*other.m_pChild[i]);
	}

	// Create new MyEntityList
	entityCount = other.entityCount;
	for (uint i = 0; i < entityCount; ++i) {
		m_EntityList.push_back(other.m_EntityList[i]);
	}

	//Copy root leaves
	m_pRoot = other.m_pRoot;
	if (this == m_pRoot) {
		float fChildCount = other.m_lChild.size();

		for (uint i = 0; i < fChildCount; ++i) {
			m_lChild.push_back(other.m_lChild[i]);
		}
	}

	return *this;
}

Simplex::MyOctant::~MyOctant(void)
{
	//destruct that ish
	Release();
}

void Simplex::MyOctant::Swap(MyOctant & other)
{
	//call swap on literally everything 
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);
	std::swap(m_EntityList, other.m_EntityList);
	std::swap(entityCount, other.entityCount);
	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);
	std::swap(m_fSize, other.m_fSize);
	std::swap(m_uID, other.m_uID);
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_uChildren, other.m_uChildren);
	std::swap(m_pParent, other.m_pParent);
	std::swap(m_pChild, other.m_pChild);

}

//Getter for size of oct
Simplex::vector3 Simplex::MyOctant::GetSize(void)
{
	return m_fSize;
}

//Geter for center vector
Simplex::vector3 Simplex::MyOctant::GetCenterGlobal(void)
{
	return m_v3Center;
}

//Getter for min vector
Simplex::vector3 Simplex::MyOctant::GetMinGlobal(void)
{
	return m_v3Min;
}

//Getter for max vector
Simplex::vector3 Simplex::MyOctant::GetMaxGlobal(void)
{
	return m_v3Max;
}

bool Simplex::MyOctant::IsColliding(uint a_uRBIndex)
{
	//Get rigid body max and min for collison check
	MyRigidBody* rb = m_pEntityMngr->GetRigidBody(a_uRBIndex);
	vector3 rbMin = rb->GetMinGlobal();
	vector3 rbMax = rb->GetMaxGlobal();

	//Collision check AABB (since cubes)
	if (rbMax.x > m_v3Min.x && rbMax.y > m_v3Min.y && rbMax.z > m_v3Min.z && rbMin.x < m_v3Max.x && rbMin.y < m_v3Max.y && rbMin.z < m_v3Max.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
{
	//Render the octant with lines
	if (a_nIndex >= m_uOctantCount)
	{
		DisplayLeafs();
		return;
	}

	m_lChild[a_nIndex]->DisplayCurrent(a_v3Color);
}

void Simplex::MyOctant::DisplayCurrent(vector3 a_v3Color)
{
	matrix4 scaleMatrix = glm::scale(IDENTITY_M4, m_fSize);
	matrix4 transMatrix = glm::translate(IDENTITY_M4, m_v3Center);
	m_pMeshMngr->AddWireCubeToRenderList((transMatrix*scaleMatrix), a_v3Color); //Render single octant
}

void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
{
	if (IsLeaf())
	{
		DisplayCurrent(a_v3Color);
	}
	else
	{
		//Recursion to show grid
		for (int i = 0; i < m_uChildren; ++i)
		{
			m_pChild[i]->DisplayLeafs(a_v3Color);
		}
	}
}

void Simplex::MyOctant::ClearEntityList(void)
{
	//Empty the entity list
	for (int i = 0; i < m_uChildren; ++i)
	{
		m_pChild[i]->ClearEntityList();
	}

	m_EntityList.clear();
}

void Simplex::MyOctant::Subdivide(void)
{
	//divide until less than ideal
	if (m_uLevel >= m_uMaxLevel || !ContainsMoreThan(m_uIdealEntityCount))
	{
		m_pRoot->m_lChild.push_back(this);
		m_uLeafNodes += 1;
		return;
	}

	//Create individual octants
	m_pChild[0] = new MyOctant(m_v3Center + vector3(-m_fSize.x / 4, m_fSize.y / 4, -m_fSize.z / 4), m_fSize / 2.f);
	m_pChild[1] = new MyOctant(m_v3Center + vector3(-m_fSize.x / 4, m_fSize.y / 4, m_fSize.z / 4), m_fSize / 2.f);
	m_pChild[2] = new MyOctant(m_v3Center + vector3(-m_fSize.x / 4, -m_fSize.y / 4, -m_fSize.z / 4), m_fSize / 2.f);
	m_pChild[3] = new MyOctant(m_v3Center + vector3(-m_fSize.x / 4, -m_fSize.y / 4, m_fSize.z / 4), m_fSize / 2.f);
	m_pChild[4] = new MyOctant(m_v3Center + vector3(m_fSize.x / 4, -m_fSize.y / 4, -m_fSize.z / 4), m_fSize / 2.f);
	m_pChild[5] = new MyOctant(m_v3Center + vector3(m_fSize.x / 4, -m_fSize.y / 4, m_fSize.z / 4), m_fSize / 2.f);
	m_pChild[6] = new MyOctant(m_v3Center + vector3(m_fSize.x / 4, m_fSize.y / 4, -m_fSize.z / 4), m_fSize / 2.f);
	m_pChild[7] = new MyOctant(m_v3Center + vector3(m_fSize.x / 4, m_fSize.y / 4, m_fSize.z / 4), m_fSize / 2.f);

	//handle child octants
	m_uChildren = 8;

	for (int i = 0; i < m_uChildren; ++i)
	{
		m_pChild[i]->m_pParent = this;
		m_pChild[i]->m_uLevel = m_uLevel + 1;
		m_pChild[i]->m_pRoot = m_pRoot;

		//Handle collisions
		for (int j = 0; j < entityCount; ++j)
		{
			if (m_pChild[i]->IsColliding(m_EntityList[j]))
				m_pChild[i]->m_EntityList.push_back(m_EntityList[j]);
		}

		m_pChild[i]->entityCount = m_pChild[i]->m_EntityList.size();
		m_pChild[i]->Subdivide();
	}
}


Simplex::MyOctant * Simplex::MyOctant::GetChild(uint a_nChild)
{
	//Return child octant as long as there are more than 1
	if (m_uChildren == 0)
	{
		return nullptr;
	}
	else
	{
		return m_pChild[a_nChild];
	}
}

Simplex::MyOctant * Simplex::MyOctant::GetParent(void)
{
	//Getter for parent octant
	return m_pParent;
}

bool Simplex::MyOctant::IsLeaf(void)
{
	//is leaf if children is 0
	return m_uChildren == 0;
}

bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
{
	//checker for entity count
	return entityCount > a_nEntities;
}

void Simplex::MyOctant::KillBranches(void)
{
	//deletes branches
	if (IsLeaf())
	{
		return;
	}
	else
	{
		for (int i = 0; i < m_uChildren; ++i)
		{
			m_pChild[i]->KillBranches();
			SafeDelete(m_pChild[i]);
		}
	}
}

void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
{
	if (IsLeaf())
	{
		for (uint i = 0; i < entityCount; ++i)
		{
			m_pEntityMngr->AddDimension(m_EntityList[i], m_uID);
		}
	}
	else
	{
		for (uint i = 0; i < m_uChildren; ++i)
		{
			m_pChild[i]->ConstructTree();
		}
	}
}

Simplex::uint Simplex::MyOctant::GetOctantCount(void)
{
	return m_uOctantCount;
}

Simplex::uint Simplex::MyOctant::GetLeafCount(void)
{
	return m_uLeafNodes;
}

void Simplex::MyOctant::Release(void)
{
	if (this == m_pRoot) {
		KillBranches();
	}
}