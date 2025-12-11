#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define N 50 //最大学生数
#define LEN sizeof(struct student) //结构体字节
#define FORMAT "%-8s %-8s %-6s %-6.1f %-6.1f %-6.1f %-6.1f\n"
#define DATA stu[i].id, stu[i].name, stu[i].sex,stu[i].chinese, stu[i].math, stu[i].english, stu[i].average

//学生信息
struct student {
    char id[114514];     // 学号
    char name[114514];   // 姓名
    char sex[100];       // 性别
    float chinese;       // 语文
    float math;          // 数学
    float english;       // 英语
    float average;       // 平均分
};

struct student stu[N];  // 学生
int n = 0;              // 当前学生数

// 函数声明
void menu();            // 菜单
void input();           // 1.输入
void find();            // 2.查找
void del();             // 3.删除
void modify();          // 4.修改
void insert();          // 5.插入
void sort();            // 6.排序
void count();           // 7.统计个数
void display();         // 8.显示
void save();            // 保存
void load();            // 读取

int main() {
    load();
    char ch;
    while (1) {
        menu();
        ch = getch();  //从控制台无回显地读取一个字符 不需要按回车键 不会显示在屏幕上
        system("cls");
        switch (ch) {
            case '1': input(); break;
            case '2': find(); break;
            case '3': del(); break;
            case '4': modify(); break;
            case '5': insert(); break;
            case '6': sort(); break;
            case '7': count(); break;
            case '8': display(); break;
            case '0': save(); printf("数据已保存，退出系统！\n"); exit(0);//立即终止整个程序的运行
            default: printf("输入无效，请按任意键重新选择！\n"); getch();
        }
    }
    return 0;
}

// 菜单
void menu() {
    printf("┌──────────────────────────────────┐\n");
    printf("│    学生信息管理系统(容量%d)      │\n",N);
    printf("├──────────────────────────────────┤\n");
    printf("│  1.输入           2.查找         │\n");
    printf("│  3.删除           4.修改         │\n");
    printf("│  5.插入           6.排序         │\n");
    printf("│  7.统计个数       8.显示         │\n");
    printf("│  0.退出系统                      │\n");
    printf("└──────────────────────────────────┘\n");
    printf("请输入功能编号(0-8)：");
}

// 1.输入学生记录
void input() {
    printf("┌──────────────────────────────────┐\n");
    printf("│           输入学生记录           │\n");
    printf("└──────────────────────────────────┘\n");
    while (1) {
        if (n >= N) {
            printf("学生数量已达上限！\n");
            break;
        }
		while (1) {
		    printf("学号(8位以内)："); scanf("%s", stu[n].id);
		    int flag = 0; // 标记重复
		    // 检查学号是否重复
		    int i;
		    for (i = 0; i < n; i++) {
		        if (strcmp(stu[i].id, stu[n].id) == 0) {
		            flag = 1;
		            break;
		        }
		    }
		    if (flag) {
		        printf("警告：该学号已存在，请重新输入！\n");
		    } else {
		        break;
		    }
		}
        printf("姓名(英文8字节以内)："); scanf("%s", stu[n].name);
        printf("性别："); scanf("%s", stu[n].sex);
        printf("语文："); scanf("%f", &stu[n].chinese);
        printf("数学："); scanf("%f", &stu[n].math);
        printf("英语："); scanf("%f", &stu[n].english);
        stu[n].average = (stu[n].chinese + stu[n].math + stu[n].english) / 3.0;
        n++;
        printf("是否继续输入？(y/n)：");
        char ch = getch();
        if (ch != 'y' && ch != 'Y') break; //防呆设计 太贴心 
        system("cls");
    }
    save();
    printf("不继续输入，按任意键返回菜单！\n");
    getch();
    system("cls");
}

// 2.查找记录（按学号）
void find() {
    printf("┌──────────────────────────────────┐\n");
    printf("│           查找学生记录           │\n");
    printf("└──────────────────────────────────┘\n");
    char id[12];
    printf("请输入要查找的学号："); scanf("%s", id);
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(stu[i].id, id) == 0) {
            printf("┌─────────────────────────────────────────────────┐\n");
            printf("学号     姓名     性别   语文  数学   英语  平均分\n");
            printf("└─────────────────────────────────────────────────┘\n");
            printf(FORMAT, DATA);
            printf("└─────────────────────────────────────────────────┘\n");
            printf("任意键返回\n");
            getch();
            system("cls");
            return;
        }
    }
    printf("未找到该学号的学生！\n");
    printf("任意键返回\n");
    getch();
    system("cls");
}

// 3.删除记录
void del() {
    printf("┌──────────────────────────────────┐\n");
    printf("│           删除学生记录           │\n");
    printf("└──────────────────────────────────┘\n");
    char id[12];
    printf("请输入要删除的学号："); scanf("%s", id);
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(stu[i].id, id) == 0) {
            // 后续元素前移
            int j;
            for (j = i; j < n - 1; j++) {
                stu[j] = stu[j + 1];
            }
            n--;
            save();
            printf("删除成功！\n");
            printf("任意键返回\n");
            getch();
            system("cls");
            return;
        }
    }
    printf("未找到该学号的学生！\n");
    getch();
    system("cls");
}

