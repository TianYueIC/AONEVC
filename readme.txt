1.����dspasm
    CDSPCode�ࡡSetRoot ()����
    �����޸�CPU�жϴ������������
    ������Ҫ�������Զ�����ʱ����"goto Main"������һ�С�
2. ����SSX32BΪ��������
    SSX32BEmulaloc������
    CVHacdware��
    ReadRP��WriteRPΪӲ������������̡�
    CSSX32BEmulator��
    Step()������Ӳ��ִ�е���ָ��ķ�����̡�
3.��ROM���ݵķ���
    �޸�AONEVC->commonDialog->Src->RomData.cpp->line426;
4.ssx16b�����������������ȱ��һЩ�ļ�,��watchview.h,DSPCore.h,watchview.cpp,DSPCore.cpp:
   ����������ȱ�ٵ��ļ���watchview.h,DSPCore.h,watchview.cpp,DSPCore.cpp�ֱ���ӵ�ssx16b\incude, ssx16b\src�У�
   ���޸Ĳ���#include��·��Ϊssx16b\incude����;
5.ssx16b���������debug��rebuild all OK,����, release��rebuild all ERROR:
    Project.seetings.release for all projects => MFC static link library
6. Ѱ�ҹ������ļ�·���ķ���:
    FileView.xxxx.h/xxxx.cpp.�Ҽ�.Properties.filename;
7. ����FTn�ĺ���:
    CVHardware.Tranfor();
8. ����RPn�ĺ���:
    CVHardware.WriteRP(),ReadRP();
9. 2006.09.01:
    ������16A,32A,16B,32B,���е�CPU����һ��CPU,���е�CPU���������ֻ��һ��SSX32Aƽ̨��DSPCore5.00.exe�����ϰ汾:
    RAMSIZE=512;
    ���¶�����FT:
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
    Modified "(UINT) /= (UINT)"����in ECCLIB, by mengxianjun, 2006.12.16
    Modified "GetInverse()"in ECCLIB, by mengxianjun, 2006.12.29

11. 2007.02.15
    1. ����D:\work\Xuepeng\AONEVC\CommonDialog\Src\RomHData.cpp, by xuepeng,2007.02.15;
    2. �޸�Ϊ���������, by xuepeng,2007.02.15;
       DSPCORE5.01.EXE;

12. 2007.03.19
    1. �޸�D:\work\Xuepeng\AONEVC\CommonDialog\Src\RomHData.cpp, ����ROM-H��ͼ,.cif�ļ�, by xuepeng,2007.03.19;
       DSPCORE5.02.EXE;

13. 2007.06.14
   1. by zhangxuepeng:
    ��RSA���еĳ�Ա����MontgomerySqare();ɾ��
    ��modPowerMontgomery�����ڵ�ѭ����Ϊ��
    ����������
    MSegInt p_;
    while(pos >= 0)
    {
        p_ = p;
        MontgomeryMulit(p,p_);
        if(e.TestBit(pos--)) MontgomeryMulit(p,x);
    }
    ���ɽ������
    ��ѧ��
    2007��5��31��
    
    2.  by mengxianjun:
    ����RSA���еĳ�Ա����MontgomerySqare()��Ϊ:
    void RSA::MontgomerySquare(MSegInt& p)const
    {
        MSegInt p_=p;
        MontgomeryMulit(p,p_);
    }
    // �������ַ���������OK,��������2;
       
14. 2007.11.07
    �汾: DSPCore5.03.exe
    1. �޸� D:\work\Xuepeng\AONEVC\CommonDialog\Src\RomHData.cpp�ļ��ں��� void CROMData::WriteHLayout(FILE *fp) 
    �� cy = (blocks+1)*72*32-((i+1) / 2)*72;
    ��Ϊ cy = -blocks*72*32-((i+1) / 2)*72;

15. 2015.12.02
    1. �汾: DSPCore5.04.exe
    2. �������ļ�: D:\work\AONEVC\SSX32A\SSX32A.DSW;
    3. FilesView->SSX32A Files->Source Files->RomHData.cpp;
    4. �޸� D:\work\Xuepeng\AONEVC\CommonDialog\Src\RomHData.cpp�ļ��ں��� void CROMData::WriteHLayout(FILE *fp)
      �޸�Ŀ�ģ���ԭ��һ��.cod �ļ�����һ����ģ�飬�ĳɰ��� 1 k һ��ģ�飬���ɶ��ģ�� 
			a) �� cLayoutHead ��ģ��˵������ ��DS n 1000 2�� �� 9 ��ROMHCOD�� һ������ while ѭ��֮�ڣ�����ѭ����ʼ��
			b) �� cLayoutTail ��ģ��������� ��DF;�� ���� while ѭ���ڣ�����ѭ��������
      c) �� blocks ������4 Ϊһ��ģ��
      by xuepeng, 2015-12-2 11:50AM
      d) ResourceView->SSX32A resource->String Table->String Table->IDR_MAINFRAME => DSPCore5.04
      e) Project ->Settings ->SSX32A->Win32 Debug -> Debug/DSPCore5.04.exe
      f) Project ->Settings ->SSX32A->Win32 Release -> Release/DSPCore5.04.exe
      by xianjun, 2015-12-2 04:40PM
      
16. 2016-8-22 10:57AM      
    1. ��D:\work\AONEVC\SSX32A\Release\DSPCore5.04.exe�����³�ʹ��.

16. 2020-1-18 2:45PM      
    1. �޸��㷨��ʹ������.v�ļ����°�32λ����ƥ��.
    2. ��D:\work\AONEVC\SSX32A\Release\DSPCore5.05.exe�����ʹ��.

    