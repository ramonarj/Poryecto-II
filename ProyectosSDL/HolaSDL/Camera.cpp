#include "Camera.h"
#include "PlayState.h"

Camera* Camera::s_pCamera = new Camera();

Camera::Camera() : m_pTarget(nullptr), m_position(0, 0)
{

}

Camera::~Camera()
{

}


const Vector2D Camera::getPosition() const
{

	Vector2D pos(m_pTarget->getPosition().getX() - (Game::Instance()->getWindowWidth() / 2),
		m_pTarget->getPosition().getY() - (Game::Instance()->getWindowHeight() / 2));

	if (pos.getX() < 0)
		pos.setX(0);
	else if (pos.getX() > PlayState::Instance()->getMapWidth() - Game::Instance()->getWindowWidth())
		pos.setX(PlayState::Instance()->getMapWidth() - Game::Instance()->getWindowWidth());

	if (pos.getY() < 0)
		pos.setY(0);
	else if (pos.getY() > PlayState::Instance()->getMapHeight() - Game::Instance()->getWindowHeight())
		pos.setY(PlayState::Instance()->getMapHeight() - Game::Instance()->getWindowHeight());

	/*if (pos.getX() < 0)
		pos.setX(0);

	if (pos.getX() > Game::Instance()->getWindowWidth())
		pos.setX(Game::Instance()->getWindowWidth());

	if (pos.getY() < 0)
		pos.setY(0);

	if (pos.getY() > Game::Instance()->getWindowHeight())
		pos.setY(Game::Instance()->getWindowHeight());*/

	//pos.set(0, 0);

	return pos;
}
