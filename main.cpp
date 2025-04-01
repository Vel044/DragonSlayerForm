//main.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "tui_lib.hpp"

using namespace std;
using namespace TUI;

struct DragonSlayerInfo {
    std::string name;
    std::string studentID;
    std::string department;
    std::vector<std::string> skills;
    int courage;
    std::string availableTime;
    bool training;
    std::string notes;
};

void saveToYAML(const DragonSlayerInfo &info, const std::string &filename) {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "�޷����ļ� " << filename << " д�����ݣ�" << std::endl;
        return;
    }
    ofs << "name: \"" << info.name << "\"" << std::endl;
    ofs << "student-id: " << info.studentID << std::endl;
    ofs << "department: \"" << info.department << "\"" << std::endl;
    ofs << "skills:" << std::endl;
    for (const auto &skill : info.skills) {
        ofs << "- \"" << skill << "\"" << std::endl;
    }
    ofs << "courage: " << info.courage << std::endl;
    ofs << "available-time: \"" << info.availableTime << "\"" << std::endl;
    ofs << "training: " << (info.training ? "true" : "false") << std::endl;
    ofs << "notes: \"" << info.notes << "\"" << std::endl;
    ofs.close();
}

int main() {
    DragonSlayerInfo info;

    clearScreen();
    std::cout << "����������������������������������������������[ ������ʿ��Ϣ��д ]����������������������������������������������" << std::endl;

    // 1. ����
    info.name = inputField("[ 1. ���� ]: ");

    // 2. ѧ�� (����֤��ʽ)
    info.studentID = inputValidatedField("[ 2. ѧ�� ]: ", validateStudentID, "ѧ�Ÿ�ʽ���������ԣ���ʽʾ����1120251997");

    // 3. Ժϵ
    std::vector<std::string> departments = {
        "������Ժ", "�����Ժ", "������Ժ", "������Ժ", "������Ժ", "������Ժ", "������Ժ"
    };
    int deptIndex = selectFromList("[ 3. Ժϵ ] ��ѡ��Ժϵ��", departments);
    info.department = departments[deptIndex];

    // 4. �س����ܣ��ɶ�ѡ��������У����н�����
    info.skills = inputSkills("[ 4. �س����� ] ����������س����ܣ�ÿ��һ����н�������");

    // 5. ����ֵ��1-10�֣�
    info.courage = inputIntegerField("[ 5. ����ֵ���� (1-10��) ]: ", 1, 10);

    // 6. �ɲ����ж���ʱ�� (��ʽ HH:MM-HH:MM, ���ó���6Сʱ)
    info.availableTime = inputTimeRange("[ 6. �ɲ����ж���ʱ�� ] (��ʽ HH:MM-HH:MM, ���ó���6Сʱ): ");

    // 7. �Ƿ�Ը����ܸ�ǿ��ѵ�� (Y/N)
    info.training = inputYesNoField("[ 7. �Ƿ�Ը����ܸ�ǿ��ѵ�� ]");

    // 8. ��ע (��ѡ)
    info.notes = inputField("[ 8. ��ע (��ѡ) ]: ");

    // ���ȷ�ϲ�����
    clearScreen();
    std::cout << "���ڱ������ݵ� output.yaml ..." << std::endl;
    saveToYAML(info, "output.yaml");
    std::cout << "����ɹ���" << std::endl;
    waitForKey();

    return 0;
}
