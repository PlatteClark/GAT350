#include "Bullet.h"
#include "Engine.h"

void Bullet::Update()
{
	squampernaut::Vector2 direction{ 1, 0 };
	direction = squampernaut::Vector2::Rotate(direction, m_transform.rotation);

	squampernaut::Vector2 velocity = direction * m_speed * squampernaut::g_time.deltaTime;

	m_transform.position += velocity;

	if (m_transform.position.x > squampernaut::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x > 0) m_transform.position.x = squampernaut::g_renderer.GetWidth();
	if (m_transform.position.y > squampernaut::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y > 0) m_transform.position.y = squampernaut::g_renderer.GetHeight();
}
