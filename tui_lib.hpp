// tui_lib.hpp
// 头文件

#ifndef TUI_LIB_HPP
#define TUI_LIB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <regex>

// 四种颜色宏
#define COLOR_RESET "\033[0m"
#define COLOR_ARROW "\033[91m"    // 红色：箭头
#define COLOR_PROMPT "\033[94m"   // 蓝色：提示词
#define COLOR_INPUT "\033[96m"    // 青色：输入时显示
#define COLOR_FILLED "\033[93m"   // 黄色：已填写的内容

namespace TUI {

    // 清屏
    void clearScreen();

    // 等待任意键
    void waitForKey();

    // 获取一个字符串输入
    std::string inputField(const std::string &prompt);

    // 获取一个字符串输入，并利用验证器判断输入是否合法，不合法时显示错误提示继续输入
    std::string inputValidatedField(const std::string &prompt, std::function<bool(const std::string&)> validator, const std::string &errorMsg);

    // 获取一个整数输入，在[min, max]范围内
    int inputIntegerField(const std::string &prompt, int min, int max);

    // 从给定选项中选择（返回选项索引）
    int selectFromList(const std::string &prompt, const std::vector<std::string> &options);

    // 输入多个技能（允许添加技能），以空行结束输入
    std::vector<std::string> inputSkills(const std::string &prompt);

    // 输入时间段（格式 HH:MM-HH:MM），并验证合法性与时间跨度不超过6小时
    std::string inputTimeRange(const std::string &prompt);

    // 输入是否愿意接受高强度训练（Y/N）
    bool inputYesNoField(const std::string &prompt);

    // 验证学号格式
    bool validateStudentID(const std::string &id);

    // 验证时间范围是否合法且不超过6小时（允许跨日）
    bool validateTimeRange(const std::string &timeRange);

    // 交互式勇气值输入，左右选择数字
    int interactiveCourageField(const std::string &prompt, int min, int max);

    // 交互式可参与行动的时间输入，格式 HH:MM-HH:MM，左右选择编辑位，上下加减数字
    std::string interactiveTimeRangeField(const std::string &prompt);

}

#endif // TUI_LIB_HPP
