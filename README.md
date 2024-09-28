# GPU Temperature Monitor

## Overview

**GPU Temperature Monitor** is a tool that allows you to visualize GPU temperature changes over time. By moving your mouse over the graph, you can view detailed information.

## Features

- **Visualize Temperature Changes**: Track GPU temperature variations over time with an interactive graph.
- **Detailed Temperature Monitoring**: Unlike typical tools such as NVIDIA GeForce Experience and Windows Task Manager, this tool provides access to:
  - GPU Temperature
  - GPU hotspot Temperature
  - Memory Temperature

  This is achieved using NVAPI's undocumented interface, similar to what AIDA offers.

## Limitations

- **NVidia GPUs Only**: This tool is designed specifically for NVidia graphics cards. It does not support integrated or AMD GPUs.
- **Single GPU Display**: If you have multiple NVidia GPUs, the tool will only display information for the last detected GPU.

## Tested Environment

- **Operating System**: Windows 11
- **CPU**: Intel
- **GPU**: NVIDIA GeForce RTX 4090

## License

This project is licensed under the GNU General Public License (GPL).

---

# GPU 温度监测工具

## 概述

**GPU 温度监测工具** 能够让您直观地查看 GPU 温度随时间的变化。通过将鼠标移动到图表上，可以查看详细信息。

## 特色

- **可视化温度变化**：通过交互式图表轻松跟踪 GPU 温度的变化。
- **详细温度监测**：与 NVIDIA GeForce Experience 和 Windows 资源管理器等常规工具不同，本工具提供：
  - GPU 温度
  - GPU 核心热点温度
  - 显存温度

  这是通过 NVAPI 的未公开接口实现的，目前市面上仅 AIDA 可以查看这些数据。

## 限制

- **仅支持 NVidia 显卡**：本工具专为 NVidia 显卡设计，不支持集成显卡或 AMD 显卡。
- **单显卡显示**：如果您有多张 NVidia 显卡，程序默认仅显示最后一张显卡的信息。

## 测试环境

- **操作系统**：Windows 11
- **CPU**：Intel
- **GPU**：NVIDIA GeForce RTX 4090

## 开源协议

本项目使用 GNU General Public License (GPL) 协议。
