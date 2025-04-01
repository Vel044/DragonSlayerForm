//tui_lib.cpp


#include "tui_lib.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <regex>
#include <ctime>
#include <cstdlib>

namespace TUI {

    void clearScreen() {
        // Windows下清屏
        system("cls");
    }

    void waitForKey() {
        std::cout << "按任意键继续..." << std::endl;
        _getch();
    }

    std::string inputField(const std::string &prompt) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    }

    std::string inputValidatedField(const std::string &prompt, std::function<bool(const std::string&)> validator, const std::string &errorMsg) {
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (validator(input)) {
                break;
            } else {
                std::cout << errorMsg << std::endl;
            }
        }
        return input;
    }

    int inputIntegerField(const std::string &prompt, int min, int max) {
        int value;
        std::string line;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            if (iss >> value && value >= min && value <= max) {
                break;
            }
            std::cout << "请输入 " << min << " 到 " << max << " 之间的整数。" << std::endl;
        }
        return value;
    }

    int selectFromList(const std::string &prompt, const std::vector<std::string> &options) {
        int selection = 0;
        while (true) {
            clearScreen();
            std::cout << prompt << std::endl;
            for (size_t i = 0; i < options.size(); ++i) {
                if (i == (size_t)selection)
                    std::cout << " -> [" << i+1 << "] " << options[i] << std::endl;
                else
                    std::cout << "    [" << i+1 << "] " << options[i] << std::endl;
            }
            std::cout << "使用上下方向键选择，回车确认。" << std::endl;
            int ch = _getch();
            // Windows下：上下箭头前会返回224，再读取一个键码
            if (ch == 224) {
                int key = _getch();
                if (key == 72) { // 上箭头
                    if (selection > 0)
                        selection--;
                } else if (key == 80) { // 下箭头
                    if (selection < (int)options.size()-1)
                        selection++;
                }
            } else if (ch == 13) { // 回车键
                break;
            }
        }
        return selection;
    }

    std::vector<std::string> inputSkills(const std::string &prompt) {
        std::vector<std::string> skills;
        std::cout << prompt << std::endl;
        std::cout << "请输入你的技能，每行一个，输入空行结束:" << std::endl;
        while (true) {
            std::string skill;
            std::getline(std::cin, skill);
            if (skill.empty())
                break;
            skills.push_back(skill);
        }
        return skills;
    }

    // 将时间字符串转换为分钟数，格式 HH:MM
    int timeStrToMinutes(const std::string &timeStr) {
        int hh, mm;
        char colon;
        std::istringstream iss(timeStr);
        iss >> hh >> colon >> mm;
        return hh * 60 + mm;
    }

    // 检查时间格式 HH:MM-HH:MM 并验证时间跨度不超过6小时
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
            std::cout << prompt << " (Y/N): ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "Y" || input == "y")
                return true;
            else if (input == "N" || input == "n")
                return false;
            else
                std::cout << "请输入 Y 或 N." << std::endl;
        }
    }

    bool validateStudentID(const std::string &id) {
        // 学号总长度应为10位, 前两位必须为 11, 13, 31, 33, 53, 61, 中间四位为年份(1000-9999), 后四位为序号
        std::regex idRegex("^(11|13|31|33|53|61)(\\d{4})(\\d{4})$");
        return std::regex_match(id, idRegex);
    }

} // namespace TUI
