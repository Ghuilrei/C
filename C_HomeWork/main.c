//
//  main.c
//  C_HomeWork
//
//  Created by 孙宇航 on 2020/3/11.
//  Copyright © 2020 孙宇航. All rights reserved.
//

//Windows环境下运行失败

//所有system()中的clear仅用于MacOS和Linux系统
//Windows运行需将system()中的参数改为“cls”
//Windows运行需将头文件“#include <unistd.h>”改为“#include <windows.h>”

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int finally=0;          //数据总数
int language=-1;        //语言
int check=0;                //检查scanf函数是否读取成功
int saremind=0;             //保存提醒

//员工信息
typedef struct Salary_Info{
    long int Card_No;
    char name[20];
    int month;
    float Init_Salary;
    float Water_Rate;
    float Electric_Rate;
    float tax;
    float Final_Salary;
}SALARY;

//统计信息
typedef struct Salary_Sum{
    long int Card_No;
    double sum;
    struct Salary_Sum *next;
}SUM;

//a单向链表
typedef struct link {
    SALARY date;
    struct link *next;
}LINK;

struct link *ReadFile(LINK *head,char filename[50]);                                //读取文件
int SaveFile(LINK *head,char filename[50]);                                         //保存文件
void SaveRemind(LINK *head, char filename[50], int saremind);                       //未保存文件提醒
struct link *InformationInput (int a);                                              //信息输入      a：打印输入第a个员工
struct link *InformationDelete (LINK *head,int a[]);                                //删除模块      a：删除第a个结点
struct link *InformationQuery (LINK *head, long int Card_NO, char name[20]);        //信息查找
struct link *InformationInsert(LINK *head,int *pd);                                 //信息插入
void InformationBrowsing (LINK *head,int a);                                        //信息浏览      a：打印方式（1->全部打印；0->自行选择）
struct link *InformationSorting (LINK *head, int chose);                            //信息排序
void InformationStatistics (LINK *head, SUM *head1, int a, int b);                  //信息统计
void ErrorWarning (void);                                                           //错误提醒
void Goodbye (void);                                                                //结束语
void DeleteMemory(struct link *head);                                               //还LINK内存
void DeleteMemory2(SUM *head);                                                      //还SUM内存

