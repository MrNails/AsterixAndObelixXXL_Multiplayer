#include "TextBox.h"
#include "imgui.h"

#pragma region Additional functions

void DrawTextBox(GUI::TextBox* textBox, const char* name);

#pragma endregion

GUI::TextBoxBasic::TextBoxBasic(const char* name) : IControl::IControl(name) 
{
	_hint = nullptr;
	_flgs = TB_None;
	_labelPos = TBLP_Right;
}

GUI::TextBoxBasic::~TextBoxBasic()
{
	if (_hint != nullptr)
		DeleteStringAndSetNull(&_hint);

	_flgs = TB_None;
}

GUI::TextBoxFlags GUI::TextBoxBasic::GetFlags() const noexcept
{
	return _flgs;
}

void GUI::TextBoxBasic::SetFlags(TextBoxFlags flags) noexcept
{
	_flgs = flags;
}

GUI::TextBoxLabelPosition GUI::TextBoxBasic::GetLabelPosition() const noexcept
{
	return _labelPos;
}

void GUI::TextBoxBasic::SetLabelPosition(TextBoxLabelPosition labelPosition) noexcept
{
	_labelPos = labelPosition;
}

const char* GUI::TextBoxBasic::GetHint() const noexcept
{
	return _hint;
}

void GUI::TextBoxBasic::SetHint(const char* hint, bool deleteOldHint) noexcept
{
	if (deleteOldHint)
		DeleteStringAndSetNull(&_hint);

	_hint = hint;
}


GUI::TextBox::TextBox() : TextBox::TextBox(GenerateSequentialControlName("TextBox")) { }

GUI::TextBox::TextBox(const char* name) : TextBoxBasic(name)
{
	_textLength = DEFAULT_TB_LENGTH;
	_text = new char[_textLength];

	memset(_text, 0, _textLength);
}

GUI::TextBox::~TextBox()
{
	if (_text != nullptr)
		delete[_textLength] _text;

	_textLength = 0;
	_text = nullptr;
}

char* GUI::TextBox::GetText() const noexcept
{
	return _text;
}

void GUI::TextBox::SetText(const char* text)
{
	if (text == nullptr)
		return;

	strcpy_s(_text, GetTextLength(), text);
}

int GUI::TextBox::GetTextLength() const noexcept
{
	return _textLength;
}

void GUI::TextBox::SetTextLength(int length)
{
	if (length <= 0)
		throw std::runtime_error("Text length cannot be less or equal 0.");

	if (length < _textLength) {
		_textLength = length;
		_text[length] = '\0';
	}
	else {
		auto newStr = new char[length];
		memset(newStr, 0, length);

		strcpy_s(newStr, _textLength, _text);

		DeleteStringAndSetNull(&_text);

		_textLength = length;
		_text = newStr;
	}
}

void GUI::TextBox::Draw() noexcept
{
	if (!GetIsVisible())
		return;

	const char* name = GetName();
	//Offset for removing ## in text
	int offset = 2;

	switch (GetLabelPosition())
	{
	case TBLP_Top: 
		ImGui::Text(name + offset);
		DrawTextBox(this, name);
		offset -= 2;
		break;
	case TBLP_Bottom:
		DrawTextBox(this, name);
		ImGui::Text(name + offset);
		offset -= 2;
		break;
	case TBLP_Left:
		ImGui::Text(name + offset); ImGui::SameLine();
		offset -= 2;
	case TBLP_Right:
	default:
		DrawTextBox(this, name);
		break;
	}
}

GUI::TextBoxInt::TextBoxInt() : TextBoxInt::TextBoxInt(GenerateSequentialControlName("TextBoxInt")) {}

GUI::TextBoxInt::TextBoxInt(const char* name)
	: TextBoxBasic::TextBoxBasic(name)
{
	_value = 0;
}

int GUI::TextBoxInt::GetValue() const noexcept
{
	return _value;
}

void GUI::TextBoxInt::SetValue(int value) noexcept
{
	_value = value;
}

void GUI::TextBoxInt::Draw() noexcept
{
	if (!GetIsVisible())
		return;

	const char* name = GetName();
	//Offset for removing ## in text
	int offset = 2;

	switch (GetLabelPosition())
	{
	case TBLP_Top:
		ImGui::Text(name + offset);
		ImGui::InputInt(GetName(), &_value, 1, 100, GetFlags());
		offset -= 2;
		break;
	case TBLP_Bottom:
		ImGui::InputInt(GetName(), &_value, 1, 100, GetFlags());
		ImGui::Text(name + offset);
		offset -= 2;
		break;
	case TBLP_Left:
		ImGui::Text(name + offset); ImGui::SameLine();
		offset -= 2;
	case TBLP_Right:
	default:
		ImGui::InputInt(GetName(), &_value, 1, 100, GetFlags());
		break;
	}

	
}


void DrawTextBox(GUI::TextBox* textBox, const char* name) {
	auto hint = textBox->GetHint();

	if (hint)
		ImGui::InputTextWithHint(name, hint, textBox->GetText(), textBox->GetTextLength(), textBox->GetFlags());
	else
		ImGui::InputText(name, textBox->GetText(), textBox->GetTextLength(), textBox->GetFlags());
}