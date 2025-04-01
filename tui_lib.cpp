// tui_lib.cpp
// ��ʵ��

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
    std::cout << COLOR_PROMPT << "�����������..." << COLOR_RESET << std::endl;
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
        std::cout << COLOR_FILLED << "������ " << min << " �� " << max << " ֮���������" << COLOR_RESET << std::endl;
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
        std::cout << COLOR_PROMPT << "ʹ�����·����ѡ�񣬻س�ȷ�ϡ�" << COLOR_RESET << std::endl;
        int ch = _getch();
        if(ch == 0 || ch == 224) {
            int key = _getch();
            if(key == 72 && selection > 0) { // �ϼ�ͷ
                selection--;
            } else if(key == 80 && selection < (int)options.size()-1) { // �¼�ͷ
                selection++;
            }
        } else if(ch == 13) { // �س���
            break;
        }
    }
    return selection;
}

std::vector<std::string> inputSkills(const std::string &prompt) {
    std::vector<std::string> skills;
    std::cout << COLOR_PROMPT << prompt << COLOR_RESET << std::endl;
    std::cout << COLOR_PROMPT << "��������ļ��ܣ�ÿ��һ����������н���:" << COLOR_RESET << std::endl;
    while (true) {
        std::string skill;
        std::getline(std::cin, skill);
        if (skill.empty())
            break;
        skills.push_back(skill);
    }
    return skills;
}

// ������������ʱ���ַ���ת��Ϊ����������ʽ HH:MM
int timeStrToMinutes(const std::string &timeStr) {
    int hh, mm;
    char colon;
    std::istringstream iss(timeStr);
    iss >> hh >> colon >> mm;
    return hh * 60 + mm;
}

bool validateTimeRange(const std::string &timeRange) {
    // ��ʽ��HH:MM-HH:MM
    std::regex timeRegex("^([01]?\\d|2[0-3]):([0-5]\\d)-(([01]?\\d|2[0-3]):([0-5]\\d))$");
    std::smatch match;
    if (!std::regex_match(timeRange, match, timeRegex)) {
        return false;
    }
    // �ָ�ɿ�ʼʱ��ͽ���ʱ��
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
    } else { // ����
        diff = (24 * 60 - startMinutes) + endMinutes;
    }
    // ���ó���6Сʱ = 360���ӣ��Ҳ���Ϊ0����
    return diff > 0 && diff <= 360;
}

std::string inputTimeRange(const std::string &prompt) {
    return inputValidatedField(prompt,
        validateTimeRange,
        "ʱ���ʽ�����ʱ������6Сʱ���밴�� HH:MM-HH:MM ��ʽ���룬��ȷ��ʱ��β�����6Сʱ��");
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
            std::cout << COLOR_FILLED << "������ Y �� N." << COLOR_RESET << std::endl;
    }
}

bool validateStudentID(const std::string &id) {
    // ѧ���ܳ���ӦΪ10λ, ǰ��λ����Ϊ 11, 13, 31, 33, 53, 61������8λ����
    std::regex idRegex("^(11|13|31|33|53|61)(\\d{4})(\\d{4})$");
    return std::regex_match(id, idRegex);
}

// ����ʽ����ֵ���룬����ѡ������
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
            if(key == 75 && value > min) { // ���ͷ
                value--;
            } else if(key == 77 && value < max) { // �Ҽ�ͷ
                value++;
            }
        } else if(ch == 13) { // Enter
            break;
        }
    }
    return value;
}

// ����ʽ�ɲ����ж���ʱ�����룬��ʽ HH:MM-HH:MM������ѡ��༭λ�����¼Ӽ�����
std::string interactiveTimeRangeField(const std::string &prompt) {
    // ��ʼʱ��Ĭ��ֵ
    std::string timeStr = "16:00-22:00";
    // �ɱ༭��λ�ã�0,1,3,4,6,7,9,10
    std::vector<int> editablePositions = {0, 1, 3, 4, 6, 7, 9, 10};
    int selIndex = 0;
    while(true) {
        clearScreen();
        std::cout << COLOR_PROMPT << prompt << " (����ѡ��λ�����¼Ӽ����֣�Enterȷ��)" << COLOR_RESET << std::endl;
        // ��ʾװ����
        std::cout << "�� " << COLOR_PROMPT << "[ 6. �ɲ����ж���ʱ�� �ɲ����ж���ʱ�� �ɲ����ж���ʱ�� �ɲ����ж���ʱ�� �ɲ����ж���ʱ�� ] (���ó��� 6 Сʱ)" << COLOR_RESET << " ��" << std::endl;
        std::cout << "�� " << COLOR_PROMPT << "+ " << COLOR_RESET << "��" << std::endl;
        std::cout << "�� ";
        for (int i = 0; i < (int)timeStr.size(); i++) {
            if (i == editablePositions[selIndex]) {
                std::cout << COLOR_ARROW << "[" << timeStr[i] << "]" << COLOR_RESET;
            } else {
                std::cout << COLOR_INPUT << timeStr[i] << COLOR_RESET;
            }
            if(i < (int)timeStr.size()-1)
                std::cout << " ";
        }
        std::cout << " ��" << std::endl;
        std::cout << "�� " << COLOR_PROMPT << "- " << COLOR_RESET << "��" << std::endl;

        int ch = _getch();
        if(ch == 0 || ch == 224) {
            int key = _getch();
            if(key == 75) { // ���ͷ��ѡ��ǰһ���༭λ
                if(selIndex > 0) selIndex--;
            } else if(key == 77) { // �Ҽ�ͷ��ѡ���һ���༭λ
                if(selIndex < (int)editablePositions.size()-1) selIndex++;
            } else if(key == 72) { // �ϼ�ͷ�����ӵ�ǰ����
                char c = timeStr[editablePositions[selIndex]];
                if(c >= '0' && c <= '9') {
                    int digit = c - '0';
                    digit = (digit + 1) % 10;
                    timeStr[editablePositions[selIndex]] = '0' + digit;
                }
            } else if(key == 80) { // �¼�ͷ�����ٵ�ǰ����
                char c = timeStr[editablePositions[selIndex]];
                if(c >= '0' && c <= '9') {
                    int digit = c - '0';
                    digit = (digit + 9) % 10;
                    timeStr[editablePositions[selIndex]] = '0' + digit;
                }
            }
        } else if(ch == 13) { // Enter ��
            if(validateTimeRange(timeStr)) {
                break;
            } else {
                std::cout << COLOR_FILLED << "ʱ���ʽ�����ʱ������6Сʱ���������" << COLOR_RESET << std::endl;
                waitForKey();
            }
        }
    }
    return timeStr;
}

} // namespace TUI
