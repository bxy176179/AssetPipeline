#include "Scene/Light.h"
#include "LightImpl.h"

namespace cd
{

Light::Light(InputArchive& inputArchive)
{
	m_pLightImpl = new LightImpl(inputArchive);
}

Light::Light(InputArchiveSwapBytes& inputArchive)
{
	m_pLightImpl = new LightImpl(inputArchive);
}

Light::Light(LightID lightID, const LightType type)
{
	m_pLightImpl = new LightImpl(lightID, type);
}

Light::Light(Light&& rhs)
{
	*this = cd::MoveTemp(rhs);
}

Light& Light::operator=(Light&& rhs)
{
	std::swap(m_pLightImpl, rhs.m_pLightImpl);
	return *this;
}

Light::~Light()
{
	if (m_pLightImpl)
	{
		delete m_pLightImpl;
		m_pLightImpl = nullptr;
	}
}

void Light::Init(LightID lightID, LightType type)
{
	m_pLightImpl->Init(lightID, type);
}

std::pair<float, float> Light::CalculateScaleAndOffset(float innerAngle, float outerAngle) const
{
	return m_pLightImpl->CalculateScaleAndOffset(innerAngle, outerAngle);
}

LightID Light::GetID() const
{
	return m_pLightImpl->GetID();
}

LightType Light::GetType() const
{
	return m_pLightImpl->GetType();
}

void Light::SetName(const char* pName)
{
	return m_pLightImpl->SetName(pName);
}

const char* Light::GetName() const
{
	return m_pLightImpl->GetName().c_str();
}

void Light::SetIntensity(float intensity)
{
	m_pLightImpl->SetIntensity(intensity);
}

float& Light::GetIntensity()
{
	return m_pLightImpl->GetIntensity();
}

float Light::GetIntensity() const
{
	return m_pLightImpl->GetIntensity();
}

void Light::SetRange(const float range)
{
	m_pLightImpl->SetRange(range);
}

float& Light::GetRange()
{
	return m_pLightImpl->GetRange();
}

float Light::GetRange() const
{
	return m_pLightImpl->GetRange();
}

void Light::SetRadius(const float radius)
{
	m_pLightImpl->SetRadius(radius);
}

float& Light::GetRadius()
{
	return m_pLightImpl->GetRange();
}

float Light::GetRadius() const
{
	return m_pLightImpl->GetRange();
}

void Light::SetWidth(const float width)
{
	m_pLightImpl->SetWidth(width);
}

float& Light::GetWidth()
{
	return m_pLightImpl->GetWidth();
}

float Light::GetWidth() const
{
	return m_pLightImpl->GetWidth();
}

void Light::SetHeight(const float height)
{
	m_pLightImpl->SetHeight(height);
}

float& Light::GetHeight()
{
	return m_pLightImpl->GetHeight();
}

float Light::GetHeight() const
{
	return m_pLightImpl->GetHeight();
}

void Light::SetAngleScale(const float angleScale)
{
	return m_pLightImpl->SetAngleScale(angleScale);
}

float& Light::GetAngleScale()
{
	return m_pLightImpl->GetAngleScale();
}

float Light::GetAngleScale() const
{
	return m_pLightImpl->GetAngleScale();
}

void Light::SetAngleOffset(const float angleOffset)
{
	return m_pLightImpl->SetAngleOffset(angleOffset);
}

float& Light::GetAngleOffset()
{
	return m_pLightImpl->GetAngleOffset();
}

float Light::GetAngleOffset() const
{
	return m_pLightImpl->GetAngleOffset();
}

void Light::SetPosition(cd::Point position)
{
	m_pLightImpl->SetPosition(cd::MoveTemp(position));
}

cd::Point& Light::GetPosition()
{
	return m_pLightImpl->GetPosition();
}

const cd::Point& Light::GetPosition() const
{
	return m_pLightImpl->GetPosition();
}

void Light::SetColor(const cd::Vec3f color)
{
	m_pLightImpl->SetColor(cd::MoveTemp(color));
}

cd::Vec3f& Light::GetColor()
{
	return m_pLightImpl->GetColor();
}

const cd::Vec3f& Light::GetColor() const
{
	return m_pLightImpl->GetColor();
}

void Light::SetDirection(cd::Direction direction)
{
	m_pLightImpl->SetDirection(cd::MoveTemp(direction));
}

cd::Direction& Light::GetDirection()
{
	return m_pLightImpl->GetDirection();
}

const cd::Direction& Light::GetDirection() const
{
	return m_pLightImpl->GetDirection();
}

void Light::SetUp(const cd::Direction up)
{
	m_pLightImpl->SetUp(cd::MoveTemp(up));
}

cd::Direction& Light::GetUp()
{
	return m_pLightImpl->GetUp();
}

const cd::Direction& Light::GetUp() const
{
	return m_pLightImpl->GetUp();
}

Light& Light::operator<<(InputArchive& inputArchive)
{
	*m_pLightImpl << inputArchive;
	return *this;
}

Light& Light::operator<<(InputArchiveSwapBytes& inputArchive)
{
	*m_pLightImpl << inputArchive;
	return *this;
}

const Light& Light::operator>>(OutputArchive& outputArchive) const
{
	*m_pLightImpl >> outputArchive;
	return *this;
}

const Light& Light::operator>>(OutputArchiveSwapBytes& outputArchive) const
{
	*m_pLightImpl >> outputArchive;
	return *this;
}

}