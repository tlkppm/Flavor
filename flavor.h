#pragma once

#include <Windows.h>
#include <string>
#include <functional>
#include <map>
#include <wrl.h>

struct ICoreWebView2;
struct ICoreWebView2Controller;
struct ICoreWebView2Environment;

namespace Flavor
{
    inline bool g_Running = true;
    inline HWND g_Hwnd = nullptr;
    inline Microsoft::WRL::ComPtr<ICoreWebView2Controller> g_WebViewController;
    inline Microsoft::WRL::ComPtr<ICoreWebView2> g_WebView;

    inline int g_WindowWidth = 800;
    inline int g_WindowHeight = 500;

    bool Initialize();
    void Shutdown();
    void RunMessageLoop();

    using MessageCallback = std::function<void(const std::wstring& type, const std::wstring& payload)>;
    void RegisterMessageHandler(const std::wstring& type, MessageCallback callback);
    void UnregisterMessageHandler(const std::wstring& type);
    
    void SendToUI(const std::wstring& type, const std::wstring& payload = L"");
    void ExecuteScript(const std::wstring& script);

    void SetWindowTransparent(bool transparent);
    void SetWindowTopmost(bool topmost);
    void SetWindowSize(int width, int height);
}

extern "C" __declspec(dllexport) void StartFlavor();
extern "C" __declspec(dllexport) void StopFlavor();
extern "C" __declspec(dllexport) void FlavorSendMessage(const wchar_t* type, const wchar_t* payload);
extern "C" __declspec(dllexport) void SetTransparent(bool transparent);
extern "C" __declspec(dllexport) void SetTopmost(bool topmost);
