<div align="center">

# 🎨 Flavor

**A modern, high-performance GUI framework for native applications using WebView2 and React**

**一个基于 WebView2 和 React 的现代化高性能原生应用 GUI 框架**

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://isocpp.org/)
[![React](https://img.shields.io/badge/React-18-61dafb.svg)](https://react.dev/)
[![WebView2](https://img.shields.io/badge/WebView2-Latest-green.svg)](https://developer.microsoft.com/en-us/microsoft-edge/webview2/)

[English](#english) | [中文](#中文)

</div>

---

## English

### Overview

Flavor is a lightweight DLL framework that enables you to create beautiful, modern user interfaces for native Windows applications. It combines the power of C++ with the flexibility of web technologies (React, TailwindCSS) through Microsoft's WebView2 runtime.

### ✨ Features

- **Modern UI Stack** - Build interfaces with React, TypeScript, and TailwindCSS
- **Native Performance** - C++ core with minimal overhead
- **Bi-directional Communication** - Seamless messaging between C++ and JavaScript
- **Hot Reload Support** - Rapid UI development with Vite
- **Lightweight** - Small DLL footprint (~500KB)
- **Customizable Window** - Transparent, topmost, and resizable options

### 📋 Requirements

- Windows 10 version 1809+ or Windows 11
- [WebView2 Runtime](https://developer.microsoft.com/en-us/microsoft-edge/webview2/) (usually pre-installed on Windows 10/11)
- Visual Studio 2022+ with C++20 support (for building)
- Node.js 18+ (for UI development)

### 🚀 Quick Start

#### 1. Clone the repository

```bash
git clone https://github.com/tlkppm/Flavor.git
cd Flavor
```

#### 2. Build the UI

```bash
cd ui
npm install
npm run build
```

#### 3. Build the DLL

Open `Flavor.sln` in Visual Studio and build in Release|x64 configuration.

#### 4. Use in your application

```cpp
#include <Windows.h>

typedef void (*StartFlavorFunc)();

int main() {
    HMODULE hModule = LoadLibraryW(L"Flavor.dll");
    auto StartFlavor = (StartFlavorFunc)GetProcAddress(hModule, "StartFlavor");
    StartFlavor();
    FreeLibrary(hModule);
    return 0;
}
```

### 📡 API Reference

#### Exported Functions

| Function | Description |
|----------|-------------|
| `StartFlavor()` | Initialize and show the GUI window |
| `StopFlavor()` | Close the GUI and cleanup resources |
| `FlavorSendMessage(type, payload)` | Send a message to the UI |
| `SetTransparent(bool)` | Enable/disable window transparency |
| `SetTopmost(bool)` | Set window always-on-top |

#### C++ Namespace API

```cpp
namespace Flavor {
    void RegisterMessageHandler(const std::wstring& type, MessageCallback callback);
    void UnregisterMessageHandler(const std::wstring& type);
    void SendToUI(const std::wstring& type, const std::wstring& payload);
    void ExecuteScript(const std::wstring& script);
    void SetWindowTransparent(bool transparent);
    void SetWindowTopmost(bool topmost);
    void SetWindowSize(int width, int height);
}
```

#### React Hooks

```tsx
import { useFlavor, useFlavorMessage, useFlavorState } from './hooks/useFlavor';

// Send messages to C++
const { send, isConnected } = useFlavor();
send('action', { data: 'value' });

// Listen for messages from C++
useFlavorMessage('update', (msg) => {
    console.log(msg.payload);
});

// Bi-directional state sync
const [value, setValue] = useFlavorState('setting', initialValue);
```

### 📁 Project Structure

```
Flavor/
├── ui/                     # React frontend
│   ├── src/
│   │   ├── App.tsx        # Main application component
│   │   ├── hooks/         # React hooks including useFlavor
│   │   └── main.tsx       # Entry point
│   ├── dist/              # Built UI files
│   └── package.json
├── packages/              # Dependencies (WebView2, WIL)
├── flavor.cpp             # Core implementation
├── flavor.h               # Public API header
├── Flavor.vcxproj         # Visual Studio project
└── Flavor.sln             # Visual Studio solution
```

### 🤝 Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 中文

### 概述

Flavor 是一个轻量级 DLL 框架，让你能够为原生 Windows 应用程序创建美观、现代的用户界面。它通过微软的 WebView2 运行时，将 C++ 的强大性能与 Web 技术（React、TailwindCSS）的灵活性相结合。

### ✨ 特性

- **现代 UI 技术栈** - 使用 React、TypeScript 和 TailwindCSS 构建界面
- **原生性能** - C++ 核心，开销极小
- **双向通信** - C++ 与 JavaScript 之间无缝消息传递
- **热重载支持** - 使用 Vite 快速开发 UI
- **轻量级** - DLL 体积小（约 500KB）
- **可定制窗口** - 支持透明、置顶和调整大小

### 📋 系统要求

- Windows 10 版本 1809+ 或 Windows 11
- [WebView2 运行时](https://developer.microsoft.com/zh-cn/microsoft-edge/webview2/)（通常已预装在 Windows 10/11 上）
- Visual Studio 2022+，支持 C++20（用于构建）
- Node.js 18+（用于 UI 开发）

### 🚀 快速开始

#### 1. 克隆仓库

```bash
git clone https://github.com/tlkppm/Flavor.git
cd Flavor
```

#### 2. 构建 UI

```bash
cd ui
npm install
npm run build
```

#### 3. 构建 DLL

在 Visual Studio 中打开 `Flavor.sln`，使用 Release|x64 配置进行构建。

#### 4. 在应用程序中使用

```cpp
#include <Windows.h>

typedef void (*StartFlavorFunc)();

int main() {
    HMODULE hModule = LoadLibraryW(L"Flavor.dll");
    auto StartFlavor = (StartFlavorFunc)GetProcAddress(hModule, "StartFlavor");
    StartFlavor();
    FreeLibrary(hModule);
    return 0;
}
```

### 📡 API 参考

#### 导出函数

| 函数 | 描述 |
|------|------|
| `StartFlavor()` | 初始化并显示 GUI 窗口 |
| `StopFlavor()` | 关闭 GUI 并清理资源 |
| `FlavorSendMessage(type, payload)` | 向 UI 发送消息 |
| `SetTransparent(bool)` | 启用/禁用窗口透明 |
| `SetTopmost(bool)` | 设置窗口置顶 |

#### C++ 命名空间 API

```cpp
namespace Flavor {
    void RegisterMessageHandler(const std::wstring& type, MessageCallback callback);
    void UnregisterMessageHandler(const std::wstring& type);
    void SendToUI(const std::wstring& type, const std::wstring& payload);
    void ExecuteScript(const std::wstring& script);
    void SetWindowTransparent(bool transparent);
    void SetWindowTopmost(bool topmost);
    void SetWindowSize(int width, int height);
}
```

#### React Hooks

```tsx
import { useFlavor, useFlavorMessage, useFlavorState } from './hooks/useFlavor';

// 向 C++ 发送消息
const { send, isConnected } = useFlavor();
send('action', { data: 'value' });

// 监听来自 C++ 的消息
useFlavorMessage('update', (msg) => {
    console.log(msg.payload);
});

// 双向状态同步
const [value, setValue] = useFlavorState('setting', initialValue);
```

### 📁 项目结构

```
Flavor/
├── ui/                     # React 前端
│   ├── src/
│   │   ├── App.tsx        # 主应用组件
│   │   ├── hooks/         # React hooks，包括 useFlavor
│   │   └── main.tsx       # 入口点
│   ├── dist/              # 构建后的 UI 文件
│   └── package.json
├── packages/              # 依赖项（WebView2、WIL）
├── flavor.cpp             # 核心实现
├── flavor.h               # 公共 API 头文件
├── Flavor.vcxproj         # Visual Studio 项目
└── Flavor.sln             # Visual Studio 解决方案
```

### 🤝 贡献

我们欢迎贡献！请参阅 [CONTRIBUTING.md](CONTRIBUTING.md) 了解指南。

### 📄 许可证

本项目采用 MIT 许可证 - 详情请参阅 [LICENSE](LICENSE) 文件。

---

<div align="center">

**Made with ❤️ by the Flavor Team**

</div>
