#pragma once
#include <d3d9.h>

namespace GUI {
	inline const wchar_t* WND_CLASS_NAME = L"MultiplayerDLLClass";
	inline const wchar_t* WND_NAME = L"Multiplayer DLL";

	inline bool isOpen = true;
	inline bool isSetup = false;

	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };
	inline WNDPROC originalWndProcess = nullptr;

	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline LPDIRECT3D9 d3d9 = nullptr;

	bool SetupWindowClass(const wchar_t* wndClassName) noexcept;
	void DestroyWindowClass() noexcept;

	bool SetupWindow(const wchar_t* wndName) noexcept;
	void DestroyWindow() noexcept;

	bool SetupDirectX() noexcept;
	void DestroyDirectX() noexcept;

	void Setup();

	void SetupMenu(LPDIRECT3DDEVICE9 device) noexcept;
	void Destroy() noexcept;

	void Render() noexcept;
}