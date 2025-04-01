//tui_lib.hpp

#ifndef TUI_LIB_HPP
#define TUI_LIB_HPP

#include <string>
#include <vector>
#include <functional>

namespace TUI {

    // ����
    void clearScreen();

    // �ȴ������
    void waitForKey();

    // ��ȡһ���ַ�������
    std::string inputField(const std::string &prompt);

    // ��ȡһ���ַ������룬��������֤���ж������Ƿ�Ϸ������Ϸ�ʱ��ʾ������ʾ��������
    std::string inputValidatedField(const std::string &prompt, std::function<bool(const std::string&)> validator, const std::string &errorMsg);

    // ��ȡһ���������룬��[min, max]��Χ��
    int inputIntegerField(const std::string &prompt, int min, int max);

    // �Ӹ���ѡ����ѡ�񣨷���ѡ��������
    int selectFromList(const std::string &prompt, const std::vector<std::string> &options);

    // ���������ܣ�������Ӽ��ܣ����Կ��н�������
    std::vector<std::string> inputSkills(const std::string &prompt);

    // ����ʱ��Σ���ʽ HH:MM-HH:MM��������֤�Ϸ�����ʱ���Ȳ�����6Сʱ
    std::string inputTimeRange(const std::string &prompt);

    // �����Ƿ�Ը����ܸ�ǿ��ѵ����Y/N��
    bool inputYesNoField(const std::string &prompt);

    // ��֤ѧ�Ÿ�ʽ
    bool validateStudentID(const std::string &id);

    // ��֤ʱ�䷶Χ�Ƿ�Ϸ��Ҳ�����6Сʱ��������գ�
    bool validateTimeRange(const std::string &timeRange);
}

#endif // TUI_LIB_HPP