int main(int argc, const char * argv[]) {
    
    int pd=0;                   //随意啦。。。。用的时候要归零
    int chose;                  //选择
    int i=0,n=0;                //循环用变量
    struct link *head =NULL;
    struct link *h=NULL;        //新建头节点
    char filename[50];          //文件夹名
    LINK *p=NULL,*pr=NULL;
    long int Card_NO;           //查找的卡号
    char name[20];              //文件名
    int del[21]={0};            //删除的节点序号
    SUM *head1=NULL;            //信息统计头指针
    int a=0,b=0;                //月份上下限
    
    //语言
    system("clear");
    do {
        printf("Please choose the language:\n");
        printf("    1-------------简体中文\n");
        printf("    2-------------English\n");
        printf("Please entry:");
        setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
        scanf("%d",&language);
        system("clear");
    } while (language!=1&&language!=2);
    if (language==1) {
        printf("\n\n\n**********欢迎使用工资管理系统！**********\n\n\n\n");
        
    }
    else if(language==2){
        printf("\n\n\n**********Welcome to Wage Management System!**********\n\n\n\n");
    }
    sleep(2);
ONEBegining:
    system("clear");            //清屏
    chose=0;
    finally=0;
    //菜单
    if (language==1) {
        printf("================工 资 管 理 系 统================\n");
        printf("-----------------------------------------------\n");
        printf("        1-------------------新建文件\n");
        printf("        2-------------------选择文件\n");
        printf("        3-------------------退出系统\n");
        printf("----------------------------------------------\n");
        printf("    请在以上功能中选择(1-3):");
    }
    else if(language==2){
        printf("============Wage Management System============\n");
        printf("----------------------------------------------\n");
        printf("        1------------------New File\n");
        printf("        2------------------Select File\n");
        printf("        3------------------Exit System\n");
        printf("---------------------------------------------\n");
        printf("Please choose from the above functions(1—3):");
    }
    for (i=0; i<=50||filename[i]!='\0'; i++) {
        filename[i]='0';
    }
    setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
    scanf("%d",&chose);
    switch (chose) {
        case 1:
            goto Newlybuild;        //跳转信息添加
            break;
        case 2:
            system("clear");
            printf("---------------------------------------------\n");
            system("ls");
            printf("---------------------------------------------\n");
            head=ReadFile(head, filename);
            if (head==NULL) {                                       //防止导入文件中无员工信息进入文件操作模块，导致程序出错
                goto ONEBegining;
            }
            break;
        case 3:
            Goodbye();
            exit(0);
            break;
            
        default:
            if (language==1) {
                printf("\n错误!\n");
            }
            else if(language==2){
                printf("\nError!\n");
            }
            ErrorWarning();
            goto ONEBegining;
    }
TWOBegining:
    system("clear");
    if (language==1) {
        printf("================工 资 管 理 系 统================\n");
        printf("-----------------------------------------------\n");
        printf("     1------------------信息添加\n");
        printf("     2------------------信息查询\n");
        printf("     3------------------信息插入\n");
        printf("     4------------------信息预览\n");
        printf("     5------------------信息排序\n");
        printf("     6------------------信息删除\n");
        printf("     7------------------信息统计\n");
        printf("     8------------------保 存 \n");
        printf("     0------------------返 回 \n");
        printf("---------------------------------------------\n");
        printf("    请在以上功能中选择(0—6):");
    }
    else if (language==2){
        printf("============Wage Management System============\n");
        printf("----------------------------------------------\n");
        printf("     1------------------Information Addition\n");
        printf("     2------------------Information Search\n");
        printf("     3------------------Information Insertion\n");
        printf("     4------------------Information Preview\n");
        printf("     5------------------Information Sorting\n");
        printf("     6------------------Information Deletion\n");
        printf("     7------------------Information Statistics\n");
        printf("     8------------------Save File\n");
        printf("     0------------------Return\n");
        printf("---------------------------------------------\n");
        printf("Please choose among the above functions.(0—6):");
    }
    setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
    check=scanf("%d",&chose);
    if (check!=1) {
        ErrorWarning();
        goto TWOBegining;
    }
    switch (chose) {
            //返回
        case 0:
            if (saremind==1) {
                SaveRemind(head, filename, saremind);           //保存提醒
                DeleteMemory(head);                             //还内存
            }
            head=NULL;                                          //重置，准备下一次读文件
            goto ONEBegining;
            break;
            
            //信息添加
        case 1:
        Newlybuild:
            system("clear");
            saremind=1;
            h=NULL;
            pr=head;
            do {
                if (language==1) {
                    printf("想添加几条员工信息：");
                }
                else if(language==2){
                    printf("How many employees would you like to add:");
                }
                setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
                check=scanf("%d",&n);
            } while (check==0);
            if (head==NULL&&n==0) {                                             //防止未添加员工信息进入文件操作模块，导致程序出错
                if (language==1) {
                    printf("至少添加一位员工信息！\n");
                }
                else if(language==2){
                    printf("How many employees would you like to add!\n");
                }
                ErrorWarning();
                goto ONEBegining;
            }
            pr=(struct link *)malloc(sizeof(struct link));
            h=pr;
            for (i=1; i<=n; i++) {
                p = InformationInput(finally);
                pr->next=p;
                pr=pr->next;
            }
            if (head==NULL) {
                head=h->next;
            }
            else{
                pr=head;
                while(pr->next!=NULL){
                    pr=pr->next;
                }
                pr->next=h->next;
            }
            free(h);
            break;
            
            //信息查询
        case 2:
        POINT2:
            system("clear");
            if (language==1) {
                printf("==================信 息 查 询==================\n");
                printf("----------------------------------------------\n");
                printf("     0-------------------返回上一级\n");
                printf("     1-------------------按照工资卡号查询\n");
                printf("     2-------------------按照姓名查询\n");
                printf("---------------------------------------------\n");
                printf("    请在以上功能中选择(0—2):");
            }
            else if (language==2){
                printf("==============Information search==============\n");
                printf("----------------------------------------------\n");
                printf("     0-------------Return\n");
                printf("     1-------------Search by SalaryCard ID\n");
                printf("     2-------------Search by name\n");
                printf("---------------------------------------------\n");
                printf("Please choose from the above functions(0—2):");
            }
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            check=scanf("%d",&chose);
            if (check!=1) {
                ErrorWarning();
                goto POINT2;
            }
            switch (chose) {
                    //返回
                case 0:
                    goto TWOBegining;
                    break;
                    
                    //工资卡号查询
                case 1:
                    do {
                        system("clear");
                        if (language==1) {
                            printf("你想查看哪个卡号的信息：");
                        }
                        else if(language==2){
                            printf("Which card number do you want to check:");
                        }
                        check=scanf("%ld",&Card_NO);
                    } while (check==0);
                    InformationQuery (head, Card_NO, "¥¥¥¥¥¥");        //传入的第三个变量为字符串型，利用特殊符号躲避检查，仅查询卡号
                    break;
                    
                    //姓名查询
                case 2:
                    system("clear");
                    if (language==1) {
                        printf("你想查看谁的信息？");
                    }
                    else if(language==2){
                        printf("whose information do you want to check:");
                    }
                    scanf("%s",name);
                    InformationQuery (head, -1, name);            //传入的第二个参数为整形，利用特殊数据躲避检查，仅查询姓名
                    break;
                    
                    //错误
                default:
                    if (language==1) {
                        printf("\n错误!\n");
                    }
                    else if(language==2){
                        printf("\nError!\n");
                    }
                    ErrorWarning();
                    goto POINT2;
                    break;
            }
            break;
            
            
            //信息插入
        case 3:
            system("clear");
            saremind=1;                         //标记修改文件
            do {
                if (language==1) {
                    printf("想插入几位新员工信息：");
                }
                else if (language==2){
                    printf("How many new employees would you like to insert:");
                }
                setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
                check=scanf("%d",&n);
            } while (check!=1);
            for (i=1; i<=n; i++) {
                InformationBrowsing(head,1);        //预先浏览，1->全部打印
                pd=0;
                head = InformationInsert(head,&pd);
                if (pd==1) {
                    i--;
                }
            }
            break;
            
            //信息浏览
        case 4:
            system("clear");
            InformationBrowsing(head,0);        //信息浏览，0->自行选择
            break;
            
            //信息排序
        case 5:
            saremind=1;                         //标记修改文件
        POINT3:
            system("clear");
            if (language==1) {
                printf("==================信 息 排 序==================\n");
                printf("----------------------------------------------\n");
                printf("     0-------------------返回上一级\n\n");
                printf("     1-------------------按照工资卡号升序排列\n");
                printf("     2-------------------按照工资卡号降序排列\n\n");
                printf("     3-------------------按照实发工资升序排列\n");
                printf("     4-------------------按照实发工资降序排列\n\n");
                printf("     5-------------------按照姓名(由A到Z)查询\n");
                printf("     6-------------------按照姓名(由Z到A)查询\n");
                printf("---------------------------------------------\n");
                printf("    请在以上功能中选择(0—6):");
            }
            else if (language==2){
                printf("==============Information Sorting==============\n");
                printf("----------------------------------------------\n");
                printf("     0------Return\n");
                printf("     1------In ascending order according to payroll card number\n");
                printf("     2------In descending order according to payroll card number\n\n");
                printf("     3------In order of wage rise\n");
                printf("     4------In descending order of wages\n\n");
                printf("     5------Rank by name (from A to Z)\n");
                printf("     6------Rank by name (from Z to A)\n");
                printf("---------------------------------------------\n");
                printf("Please choose from the above functions(0—6):");
            }
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            check=scanf("%d",&chose);
            if (check!=1) {
                goto POINT3;
            }
            if (chose==0) {
                goto TWOBegining;
            }
            else if(1<=chose&&chose<=6){
                head = InformationSorting(head, chose);
                InformationBrowsing(head, 1);
            }
            else{
                if (language==1) {
                    printf("\n错误!\n");
                }
                else if(language==2){
                    printf("\nError!\n");
                }
                ErrorWarning();
                goto POINT3;
            }
            break;
            
            //信息删除
        case 6:
            system("clear");
            saremind = 1;
            InformationBrowsing(head, 1);
            if (language==1) {
                printf("(每次上限20条，序号之间用空格隔开，输入“0”+“回车键”结束)\n");
                printf("请输入想删除的员工信息序号：");
            }
            else if(language==2){
                printf(" (up to 20 at a time, separated by spaces,enter \"0\" +\"Enter\"to end)\n");
                printf("Please enter the serial number of the employee information you want to delete:");
            }
            n=0;
            do {
                check=scanf("%d",&del[n]);
                if (check==1) {
                    n++;
                }
            }while (n!=20&&del[n-1]!=0);
            head=InformationDelete(head, del);
            for (i=0;i<=20 ; i++) {
                del[i]=0;
            }
            break;
            
            //信息统计
        case 7:
            system("clear");
            saremind=1;                         //标记修改文件
            if (language==1) {
                do {
                    printf("请输入月份下限：");
                    setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
                    check=scanf("%d",&a);
                } while (check!=1||a<1||a>12);
                do {
                    printf("请输入月份上限：");
                    setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
                    check=scanf("%d",&b);
                } while (check!=1||a<1||a>12);
            }
            else if(language==2){
                do {
                    printf("Please enter the maximum monthly limit:");
                    setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
                    check=scanf("%d",&a);
                } while (check!=1||a<1||a>12);
                do {
                    printf("Please enter the lower limit of the month:");
                    setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
                    check=scanf("%d",&b);
                } while (check!=1||a<1||a>12);
            }
            InformationStatistics(head, head1, a, b);
            break;
            
            //保存
        case 8:
            system("clear");
            saremind=0;                     //保存文件，恢复为未修改
            SaveFile(head, filename);
            break;
            
            //错误
        default:
            if (language==1) {
                printf("\n错误!\n");
            }
            else if(language==2){
                printf("\nError!\n");
            }
            ErrorWarning();
            goto TWOBegining;
    }
    //操作完成，回到菜单
    if (language==1) {
        printf("\n操作完成！\n");
    }
    else if(language==2){
        printf("\nCompleted operation!\n");
    }
    ErrorWarning();
    goto TWOBegining;
    return 0;
}

