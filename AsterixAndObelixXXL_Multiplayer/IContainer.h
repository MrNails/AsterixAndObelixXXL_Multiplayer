#pragma once
#include <list>
#include "IControl.h"

namespace GUI {

	class IContainer {
		std::list<IControl*>* _children;

	public:
		IContainer() {
			_children = new std::list<IControl*>();
		}
		~IContainer() {
			if (_children != nullptr)
				delete _children;

			_children = nullptr;
		}

		std::list<IControl*>* GetList() noexcept {
			return _children;
		}
	};
}