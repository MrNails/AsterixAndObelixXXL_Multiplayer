#include "GUI.h"

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_win32.h"
#include "../imgui/backends/imgui_impl_dx9.h"

#include <stdexcept>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler (
	HWND hWnd, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam
);

bool GUI::SetupWindowClass(const char* wndClassName) noexcept
{
	return false;
}

void GUI::DestroyWindowClass() noexcept
{
}

bool GUI::SetupWindow(const char* wndName) noexcept
{
	return false;
}

void GUI::DestroyWindow() noexcept
{
}

bool GUI::SetupDirectX() noexcept
{
	return false;
}

void GUI::DestroyDirectX() noexcept
{
}

void GUI::Setup()
{
}

void GUI::SetupMenu(LPDIRECT3DDEVICE9 device) noexcept
{
}

void GUI::Destroy() noexcept
{
}

void GUI::Render() noexcept
{
}