//导入文件
struct link *ReadFile(LINK *head,char filename[50]){
    char pd;                    //“是否”判断
    int i,m;
    LINK *p=NULL,*pr=head;
    FILE *fp;
    if (language==1) {
        printf("请输入文件名：");
    }
    else if (language==2){
        printf("Please enter the file name:");
    }
    scanf("%s",filename);
    fp=fopen(filename, "r");                //“r”方式打开，若文件不存在，返回值为NULL
    if (fp==NULL) {
        if (language==1) {
            printf("\n错误！文件不存在！\n");        }
        else if(language==2){
            printf("\nError! Documents do not exist!\n");
        }
        ErrorWarning();
        fclose(fp);
        return NULL;                        //如果是NULL返回主函数
    }
    m=fscanf(fp, "A total of %d data\n",&finally);
    if (m==-1) {                                                        //无法读入finally，文件不是本程序生成
        if (language==1) {
            printf("\n无法正确导入此文件！\n");
        }
        else if(language==2){
            printf("\nThis file cannot be imported properly.\n");
        }
        ErrorWarning();
        return NULL;
    }
    if (finally==0) {
        if (language==1) {
            printf("\n文件中至少存在一位员工信息！\n");
        }
        else if(language==2){
            printf("\nAt least one employee in the file!\n");
        }
        ErrorWarning();
        return NULL;
    }
    for (i=0; i<finally; i++) {
        pr=head;
        p=(struct link *)malloc(sizeof(struct link));
        p->date.month=-1;
        p->next=NULL;
        if (p==NULL) {                                              //内存不足
            printf("ERROR!!!No enough memory to allocate!\n");
            return NULL;
        }
        if (head==NULL) {                       //在程序中新建单向链表
            head=p;
        }
        else{
            while (pr->next!=NULL) {
                pr=pr->next;
            }
            pr->next=p;
        }
        fscanf(fp,"| %*d  |  %ld | %s |   %d  |  %f  |  %f   |   %f    | %f  | %f  |\n",&p->date.Card_No,p->date.name,&p->date.month,&p->date.Init_Salary,&p->date.Water_Rate,&p->date.Electric_Rate,&p->date.tax,&p->date.Final_Salary);
        if (p->date.month==-1&&head->next==NULL) {
            if (language==1) {
                printf("\n错误！文件已被人为修改！\n");
                printf("文件中至少存在一位员工信息！\n");
            }
            else if(language==2){
                printf("\nError! The document has been artificially modified!\n");
                printf("At least one employee in the file!\n");
            }
            free(head);
            ErrorWarning();
            return NULL;
        }
        if (p->date.month==-1&&head->next!=NULL) {
            if (language==1) {
                printf("\n错误！文件已被人为修改！\n");
                printf("文件中存在错误！\n");
            }
            else if(language==2){
                printf("\nError! The document has been artificially modified!\n");
                printf("Error in file!\n");
            }
            DeleteMemory(head);
            ErrorWarning();
            return NULL;
        }
        p->next=NULL;
    }
    p=(struct link *)malloc(sizeof(struct link));
    p->date.month=-1;
    p->next=NULL;
    fscanf(fp,"| %*d  |  %ld | %s |   %d  |  %f  |  %f   |   %f    | %f  | %f  |\n",&p->date.Card_No,p->date.name,&p->date.month,&p->date.Init_Salary,&p->date.Water_Rate,&p->date.Electric_Rate,&p->date.tax,&p->date.Final_Salary);
    if (p->date.month==-1) {
        free(p);
    }
    else{
        if (language==1) {
            printf("\n错误！文件已被人为修改！\n");
            printf("检测出文件中仍有未读取数据！\n");
        }
        else if(language==2){
            printf("\nError! The document has been artificially modified!\n");
            printf("Detecting that there are still unread data in the file!\n");
        }
        do {
            if (language==1) {
                printf("是否继续？(Y/N)");
            }
            else if(language==2){
                printf(" Do you want to continue?(Y/N)");
            }
            scanf(" %c",&pd);
            if (pd=='N'||pd=='n') {
                return NULL;
            }
        } while (pd!='N'&&pd!='n'&&pd!='y'&&pd!='Y');
    }
    fclose(fp);
    if (language==1) {
        printf("\n文件导入成功！\n");
    }
    else if(language==2){
        printf("\nFile Reading Successfully\n");
    }
    ErrorWarning();
    return head;
}

