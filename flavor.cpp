#include <Windows.h>
#include <wrl.h>
#include <wil/com.h>
#include <string>
#include <functional>
#include <map>
#include <shlwapi.h>
#include <dwmapi.h>

#include "WebView2.h"
#include "flavor.h"

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "dwmapi.lib")

using namespace Microsoft::WRL;

static std::map<std::wstring, Flavor::MessageCallback> g_MessageHandlers;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
        if (Flavor::g_WebViewController)
        {
            RECT bounds;
            GetClientRect(hWnd, &bounds);
            Flavor::g_WebViewController->put_Bounds(bounds);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

namespace Flavor
{
    static HMODULE GetCurrentModule()
    {
        HMODULE hModule = nullptr;
        GetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCWSTR)&GetCurrentModule,
            &hModule);
        return hModule;
    }

    static std::wstring GetUIPath()
    {
        wchar_t modulePath[MAX_PATH];
        GetModuleFileNameW(GetCurrentModule(), modulePath, MAX_PATH);
        PathRemoveFileSpecW(modulePath);
        
        std::wstring path = modulePath;
        path += L"\\ui\\dist\\index.html";
        return path;
    }

    bool Initialize()
    {
        WNDCLASSEXW wc = {};
        wc.cbSize = sizeof(wc);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = L"FlavorWindow";
        RegisterClassExW(&wc);

        g_Hwnd = CreateWindowExW(
            0,
            L"FlavorWindow",
            L"Flavor",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            g_WindowWidth, g_WindowHeight,
            nullptr, nullptr,
            GetModuleHandle(nullptr),
            nullptr
        );

        if (!g_Hwnd)
            return false;

        ShowWindow(g_Hwnd, SW_SHOW);
        UpdateWindow(g_Hwnd);

        wchar_t userDataPath[MAX_PATH];
        GetTempPathW(MAX_PATH, userDataPath);
        wcscat_s(userDataPath, L"Flavor");

        HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
            nullptr, userDataPath, nullptr,
            Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
                [](HRESULT result, ICoreWebView2Environment* env) -> HRESULT
                {
                    if (FAILED(result))
                        return result;

                    env->CreateCoreWebView2Controller(
                        g_Hwnd,
                        Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                            [](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT
                            {
                                if (FAILED(result) || !controller)
                                    return result;

                                g_WebViewController = controller;
                                g_WebViewController->get_CoreWebView2(&g_WebView);

                                ICoreWebView2Settings* settings;
                                g_WebView->get_Settings(&settings);
                                settings->put_IsScriptEnabled(TRUE);
                                settings->put_AreDefaultScriptDialogsEnabled(TRUE);
                                settings->put_IsWebMessageEnabled(TRUE);
                                settings->put_AreDevToolsEnabled(TRUE);

                                RECT bounds;
                                GetClientRect(g_Hwnd, &bounds);
                                g_WebViewController->put_Bounds(bounds);

                                // 设置虚拟主机映射解决CORS问题
                                ICoreWebView2_3* webview3 = nullptr;
                                g_WebView->QueryInterface(IID_PPV_ARGS(&webview3));
                                if (webview3)
                                {
                                    std::wstring uiFolder = GetUIPath();
                                    size_t pos = uiFolder.rfind(L"\\index.html");
                                    if (pos != std::wstring::npos)
                                    {
                                        uiFolder = uiFolder.substr(0, pos);
                                    }
                                    webview3->SetVirtualHostNameToFolderMapping(
                                        L"flavor.local",
                                        uiFolder.c_str(),
                                        COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND_ALLOW
                                    );
                                    webview3->Release();
                                }

                                g_WebView->add_WebMessageReceived(
                                    Callback<ICoreWebView2WebMessageReceivedEventHandler>(
                                        [](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT
                                        {
                                            wchar_t* message;
                                            args->TryGetWebMessageAsString(&message);
                                            if (message)
                                            {
                                                std::wstring msg(message);
                                                std::wstring type, payload;
                                                
                                                size_t typeStart = msg.find(L"\"type\":\"");
                                                if (typeStart != std::wstring::npos)
                                                {
                                                    typeStart += 8;
                                                    size_t typeEnd = msg.find(L"\"", typeStart);
                                                    if (typeEnd != std::wstring::npos)
                                                    {
                                                        type = msg.substr(typeStart, typeEnd - typeStart);
                                                    }
                                                }
                                                
                                                size_t payloadStart = msg.find(L"\"payload\":");
                                                if (payloadStart != std::wstring::npos)
                                                {
                                                    payloadStart += 10;
                                                    size_t payloadEnd = msg.rfind(L"}");
                                                    if (payloadEnd != std::wstring::npos)
                                                    {
                                                        payload = msg.substr(payloadStart, payloadEnd - payloadStart);
                                                    }
                                                }
                                                
                                                auto it = g_MessageHandlers.find(type);
                                                if (it != g_MessageHandlers.end())
                                                {
                                                    it->second(type, payload);
                                                }
                                                
                                                auto allIt = g_MessageHandlers.find(L"*");
                                                if (allIt != g_MessageHandlers.end())
                                                {
                                                    allIt->second(type, payload);
                                                }
                                            }
                                            CoTaskMemFree(message);
                                            return S_OK;
                                        }
                                    ).Get(), nullptr
                                );

                                // 使用虚拟主机地址而非file://协议
                                g_WebView->Navigate(L"https://flavor.local/index.html");

                                return S_OK;
                            }
                        ).Get()
                    );
                    return S_OK;
                }
            ).Get()
        );

        return SUCCEEDED(hr);
    }

    void Shutdown()
    {
        if (g_WebViewController)
        {
            g_WebViewController->Close();
            g_WebViewController = nullptr;
        }
        g_WebView = nullptr;

        if (g_Hwnd)
        {
            DestroyWindow(g_Hwnd);
            g_Hwnd = nullptr;
        }

        UnregisterClassW(L"FlavorWindow", GetModuleHandle(nullptr));
    }

    void RunMessageLoop()
    {
        MSG msg;
        while (g_Running && GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                g_Running = false;
            }
        }
    }

    void RegisterMessageHandler(const std::wstring& type, MessageCallback callback)
    {
        g_MessageHandlers[type] = callback;
    }

    void UnregisterMessageHandler(const std::wstring& type)
    {
        g_MessageHandlers.erase(type);
    }

    void SendToUI(const std::wstring& type, const std::wstring& payload)
    {
        if (g_WebView)
        {
            std::wstring message = L"{\"type\":\"" + type + L"\"";
            if (!payload.empty())
            {
                message += L",\"payload\":" + payload;
            }
            message += L"}";
            g_WebView->PostWebMessageAsString(message.c_str());
        }
    }

    void ExecuteScript(const std::wstring& script)
    {
        if (g_WebView)
        {
            g_WebView->ExecuteScript(script.c_str(), nullptr);
        }
    }

    void SetWindowTransparent(bool transparent)
    {
        if (!g_Hwnd) return;

        LONG exStyle = GetWindowLong(g_Hwnd, GWL_EXSTYLE);
        if (transparent)
        {
            SetWindowLong(g_Hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED);
            SetLayeredWindowAttributes(g_Hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
            
            MARGINS margins = { -1 };
            DwmExtendFrameIntoClientArea(g_Hwnd, &margins);
        }
        else
        {
            SetWindowLong(g_Hwnd, GWL_EXSTYLE, exStyle & ~WS_EX_LAYERED);
        }
    }

    void SetWindowTopmost(bool topmost)
    {
        if (!g_Hwnd) return;
        SetWindowPos(g_Hwnd, topmost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }

    void SetWindowSize(int width, int height)
    {
        if (!g_Hwnd) return;
        SetWindowPos(g_Hwnd, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
    }
}

void StartFlavor()
{
    if (!Flavor::Initialize())
        return;

    Flavor::RunMessageLoop();
    Flavor::Shutdown();
}

void StopFlavor()
{
    Flavor::g_Running = false;
    if (Flavor::g_Hwnd)
    {
        PostMessage(Flavor::g_Hwnd, WM_CLOSE, 0, 0);
    }
}

void FlavorSendMessage(const wchar_t* type, const wchar_t* payload)
{
    Flavor::SendToUI(type ? type : L"", payload ? payload : L"");
}

void SetTransparent(bool transparent)
{
    Flavor::SetWindowTransparent(transparent);
}

void SetTopmost(bool topmost)
{
    Flavor::SetWindowTopmost(topmost);
}
