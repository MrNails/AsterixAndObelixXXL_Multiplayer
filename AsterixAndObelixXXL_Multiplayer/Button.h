#pragma once
#include "IControl.h"

namespace GUI {
	class Button;

	typedef void (*ClickHandler)(const Button*);

	class Button : public IControl
	{
		const char* _content;
		ClickHandler _clickHandler;

	public:
		Button();
		Button(const char* name);
		Button(const char* content, const char* name);
		~Button();

		void SetContent(const char* content, bool deleteOldContent = false) noexcept;
		void SetOnClichHandler(ClickHandler clickHandler) noexcept;

		const char* GetContent() const noexcept;
		ClickHandler GetOnClichHandler() const noexcept;

		virtual void Draw() noexcept override;
	};
}

