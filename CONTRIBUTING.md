# Contributing to Flavor

Thank you for your interest in contributing to Flavor. This document provides guidelines for contributing to the project.

---

**[English](#guidelines)** | **[中文](#贡献指南)**

---

## Guidelines

### Code of Conduct

All contributors are expected to adhere to professional standards of conduct. Be respectful, constructive, and inclusive in all interactions.

### Reporting Issues

Before submitting an issue:

1. Search existing issues to avoid duplicates
2. Use the issue template if available
3. Provide clear reproduction steps
4. Include environment details (OS version, Visual Studio version, Node.js version)

### Pull Requests

1. Fork the repository and create a feature branch from `main`
2. Follow the coding standards described below
3. Write clear commit messages
4. Test your changes thoroughly
5. Update documentation if necessary
6. Submit a pull request with a clear description

### Coding Standards

#### C++ Code

- Use C++20 standard features
- Follow Microsoft C++ coding conventions
- Use meaningful names for variables and functions
- Document public APIs with comments

#### TypeScript/React Code

- Use TypeScript for type safety
- Follow React functional component patterns
- Use TailwindCSS for styling
- Keep components focused and reusable

#### Commit Messages

Use the conventional commits format:

```
type(scope): description
```

Types: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`

### Development Setup

```bash
# Clone repository
git clone https://github.com/YOUR_USERNAME/Flavor.git
cd Flavor

# Install UI dependencies
cd ui
npm install

# Development mode
npm run dev

# Production build
npm run build
```

### License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

## 贡献指南

感谢您有兴趣为 Flavor 做出贡献。本文档提供项目贡献指南。

### 行为准则

所有贡献者都应遵守专业的行为标准。在所有互动中保持尊重、建设性和包容性。

### 报告问题

提交问题之前：

1. 搜索现有问题以避免重复
2. 如有问题模板请使用
3. 提供清晰的重现步骤
4. 包含环境详情（操作系统版本、Visual Studio 版本、Node.js 版本）

### Pull Request

1. Fork 仓库并从 `main` 创建功能分支
2. 遵循下述编码标准
3. 编写清晰的提交消息
4. 彻底测试您的更改
5. 如有必要更新文档
6. 提交带有清晰描述的 Pull Request

### 编码标准

#### C++ 代码

- 使用 C++20 标准特性
- 遵循 Microsoft C++ 编码约定
- 使用有意义的变量和函数名
- 为公共 API 添加注释文档

#### TypeScript/React 代码

- 使用 TypeScript 确保类型安全
- 遵循 React 函数组件模式
- 使用 TailwindCSS 进行样式设计
- 保持组件专注且可复用

#### 提交消息

使用约定式提交格式：

```
类型(范围): 描述
```

类型：`feat`、`fix`、`docs`、`style`、`refactor`、`test`、`chore`

### 开发环境设置

```bash
# 克隆仓库
git clone https://github.com/YOUR_USERNAME/Flavor.git
cd Flavor

# 安装 UI 依赖
cd ui
npm install

# 开发模式
npm run dev

# 生产构建
npm run build
```

### 许可证

通过贡献，您同意您的贡献将在 MIT 许可证下授权。
