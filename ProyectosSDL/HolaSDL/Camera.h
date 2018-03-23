#pragma once
#include "Vector2D.h"
#include "Game.h"
#include "LevelParser.h"
#include <memory>

class Camera
{
public:
	static Camera* Instance()
	{
		if (s_pCamera.get() == nullptr)
			s_pCamera.reset(new Camera());
		return s_pCamera.get();
	}
	~Camera();

	void setTarget(Entity* target) { m_pTarget = target; };
	void setPosition(const Vector2D& position) {
		m_position = position;
	}
	const Vector2D getPosition() const;

	int getZoom() { return zoom; };

private:
	Camera();
	// the camera's target
	Entity* m_pTarget;
	// the camera's position
	Vector2D m_position;

	static unique_ptr<Camera> s_pCamera;

	int zoom;

};
typedef Camera Camera;

