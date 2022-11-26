#include "Button.h"

#include "imgui.h"

GUI::Button::Button() : Button::Button(GenerateSequentialControlName("Button")) { }

GUI::Button::Button(const char* name) : Button::Button(nullptr, name) { }

GUI::Button::Button(const char* content, const char* name)
	: IControl::IControl(name)
{
	SetContent(content);
	SetOnClichHandler(nullptr);
}

GUI::Button::~Button()
{
	DeleteStringAndSetNull(&_content);
}

void GUI::Button::SetContent(const char* content, bool deleteOldContent) noexcept
{
	if (deleteOldContent)
		DeleteStringAndSetNull(&_content);

	_content = content;
}

void GUI::Button::SetOnClichHandler(GUI::ClickHandler clickHandler) noexcept
{
	_clickHandler = clickHandler;
}

const char* GUI::Button::GetContent() const noexcept
{
	return _content;
}

GUI::ClickHandler GUI::Button::GetOnClichHandler() const noexcept
{
	return _clickHandler;
}

void GUI::Button::Draw() noexcept
{
	if (!GetIsVisible())
		return;

	if (ImGui::Button(_content == nullptr ? EMPTY_STRING : _content) && _clickHandler != nullptr)
		_clickHandler(this);
}
