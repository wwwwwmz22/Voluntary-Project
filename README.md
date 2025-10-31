# `Voluntary-Project`

## 项目简介

友邻空间志愿者报名系统是一个志愿者数字化管理系统，主要涵盖志愿者管理、值班信息管理等功能，便于书吧的志愿者招募，辅助楼委会管理书吧的日常志愿服务。

## 软件架构

### 后端核心技术栈

这是友邻空间志愿者报名系统后端代码

### `CPP`技术栈

#### 后端核心技术栈

| 技术              | 说明               | 版本                                                   | 备注                                                         |
| ----------------- | ------------------ | ------------------------------------------------------ | ------------------------------------------------------------ |
| `oat++`           | Web框架            | `1.3.0`                                                | https://github.com/oatpp/oatpp                               |
| `MySQL Connector` | `MySQL`连接驱动库  | 8.0.27                                                 | https://dev.mysql.com/downloads/connector/cpp/<br>https://dev.mysql.com/doc/connector-cpp/1.1/en/connector-cpp-apps.html |
| `JWT`             | `JSON` Web Token   | [v1.4](https://github.com/arun11299/cpp-jwt/tree/v1.4) | https://opensourcelibs.com/lib/cpp-jwt                       |
| `OpenSSL`         | 开源安全套接层协议 | `1.1.1L`                                               | https://www.openssl.org/<br>https://www.xolphin.com/support/OpenSSL/OpenSSL_-_Installation_under_Windows |

#### 后端扩展技术栈

| 技术       | 说明              | 版本     | 备注                                               |
| ---------- | ----------------- | -------- | -------------------------------------------------- |
| `xlnt`     | excel报表         | 1.5.0    | https://github.com/tfussell/xlnt                   |
| `fastdfs`  | 文件存储客户端    | latest   | https://gitee.com/fastdfs100                       |
| `yaml-cpp` | 解析`yaml`数据    | 0.7.0    | https://github.com/jbeder/yaml-cpp                 |
| `nacos`    | `nacos`客户端     | `v1.1.0` | https://github.com/nacos-group/nacos-sdk-cpp       |

## 环境要求

### 开发工具

| 工具            | 说明                  | 版本      | 备注                                                         |
| --------------- | --------------------- | --------- | ------------------------------------------------------------ |
| `Navicat`       | 数据库连接工具        | latest    | https://www.navicat.com.cn/                                  |
| `RDM`           | `Redis`可视化管理工具 | latest    | https://github.com/uglide/RedisDesktopManager<br>https://gitee.com/qishibo/AnotherRedisDesktopManager |
| `PowerDesigner` | 数据库设计工具        | 16.6      | http://powerdesigner.de/                                     |
| `Axure`         | 原型设计工具          | 9         | https://www.axure.com/                                       |
| `MindMaster`    | 思维导图设计工具      | latest    | http://www.edrawsoft.cn/mindmaster                           |
| `Visio`         | 流程图绘制工具        | latest    | https://www.microsoft.com/zh-cn/microsoft-365/visio/flowchart-software |
| `Apifox`        | `API`接口调试工具     | latest    | https://apifox.com/                                          |
| `Git`           | 项目版本管控工具      | latest    | https://git-scm.com/                                         |
| `VS`            | `C++`开发`IDE`        | 2022      | https://learn.microsoft.com/en-us/visualstudio/releases/2022/release-notes |
| `Cmake`         | `C++`跨平台编译       | latest    | https://cmake.org/cmake/help/latest/index.html               |
| gtest           | 测试框架              | 1.14.0    | https://github.com/google/googletest                         |


### 开发环境

| 依赖环境  | 版本 | 备注     |
| --------- | ---- | -------- |
| `Windows` | 11   | 操作系统 |