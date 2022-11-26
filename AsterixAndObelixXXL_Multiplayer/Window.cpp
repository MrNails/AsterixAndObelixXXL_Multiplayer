#include "Window.h"
#include <string>


GUI::Window::Window() : Window::Window(GenerateSequentialControlName("Window")) {}

GUI::Window::Window(const char* name) : IControl::IControl(name)
{
	_width = 600;
	_height = 400;
	_isCollapsed = false;
}

GUI::Window::~Window()
{
	auto controls = GetControls();

	for (auto itr = controls->begin(); itr != controls->end(); itr++)
		delete (*itr);

	controls->clear();
}

void GUI::Window::Draw() noexcept
{
	if (!GetIsVisible())
		return;

	//ImVec2 vec(_width, _height);
	//ImGui::SetWindowSize(GetName(), vec);

	_isCollapsed = ImGui::Begin(GetName());

	auto controls = GetControls();
	for (auto itr = controls->begin(); itr != controls->end(); itr++)
		(*itr)->Draw();

	ImGui::End();

	//vec = ImGui::GetWindowSize();

	//std::string str = "%s: [%f;%f]\n";
	//auto outPutStr = StringFormat(str, GetName(), _width, _height);

	//printf_s(outPutStr.c_str());

	//_width = vec.x;
	//_height = vec.y;
}
