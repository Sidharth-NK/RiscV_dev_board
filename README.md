# HiFive1 Rev B Development Board Repository

## Overview

This repository contains code and resources for working with the **HiFive1 Rev B** development board, which is based on the **SiFive FE310-G002** RISC-V processor. The HiFive1 Rev B is designed for developing and testing RISC-V applications, especially for embedded system projects.

This repository includes examples and libraries for basic functionality like **LED blinking**, **UART communication**, and **sensor interfacing** using various communication protocols like **SPI** and **I2C**. It also includes instruction for wifi connectivity using the esp32 SOLO-1 module in the board                            . It also includes configurations and setup instructions for working with the **Freedom SDK**, **Freedom Metal**, and **PlatformIO**.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Getting Started](#getting-started)
- [Examples](#examples)
- [Supported Peripherals](#supported-peripherals)
- [License](#license)

## Features

- **RISC-V Architecture**: Leverage the RISC-V instruction set with the FE310-G002 core.
- **PlatformIO Support**: Integrated with PlatformIO for easy development and debugging.
- **Freedom SDK**: Libraries and tools from SiFive's Freedom SDK to work with the HiFive1 Rev B board.
- **Freedom Metal Framework**: Low-level hardware abstraction to interact with peripherals.
- **UART Communication**: For serial communication with the host computer.
- **GPIO & LED Control**: Simple examples to blink LEDs and handle digital I/O.
- **SPI/I2C Interfacing**: Support for interfacing with external sensors and modules.

## Requirements

Before you begin, ensure you have the following tools and software installed:

- **PlatformIO**: A professional collaborative development environment for embedded systems.
  - Install via [PlatformIO Installation Guide](https://platformio.org/install)
- **Freedom SDK**: SiFive’s software development kit to build RISC-V applications.
  - Download from [Freedom SDK GitHub](https://github.com/sifive/freedom)
- **Freedom Metal**: Low-level framework for hardware abstraction on SiFive RISC-V boards.
  - [Freedom Metal Documentation](https://github.com/sifive/freedom-metal)

## Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/hifive1-rev-b.git
   cd hifive1-rev-b
