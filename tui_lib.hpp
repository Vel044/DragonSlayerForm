//tui_lib.hpp

#ifndef TUI_LIB_HPP
#define TUI_LIB_HPP

#include <string>
#include <vector>
#include <functional>

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
}

#endif // TUI_LIB_HPP
