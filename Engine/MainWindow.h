#pragma once
#include "WinDefines.h"
#include "CustomException.h"
#include <string>
#include <Dbt.h>

#include "SystemMessageDispatcher.h"
#include "ISystem.h"

#include "Consts.h"

// for granting special access to hWnd only for Graphics constructor
class HWNDKey
{
public:
	HWNDKey(const HWNDKey&) = delete;
	HWNDKey& operator=(HWNDKey&) = delete;
	HWNDKey() = default;
	HWND hWnd = nullptr;
};

class MainWindow : public HWNDKey, public ISystem
{
public:
	class Exception : public CustomException
	{
	public:
		using CustomException::CustomException;
		virtual std::wstring GetFullMessage() const override { return GetNote() + L"\nAt: " + GetLocation(); }
		virtual std::wstring GetExceptionType() const override { return L"Windows Exception"; }
	};

public:
	MainWindow(HINSTANCE hInst, wchar_t * pArgs);
	MainWindow(HWND hWnd);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	~MainWindow();

	virtual void RecieveMessage(ISystemMessage& message) override;

	bool IsActive() const;
	bool IsMinimized() const;
	void ShowMessageBox(const std::wstring& title, const std::wstring& message, UINT type = MB_OK) const;

	void Kill()
	{
		PostQuitMessage(0);
	}

	// returns false if quitting
	bool ProcessMessage();

	const std::wstring& GetArgs() const
	{
		return args;
	}

private:
	static LRESULT WINAPI _HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI _HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static constexpr wchar_t* wndClassName = L"GEPAA Engine";
	HINSTANCE hInst = nullptr;
	std::wstring args;
};