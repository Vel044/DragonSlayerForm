// main.cpp
// ������

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <conio.h>
#include "tui_lib.hpp"

using namespace std;
using namespace TUI;

struct DragonSlayerInfo {
    string name;
    string studentID;
    string department;
    vector<string> skills;
    int courage = 0;
    string availableTime;
    bool training = false;
    bool trainingFilled = false;
    string notes;
};

// �򵥽����ŷָ����ַ������Ϊ�����б�
vector<string> splitSkills(const string &input) {
    vector<string> skills;
    istringstream iss(input);
    string skill;
    while(getline(iss, skill, ',')) {
        size_t start = skill.find_first_not_of(" ");
        size_t end = skill.find_last_not_of(" ");
        if(start != string::npos && end != string::npos)
            skills.push_back(skill.substr(start, end - start + 1));
    }
    return skills;
}

// ����Ϣ����Ϊ YAML ��ʽ
void saveToYAML(const DragonSlayerInfo &info, const string &filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "�޷����ļ� " << filename << " д�����ݣ�" << endl;
        return;
    }
    ofs << "name: \"" << info.name << "\"" << endl;
    ofs << "student-id: " << info.studentID << endl;
    ofs << "department: \"" << info.department << "\"" << endl;
    ofs << "skills:" << endl;
    for (const auto &skill : info.skills) {
        ofs << "- \"" << skill << "\"" << endl;
    }
    ofs << "courage: " << info.courage << endl;
    ofs << "available-time: \"" << info.availableTime << "\"" << endl;
    ofs << "training: " << (info.training ? "true" : "false") << endl;
    ofs << "notes: \"" << info.notes << "\"" << endl;
    ofs.close();
}

// ���ݵ�ǰѡ������ö�Ӧ�༭����
void editField(int index, DragonSlayerInfo &info, const vector<string> &departments) {
    switch(index) {
        case 0: // ����
            info.name = inputField("������ ����: ");
            break;
        case 1: // ѧ��
            info.studentID = inputValidatedField("������ ѧ��: ", validateStudentID, "ѧ�Ÿ�ʽ���������ԣ���ʽʾ����1120251997");
            break;
        case 2: { // Ժϵ���б�ѡ��
            int deptIndex = selectFromList("��ѡ�� Ժϵ:", departments);
            info.department = departments[deptIndex];
            break;
        }
        case 3: { // �س����ܣ����ŷָ���
            string skillInput = inputField("������ �س����ܣ��ö��ŷָ�������ܣ�: ");
            info.skills = splitSkills(skillInput);
            break;
        }
        case 4: // ����ʽ����ֵѡ��
            info.courage = interactiveCourageField("������ ����ֵ (ʹ�����Ҽ�ͷѡ��):", 1, 10);
            break;
        case 5: // ����ʽ�ɲ����ж���ʱ��༭
            info.availableTime = interactiveTimeRangeField("������ �ɲ����ж���ʱ��");
            break;
        case 6: // �Ƿ���ܸ�ǿ��ѵ��
            info.training = inputYesNoField("�Ƿ�Ը����ܸ�ǿ��ѵ��");
            info.trainingFilled = true;
            break;
        case 7: // ��ע
            info.notes = inputField("������ ��ע (��ѡ): ");
            break;
    }
}

int main() {
    DragonSlayerInfo info;
    vector<string> departments = {
        "������Ժ", "�����Ժ", "������Ժ", "������Ժ", "������Ժ", "������Ժ", "������Ժ"
    };

    const int totalFields = 8;  // 8���ֶ�
    int currentSelection = 0;
    bool formSubmitted = false;

    while(!formSubmitted) {
        clearScreen();
        cout << COLOR_PROMPT << "���������������������������� ������ʿ��Ϣ��д�� ����������������������������" << COLOR_RESET << endl;

        cout << (currentSelection == 0 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "1. ����: "
             << (info.name.empty() ? COLOR_FILLED "δ��д" COLOR_RESET : string(COLOR_INPUT) + info.name + COLOR_RESET) << endl;

        cout << (currentSelection == 1 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "2. ѧ��: "
             << (info.studentID.empty() ? COLOR_FILLED "δ��д" COLOR_RESET : string(COLOR_INPUT) + info.studentID + COLOR_RESET) << endl;

        cout << (currentSelection == 2 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "3. Ժϵ: "
             << (info.department.empty() ? COLOR_FILLED "δѡ��" COLOR_RESET : string(COLOR_INPUT) + info.department + COLOR_RESET) << endl;

        cout << (currentSelection == 3 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "4. �س�����: ";
        if(info.skills.empty()) {
            cout << COLOR_FILLED "δ��д" COLOR_RESET << endl;
        } else {
            for (size_t i = 0; i < info.skills.size(); ++i) {
                cout << COLOR_INPUT << info.skills[i] << COLOR_RESET;
                if(i < info.skills.size()-1)
                    cout << ", ";
            }
            cout << endl;
        }

        cout << (currentSelection == 4 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "5. ����ֵ (1-10): "
             << (info.courage == 0 ? COLOR_FILLED "δ��д" COLOR_RESET : string(COLOR_INPUT) + to_string(info.courage) + COLOR_RESET) << endl;

        cout << (currentSelection == 5 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "6. �ɲ����ж���ʱ��: "
             << (info.availableTime.empty() ? COLOR_FILLED "δ��д" COLOR_RESET : string(COLOR_INPUT) + info.availableTime + COLOR_RESET) << endl;

        cout << (currentSelection == 6 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "7. �Ƿ���ܸ�ǿ��ѵ��: ";
        if(!info.trainingFilled)
            cout << COLOR_FILLED "δ��д" COLOR_RESET << endl;
        else
            cout << COLOR_INPUT << (info.training ? "��" : "��") << COLOR_RESET << endl;

        cout << (currentSelection == 7 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "8. ��ע: "
             << (info.notes.empty() ? COLOR_FILLED "δ��д" COLOR_RESET : string(COLOR_INPUT) + info.notes + COLOR_RESET) << endl;

        cout << (currentSelection == totalFields ? COLOR_ARROW "-> " COLOR_RESET : "   ") << "�ύ��" << endl;

        int ch = _getch();
        if(ch == 0 || ch == 224) {
            int key = _getch();
            if(key == 72 && currentSelection > 0) { // �ϼ�ͷ
                currentSelection--;
            } else if(key == 80 && currentSelection < totalFields) { // �¼�ͷ
                currentSelection++;
            }
        } else if(ch == 13) { // �س���
            if(currentSelection == totalFields) { // �ύ
                if(info.name.empty() || info.studentID.empty() || info.department.empty() ||
                   info.courage == 0 || info.availableTime.empty() || !info.trainingFilled) {
                    cout << "\n" << COLOR_FILLED << "��ȷ�����б����������д��" << COLOR_RESET << endl;
                    waitForKey();
                } else {
                    formSubmitted = true;
                }
            } else {
                editField(currentSelection, info, departments);
            }
        }
    }

    clearScreen();
    cout << COLOR_PROMPT << "���ڱ������ݵ� output.yaml ..." << COLOR_RESET << endl;
    saveToYAML(info, "output.yaml");
    cout << COLOR_PROMPT << "����ɹ���" << COLOR_RESET << endl;
    waitForKey();

    return 0;
}