//保存文件
int SaveFile(LINK *head,char filename[50]){
    int i;
    LINK *p=head;
    FILE *fp;
    char cho;
    if (language==1) {
        printf("请输入文件名：");
    }
    else if (language==2){
        printf("Please enter the file name:");
    }
    scanf(" %s",filename);
    fp=fopen(filename, "r");            //检测文件是否已经存在
    if (fp!=NULL) {
        fclose(fp);
        do {
            if (language==1) {
                printf("文件已存在，是否覆盖？(Y/N)");
            }
            else if (language==2){
                printf("Does the file already exist and overwrite it?(Y/N)");
            }
            scanf(" %c",&cho);
        } while (cho!='y'&&cho!='Y'&&cho!='N'&&cho!='n');
        if (cho=='n'||cho=='N') {
            saremind=1;
            return -1;
        }
    }
    fclose(fp);
    fp=fopen(filename, "w");            //“w”方式打开可以重写文件
    fprintf(fp,"A total of %d data\n",finally);
    for (i=1; i<=finally; i++) {
        fprintf(fp,"| %3d  |  %13ld | %15s |   %2d  |  %13.2f  |  %8.2f   |   %8.2f    | %10.2f  | %11.2f  |\n",i,p->date.Card_No,p->date.name,p->date.month,p->date.Init_Salary,p->date.Water_Rate,p->date.Electric_Rate,p->date.tax,p->date.Final_Salary);
        p = p->next;
    }
    fclose(fp);
    return 0;
}

