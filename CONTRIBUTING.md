# Contributing to Flavor | 贡献指南

[English](#english) | [中文](#中文)

---

## English

Thank you for your interest in contributing to Flavor! This document provides guidelines and information about contributing.

### Code of Conduct

This project adheres to our [Code of Conduct](CODE_OF_CONDUCT.md). By participating, you are expected to uphold this code.

### How to Contribute

#### Reporting Bugs

Before creating bug reports, please check existing issues to avoid duplicates. When creating a bug report, include:

- **Clear title** describing the issue
- **Steps to reproduce** the behavior
- **Expected behavior** vs **actual behavior**
- **Environment details** (OS version, Visual Studio version, Node.js version)
- **Screenshots or logs** if applicable

#### Suggesting Features

Feature suggestions are welcome! Please include:

- **Clear description** of the feature
- **Use case** explaining why this feature would be useful
- **Possible implementation** approach (optional)

#### Pull Requests

1. **Fork** the repository
2. **Create a branch** from `main` for your feature (`git checkout -b feature/amazing-feature`)
3. **Make your changes** following the coding standards below
4. **Test your changes** thoroughly
5. **Commit** with clear, descriptive messages
6. **Push** to your fork
7. **Open a Pull Request** with a clear description

### Development Setup

```bash
# Clone your fork
git clone https://github.com/YOUR_USERNAME/Flavor.git
cd Flavor

# Install UI dependencies
cd ui
npm install

# Build UI for development
npm run dev

# Or build for production
npm run build
```

### Coding Standards

#### C++ Code

- Use C++20 features where appropriate
- Follow Microsoft's C++ coding conventions
- Use meaningful variable and function names
- Add comments for complex logic
- Keep functions focused and small

#### TypeScript/React Code

- Use TypeScript for type safety
- Follow React best practices and hooks patterns
- Use functional components
- Keep components small and reusable
- Use TailwindCSS for styling

#### Commit Messages

Follow conventional commits format:

```
type(scope): description

[optional body]

[optional footer]
```

Types: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`

Examples:
- `feat(ui): add dark mode toggle`
- `fix(core): resolve memory leak in message handler`
- `docs: update API reference`

### Testing

- Test C++ changes by building and running the DLL
- Test UI changes in development mode with `npm run dev`
- Ensure no regressions in existing functionality

### License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

## 中文

感谢您有兴趣为 Flavor 做出贡献！本文档提供贡献的指南和信息。

### 行为准则

本项目遵守我们的[行为准则](CODE_OF_CONDUCT.md)。参与即表示您同意遵守此准则。

### 如何贡献

#### 报告 Bug

在创建 Bug 报告之前，请检查现有 issue 以避免重复。创建 Bug 报告时，请包括：

- **清晰的标题** 描述问题
- **重现步骤**
- **预期行为** 与 **实际行为**
- **环境详情**（操作系统版本、Visual Studio 版本、Node.js 版本）
- **截图或日志**（如适用）

#### 功能建议

欢迎功能建议！请包括：

- **清晰的描述**
- **使用场景** 解释为什么这个功能有用
- **可能的实现** 方法（可选）

#### Pull Request

1. **Fork** 仓库
2. 从 `main` **创建分支**（`git checkout -b feature/amazing-feature`）
3. 遵循以下编码标准 **进行更改**
4. **彻底测试** 您的更改
5. 使用清晰的描述性消息 **提交**
6. **推送** 到您的 fork
7. **打开 Pull Request** 并提供清晰的描述

### 开发环境设置

```bash
# 克隆您的 fork
git clone https://github.com/YOUR_USERNAME/Flavor.git
cd Flavor

# 安装 UI 依赖
cd ui
npm install

# 开发模式构建 UI
npm run dev

# 或生产模式构建
npm run build
```

### 编码标准

#### C++ 代码

- 适当使用 C++20 特性
- 遵循 Microsoft C++ 编码约定
- 使用有意义的变量和函数名
- 为复杂逻辑添加注释
- 保持函数专注且简小

#### TypeScript/React 代码

- 使用 TypeScript 确保类型安全
- 遵循 React 最佳实践和 hooks 模式
- 使用函数组件
- 保持组件小巧且可复用
- 使用 TailwindCSS 进行样式设计

#### 提交消息

遵循约定式提交格式：

```
类型(范围): 描述

[可选正文]

[可选页脚]
```

类型：`feat`、`fix`、`docs`、`style`、`refactor`、`test`、`chore`

示例：
- `feat(ui): 添加深色模式切换`
- `fix(core): 修复消息处理器中的内存泄漏`
- `docs: 更新 API 参考`

### 测试

- 通过构建和运行 DLL 测试 C++ 更改
- 使用 `npm run dev` 在开发模式下测试 UI 更改
- 确保现有功能没有回归

### 许可证

通过贡献，您同意您的贡献将在 MIT 许可证下授权。
