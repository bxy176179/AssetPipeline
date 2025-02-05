#include "BoneImpl.h"

namespace cd
{

BoneImpl::BoneImpl(BoneID id, std::string name)
{
	Init(id, cd::MoveTemp(name));
}

void BoneImpl::Init(BoneID id, std::string name)
{
	m_id = id;
	m_name = cd::MoveTemp(name);
}

}