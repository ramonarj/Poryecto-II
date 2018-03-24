#include "Camera.h"
#include "PlayState.h"

unique_ptr<Camera> Camera::s_pCamera = nullptr;

Camera::Camera() : m_pTarget(nullptr), m_position(0, 0), zoom(1)
{

}

Camera::~Camera()
{

}


const Vector2D Camera::getPosition() const
{
	double width = Game::Instance()->getWindowWidth();
	double heigth = Game::Instance()->getWindowHeight();

	Vector2D pos(m_pTarget->getPosition().getX() + m_pTarget->getWidth() / 2 - (width / 2),
		m_pTarget->getPosition().getY() + m_pTarget->getHeight() / 2 - (heigth / 2));

	if (pos.getX() < 0)
		pos.setX(0);
	else if (pos.getX() > PlayState::Instance()->getMapWidth() - width)
		pos.setX(PlayState::Instance()->getMapWidth() - width);

	if (pos.getY() < 0)
		pos.setY(0);
	else if (pos.getY() > PlayState::Instance()->getMapHeight() - heigth)
		pos.setY(PlayState::Instance()->getMapHeight() - heigth);

	return pos;
}
