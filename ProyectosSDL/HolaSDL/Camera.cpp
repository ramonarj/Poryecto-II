#include "Camera.h"

Camera* Camera::s_pCamera = new Camera();

Camera::Camera() : m_pTarget(0, 0), m_position(0, 0)
{

}

Camera::~Camera()
{

}


const Vector2D Camera::getPosition() const
{
	Vector2D pos(m_pTarget.getX() - (Game::Instance()->getWindowWidth() / 2), m_pTarget.getY() - (Game::Instance()->getWindowHeight() / 2));

	if (pos.getX() < 0)
		pos.setX(0);
	else if (pos.getX() > Game::Instance()->getWindowWidth())
		pos.setX(Game::Instance()->getWindowWidth());
	if (pos.getY() < 0)
		pos.setY(0);
	else if (pos.getY() > Game::Instance()->getWindowHeight())
		pos.setY(Game::Instance()->getWindowWidth());

	pos.set(0, 0);

	return pos;
}
