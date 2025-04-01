// main.cpp
// 主程序

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

// 简单将逗号分隔的字符串拆分为技能列表
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

// 将信息保存为 YAML 格式
void saveToYAML(const DragonSlayerInfo &info, const string &filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "无法打开文件 " << filename << " 写入数据！" << endl;
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

// 根据当前选中项调用对应编辑函数
void editField(int index, DragonSlayerInfo &info, const vector<string> &departments) {
    switch(index) {
        case 0: // 姓名
            info.name = inputField("请输入 姓名: ");
            break;
        case 1: // 学号
            info.studentID = inputValidatedField("请输入 学号: ", validateStudentID, "学号格式错误，请重试！格式示例：1120251997");
            break;
        case 2: { // 院系（列表选择）
            int deptIndex = selectFromList("请选择 院系:", departments);
            info.department = departments[deptIndex];
            break;
        }
        case 3: { // 特长技能（逗号分隔）
            string skillInput = inputField("请输入 特长技能（用逗号分隔多个技能）: ");
            info.skills = splitSkills(skillInput);
            break;
        }
        case 4: // 交互式勇气值选择
            info.courage = interactiveCourageField("请输入 勇气值 (使用左右箭头选择):", 1, 10);
            break;
        case 5: // 交互式可参与行动的时间编辑
            info.availableTime = interactiveTimeRangeField("请输入 可参与行动的时间");
            break;
        case 6: // 是否接受高强度训练
            info.training = inputYesNoField("是否愿意接受高强度训练");
            info.trainingFilled = true;
            break;
        case 7: // 备注
            info.notes = inputField("请输入 备注 (可选): ");
            break;
    }
}

int main() {
    DragonSlayerInfo info;
    vector<string> departments = {
        "特立书院", "睿信书院", "明德书院", "北京书院", "求是书院", "精工书院", "令闻书院"
    };

    const int totalFields = 8;  // 8个字段
    int currentSelection = 0;
    bool formSubmitted = false;

    while(!formSubmitted) {
        clearScreen();
        cout << COLOR_PROMPT << "┌───────────── 屠龙勇士信息填写表单 ─────────────┐" << COLOR_RESET << endl;

        cout << (currentSelection == 0 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "1. 姓名: "
             << (info.name.empty() ? COLOR_FILLED "未填写" COLOR_RESET : string(COLOR_INPUT) + info.name + COLOR_RESET) << endl;

        cout << (currentSelection == 1 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "2. 学号: "
             << (info.studentID.empty() ? COLOR_FILLED "未填写" COLOR_RESET : string(COLOR_INPUT) + info.studentID + COLOR_RESET) << endl;

        cout << (currentSelection == 2 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "3. 院系: "
             << (info.department.empty() ? COLOR_FILLED "未选择" COLOR_RESET : string(COLOR_INPUT) + info.department + COLOR_RESET) << endl;

        cout << (currentSelection == 3 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "4. 特长技能: ";
        if(info.skills.empty()) {
            cout << COLOR_FILLED "未填写" COLOR_RESET << endl;
        } else {
            for (size_t i = 0; i < info.skills.size(); ++i) {
                cout << COLOR_INPUT << info.skills[i] << COLOR_RESET;
                if(i < info.skills.size()-1)
                    cout << ", ";
            }
            cout << endl;
        }

        cout << (currentSelection == 4 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "5. 勇气值 (1-10): "
             << (info.courage == 0 ? COLOR_FILLED "未填写" COLOR_RESET : string(COLOR_INPUT) + to_string(info.courage) + COLOR_RESET) << endl;

        cout << (currentSelection == 5 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "6. 可参与行动的时间: "
             << (info.availableTime.empty() ? COLOR_FILLED "未填写" COLOR_RESET : string(COLOR_INPUT) + info.availableTime + COLOR_RESET) << endl;

        cout << (currentSelection == 6 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "7. 是否接受高强度训练: ";
        if(!info.trainingFilled)
            cout << COLOR_FILLED "未填写" COLOR_RESET << endl;
        else
            cout << COLOR_INPUT << (info.training ? "是" : "否") << COLOR_RESET << endl;

        cout << (currentSelection == 7 ? COLOR_ARROW "-> " COLOR_RESET : "   ")
             << "8. 备注: "
             << (info.notes.empty() ? COLOR_FILLED "未填写" COLOR_RESET : string(COLOR_INPUT) + info.notes + COLOR_RESET) << endl;

        cout << (currentSelection == totalFields ? COLOR_ARROW "-> " COLOR_RESET : "   ") << "提交表单" << endl;

        int ch = _getch();
        if(ch == 0 || ch == 224) {
            int key = _getch();
            if(key == 72 && currentSelection > 0) { // 上箭头
                currentSelection--;
            } else if(key == 80 && currentSelection < totalFields) { // 下箭头
                currentSelection++;
            }
        } else if(ch == 13) { // 回车键
            if(currentSelection == totalFields) { // 提交
                if(info.name.empty() || info.studentID.empty() || info.department.empty() ||
                   info.courage == 0 || info.availableTime.empty() || !info.trainingFilled) {
                    cout << "\n" << COLOR_FILLED << "请确保所有必填项均已填写！" << COLOR_RESET << endl;
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
    cout << COLOR_PROMPT << "正在保存数据到 output.yaml ..." << COLOR_RESET << endl;
    saveToYAML(info, "output.yaml");
    cout << COLOR_PROMPT << "保存成功！" << COLOR_RESET << endl;
    waitForKey();

    return 0;
}