//保存提醒
void SaveRemind(LINK *head,char filename[50],int saremind){
    char pd1;
    if (saremind!=1) {            //1表示未进行修改
        return;
    }
    else{
        do {
            if (language==1) {
                printf("文件尚未储存，是否储存文件？(Y/N)");
            }
            else if (language==2){
                printf("Documents are not yet stored. Do you want to save them?(Y/N)");
            }
            scanf(" %c",&pd1);
        } while (pd1!='y'&&pd1!='Y'&&pd1!='N'&&pd1!='n');
        if (pd1=='y'||pd1=='Y') {
            SaveFile(head, filename);
        }
    }
}

//信息输入
struct link *InformationInput (int a){
    struct link *p=NULL;
    p=(struct link *)malloc(sizeof(struct link));
    memset(p, 0, sizeof(struct link));
    if (p==NULL) {
        printf("ERROR!!!No enough memory to allocate!\n");
        return NULL;
    }
    if (language==1) {
        printf("\n请输入第%d条员工的信息：\n",a+1);
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("请输入员工的工资卡号：");
            check=scanf("%ld",&p->date.Card_No);
        } while (check!=1);
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("请输入员工的姓名：");
            check=scanf("%s", p->date.name);
        } while (check!=1);
        printf("请输入月份：");
        scanf("%d",&p->date.month);
        while (p->date.month>12||p->date.month<1) {            //对月份进行检查
            setbuf(stdin, NULL);                            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("错误！！请重新输入月份：");
            scanf("%d",&p->date.month);
        }
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("请输入员工的应付工资：");
            check=scanf("%f",&p->date.Init_Salary);
        } while (check!=1);
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("请输入员工的水费：");
            check=scanf("%f",&p->date.Water_Rate);
        } while (check!=1);
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("请输入员工的电费：");
            check=scanf("%f",&p->date.Electric_Rate);
        } while (check!=1);
    }
    else if (language==2){
        printf("\nPlease input the %dth Employee Information:\n",a+1);
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("Please input employee's salary card number:");
            check=scanf("%ld",&p->date.Card_No);
        } while (check!=1);
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("Please inout employee's name:");
            check=scanf("%s", p->date.name);
        } while (check!=1);
        printf("Please input month:");
        scanf("%d",&p->date.month);
        while (p->date.month>12||p->date.month<1) {            //对月份进行检查
            setbuf(stdin, NULL);                            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("Error!!  Please input month again:");
            scanf("%d",&p->date.month);
        }
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("Please inout employee's Payable wages:");
            check=scanf("%f",&p->date.Init_Salary);
        } while (check!=1);
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("Please input employee's water rent:");
            check=scanf("%f",&p->date.Water_Rate);
        } while (check!=1);
        do {
            setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
            printf("Please inout employee's electric charge:");
            check=scanf("%f",&p->date.Electric_Rate);
        } while (check!=1);
    }
    if((int)&p->date.Init_Salary<=800){
        p->date.tax=0;
    }
    else if ((int)p->date.Init_Salary>800&&(int)p->date.Init_Salary<=1400){
        p->date.tax=(p->date.Init_Salary-800)*0.05;
    }
    else if ((int)p->date.Init_Salary>1400){
        p->date.tax=(p->date.Init_Salary-1400)*0.1;
    }
    p->date.Final_Salary=(p->date.Init_Salary)-(p->date.Electric_Rate)-(p->date.Water_Rate)-(p->date.tax);
    if (language==1) {
        printf("*该员工应发工资为：%.2f\n",p->date.Final_Salary);
    }
    else if (language==2){
        printf("*The employee shall be paid as follows:%.2f",p->date.Final_Salary);
    }
    p->next=NULL;
    finally++;                    //总数需+1
    return p;
}

