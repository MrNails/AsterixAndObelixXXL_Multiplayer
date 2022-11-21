#pragma once
#include "Window.h"

namespace GUI {
	class IWindowable {
		Window* _parrentWnd;
	public:
		void SetWindow(Window* window) noexcept {
			_parrentWnd = window;
		}
		Window* GetWindow() const noexcept {
			return  _parrentWnd;
		}
	};
}