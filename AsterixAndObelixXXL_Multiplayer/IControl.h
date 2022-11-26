#pragma once
#include <stdexcept>
#include <map>
#include "Helpers.h"

namespace GUI {
	class IControl
	{
		inline static std::map<const char*, unsigned int> controlsNames;

		bool _isVisible;
		const char* _name;
	public:
		IControl(const char* name) {
			_isVisible = true;
			SetName(name);
		};
		IControl(const IControl&& control) noexcept {
			auto nameLen = strlen(control.GetName());
			auto tmpName = new char[nameLen];

			memcpy_s(tmpName, nameLen, control.GetName(), nameLen);
			SetName(tmpName);
		}
		~IControl() {
			if (_name != nullptr)
				delete[] _name;
			_name = nullptr;
		}

		virtual void Draw() noexcept = 0;

		void SetName(const char* name, bool deleteOldText = false) {
			if (name == nullptr || std::strlen(name) == 0)
				throw std::runtime_error("Control name cannot be empty.");

			if (deleteOldText)
				DeleteStringAndSetNull(&_name);

			_name = name;
		}

		const char* GetName() const noexcept {
			return _name;
		}

		void SetIsVisible(bool isVisible) noexcept {
			_isVisible = isVisible;
		}

		bool GetIsVisible() const noexcept {
			return _isVisible;
		}

		static const char* GenerateSequentialControlName(const char* controlName) {
			if (controlName == nullptr)
				return EMPTY_STRING;

			unsigned int controlNumber = 0;
			auto elemPos = controlsNames.find(controlName);
			if (elemPos == controlsNames.end())
				controlsNames.insert(std::pair<const char*, unsigned int>{ controlName, controlNumber });
			else
			{
				controlNumber = elemPos->second + 1;
				elemPos->second = controlNumber;
			}

			//int numLen = 0;
			//unsigned int tmpNumber = controlNumber;
			//do 
			//{
			//	numLen++;
			//	tmpNumber /= 10;
			//} while (tmpNumber != 0);

			//char* newStr = new char[strlen(controlName) + numLen];

			return StringFormat("%s%d", controlName, controlNumber);
		}
	};


}

