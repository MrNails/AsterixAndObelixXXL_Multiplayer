#pragma once
#include <d3d9.h>
#include "pch.h"

namespace GUI {
	bool isOpen = true;
	bool isSetup = false;

	HWND window = nullptr;
	WNDCLASSEX windowClass = { };
	WNDPROC originalWndProcess = nullptr;

	LPDIRECT3DDEVICE9 device = nullptr;
	LPDIRECT3D9 d3d9 = nullptr;

	bool SetupWindowClass(const char* wndClassName) noexcept;
	void DestroyWindowClass() noexcept;

	bool SetupWindow(const char* wndName) noexcept;
	void DestroyWindow() noexcept;

	bool SetupDirectX() noexcept;
	void DestroyDirectX() noexcept;

	void Setup();

	void SetupMenu(LPDIRECT3DDEVICE9 device) noexcept;
	void Destroy() noexcept;

	void Render() noexcept;
}