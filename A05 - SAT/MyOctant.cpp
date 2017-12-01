#include "MyOctant.h"
using namespace Simplex;

//declaring static variables
uint MyOctant::m_uOctantCount;
uint MyOctant::m_uLeafCount;
uint MyOctant::m_uMaxLevel;
uint MyOctant::m_uIdealEntityCount;

//constructor for root
MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	//creates the root octant
	Init();
	m_pRoot = this;
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;

	//sets the max/min to center
	m_v3Max = m_v3Min = m_pEntityMngr->GetRigidBody()->GetCenterGlobal();
	m_uCurrEntityCount = m_pEntityMngr->GetEntityCount();
	for (uint i = 0; i < m_uCurrEntityCount; ++i)
	{
		m_lEntityList.push_back(i);

		//get min/max
		vector3 rb_min = m_pEntityMngr->GetRigidBody(i)->GetMinGlobal();
		vector3 rb_max = m_pEntityMngr->GetRigidBody(i)->GetMaxGlobal();

		//set min/max for the octant
		if (rb_min.x < m_v3Min.x) m_v3Min.x = rb_min.x;
		if (rb_min.y < m_v3Min.y) m_v3Min.y = rb_min.y;
		if (rb_min.z < m_v3Min.z) m_v3Min.z = rb_min.z;
		if (rb_max.x > m_v3Max.x) m_v3Max.x = rb_max.x;
		if (rb_max.y > m_v3Max.y) m_v3Max.y = rb_max.y;
		if (rb_max.z > m_v3Max.z) m_v3Max.z = rb_max.z;
	}

	//calculate center/size
	m_v3Center = (m_v3Min + m_v3Max) / 2.f;
	m_v3Size = m_v3Max - m_v3Min;

	//create appropriate children
	Subdivide();

	//add leaf dimensions
	ConfigureDimensions();
}

//constructor for branch/leaf
MyOctant::MyOctant(vector3 a_v3Center, vector3 a_v3Size)
{
	Init();
	m_v3Center = a_v3Center;
	m_v3Size = a_v3Size;

	m_v3Max = a_v3Center + m_v3Size / 2.f;
	m_v3Min = a_v3Center - m_v3Size / 2.f;
}

//copy cunstructor
MyOctant::MyOctant(MyOctant const & other)
{
	Init();

	//copying data over
	m_uLevel = other.m_uLevel;
	m_v3Size = other.m_v3Size;
	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;
	m_pParent = other.m_pParent;

	//loops through and recursively copy/create more nodes
	m_uChildren = other.m_uChildren;
	for (uint i = 0; i < m_uChildren; ++i)
	{
		m_pChild[i] = new MyOctant(*other.m_pChild[i]);
	}

	//create a new entity list
	m_uCurrEntityCount = other.m_uCurrEntityCount;
	for (uint i = 0; i < m_uCurrEntityCount; ++i)
	{
		m_lEntityList.push_back(other.m_lEntityList[i]);
	}

	//if it's root, copy m_lChildren over
	m_pRoot = other.m_pRoot;
	if (this == m_pRoot) 
	{
		float fChildCount = other.m_lChildren.size();
		for (uint i = 0; i < fChildCount; ++i) 
		{
			m_lChildren.push_back(other.m_lChildren[i]);
		}
	}
}

//copy assignment operator
MyOctant & MyOctant::operator=(MyOctant const & other)
{
	if (&other == this)
	{
		return *this;
	}
	//release initial value
	//creates error if trying to assign child node to parent node
	Release();
	Init();

	//copying data over
	m_uLevel = other.m_uLevel;
	m_v3Size = other.m_v3Size;
	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;
	m_pParent = other.m_pParent;

	//loops through and recursively copy/create more nodes
	m_uChildren = other.m_uChildren;
	for (uint i = 0; i < m_uChildren; ++i)
	{
		m_pChild[i] = new MyOctant(*other.m_pChild[i]);
	}

	//create a new entity list
	m_uCurrEntityCount = other.m_uCurrEntityCount;
	for (uint i = 0; i < m_uCurrEntityCount; ++i)
	{
		m_lEntityList.push_back(other.m_lEntityList[i]);
	}

	//if it's root, copy m_lChildren over
	m_pRoot = other.m_pRoot;
	if (this == m_pRoot)
	{
		float fChildCount = other.m_lChildren.size();

		for (uint i = 0; i < fChildCount; ++i) 
		{
			m_lChildren.push_back(other.m_lChildren[i]);
		}
	}

	return *this;
}