// 4.修改记录
void modify() {
    printf("┌──────────────────────────────────┐\n");
    printf("│           修改学生记录           │\n");
    printf("└──────────────────────────────────┘\n");
    char id[12];
    printf("请输入要修改的学号："); scanf("%s", id);
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(stu[i].id, id) == 0) {
            printf("当前信息：\n");
            printf("姓名：%s 性别：%s 语文：%.1f 数学：%.1f 英语：%.1f\n",
                   stu[i].name, stu[i].sex, stu[i].chinese, stu[i].math, stu[i].english);
            printf("新姓名："); scanf("%s", stu[i].name);
            printf("新性别："); scanf("%s", stu[i].sex);
            printf("新语文："); scanf("%f", &stu[i].chinese);
            printf("新数学："); scanf("%f", &stu[i].math);
            printf("新英语："); scanf("%f", &stu[i].english);
            stu[i].average = (stu[i].chinese + stu[i].math + stu[i].english) / 3.0;
            save();
            printf("修改成功！\n");
            printf("任意键返回\n");
            getch();
            system("cls");
            return;
        }
    }
    printf("未找到该学号的学生！\n");
    printf("任意键返回\n");
    getch();
    system("cls");
}

// 5.插入记录
void insert() {
    printf("┌──────────────────────────────────┐\n");
    printf("│           插入学生记录           │\n");
    printf("└──────────────────────────────────┘\n");
    if (n >= N) {
        printf("学生数量已达上限！\n");
        getch();
        return;
    }
    int pos;
    printf("当前学生数：%d，请输入插入位置(1-%d)：", n, n + 1);
    scanf("%d", &pos);
    if (pos < 1 || pos > n + 1) {
        printf("位置无效！\n");
        printf("任意键返回\n");
        getch();
        system("cls");
        return;
    }
    pos--;
    // 元素后移
    int i;
    for (i = n; i > pos; i--) {
        stu[i] = stu[i - 1];
    }
    // 输入新数据
    printf("学号："); scanf("%s", stu[pos].id);
    printf("姓名："); scanf("%s", stu[pos].name);
    printf("性别："); scanf("%s", stu[pos].sex);
    printf("语文："); scanf("%f", &stu[pos].chinese);
    printf("数学："); scanf("%f", &stu[pos].math);
    printf("英语："); scanf("%f", &stu[pos].english);
    stu[pos].average = (stu[pos].chinese + stu[pos].math + stu[pos].english) / 3.0;
    n++;
    save();
    printf("插入成功！\n");
    printf("任意键返回\n");
    getch();
    system("cls");
}

// 6.排序（按平均分降序）
void sort() {
    printf("┌──────────────────────────────────┐\n");
    printf("│    排序学生记录-平均分降序       │\n");
    printf("└──────────────────────────────────┘\n");
    if (n == 0) {
        printf("暂无学生记录！\n");
        getch();
        return;
    }
    struct student temp;
    int i;
    for (i = 0; i < n - 1; i++) {
    	int j;
        for (j = 0; j < n - i - 1; j++) {
            if (stu[j].average < stu[j + 1].average) {
                temp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = temp;
            }
        }
    }
    save();
    printf("排序完成，按任意键查看结果！\n");
    getch();
    display();
}

// 7.统计学生个数
void count() {
    printf("┌──────────────────────────────────┐\n");
    printf("│           统计学生个数           │\n");
    printf("└──────────────────────────────────┘\n");
    printf("当前学生总数：%d\n", n);
    printf("任意键返回\n");
    getch();
    system("cls");
}

// 8.显示所有记录
void display() {
    printf("┌───────────────────────────────────────────────────┐\n");
    printf("│                 学生信息列表                      │\n");
    printf("└───────────────────────────────────────────────────┘\n");
    if (n == 0) {
        printf("暂无学生记录！\n");
        printf("任意键返回\n");
        getch();
        system("cls");
        return;
    }
    printf("学号     姓名    性别    语文    数学  英语  平均分\n");
    printf("────────────────────────────────────────────────────\n");
    int i;
    for (i = 0; i < n; i++) {
        printf(FORMAT, DATA);
    }
    printf("────────────────────────────────────────────────────\n");
    printf("任意键返回\n");
    getch();
    system("cls");
}

// 保存数据到文件
void save() {
    FILE *fp;                  //wb 二进制只写 
    if ((fp = fopen("stuData.txt", "wb")) == NULL) {
        printf("文件打开失败！\n");
        return;
    }
    fwrite(stu, LEN, n, fp);  
    fclose(fp);
}

// 从文件加载数据
void load() {
    FILE *fp;                 //rb 二进制只读 
    if ((fp = fopen("stuData.txt", "rb")) == NULL) {
        printf("暂无历史数据！\n");
        return;
    }
    // 读取文件
    while (fread(&stu[n], LEN, 1, fp) == 1) {
        n++;
    }
    fclose(fp);
}
