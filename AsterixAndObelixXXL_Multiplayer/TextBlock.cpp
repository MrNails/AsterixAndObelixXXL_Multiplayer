
#include "TextBlock.h"
#include "Helpers.h"

#include "imgui.h"

GUI::TextBlock::TextBlock() 
	: TextBlock::TextBlock(EMPTY_STRING) { }

GUI::TextBlock::TextBlock(const char* text) 
	: TextBlock::TextBlock(text, GenerateSequentialControlName("TextBlock")) { }

GUI::TextBlock::TextBlock(const char* text, const char* name) 
	: IControl::IControl(name)
{
	SetText(text);
}

//GUI::TextBlock::TextBlock(const TextBlock&& textBlock)
//	: IControl::IControl()
//{
//	auto textLen = strlen(textBlock.GetText());
//	auto tmpText = new char[textLen];
//
//	memcpy_s(tmpText, textLen, textBlock.GetText(), textLen);
//
//	SetText(tmpText);
//}

GUI::TextBlock::~TextBlock()
{
	if (_text != nullptr && _text != EMPTY_STRING)
		delete[] _text;
	_text = nullptr;
}

void GUI::TextBlock::SetText(const char* text, bool deleteOldText) noexcept
{
	if (deleteOldText)
		DeleteStringAndSetNull(&_text);

	_text = text;
}

const char* GUI::TextBlock::GetText() const noexcept
{
	return _text;
}

void GUI::TextBlock::Draw() noexcept
{
	if (!GetIsVisible())
		return;

	ImGui::Text(GetText());
}


