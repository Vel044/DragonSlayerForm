# 表单交互系统

## 项目简介
本项目是一个基于终端用户界面的表单交互系统，提供多种输入方式，包括文本输入、整数输入、列表选择、技能输入、勇气值选择和时间范围选择等。系统采用 C++ 编写，并使用了 Windows 平台上的 `_getch()` 进行用户输入处理。

## 功能特性
1. **清屏功能**：提供 `clearScreen()` 以清空终端界面。
2. **等待键输入**：`waitForKey()` 让用户按任意键继续。
3. **文本输入**：`inputField(prompt)` 用于获取用户输入的字符串。
4. **验证输入**：`inputValidatedField(prompt, validator, errorMsg)` 允许用户输入并进行格式验证。
5. **整数输入**：`inputIntegerField(prompt, min, max)` 获取用户输入的整数，并限制范围。
6. **列表选择**：`selectFromList(prompt, options)` 让用户通过方向键选择一个选项。
7. **技能输入**：`inputSkills(prompt)` 允许用户输入多个技能，输入空行结束。
8. **勇气值选择**：`interactiveCourageField(prompt, min, max)` 提供 1-10 的勇气值选择，用户可通过左右方向键调整。
9. **时间范围选择**：`interactiveTimeRangeField(prompt)` 允许用户调整时间段，支持 HH:MM-HH:MM 格式，并确保时长不超过 6 小时。
10. **学号验证**：`validateStudentID(id)` 验证用户输入的学号是否符合格式。

## 交互方式
- **颜色区分**：不同的输入类型（提示词、输入框、已输入内容、箭头指示）使用不同颜色显示，增强用户体验。
- **方向键交互**：
    - 上下键用于在选项列表中移动。
    - 在选择事件的时候,上下键用于改变数字从0-9.
    - 左右键用于调整勇气值或修改时间范围中的选定数字。
- **回车确认**：在选定内容后按回车键确认输入。

## 主要文件
- `main.cpp`：程序入口，调用 `tui_lib` 进行用户交互。
- `tui_lib.hpp`：头文件，定义了所有交互函数。
- `tui_lib.cpp`：实现 `tui_lib` 交互逻辑。

## 运行方式
确保你的环境支持 Windows 控制台，并编译项目：
```sh
"C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe" --build D:\Tasks\C\TUI\cmake-build-debug --target TUI -j 18
```

## 未来改进
- 支持 Linux/macOS 兼容性。
- 增强表单验证逻辑。
- 增加更多可交互输入组件。

