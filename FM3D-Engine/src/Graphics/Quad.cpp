#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	void Quad::SetSize(const Vector2f& vec) {
		m_position1.x = m_position0.x + vec.x;
		m_position1.y = m_position0.y - vec.y;
		m_uv0.x = 0.0f;
		m_uv0.y = 0.0f;
		m_uv1.x = 1.0f;
		m_uv1.y = 1.0f;
	}
	void Quad::SetSize(int x, int y) {
		Vector2f pos0px = CompCoords::ScreenSpaceToPixel(GetPos0().xy);
		Vector2f size = CompCoords::PixelToScreenSpace(Vector2f(GetTextureWidth() + pos0px.x, GetTextureHeight() + pos0px.y).Subtract(GetPos0().xy));
		m_position1.x = m_position0.x + size.x;
		m_position1.y = m_position0.y - size.y;
		m_uv0.x = 0.0f;
		m_uv0.y = 0.0f;
		m_uv1.x = 1.0f;
		m_uv1.y = 1.0f;
	}
}  