//信息删除
struct link *InformationDelete (LINK *head,int a[]){
    LINK *p=head,*pr=NULL;
    int bu=0;
    int i=0,n=0;
    int temp;
    for (i=0; a[i]!=0; i++) {                   //将需要删除的列表进行排序，防止误删
        for (n=i; a[n]!=0; n++) {
            if (a[i]>a[n]) {
                temp=a[i];
                a[i]=a[n];
                a[n]=temp;
            }
        }
    }
    n=0;
    while (a[n]!=0) {
        p=head;
        if (a[n]==1) {
            head=p->next;
        }
        else{
            for (i=1+bu; i<a[n]; i++) {
                pr=p;
                p=p->next;
            }
            pr->next=p->next;
        }
        free(p);
        n++;
        finally--;              //总数-1
        bu++;                   //补齐因删除之前结点而产生的位移
    }
    return head;
}

//信息浏览
void InformationBrowsing (struct link *head,int a){
    struct link *p = head;
    int j = 1,i,n;
    if (a==1) {
        n=finally;
    }
    else{
        do {
            if (language==1) {
                printf("\n(输入\"0\"表示全部输出在一页中)");                //打印双引号需转义
                printf("\n一页显示多少行：");
            }
            else if(language==2){
                printf("\n(Input \"0\" means all output in one page)");
                printf("\nHow many rows displayed in a page:");
            }
            do {
                setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
                check=scanf("%d",&n);
            } while (check!=1);
            if (n==0||n>finally) {                //当n=0或者n大于总数，一页打印finally条
                n=finally;
            }
        } while (n<0);
    }
    system("clear");
    while (p != NULL)
    {
        if (language==1) {
            printf("|  序号 |     工资卡号    |       姓名       |  月份  |     应发工资     |     水费     |      电费      |     税金     |    实发工资   |\n");
        }
        else if (language==2){
            printf("| NO.  |Wage Card Number|       Name      | Month |  Payable Wages  |  Water Rate |Electric Charge|      Tax    |  Net Payment |\n");
        }
        for (i=0; i<n&&p!=NULL; i++) {            //分页打印（一页n行）
            printf("| %3d   |  %13ld  | %15s  |   %2d   |  %13.2f   |  %8.2f    |   %8.2f     | %10.2f   | %11.2f   |\n", j,p->date.Card_No,p->date.name,p->date.month,p->date.Init_Salary,p->date.Water_Rate,p->date.Electric_Rate,p->date.tax,p->date.Final_Salary);
            p = p->next;
            j++;
        }
        if (j!=finally+1) {                        //没打印到最后一条，显示“按回车继续”；打印到最后一条，结束函数
            ErrorWarning();
            system("clear");
        }
    }
}

