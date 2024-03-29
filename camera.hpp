
#ifndef CAMERA_H
#define CAMERA_H
#include "Vectors.hpp"
#include "utils.hpp"



class Camera {
public:
	bool culling;
	static Camera* s_Instance;
	Vector2 m_Viewport = Vector2(720,720);
	Vector2 m_GlobalViewport = Vector2(720, 720);
	float scale = 1.0f;
	Vector2 m_Offset;
	Vector2* m_target = new Vector2(0,0);
	static Camera* GetInstance(){ return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }
	Vector2 getViewport() {return m_Viewport;}
	void SetTarget(Vector2* targ) {
		m_target = targ;
	};
	void Update() {}
	static void lu_SetTarget(Vector2* target) {
		GetInstance()->m_target = target;
	}
	static float lu_GetScale() {
		return GetInstance()->scale;
	}
	static void lu_SetScale(float _target) {
		GetInstance()->scale = _target;
	}
	static Vector2 lu_GetPosition() {
		return *GetInstance()->m_target;
	}
	static void lu_SetPosition(Vector2 * _target) {
		GetInstance()->m_target = _target;
	}
	static Vector2 Vector2ToCameraSpace(Vector2 v) {
		return (v + -*GetInstance()->m_target) + GetInstance()->m_Offset;
	}
	static SDL_Rect* RectToCameraSpace(SDL_Rect* v) {
		Vector2 _mtargetv(GetInstance()->m_target->x + v->x, GetInstance()->m_target->y + v->y);
		std::cout << "Offset: " << _mtargetv << '\n';
		v->x -= _mtargetv.x;
		v->y -= _mtargetv.y;
		return v;
	}
	Camera() {};
	Camera(Vector2* targ) { m_target = targ; };
private:
};
Camera* Camera::s_Instance = nullptr;
#define V2CS Camera::GetInstance()->Vector2ToCameraSpace
#define R2CS Camera::GetInstance()->RectToCameraSpace
#define C_TG Camera::GetInstance()->m_target

#endif // CAMERA_H