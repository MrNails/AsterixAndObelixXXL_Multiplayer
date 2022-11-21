#pragma once
#include <stdexcept>


namespace GUI {
	class IControl
	{
		bool _isVisible;
		const char* _name;
	public:

		IControl(const char* name) {
			_isVisible = true;
			SetName(name);
		};

		virtual void Draw() = 0;

		void SetName(const char* name) {
			if (name == nullptr || std::strlen(name) == 0)
				throw std::runtime_error("Control name cannot be empty.");

			_name = name;
		}

		const char* GetName() const noexcept {
			return _name;
		}

		void SetIsVisible(bool isVisible) noexcept {
			_isVisible = isVisible;
		}

		bool GetIsVisible() const noexcept {
			return _isVisible;
		}
	};

	
}