//信息查找
struct link *InformationQuery (LINK *head, long int Card_NO, char name[20]){
    struct link *p = head;
    int j = 1,flag=0,begin=0;
    while (p != NULL)
    {
        if (Card_NO==p->date.Card_No||strcmp(name,p->date.name)==0) {        //对卡号或姓名进行查询
            flag=1;                                //标志变量（0->未找到符合要求的信息，1->找到符合要求的信息）
            if (begin==0) {
                if (language==1) {
                    printf("|  序号 |     工资卡号    |       姓名       |  月份  |     应发工资     |     水费     |      电费      |     税金     |    实发工资   |\n");
                }
                else if (language==2){
                    printf("| NO.  |Wage Card Number|       Name      | Month |  Payable Wages  |  Water Rate |Electric Charge|      Tax    |  Net Payment |\n");
                }
                begin=1;
            }
            printf("| %3d   |  %13ld  | %15s  |   %2d   |  %13.2f   |  %8.2f    |   %8.2f     | %10.2f   | %11.2f   |\n", j,p->date.Card_No,p->date.name,p->date.month,p->date.Init_Salary,p->date.Water_Rate,p->date.Electric_Rate,p->date.tax,p->date.Final_Salary);
        }
        p = p->next;
        j++;
    }
    if (flag==0) {
        if (language==1) {
            printf("未找到符合要求的信息。\n");
        }
        else if (language==2){
            printf("Failure to find the required information.\n");
        }
    }
    return head;
}

//信息插入
struct link *InformationInsert(LINK *head,int *pd){
    struct link *pr = head, *p = head, *temp = NULL;
    int i,a,n;
    if (language==1) {
        printf("\n请输入要在新节点后插入的节点的序号：");
    }
    else if (language==2){
        printf("\nPlease enter the Order Number of which node you want to insert after the new node:");
    }
    do {
        setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
        check=scanf("%d",&a);
    } while (check!=1);
    n=a;
    if (a!=0){
        for (i=1; i<a; i++) {                    //先遍历到a，检查有没有超出链表大小
            if (pr->next==NULL) {                //超出链表大小
                if (language==1) {
                    printf("错误！此列表中没有第%d节点。",a);
                }
                else if (language==2){
                    printf("Error!There are no the %dth node in this list.\n",a);
                }
                *pd = 1;
                return head;
            }
            pr=pr->next;
        }
        p=InformationInput(a);
        sleep(1);
        //修改链表结点指针，将新的结点插入进去
        p->next=NULL;
        temp=pr->next;
        pr->next=p;
        p->next=temp;
    }
    else if (a==0){
        p=InformationInput(a);
        p->next=head;
        head=p;
        sleep(1);
    }
    return head;
}

//信息排序（选择排序）
struct link *InformationSorting (LINK *head, int chose){
    LINK *pfirst=NULL,*pend=NULL;
    SALARY temp;
    int pd=0;
    pfirst=head;
    while(pfirst != pend){
        while(pfirst->next != pend){
            switch (chose) {            //不同标准选择
                case 1:
                    pd=(int)(pfirst->date.Card_No-pfirst->next->date.Card_No);
                    break;
                case 2:
                    pd=-(int)(pfirst->date.Card_No-pfirst->next->date.Card_No);
                    break;
                case 3:
                    pd=pfirst->date.Final_Salary-pfirst->next->date.Final_Salary;
                    break;
                case 4:
                    pd=-(pfirst->date.Final_Salary-pfirst->next->date.Final_Salary);
                    break;
                case 5:
                    pd=strcmp(pfirst->date.name,pfirst->next->date.name);
                    break;
                case 6:
                    pd=-strcmp(pfirst->date.name,pfirst->next->date.name);
                    break;
                default:
                    if (language==1) {
                        printf("未知错误！\n");
                    }
                    else if (language==2){
                        printf("Unknown Error!\n");
                    }
                    ErrorWarning();
                    return head;
            }
            if(pd>0){
                temp=pfirst->date;
                pfirst->date=pfirst->next->date;
                pfirst->next->date=temp;
            }
            pfirst=pfirst->next;
        }
        pend=pfirst;
        pfirst=head;
    }
    return head;
}

