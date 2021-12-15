1.工程dspasm
    CDSPCode类　SetRoot ()函数
    用于修改CPU中断处理程序编译机制
    若不需要编译器自动处理时，将"goto Main"行上移一行。
2. 工程SSX32B为主工程中
    SSX32BEmulaloc工程中
    CVHacdware类
    ReadRP、WriteRP为硬件操作仿真过程。
    CSSX32BEmulator类
    Step()主法。硬件执行单条指令的仿真过程。
3.找ROM数据的方法
    修改AONEVC->commonDialog->Src->RomData.cpp->line426;
4.ssx16b编译仿真器编译链接缺少一些文件,如watchview.h,DSPCore.h,watchview.cpp,DSPCore.cpp:
   将编译连接缺少的文件如watchview.h,DSPCore.h,watchview.cpp,DSPCore.cpp分别添加到ssx16b\incude, ssx16b\src中，
   并修改部分#include的路径为ssx16b\incude即可;
5.ssx16b编译仿真器debug版rebuild all OK,但是, release版rebuild all ERROR:
    Project.seetings.release for all projects => MFC static link library
6. 寻找工程中文件路径的方法:
    FileView.xxxx.h/xxxx.cpp.右键.Properties.filename;
7. 定义FTn的函数:
    CVHardware.Tranfor();
8. 定义RPn的函数:
    CVHardware.WriteRP(),ReadRP();
9. 2006.09.01:
    不论是16A,32A,16B,32B,所有的CPU都是一套CPU,所有的CPU编译仿真器只有一套SSX32A平台的DSPCore5.00.exe或以上版本:
    RAMSIZE=512;
    最新定义了FT:
        #define ShiftR1                         FT0
        #define RotateL24		                FT1
        #define RotateL16		                FT2
        #define RotateL8		                FT3
        #define RotateL1		                FT4
        #define RotateR1                        FT5
        #define Reverse	                        FT6
        #define Not			                    FT7
        #define High16Set1                      FT15    // the input data should be 0X0000xxxx, the output is 0Xffffxxxx
        #define Low16Set1_01                    FT15    // the input data should be 0X0001xxxx, the output is 0Xxxxxffff
        #define Exp_03                          FT15    // the input data should be 0X0003xxxx, the output is 2^x
        #define Log_04                          FT15    // the input data should be 0X0004xxxx, the output is int[log2(x)]

10. 2006.12.15
    Added "IsPrime()" in ECCLIB by mengxianjun, 2006.12.15
    Modified "(UINT) /= (UINT)"运算in ECCLIB, by mengxianjun, 2006.12.16
    Modified "GetInverse()"in ECCLIB, by mengxianjun, 2006.12.29

11. 2007.02.15
    1. 增加D:\work\Xuepeng\AONEVC\CommonDialog\Src\RomHData.cpp, by xuepeng,2007.02.15;
    2. 修改为编译项记忆, by xuepeng,2007.02.15;
       DSPCORE5.01.EXE;

12. 2007.03.19
    1. 修改D:\work\Xuepeng\AONEVC\CommonDialog\Src\RomHData.cpp, 生成ROM-H版图,.cif文件, by xuepeng,2007.03.19;
       DSPCORE5.02.EXE;

13. 2007.06.14
   1. by zhangxuepeng:
    把RSA类中的成员函数MontgomerySqare();删掉
    把modPowerMontgomery函数内的循环改为：
    。。。。。
    MSegInt p_;
    while(pos >= 0)
    {
        p_ = p;
        MontgomeryMulit(p,p_);
        if(e.TestBit(pos--)) MontgomeryMulit(p,x);
    }
    即可解决问题
    张学鹏
    2007年5月31日
    
    2.  by mengxianjun:
    仅把RSA类中的成员函数MontgomerySqare()换为:
    void RSA::MontgomerySquare(MSegInt& p)const
    {
        MSegInt p_=p;
        MontgomeryMulit(p,p_);
    }
    // 以上两种方法均测试OK,保留方法2;
       
14. 2007.11.07
    版本: DSPCore5.03.exe
    1. 修改 D:\work\Xuepeng\AONEVC\CommonDialog\Src\RomHData.cpp文件内函数 void CROMData::WriteHLayout(FILE *fp) 
    将 cy = (blocks+1)*72*32-((i+1) / 2)*72;
    改为 cy = -blocks*72*32-((i+1) / 2)*72;

15. 2015.12.02
    1. 版本: DSPCore5.04.exe
    2. 主工程文件: D:\work\AONEVC\SSX32A\SSX32A.DSW;
    3. FilesView->SSX32A Files->Source Files->RomHData.cpp;
    4. 修改 D:\work\Xuepeng\AONEVC\CommonDialog\Src\RomHData.cpp文件内函数 void CROMData::WriteHLayout(FILE *fp)
      修改目的：将原来一个.cod 文件生成一个大模块，改成按照 1 k 一个模块，生成多个模块 
			a) 将 cLayoutHead 中模块说明部分 “DS n 1000 2” 及 9 “ROMHCOD” 一起移入 while 循环之内，放在循环开始处
			b) 将 cLayoutTail 中模块结束部分 “DF;” 移入 while 循环内，放在循环结束处
      c) 以 blocks 计数满4 为一个模块
      by xuepeng, 2015-12-2 11:50AM
      d) ResourceView->SSX32A resource->String Table->String Table->IDR_MAINFRAME => DSPCore5.04
      e) Project ->Settings ->SSX32A->Win32 Debug -> Debug/DSPCore5.04.exe
      f) Project ->Settings ->SSX32A->Win32 Release -> Release/DSPCore5.04.exe
      by xianjun, 2015-12-2 04:40PM
      
16. 2016-8-22 10:57AM      
    1. 将D:\work\AONEVC\SSX32A\Release\DSPCore5.04.exe交给陈晨使用.

16. 2020-1-18 2:45PM      
    1. 修改算法，使码点计算.v文件与新版32位规则匹配.
    2. 将D:\work\AONEVC\SSX32A\Release\DSPCore5.05.exe交给杨桓使用.

    