#pragma once
#include "Vector2D.h"
#include "Game.h"
#include "LevelParser.h"
class Camera
{
public:
	static Camera* Instance()
	{
		if (s_pCamera == 0)
		{
			s_pCamera = new Camera();
		}
		return s_pCamera;
	}


	void setTarget(Entity* target) { m_pTarget = target; };
	void setPosition(const Vector2D& position) {
		m_position = position;
	}
	const Vector2D getPosition() const;

private:
	Camera();
	~Camera();
	// the camera's target
	Entity* m_pTarget;
	// the camera's position
	Vector2D m_position;
	static Camera* s_pCamera;

};
typedef Camera Camera;

