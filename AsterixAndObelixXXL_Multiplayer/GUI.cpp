#pragma once
#include "GUI.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include <stdexcept>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);

LRESULT CALLBACK WindowProcess(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);

bool GUI::SetupWindowClass(const wchar_t* wndClassName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = wndClassName;
	windowClass.hIconSm = NULL;

	return RegisterClassEx(&windowClass);
}

void GUI::DestroyWindowClass() noexcept
{
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool GUI::SetupWindow(const wchar_t* wndName) noexcept
{
	window = CreateWindow(
		windowClass.lpszClassName,
		wndName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		200,
		200,
		0,
		0,
		windowClass.hInstance,
		0
	);

	return window != NULL;
}

void GUI::DestroyWindow() noexcept
{
	if (window)
		DestroyWindow(window);
}

bool GUI::SetupDirectX() noexcept
{
	const auto handle = GetModuleHandleA("d3d9.dll");

	if (!handle)
		return false;

	using CreateFunc = LPDIRECT3D9(__stdcall*)(UINT);

	const auto createFunc = reinterpret_cast<CreateFunc>(GetProcAddress(handle, "Direct3DCreate9"));

	if (!createFunc)
		return false;

	d3d9 = createFunc(D3D_SDK_VERSION);

	if (!d3d9)
		return false;

	D3DPRESENT_PARAMETERS params = { };
	params.BackBufferWidth = 0;
	params.BackBufferHeight = 0;
	params.BackBufferFormat = D3DFMT_UNKNOWN;
	params.BackBufferCount = 0;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = window;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	return d3d9->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_NULLREF,
		window,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT,
		&params,
		&device
	) >= 0;
}

void GUI::DestroyDirectX() noexcept
{
	if (device) {
		device->Release();
		device = NULL;
	}

	if (d3d9) {
		d3d9->Release();
		d3d9 = NULL;
	}
}

void GUI::Setup()
{
	if (!SetupWindowClass(WND_CLASS_NAME))
		throw std::runtime_error("Failed to create IMGUI window class.");

	if (!SetupWindow(WND_NAME))
		throw std::runtime_error("Failed to create IMGUI window.");

	if (!SetupDirectX())
		throw std::runtime_error("Failed to create d3d9 device.");

	DestroyWindow();
	DestroyWindowClass();
}

void GUI::SetupMenu(LPDIRECT3DDEVICE9 device) noexcept
{
	D3DDEVICE_CREATION_PARAMETERS params = { };
	device->GetCreationParameters(&params);

	window = params.hFocusWindow;

	if (!window) {
		OutputDebugString(L"Error setup menu. Window is null");
		return;
	}

	originalWndProcess = reinterpret_cast<WNDPROC>(
		SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcess))
		);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	GUI::isSetup = true;
}

void GUI::Destroy() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(
		window,
		GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(originalWndProcess)
	);

	DestroyDirectX();
}

void GUI::Render() noexcept
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	for (auto itr = controls.begin(); itr != controls.end(); itr++)
		(*itr)->Draw();

	//ImGui::Begin("Test menu", &isOpen, wndFlgs);

	//if (ImGui::BeginMenuBar()) {
	//	if (ImGui::BeginMenu("Windows")) {
	//		ImGui::MenuItem("Help", NULL, &helpPressed);
	//		ImGui::EndMenu();
	//	}

	//	if (helpPressed) {
	//		ImGui::Begin("Help");
	//		ImGui::Text("For minimize/maximize window press Insert \nFor fully close menu press End");
	//		ImGui::End();
	//	}
	//	ImGui::EndMenuBar();
	//}

	//	ImGui::Text("Test text");
	//ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		GUI::isOpen = !GUI::isOpen;

	if (GUI::isOpen && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return 1;

	return CallWindowProc(
		GUI::originalWndProcess,
		hWnd,
		msg,
		wParam,
		lParam
	);
}