//信息统计
void InformationStatistics (LINK *head, SUM *head1, int a, int b){
    SUM *p = NULL,*q = NULL;
    int j=1,flag=0;
    LINK *pr = head;
    while (pr!=NULL) {
        if (pr->date.month<=b&&pr->date.month>=a) {                     //检测是否符合月份
            if (head1==NULL) {
                q=(SUM *)malloc(sizeof(SUM));
                q->next=NULL;
                q->sum=0;
                head1=q;
                q->Card_No=pr->date.Card_No;
                q->sum=q->sum+pr->date.Final_Salary;
            }
            else{
                p=head1;
                while (p!=NULL) {
                    if (p->Card_No==pr->date.Card_No) {
                        p->sum=p->sum+pr->date.Final_Salary;
                        flag=1;
                        break;
                    }
                    p=p->next;
                }
                if (flag==0) {
                    p=head1;
                    while (p->next!=NULL) {
                        p=p->next;
                    }
                    q=(SUM *)malloc(sizeof(SUM));
                    q->next=NULL;
                    q->sum=0;
                    p->next=q;
                    q->Card_No=pr->date.Card_No;
                    q->sum=q->sum+pr->date.Final_Salary;
                }
            }
        }
        pr=pr->next;
    }
    p=head1;
    if (head1==NULL) {
        if (language==1) {
            printf("未找到符合要求的信息！\n");
        }
        else if (language==2){
            printf("Failed to find the required information!\n");
        }
        return;
    }
    if (language==1) {
        printf("|  序号 |     工资卡号    |    实发工资    |\n");
    }
    else if (language==2){
        printf("| NO.  |Wage Card Number|  Net Payment |\n");
    }
    while (p!= NULL)
    {
        printf("| %3d  |  %13ld | %11.2f  |\n", j,p->Card_No,p->sum);
        p = p->next;
        j++;
    }
    DeleteMemory2(head1);                                       //释放内存
    head1=NULL;                                                 //重置指针，下次再用
}

//结束语
void Goodbye (void){
    int a;
    srand((unsigned)time(NULL));
    if (language==1) {
        a = rand()%4;
        switch (a) {
            case 0:
                printf("祝您一天愉快!\n");
                break;
            case 1:
                printf("再见!\n");
                break;
            case 2:
                printf("回见!\n");
                break;
            case 3:
                printf("保重!\n");
                break;
            case 4:
                printf("祝一切都好!\n");
                break;
            default:
                printf("拜拜!\n");
                break;
        }
    }
    else if (language==2){
        a = rand()%10;
        switch (a) {
            case 0:
                printf("Good day!\n");
                break;
            case 1:
                printf("Bye bye!\n");
                break;
            case 2:
                printf("Bye bye!\n");
                break;
            case 3:
                printf("Toodledoo!\n");
                break;
            case 4:
                printf("Have a nice day!\n");
                break;
            case 5:
                printf("All the best!\n");
                break;
            case 6:
                printf("Be seeing you!");
                break;
            case 7:
                printf("So long!\n");
                break;
            case 8:
                printf("See you later alligator!\n");
                break;
            case 9:
                printf("Take care!\n");
                break;
                
            default:
                printf("Good Bye!\n");
                break;
        }
    }
    sleep(2);
    system("clear");
}

//还LINK内存
void DeleteMemory(struct link *head){
    struct link *p = head, *pr = NULL;
    while (p != NULL)
    {
        pr = p;
        p = p->next;
        free(pr);
    }
}

//还SUM内存
void DeleteMemory2(SUM *head){
    SUM *p = head, *pr = NULL;
    while (p != NULL)
    {
        pr = p;
        p = p->next;
        free(pr);
    }
}

void ErrorWarning (void){
    if (language==1) {
        printf("按回车键继续...");
    }
    else if(language==2){
        printf("Press Enter to continue...");
    }
    setbuf(stdin, NULL);            //把输入缓冲区设置为无缓冲,直接从流读取数据
    scanf("%*c");
    system("clear");
}
