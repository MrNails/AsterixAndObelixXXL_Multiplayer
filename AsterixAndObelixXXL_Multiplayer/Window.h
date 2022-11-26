#pragma once
#include "IControl.h"
#include "IContainer.h"
#include "imgui.h"

namespace GUI {
	class Window : public IControl, public IContainer
	{
		float _width, 
			_height;
		bool _isCollapsed;

	public:
		Window();
		Window(const char* name);
		~Window();

		void SetWidth(float width);
		void SetHeight(float height);
		void SetIsCollapsed(bool isCollapsed) noexcept;

		float GetWidth() const noexcept;
		float GetHeight() const noexcept;
		bool GetIsCollapsed() const noexcept;

		virtual void Draw() noexcept override;

	};
}
