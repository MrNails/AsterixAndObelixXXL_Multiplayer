#pragma once
#include "IControl.h"

namespace GUI {
	class TextBlock : public IControl
	{
		const char* _text;

	public:
		TextBlock();
		TextBlock(const char* text);
		TextBlock(const char* text, const char* name);
		TextBlock(const TextBlock& textBlock);
		~TextBlock();

		void SetText(const char* text, bool deleteOldText = false) noexcept;
		const char* GetText() const noexcept;

		virtual void Draw() noexcept;
	};
}

