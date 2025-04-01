// tui_lib.cpp
// 库实现

#include "tui_lib.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <functional>
#include <conio.h>
#include <cstdlib>
#include <fstream>

namespace TUI {

void clearScreen() {
    system("cls");
}

void waitForKey() {
    std::cout << COLOR_PROMPT << "按任意键继续..." << COLOR_RESET << std::endl;
    _getch();
}

std::string inputField(const std::string &prompt) {
    std::string input;
    std::cout << COLOR_PROMPT << prompt << COLOR_RESET;
    std::getline(std::cin, input);
    return input;
}

std::string inputValidatedField(const std::string &prompt, std::function<bool(const std::string&)> validator, const std::string &errorMsg) {
    std::string input;
    while (true) {
        std::cout << COLOR_PROMPT << prompt << COLOR_RESET;
        std::getline(std::cin, input);
        if (validator(input)) {
            break;
        } else {
            std::cout << COLOR_FILLED << errorMsg << COLOR_RESET << std::endl;
        }
    }
    return input;
}

int inputIntegerField(const std::string &prompt, int min, int max) {
    int value;
    std::string line;
    while (true) {
        std::cout << COLOR_PROMPT << prompt << COLOR_RESET;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        if (iss >> value && value >= min && value <= max) {
            break;
        }
        std::cout << COLOR_FILLED << "请输入 " << min << " 到 " << max << " 之间的整数。" << COLOR_RESET << std::endl;
    }
    return value;
}

int selectFromList(const std::string &prompt, const std::vector<std::string> &options) {
    int selection = 0;
    while (true) {
        clearScreen();
        std::cout << COLOR_PROMPT << prompt << COLOR_RESET << std::endl;
        for (size_t i = 0; i < options.size(); ++i) {
            if (i == (size_t)selection)
                std::cout << COLOR_ARROW << " -> [" << i+1 << "] " << options[i] << COLOR_RESET << std::endl;
            else
                std::cout << "    [" << i+1 << "] " << COLOR_INPUT << options[i] << COLOR_RESET << std::endl;
        }
        std::cout << COLOR_PROMPT << "使用上下方向键选择，回车确认。" << COLOR_RESET << std::endl;
        int ch = _getch();
        if(ch == 0 || ch == 224) {
            int key = _getch();
            if(key == 72 && selection > 0) { // 上箭头
                selection--;
            } else if(key == 80 && selection < (int)options.size()-1) { // 下箭头
                selection++;
            }
        } else if(ch == 13) { // 回车键
            break;
        }
    }
    return selection;
}

std::vector<std::string> inputSkills(const std::string &prompt) {
    std::vector<std::string> skills;
    std::cout << COLOR_PROMPT << prompt << COLOR_RESET << std::endl;
    std::cout << COLOR_PROMPT << "请输入你的技能，每行一个，输入空行结束:" << COLOR_RESET << std::endl;
    while (true) {
        std::string skill;
        std::getline(std::cin, skill);
        if (skill.empty())
            break;
        skills.push_back(skill);
    }
    return skills;
}

// 辅助函数：将时间字符串转换为分钟数，格式 HH:MM
int timeStrToMinutes(const std::string &timeStr) {
    int hh, mm;
    char colon;
    std::istringstream iss(timeStr);
    iss >> hh >> colon >> mm;
    return hh * 60 + mm;
}

bool validateTimeRange(const std::string &timeRange) {
    // 格式：HH:MM-HH:MM
    std::regex timeRegex("^([01]?\\d|2[0-3]):([0-5]\\d)-(([01]?\\d|2[0-3]):([0-5]\\d))$");
    std::smatch match;
    if (!std::regex_match(timeRange, match, timeRegex)) {
        return false;
    }
    // 分割成开始时间和结束时间
    size_t pos = timeRange.find('-');
    if (pos == std::string::npos)
        return false;
    std::string startStr = timeRange.substr(0, pos);
    std::string endStr = timeRange.substr(pos + 1);
    int startMinutes = timeStrToMinutes(startStr);
    int endMinutes = timeStrToMinutes(endStr);
    int diff;
    if (endMinutes >= startMinutes) {
        diff = endMinutes - startMinutes;
    } else { // 跨日
        diff = (24 * 60 - startMinutes) + endMinutes;
    }
    // 不得超过6小时 = 360分钟，且不能为0分钟
    return diff > 0 && diff <= 360;
}

std::string inputTimeRange(const std::string &prompt) {
    return inputValidatedField(prompt,
        validateTimeRange,
        "时间格式错误或时长超过6小时！请按照 HH:MM-HH:MM 格式输入，且确保时间段不超过6小时。");
}

bool inputYesNoField(const std::string &prompt) {
    while (true) {
        std::cout << COLOR_PROMPT << prompt << " (Y/N): " << COLOR_RESET;
        std::string input;
        std::getline(std::cin, input);
        if (input == "Y" || input == "y")
            return true;
        else if (input == "N" || input == "n")
            return false;
        else
            std::cout << COLOR_FILLED << "请输入 Y 或 N." << COLOR_RESET << std::endl;
    }
}

bool validateStudentID(const std::string &id) {
    // 学号总长度应为10位, 前两位必须为 11, 13, 31, 33, 53, 61，后面8位数字
    std::regex idRegex("^(11|13|31|33|53|61)(\\d{4})(\\d{4})$");
    return std::regex_match(id, idRegex);
}

// 交互式勇气值输入，左右选择数字
int interactiveCourageField(const std::string &prompt, int min, int max) {
    int value = min;
    while(true) {
        clearScreen();
        std::cout << COLOR_PROMPT << prompt << COLOR_RESET << std::endl;
        for (int i = min; i <= max; i++) {
            if(i == value)
                std::cout << COLOR_ARROW << "[" << i << "] " << COLOR_RESET;
            else
                std::cout << COLOR_INPUT << i << " " << COLOR_RESET;
        }
        std::cout << std::endl;
        int ch = _getch();
        if(ch == 0 || ch == 224) {
            int key = _getch();
            if(key == 75 && value > min) { // 左箭头
                value--;
            } else if(key == 77 && value < max) { // 右箭头
                value++;
            }
        } else if(ch == 13) { // Enter
            break;
        }
    }
    return value;
}

// 交互式可参与行动的时间输入，格式 HH:MM-HH:MM，左右选择编辑位，上下加减数字
std::string interactiveTimeRangeField(const std::string &prompt) {
    // 初始时间默认值
    std::string timeStr = "16:00-22:00";
    // 可编辑的位置：0,1,3,4,6,7,9,10
    std::vector<int> editablePositions = {0, 1, 3, 4, 6, 7, 9, 10};
    int selIndex = 0;
    while(true) {
        clearScreen();
        std::cout << COLOR_PROMPT << prompt << " (左右选择位，上下加减数字，Enter确认)" << COLOR_RESET << std::endl;
        // 显示装饰行
        std::cout << "│ " << COLOR_PROMPT << "[ 6. 可参与行动的时间 可参与行动的时间 可参与行动的时间 可参与行动的时间 可参与行动的时间 ] (不得超过 6 小时)" << COLOR_RESET << " │" << std::endl;
        std::cout << "│ " << COLOR_PROMPT << "+ " << COLOR_RESET << "│" << std::endl;
        std::cout << "│ ";
        for (int i = 0; i < (int)timeStr.size(); i++) {
            if (i == editablePositions[selIndex]) {
                std::cout << COLOR_ARROW << "[" << timeStr[i] << "]" << COLOR_RESET;
            } else {
                std::cout << COLOR_INPUT << timeStr[i] << COLOR_RESET;
            }
            if(i < (int)timeStr.size()-1)
                std::cout << " ";
        }
        std::cout << " │" << std::endl;
        std::cout << "│ " << COLOR_PROMPT << "- " << COLOR_RESET << "│" << std::endl;

        int ch = _getch();
        if(ch == 0 || ch == 224) {
            int key = _getch();
            if(key == 75) { // 左箭头：选择前一个编辑位
                if(selIndex > 0) selIndex--;
            } else if(key == 77) { // 右箭头：选择后一个编辑位
                if(selIndex < (int)editablePositions.size()-1) selIndex++;
            } else if(key == 72) { // 上箭头：增加当前数字
                char c = timeStr[editablePositions[selIndex]];
                if(c >= '0' && c <= '9') {
                    int digit = c - '0';
                    digit = (digit + 1) % 10;
                    timeStr[editablePositions[selIndex]] = '0' + digit;
                }
            } else if(key == 80) { // 下箭头：减少当前数字
                char c = timeStr[editablePositions[selIndex]];
                if(c >= '0' && c <= '9') {
                    int digit = c - '0';
                    digit = (digit + 9) % 10;
                    timeStr[editablePositions[selIndex]] = '0' + digit;
                }
            }
        } else if(ch == 13) { // Enter 键
            if(validateTimeRange(timeStr)) {
                break;
            } else {
                std::cout << COLOR_FILLED << "时间格式错误或时长超过6小时，请调整。" << COLOR_RESET << std::endl;
                waitForKey();
            }
        }
    }
    return timeStr;
}

} // namespace TUI
