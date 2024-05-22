#include "KdGameObject.h"

void KdGameObject::DrawDebug()
{
	// 早期リターン
	if (!m_pDebugWire)return;

	m_pDebugWire->Draw();
}

void KdGameObject::SetScale(float scalar)
{
	Math::Vector3 scale(scalar);

	SetScale(scale);
}

void KdGameObject::SetScale(const Math::Vector3& scale)
{
	Math::Vector3 vecX = m_world.Right();
	Math::Vector3 vecY = m_world.Up();
	Math::Vector3 vecZ = m_world.Backward(); 
	
	vecX.Normalize();
	vecY.Normalize();
	vecZ.Normalize();

	m_world.Right(vecX * scale.x);
	m_world.Up(vecY * scale.y);
	m_world.Backward(vecZ * scale.z);
}

Math::Vector3 KdGameObject::GetScale() const
{
	return Math::Vector3(m_world.Right().Length(), m_world.Up().Length(), m_world.Backward().Length());
}

void KdGameObject::CalcDistSqrFromCamera(const Math::Vector3& camPos)
{
	m_distSqrFromCamera = (m_world.Translation() - camPos).LengthSquared();
}

bool KdGameObject::Intersects(const KdCollider::SphereInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetShape, m_world, pResults);
}

bool KdGameObject::Intersects(const KdCollider::BoxInfo& targetBox, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetBox, m_world, pResults);
}

bool KdGameObject::Intersects(const KdCollider::RayInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetShape, m_world, pResults);
}
