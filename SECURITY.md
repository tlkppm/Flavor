# Security Policy

[English](#english) | [中文](#中文)

---

## English

### Supported Versions

| Version | Supported          |
| ------- | ------------------ |
| 1.x.x   | :white_check_mark: |
| < 1.0   | :x:                |

### Reporting a Vulnerability

We take the security of Flavor seriously. If you have discovered a security vulnerability, we appreciate your help in disclosing it to us in a responsible manner.

#### How to Report

1. **Do NOT** create a public GitHub issue for security vulnerabilities
2. Send an email to the project maintainers with details about the vulnerability
3. Include the following information:
   - Type of vulnerability
   - Full path of the source file(s) related to the vulnerability
   - Step-by-step instructions to reproduce the issue
   - Proof-of-concept or exploit code (if possible)
   - Impact of the vulnerability

#### What to Expect

- Acknowledgment of your report within 48 hours
- Regular updates on the progress of fixing the vulnerability
- Credit in the security advisory (if desired)

#### Security Best Practices

When using Flavor in your applications:

- Keep the WebView2 runtime updated
- Validate all messages received from the UI layer
- Do not expose sensitive APIs through the message bridge
- Use HTTPS for any external resources loaded in the WebView

---

## 中文

### 支持的版本

| 版本    | 支持状态           |
| ------- | ------------------ |
| 1.x.x   | :white_check_mark: |
| < 1.0   | :x:                |

### 报告漏洞

我们非常重视 Flavor 的安全性。如果您发现了安全漏洞，我们感谢您以负责任的方式向我们披露。

#### 如何报告

1. **请勿** 为安全漏洞创建公开的 GitHub issue
2. 向项目维护者发送电子邮件，详细说明漏洞情况
3. 包括以下信息：
   - 漏洞类型
   - 与漏洞相关的源文件完整路径
   - 重现问题的详细步骤
   - 概念验证或利用代码（如果可能）
   - 漏洞的影响

#### 预期流程

- 在 48 小时内确认收到您的报告
- 定期更新修复漏洞的进展
- 在安全公告中致谢（如果您愿意）

#### 安全最佳实践

在您的应用程序中使用 Flavor 时：

- 保持 WebView2 运行时更新
- 验证从 UI 层收到的所有消息
- 不要通过消息桥接暴露敏感 API
- 对 WebView 中加载的任何外部资源使用 HTTPS
