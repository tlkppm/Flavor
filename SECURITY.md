# Security Policy

This document outlines security procedures and policies for the Flavor project.

---

**[English](#reporting-a-vulnerability)** | **[中文](#报告漏洞)**

---

## Supported Versions

| Version | Supported |
|---------|-----------|
| 1.x     | Yes       |
| < 1.0   | No        |

## Reporting a Vulnerability

If you discover a security vulnerability, please report it responsibly:

1. Do not create a public GitHub issue
2. Email the maintainers with vulnerability details
3. Include:
   - Description of the vulnerability
   - Steps to reproduce
   - Potential impact
   - Suggested fix (if any)

### Response Timeline

- Acknowledgment: within 48 hours
- Initial assessment: within 7 days
- Resolution timeline: depends on severity

## Security Considerations

When using Flavor in your applications:

- Keep WebView2 runtime updated
- Validate all messages from the UI layer
- Avoid exposing sensitive APIs through the message bridge
- Use HTTPS for external resources

---

## 安全政策

本文档概述 Flavor 项目的安全程序和政策。

## 支持的版本

| 版本  | 支持 |
|-------|------|
| 1.x   | 是   |
| < 1.0 | 否   |

## 报告漏洞

如果您发现安全漏洞，请负责任地报告：

1. 不要创建公开的 GitHub issue
2. 向维护者发送漏洞详情邮件
3. 包括：
   - 漏洞描述
   - 重现步骤
   - 潜在影响
   - 建议的修复方案（如有）

### 响应时间

- 确认收到：48 小时内
- 初步评估：7 天内
- 解决时间：取决于严重程度

## 安全注意事项

在您的应用中使用 Flavor 时：

- 保持 WebView2 运行时更新
- 验证来自 UI 层的所有消息
- 避免通过消息桥接暴露敏感 API
- 对外部资源使用 HTTPS
