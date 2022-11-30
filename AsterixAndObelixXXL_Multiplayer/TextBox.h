#pragma once
#include "IControl.h"

namespace GUI {
	/// <summary>
	/// May no properly working for different TextBox types 
	/// </summary>
	enum TextBoxFlags {
        TB_None = 0,
        TB_CharsDecimal = 1 << 0,   // Allow 0123456789.+-*/
        TB_CharsHexadecimal = 1 << 1,   // Allow 0123456789ABCDEFabcdef
        TB_CharsUppercase = 1 << 2,   // Turn a..z into A..Z
        TB_CharsNoBlank = 1 << 3,   // Filter out spaces, tabs
        TB_AutoSelectAll = 1 << 4,   // Select entire text when first taking mouse focus
        TB_EnterReturnsTrue = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
        TB_CallbackCompletion = 1 << 6,   // Callback on pressing TAB (for completion handling)
        TB_CallbackHistory = 1 << 7,   // Callback on pressing Up/Down arrows (for history handling)
        TB_CallbackAlways = 1 << 8,   // Callback on each iteration. User code may query cursor position, modify text buffer.
        TB_CallbackCharFilter = 1 << 9,   // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
        TB_AllowTabInput = 1 << 10,  // Pressing TAB input a '\t' character into the text field
        TB_CtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
        TB_NoHorizontalScroll = 1 << 12,  // Disable following the cursor horizontally
        TB_AlwaysOverwrite = 1 << 13,  // Overwrite mode
        TB_ReadOnly = 1 << 14,  // Read-only mode
        TB_Password = 1 << 15,  // Password mode, display all characters as '*'
        TB_NoUndoRedo = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
        TB_CharsScientific = 1 << 17,  // Allow 0123456789.+-*/eE (Scientific notation input)
        TB_CallbackResize = 1 << 18,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
        TB_CallbackEdit = 1 << 19,  // Callback on any edit (note that InputText() already returns true on edit, the callback is useful mainly to manipulate the underlying buffer while focus is active)
        TB_EscapeClearsAll = 1 << 20,  // Escape key clears content if not empty, and deactivate otherwise (constrast to default behavior of Escape to revert)
	};

    enum TextBoxLabelPosition {
        TBLP_Right,
        TBLP_Left,
        TBLP_Top,
        TBLP_Bottom
    };

	class TextBoxBasic : public IControl
	{
        const char* _hint;
        TextBoxFlags _flgs;
        TextBoxLabelPosition _labelPos;

	public:
		TextBoxBasic(const char* name);
		~TextBoxBasic();

        TextBoxFlags GetFlags() const noexcept;
        void SetFlags(TextBoxFlags flags) noexcept;

        TextBoxLabelPosition GetLabelPosition() const noexcept;
        void SetLabelPosition(TextBoxLabelPosition labelPosition) noexcept;

        const char* GetHint() const noexcept;
        void SetHint(const char* hint, bool deleteOldHint = false) noexcept;
	};

    class TextBox : public TextBoxBasic {
        char* _text;
        int _textLength;
        //bool _allowMultiLines;

    public:
        inline static const int DEFAULT_TB_LENGTH = 11; //Text length + '\0'

        TextBox();
        TextBox(const char* name);
        ~TextBox();

        char* GetText() const noexcept;
        /// <summary>
        /// Copy text from input string. If input text length > TextBox text length - input string wil be truncated
        /// </summary>
        /// <param name="text">Input string that will be copied</param>
        void SetText(const char* text);

        int GetTextLength() const noexcept;
        void SetTextLength(int length);

        //bool GetAllowMultiLines() const noexcept;
        //void SetAllowMultilines() noexcept;


        virtual void Draw() noexcept override;
    };

    class TextBoxInt : public TextBoxBasic {
        int _value;

    public:
        TextBoxInt();
        TextBoxInt(const char* name);

        int GetValue() const noexcept;
        void SetValue(int value) noexcept;

        virtual void Draw() noexcept override;
    };
}

