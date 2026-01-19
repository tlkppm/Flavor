# Flavor

A lightweight GUI framework for Windows native applications, combining C++ performance with modern web technologies through Microsoft WebView2.

---

**[English](#overview)** | **[中文](#概述)**

---

## Overview

Flavor enables developers to build native Windows applications with rich, modern user interfaces using familiar web technologies. The framework provides a C++ DLL that hosts a WebView2 control, allowing you to create your UI with React, TypeScript, and CSS while maintaining native application performance.

### Key Features

- **Native Performance** - C++ core with minimal runtime overhead
- **Modern UI Development** - Build interfaces using React 18, TypeScript, and TailwindCSS
- **Bi-directional Communication** - Type-safe messaging between C++ and JavaScript
- **Hot Reload** - Rapid UI iteration during development with Vite
- **Small Footprint** - Compiled DLL under 100KB (excluding WebView2 runtime)

### System Requirements

| Component | Requirement |
|-----------|-------------|
| Operating System | Windows 10 version 1809 or later, Windows 11 |
| Runtime | WebView2 Runtime (pre-installed on Windows 10/11) |
| Build Tools | Visual Studio 2022 with C++20 support |
| Node.js | Version 18.0 or later |

## Getting Started

### Installation

1. Clone the repository:

```bash
git clone https://github.com/tlkppm/Flavor.git
cd Flavor
```

2. Build the UI:

```bash
cd ui
npm install
npm run build
```

3. Open `Flavor.sln` in Visual Studio and build with Release|x64 configuration.

### Basic Usage

Load the DLL and call the exported functions:

```cpp
#include <Windows.h>

typedef void (*StartFlavorFunc)();
typedef void (*StopFlavorFunc)();

int main() {
    HMODULE module = LoadLibraryW(L"Flavor.dll");
    
    auto StartFlavor = (StartFlavorFunc)GetProcAddress(module, "StartFlavor");
    StartFlavor();  // Blocks until window is closed
    
    FreeLibrary(module);
    return 0;
}
```

## API Reference

### Exported Functions

| Function | Description |
|----------|-------------|
| `void StartFlavor()` | Initializes WebView2 and displays the GUI window. Blocks until the window is closed. |
| `void StopFlavor()` | Closes the GUI window and releases resources. |
| `void FlavorSendMessage(const wchar_t* type, const wchar_t* payload)` | Sends a JSON message to the UI layer. |
| `void SetTransparent(bool enabled)` | Enables or disables window transparency. |
| `void SetTopmost(bool enabled)` | Sets the window to always-on-top. |

### C++ Namespace API

```cpp
namespace Flavor {
    // Message handling
    using MessageCallback = std::function<void(const std::wstring& type, const std::wstring& payload)>;
    void RegisterMessageHandler(const std::wstring& type, MessageCallback callback);
    void UnregisterMessageHandler(const std::wstring& type);
    
    // Communication
    void SendToUI(const std::wstring& type, const std::wstring& payload = L"");
    void ExecuteScript(const std::wstring& script);
    
    // Window control
    void SetWindowTransparent(bool transparent);
    void SetWindowTopmost(bool topmost);
    void SetWindowSize(int width, int height);
}
```

### JavaScript API

```typescript
import { useFlavor, useFlavorMessage } from './hooks/useFlavor';

function Component() {
    const { send, isConnected } = useFlavor();
    
    // Send message to C++
    send('action', { key: 'value' });
    
    // Receive messages from C++
    useFlavorMessage('update', (message) => {
        console.log(message.payload);
    });
}
```

## Project Structure

```
Flavor/
├── flavor.h              # Public API declarations
├── flavor.cpp            # Core implementation
├── Flavor.vcxproj        # Visual Studio project
├── Flavor.sln            # Visual Studio solution
├── packages/             # Dependencies (WebView2, WIL)
├── ui/                   # React application
│   ├── src/
│   │   ├── App.tsx
│   │   ├── hooks/
│   │   │   └── useFlavor.ts
│   │   └── main.tsx
│   ├── dist/             # Production build output
│   └── package.json
└── test/                 # Test application
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for contribution guidelines.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

# 中文文档

## 概述

Flavor 是一个轻量级的 Windows 原生应用 GUI 框架，通过 Microsoft WebView2 将 C++ 性能与现代 Web 技术相结合。

该框架提供一个 C++ DLL，内置 WebView2 控件，允许开发者使用 React、TypeScript 和 CSS 构建用户界面，同时保持原生应用的性能。

### 主要特性

- **原生性能** - C++ 核心，运行时开销极小
- **现代 UI 开发** - 使用 React 18、TypeScript 和 TailwindCSS 构建界面
- **双向通信** - C++ 与 JavaScript 之间的类型安全消息传递
- **热重载** - 使用 Vite 快速迭代 UI 开发
- **体积小** - 编译后 DLL 小于 100KB（不含 WebView2 运行时）

### 系统要求

| 组件 | 要求 |
|------|------|
| 操作系统 | Windows 10 版本 1809 或更高版本，Windows 11 |
| 运行时 | WebView2 运行时（Windows 10/11 已预装） |
| 构建工具 | Visual Studio 2022，支持 C++20 |
| Node.js | 18.0 或更高版本 |

## 快速开始

### 安装

1. 克隆仓库：

```bash
git clone https://github.com/tlkppm/Flavor.git
cd Flavor
```

2. 构建 UI：

```bash
cd ui
npm install
npm run build
```

3. 在 Visual Studio 中打开 `Flavor.sln`，使用 Release|x64 配置进行构建。

### 基本用法

加载 DLL 并调用导出函数：

```cpp
#include <Windows.h>

typedef void (*StartFlavorFunc)();
typedef void (*StopFlavorFunc)();

int main() {
    HMODULE module = LoadLibraryW(L"Flavor.dll");
    
    auto StartFlavor = (StartFlavorFunc)GetProcAddress(module, "StartFlavor");
    StartFlavor();  // 阻塞直到窗口关闭
    
    FreeLibrary(module);
    return 0;
}
```

## API 参考

### 导出函数

| 函数 | 描述 |
|------|------|
| `void StartFlavor()` | 初始化 WebView2 并显示 GUI 窗口。阻塞直到窗口关闭。 |
| `void StopFlavor()` | 关闭 GUI 窗口并释放资源。 |
| `void FlavorSendMessage(const wchar_t* type, const wchar_t* payload)` | 向 UI 层发送 JSON 消息。 |
| `void SetTransparent(bool enabled)` | 启用或禁用窗口透明。 |
| `void SetTopmost(bool enabled)` | 设置窗口置顶。 |

### C++ 命名空间 API

```cpp
namespace Flavor {
    // 消息处理
    using MessageCallback = std::function<void(const std::wstring& type, const std::wstring& payload)>;
    void RegisterMessageHandler(const std::wstring& type, MessageCallback callback);
    void UnregisterMessageHandler(const std::wstring& type);
    
    // 通信
    void SendToUI(const std::wstring& type, const std::wstring& payload = L"");
    void ExecuteScript(const std::wstring& script);
    
    // 窗口控制
    void SetWindowTransparent(bool transparent);
    void SetWindowTopmost(bool topmost);
    void SetWindowSize(int width, int height);
}
```

### JavaScript API

```typescript
import { useFlavor, useFlavorMessage } from './hooks/useFlavor';

function Component() {
    const { send, isConnected } = useFlavor();
    
    // 向 C++ 发送消息
    send('action', { key: 'value' });
    
    // 接收来自 C++ 的消息
    useFlavorMessage('update', (message) => {
        console.log(message.payload);
    });
}
```

## 项目结构

```
Flavor/
├── flavor.h              # 公共 API 声明
├── flavor.cpp            # 核心实现
├── Flavor.vcxproj        # Visual Studio 项目
├── Flavor.sln            # Visual Studio 解决方案
├── packages/             # 依赖项（WebView2、WIL）
├── ui/                   # React 应用
│   ├── src/
│   │   ├── App.tsx
│   │   ├── hooks/
│   │   │   └── useFlavor.ts
│   │   └── main.tsx
│   ├── dist/             # 生产构建输出
│   └── package.json
└── test/                 # 测试应用
```

## 贡献

请参阅 [CONTRIBUTING.md](CONTRIBUTING.md) 了解贡献指南。

## 许可证

本项目采用 MIT 许可证。详情请参阅 [LICENSE](LICENSE)。
