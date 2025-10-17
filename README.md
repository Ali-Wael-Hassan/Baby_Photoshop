# Faculty of Computing and Artificial Intelligence, Cairo University

## CS213: Object-Oriented Programming

# DUCK: Simple Image Editor Application

## Team Members

- Ali Wael Abdalla             20240354
- Amr Atif Abd-ElKarim Saad    20240398
- Youssef Mohamed Hassib       20240707

## Instructor

- Dr. Mohammad El-Ramly



## Project Overview

DUCK is a desktop application developed for the **CS213: Object-Oriented Programming** course (2025/2026) at the **Faculty of Computing and Artificial Intelligence, Cairo University**.

The program allows users to perform core image manipulation and apply various filters using **C++** and the **Qt 6 Framework**. It features a modern, fluid graphical interface built with **Qt Quick (QML)**.

| Detail | Value |
| :--- | :--- |
| **Application Name** | **DUCK** |
| **Team Name** | **El 3esha Company** |
| **Instructor** | Dr. Mohammad El-Ramly |
| **Build System** | CMake + MinGW 64-bit |

---

## Key Features & Object-Oriented Design

The application showcases core OOP principles through its structured C++ backend and tightly integrated QML frontend.

### Core Functionality

* **Undo/Redo:** Implements a command history manager to allow users to revert or re-apply modifications.
* **Persistent Data:** Handles image loading and saving (`.png`, `.jpg`, `.bmp`).
* **Shortcuts:** Full support for desktop-standard keyboard controls (e.g., $\text{Ctrl}+\text{S}$ for Save, $\text{Ctrl}+\text{Z}$ for Undo).
* **Theming:** Dynamic Dark/Light Mode toggle available in the editor interface.

### Image Manipulation Tools

| Category | Features Implemented |
| :--- | :--- |
| **Tonal & Color** | Brightness, Contrast, Sun Exposure, Grayscale, Invert, Purple Filter, Infrared Filter. |
| **Geometric** | **Interactive Crop Tool** (QML selection), Resize (custom dimensions), Rotate ($\mathbf{90^\circ, 180^\circ, 270^\circ}$), and Flip (Horizontal/Vertical). |
| **Artistic** | Oil Painting Effect, Old Photo Effect, Blur, Edge Detection, and Customizable Frame Addition. |
| **Layering** | Image Merge/Overlay with options for common area cropping or full resizing. |

---

## Execution and Deployment

The application is deployed as a single, self-contained binary built for Windows.

### 1. Executable Requirements

The Release executable (`DUCK.exe`) includes all necessary Qt runtime libraries and plugins (MinGW 64-bit) for standalone execution.

### 2. Execution Path

Navigate to the following directory and run the application:

```bash
\Baby_Photoshop_fix\build\Desktop_Qt_6_10_0_MinGW_64_bit-Release\DUCK.exe
```
