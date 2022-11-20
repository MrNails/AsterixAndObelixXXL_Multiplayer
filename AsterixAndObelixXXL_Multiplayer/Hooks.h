#pragma once
#include "GUI.h"

namespace Hooks {
	void Setup();
	void Destroy() noexcept;

	constexpr void* VirtualFunction(void* thisPtr, size_t index) noexcept {
		return (*static_cast<void***>(thisPtr))[index];
	}

	using EndSceneFunc = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
	inline EndSceneFunc EndSceneOriginal = nullptr;
	long __stdcall EndScene(IDirect3DDevice9* device) noexcept;

	using ResetFunc = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
	inline ResetFunc ResetOriginal = nullptr;
	HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept;
}