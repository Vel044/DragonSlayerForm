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
        std::cerr << "无法打开文件 " << filename << " 写入数据！" << std::endl;
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
    std::cout << "┌──────────────────────[ 屠龙勇士信息填写 ]──────────────────────┐" << std::endl;

    // 1. 姓名
    info.name = inputField("[ 1. 姓名 ]: ");

    // 2. 学号 (需验证格式)
    info.studentID = inputValidatedField("[ 2. 学号 ]: ", validateStudentID, "学号格式错误，请重试！格式示例：1120251997");

    // 3. 院系
    std::vector<std::string> departments = {
        "特立书院", "睿信书院", "明德书院", "北京书院", "求是书院", "精工书院", "令闻书院"
    };
    int deptIndex = selectFromList("[ 3. 院系 ] 请选择院系：", departments);
    info.department = departments[deptIndex];

    // 4. 特长技能（可多选，输入多行，空行结束）
    info.skills = inputSkills("[ 4. 特长技能 ] 请输入你的特长技能（每行一项，空行结束）：");

    // 5. 勇气值（1-10分）
    info.courage = inputIntegerField("[ 5. 勇气值评估 (1-10分) ]: ", 1, 10);

    // 6. 可参与行动的时间 (格式 HH:MM-HH:MM, 不得超过6小时)
    info.availableTime = inputTimeRange("[ 6. 可参与行动的时间 ] (格式 HH:MM-HH:MM, 不得超过6小时): ");

    // 7. 是否愿意接受高强度训练 (Y/N)
    info.training = inputYesNoField("[ 7. 是否愿意接受高强度训练 ]");

    // 8. 备注 (可选)
    info.notes = inputField("[ 8. 备注 (可选) ]: ");

    // 最后确认并保存
    clearScreen();
    std::cout << "正在保存数据到 output.yaml ..." << std::endl;
    saveToYAML(info, "output.yaml");
    std::cout << "保存成功！" << std::endl;
    waitForKey();

    return 0;
}
