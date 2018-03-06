#include "Camera.h"

Camera* Camera::s_pCamera = new Camera();

Camera::Camera() : m_pTarget(0), m_position(0, 0)
{

}

Camera::~Camera()
{
	delete m_pTarget;
}

void Camera::update(Vector2D velocity)
{
	Vector2D pos(Game::Instance()->getEntityWithComponent<Player>()->getPosition());
	m_pTarget = &pos;
}

const Vector2D Camera::getPosition() const
{
	{
		if (m_pTarget != 0)
		{
			Vector2D pos(m_pTarget->getX() - (Game::Instance()->getWindowWidth() / 2), 0);
			if (pos.getX() < 0)
			{
				pos.setX(0);
			}
			return pos;
		}
		return m_position;
	}
}
