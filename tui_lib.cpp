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
        // Windows������
        system("cls");
    }

    void waitForKey() {
        std::cout << "�����������..." << std::endl;
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
            std::cout << "������ " << min << " �� " << max << " ֮���������" << std::endl;
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
            std::cout << "ʹ�����·����ѡ�񣬻س�ȷ�ϡ�" << std::endl;
            int ch = _getch();
            // Windows�£����¼�ͷǰ�᷵��224���ٶ�ȡһ������
            if (ch == 224) {
                int key = _getch();
                if (key == 72) { // �ϼ�ͷ
                    if (selection > 0)
                        selection--;
                } else if (key == 80) { // �¼�ͷ
                    if (selection < (int)options.size()-1)
                        selection++;
                }
            } else if (ch == 13) { // �س���
                break;
            }
        }
        return selection;
    }

    std::vector<std::string> inputSkills(const std::string &prompt) {
        std::vector<std::string> skills;
        std::cout << prompt << std::endl;
        std::cout << "��������ļ��ܣ�ÿ��һ����������н���:" << std::endl;
        while (true) {
            std::string skill;
            std::getline(std::cin, skill);
            if (skill.empty())
                break;
            skills.push_back(skill);
        }
        return skills;
    }

    // ��ʱ���ַ���ת��Ϊ����������ʽ HH:MM
    int timeStrToMinutes(const std::string &timeStr) {
        int hh, mm;
        char colon;
        std::istringstream iss(timeStr);
        iss >> hh >> colon >> mm;
        return hh * 60 + mm;
    }

    // ���ʱ���ʽ HH:MM-HH:MM ����֤ʱ���Ȳ�����6Сʱ
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
            std::cout << prompt << " (Y/N): ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "Y" || input == "y")
                return true;
            else if (input == "N" || input == "n")
                return false;
            else
                std::cout << "������ Y �� N." << std::endl;
        }
    }

    bool validateStudentID(const std::string &id) {
        // ѧ���ܳ���ӦΪ10λ, ǰ��λ����Ϊ 11, 13, 31, 33, 53, 61, �м���λΪ���(1000-9999), ����λΪ���
        std::regex idRegex("^(11|13|31|33|53|61)(\\d{4})(\\d{4})$");
        return std::regex_match(id, idRegex);
    }

} // namespace TUI