//destructor
MyOctant::~MyOctant(void)
{
	Release();
}

void MyOctant::Swap(MyOctant & other)
{
	std::swap(m_uID, other.m_uID);
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_uChildren, other.m_uChildren);
	std::swap(m_v3Size, other.m_v3Size);
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);
	std::swap(m_pParent, other.m_pParent);
	std::swap(m_pChild, other.m_pChild);
	std::swap(m_lEntityList, other.m_lEntityList);
	std::swap(m_uCurrEntityCount, other.m_uCurrEntityCount);
	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChildren, other.m_lChildren);
}

//Getters
vector3 MyOctant::GetSize(void) { return m_v3Size; }
vector3 MyOctant::GetCenterGlobal(void) { return m_v3Center; }
vector3 MyOctant::GetMinGlobal(void) { return m_v3Min; }
vector3 MyOctant::GetMaxGlobal(void) { return m_v3Max; }
uint MyOctant::GetOctantCount(void) { return m_uOctantCount; }
uint Simplex::MyOctant::GetLeafCount(void) { return m_uLeafCount; }
MyOctant * MyOctant::GetParent(void) { return m_pParent; }
MyOctant * MyOctant::GetChild(uint a_nChild)
{
	if (m_uChildren == 0)
		return nullptr;
	else return m_pChild[a_nChild];
}
bool MyOctant::IsLeaf(void) { return m_uChildren == 0; }
bool MyOctant::ContainsMoreThan(uint a_nEntities) { return m_uCurrEntityCount > a_nEntities; }
bool MyOctant::IsColliding(uint a_uRBIndex)
{
	MyRigidBody* rb = m_pEntityMngr->GetRigidBody(a_uRBIndex);
	vector3 rb_max = rb->GetMaxGlobal();
	vector3 rb_min = rb->GetMinGlobal();
	if (rb_max.x > m_v3Min.x &&
		rb_max.y > m_v3Min.y &&
		rb_max.z > m_v3Min.z &&
		rb_min.x < m_v3Max.x &&
		rb_min.y < m_v3Max.y &&
		rb_min.z < m_v3Max.z)
	{
		return true;
	}
	else return false;
}
//function to display selected octant(s)
void Simplex::MyOctant::Display(uint a_uIndex, vector3 a_v3Color)
{
	if (a_uIndex >= m_uOctantCount) 
	{
		DisplayAll();
		return;
	}

	m_lChildren[a_uIndex]->DisplayCurrent(a_v3Color);
}
//helper function to only display an octant
void MyOctant::DisplayCurrent(vector3 a_v3Color)
{
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(IDENTITY_M4, m_v3Size), a_v3Color);
}
//helper function to display all octants
void Simplex::MyOctant::DisplayAll(vector3 a_v3Color)
{
	if (IsLeaf())
	{
		DisplayCurrent(a_v3Color);
	}
	else {
		for (uint i = 0; i < m_uChildren; ++i)
		{
			m_pChild[i]->DisplayAll(a_v3Color);
		}
	}
}
//recursively clears all child nodes
void MyOctant::ClearEntityList(void)
{
	for (uint i = 0; i < m_uChildren; ++i)
	{
		m_pChild[i]->ClearEntityList();
	}
	m_lEntityList.clear();
}
//recursively subdivides
void MyOctant::Subdivide(void)
{
	//stops subdividing if at desired level of there's 5 or less entity in the octant
	if (m_uLevel >= m_uMaxLevel || !ContainsMoreThan(m_uIdealEntityCount))
	{
		m_pRoot->m_lChildren.push_back(this);
		m_uLeafCount += 1;
		return;
	}

	//prints out if someone is trying to subdivide an octant that's not a leaf
	if (m_uChildren == 8) 
	{
		std::cout << "Trying to subdivide an octant that's already subdivided" << std::endl;
		return;
	}

	//creating each octant at the right position
	m_pChild[0] = new MyOctant(m_v3Center + vector3(-m_v3Size.x / 4, m_v3Size.y / 4, -m_v3Size.z / 4), m_v3Size / 2.f);
	m_pChild[1] = new MyOctant(m_v3Center + vector3(-m_v3Size.x / 4, m_v3Size.y / 4, m_v3Size.z / 4), m_v3Size / 2.f);
	m_pChild[2] = new MyOctant(m_v3Center + vector3(-m_v3Size.x / 4, -m_v3Size.y / 4, -m_v3Size.z / 4), m_v3Size / 2.f);
	m_pChild[3] = new MyOctant(m_v3Center + vector3(-m_v3Size.x / 4, -m_v3Size.y / 4, m_v3Size.z / 4), m_v3Size / 2.f);
	m_pChild[4] = new MyOctant(m_v3Center + vector3(m_v3Size.x / 4, -m_v3Size.y / 4, -m_v3Size.z / 4), m_v3Size / 2.f);
	m_pChild[5] = new MyOctant(m_v3Center + vector3(m_v3Size.x / 4, -m_v3Size.y / 4, m_v3Size.z / 4), m_v3Size / 2.f);
	m_pChild[6] = new MyOctant(m_v3Center + vector3(m_v3Size.x / 4, m_v3Size.y / 4, -m_v3Size.z / 4), m_v3Size / 2.f);
	m_pChild[7] = new MyOctant(m_v3Center + vector3(m_v3Size.x / 4, m_v3Size.y / 4, m_v3Size.z / 4), m_v3Size / 2.f);
	m_uChildren = 8;

	//loop through and initialize children
	for (uint i = 0; i < m_uChildren; ++i) 
	{
		m_pChild[i]->m_pParent = this;
		m_pChild[i]->m_uLevel = m_uLevel + 1;
		m_pChild[i]->m_pRoot = m_pRoot;
		//loops through and adds colliding rigid bodies
		for (uint j = 0; j < m_uCurrEntityCount; ++j) 
		{
			if (m_pChild[i]->IsColliding(m_lEntityList[j]))
				m_pChild[i]->m_lEntityList.push_back(m_lEntityList[j]);
		}
		//update entity count
		m_pChild[i]->m_uCurrEntityCount = m_pChild[i]->m_lEntityList.size();
		//recursive call
		m_pChild[i]->Subdivide();
	}
}

//recursively kills all nodes except root
void MyOctant::KillBranches(void)
{
	if (IsLeaf()) 
	{
		return;
	}
	else
	{
		for (uint i = 0; i < m_uChildren; ++i)
		{
			m_pChild[i]->KillBranches();
			SafeDelete(m_pChild[i]);
		}
	}
}

//recursive call to configure dimensions for all leaves
void Simplex::MyOctant::ConfigureDimensions()
{
	if (IsLeaf())
	{
		for (uint i = 0; i < m_uCurrEntityCount; ++i) 
		{
			m_pEntityMngr->AddDimension(m_lEntityList[i], m_uID);
		}
	}
	else
	{
		for (uint i = 0; i < m_uChildren; ++i) 
		{
			m_pChild[i]->ConfigureDimensions();
		}
	}
}

//release
void MyOctant::Release(void)
{
	if (this == m_pRoot) 
	{
		KillBranches();
	}
}

//init
void MyOctant::Init(void)
{
	m_pEntityMngr = MyEntityManager::GetInstance();
	m_pMeshMngr = MeshManager::GetInstance();

	m_uID = m_uOctantCount;
	m_uOctantCount += 1;
}
