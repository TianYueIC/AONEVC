#include "stdafx.h"
#include "..\..\common\Include\xpthread.h"
#include "..\..\common\Include\corethread.h"
#include "..\Include\VHardware.h"
#include "..\Include\Emulatorcore.h"
#include "..\..\common\include\utility.h"
#include "..\..\DSPCore\include\mainfrm.h"
#include "..\..\dspasm\include\dspcode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//*************************
//**Fault Simulation.cpp **
//*************************
void FAddrFunc(int FAddr);
int MFFShell(int addr,int data,int RWFlag);
void Check();
int SF(int addr,int data,int RWFlag);
int TF(int addr,int data,int RWFlag);
int WDF(int addr,int data,int RWFlag);
int RDF(int addr,int data,int RWFlag);
int DRDF(int addr,int data,int RWFlag);
int IRF(int addr,int data,int RWFlag);
int CFst(int addr,int data,int RWFlag); 
int CFds(int addr,int data,int RWFlag);
int CFtr(int addr,int data,int RWFlag);
int CFwd(int addr,int data,int RWFlag);
int CFrd(int addr,int data,int RWFlag);
int CFdrd(int addr,int data,int RWFlag);
int CFir(int addr,int data,int RWFlag);
int dRDF(int addr,int data,int RWFlag);
int dDRDF(int addr,int data,int RWFlag);
int dIRF(int addr,int data,int RWFlag);
int dCFds(int addr,int data,int RWFlag);
int dCFrd(int addr,int data,int RWFlag);
int dCFdrd(int addr,int data,int RWFlag);
int dCFir(int addr,int data,int RWFlag);
int normal(int addr,int data,int RWFlag);
int OutBitData(int addr);
void InputBitData(int addr,int data);
const MemoryLength=3;

int FAddr1;
int FAddr2;
int RAM[MemoryLength];//the unit must be bit,i.e. 0 or 1;
int addr;         //the address used in the orperation
int data;         //the data Read from RAM or Write into RAM+
int FTypeFlag;	//reset the Fault type of RAM's
int RWFlag;       //the selection signal of Read or Write to the RAM,0:Read,1:write;
int AAddrFlag;	//take down the last address during the successive operation 
int LastVValue;
int LastAValue;
int LastRW;
int LastARW;
int Last2ARW;
int Last2AValue;
int row=0;
int col=0;
void main()
{
	int FAddr;		//reset the Fault Address
	int entry=0;
	int i=0;

	LastAValue=0;
	LastVValue=0;
	LastRW=0;
	LastARW=0;
	Last2ARW=0;
	Last2AValue=0;
	RAM[MemoryLength]=0;

	cout<<"the size of RAM is:"<<MemoryLength*32<<endl;
	cout << prompt;
	cin>>FTypeFlag;
	if(FTypeFlag==0)	//normal Check
		Check();		
	else			//Set fault and check it
	{
		cout<<"please input the Fault Address"<<"("<<"0~"<<MemoryLength*32<<"):"<<endl;
		cin>>FAddr;
		FAddrFunc(FAddr);//victim cell or the single cell//and aggressor cell	
		Check();
		cout<<"Press Any Key To Continue!"<<endl;
	}
}

void FAddrFunc(int FAddr)
{
	FAddr1=FAddr;//
	FAddr2=FAddr&0x15;
}
int MFFShell(int addr,int data,int RWFlag)
{
	if ((addr==FAddr1)||(addr==FAddr2))
	{
		switch(FTypeFlag)
		{
		case 0:
			data=normal(addr,data,RWFlag);break;
		case 1:	//SF
			data=SF(addr,data,RWFlag);break;
		case 2:	//TF
			data=TF(addr,data,RWFlag);break;
		case 3:	//WDF
			data=WDF(addr,data,RWFlag);break;
		case 4:	//RDF
			data=RDF(addr,data,RWFlag);break;
		case 5:	//DRDF
			data=DRDF(addr,data,RWFlag);break;
		case 6:	//IRF
			data=IRF(addr,data,RWFlag);break;
		case 7:	//CFst
			data=CFst(addr,data,RWFlag);break;
		case 8:	//CFds
			data=CFds(addr,data,RWFlag);break;
		case 9:	//CFtr
			data=CFtr(addr,data,RWFlag);break;
		case 10:	//CFwd
			data=CFwd(addr,data,RWFlag);break;
		case 11:	//CFrd
			data=CFrd(addr,data,RWFlag);break;
		case 12:	//CFdrd
			data=CFdrd(addr,data,RWFlag);break;
		case 13:	//CFir
			data=CFir(addr,data,RWFlag);break;
		case 14:	//dRDF
			data=dRDF(addr,data,RWFlag);break;
		case 15:	//dDRDF
			data=dDRDF(addr,data,RWFlag);break;
		case 16:	//dIRF
			data=dIRF(addr,data,RWFlag);break;
		case 17:	//dCFds
			data=dCFds(addr,data,RWFlag);break;
		case 18:	//dCFrd
			data=dCFrd(addr,data,RWFlag);break;
		case 19:	//
			data=dCFdrd(addr,data,RWFlag);break;
		case 20:	//dCFir
			data=dCFir(addr,data,RWFlag);break;
		}	//switch
	}		//if
	else		//not the Fault address
		normal(addr,data,RWFlag);
	return(data);
}
void Check()

/*{ 任意序0 ( w0  );
升1 ( r0, r0, w0, r0, w1 );	            升2 ( r1, r1, w1, r1, w0 );
降3 ( r0, r0, w0, r0, w1 );              	降4 ( r1, r1, w1, r1, w0 );
升5 ( r0, r0)  */

{
	int i;
	cout<<"\n\n\n\n"<<"**************************************************************"<<endl;
	cout<<"*                       March**SS**Test                      *"<<endl;
	cout<<"*                                                            *"<<endl;
	cout<<"**************************************************************"<<endl;
	cout<<"------------------------任意序0 ( w0  )-------------------------"<<endl;
	cout<<"操  地   RAM"<<endl;
	cout<<"作  址   值\n"<<endl;
	cout<<"W0 !\n"<<endl;
	for (i=0;i<MemoryLength*32;i++)
		data=MFFShell(i,0,1);
	cout<<"-----------------升序1 ( r0, r0, w0, r0, w1 )-------------------"<<endl;
	cout<<"操  地   RAM"<<endl;
	cout<<"作  址   值\n"<<endl;

	for (i=0;i<MemoryLength*32;i++)
	{
		data=MFFShell(i,data,0);
		cout<<"R0 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,data,0);
		cout<<"R0 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,0,1);
		cout<<"W0 !\n"<<endl;
		data=MFFShell(i,data,0);
		cout<<"R0 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,1,1);
		cout<<"W1!\n"<<endl;
		cout<<"~~~~~~~~~~~~~~~~~~~"<<endl;
	}
	cout<<"-----------------升序2 ( r1, r1, w1, r1, w0 )-------------------"<<endl;
	cout<<"操  地   RAM"<<endl;
	cout<<"作  址   值\n"<<endl;
	for (i=0;i<MemoryLength*32;i++)
	{
		data=MFFShell(i,data,0);
		cout<<"R1 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,data,0);
		cout<<"R1 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,1,1);
		cout<<"W1!\n"<<endl;
		data=MFFShell(i,data,0);
		cout<<"R1 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,0,1);
		cout<<"W0!\n"<<endl;
		cout<<"~~~~~~~~~~~~~~~~~~~"<<endl;
	}
	cout<<"-----------------降3 ( r0, r0, w0, r0, w1 )-------------------"<<endl;
	cout<<"操  地   RAM"<<endl;
	cout<<"作  址   值\n"<<endl;
	for (i=MemoryLength*32-1;i>=0;i--)
	{
		data=MFFShell(i,data,0);
		cout<<"R0 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,data,0);
		cout<<"R0 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,0,1);
		cout<<"W0 !\n"<<endl;
		data=MFFShell(i,data,0);
		cout<<"R0 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,1,1);
		cout<<"W1!\n"<<endl;
		cout<<"~~~~~~~~~~~~~~~~~~~"<<endl;
	}
	cout<<"-----------------降4 ( r1, r1, w1, r1, w0 )-------------------"<<endl;
	cout<<"操  地   RAM"<<endl;
	cout<<"作  址   值\n"<<endl;
	for (i=MemoryLength*32-1;i>=0;i--)
	{
		data=MFFShell(i,data,0);
		cout<<"R1 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,data,0);
		cout<<"R1 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,1,1);
		cout<<"W1!\n"<<endl;
		data=MFFShell(i,data,0);
		cout<<"R1 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,0,1);
		cout<<"W0!\n"<<endl;
		cout<<"~~~~~~~~~~~~~~~~~~~"<<endl;
	}
	cout<<"------------------------升5 ( r0, r0）----------------------"<<endl;
	cout<<"操  地   RAM"<<endl;
	cout<<"作  址   值\n"<<endl;
	for (i=0;i<MemoryLength*32;i++)
	{
		data=MFFShell(i,data,0);
		cout<<"R0 :"<<i<<"----"<<data<<endl;
		data=MFFShell(i,data,0);
		cout<<"R0 :"<<i<<"----"<<data<<endl;
		cout<<"~~~~~~~~~~~~~~~~~~~"<<endl;
	}
}
//////////////////////BitData/////////////////////////////
int OutBitData(int addr)
{
	col=addr>>5;
	row=addr&0x1f;
	return (RAM[col]>>row)&1;
}
void InputBitData(int addr,int data)
{
	col = addr>>5;
	row = addr&0x1f;
	RAM[col]  = (RAM[col] & ~(1<<row)) | ((data&1) << row);//////////data是32位的吗？？
}
///////////////////////Fault Model/////////////////////////
int SF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
		if (RWFlag==0)
			data=OutBitData(addr);
		else 
		{
			data=OutBitData(addr);
			cout<<"There is a 'SF'!"<<"    stuck at:"<<data<<endl;//don't write anything
		}
	else
		if(RWFlag)
			InputBitData(addr,data);
		else
			data=OutBitData(addr);
	return(data);
}
int TF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
		if(RWFlag==0)
			data=OutBitData(addr);
		else 
		{
			cout<<"There is a 'TF'!"<<endl;
			if ((RAM[addr]==0)&&(data==1))
			{
				cout<<"There is a 'TF'!"<<endl;
				InputBitData(addr,0);
			}
			else if ((RAM[addr]==1)&&(data==0))
			{
				cout<<"There is a 'TF'!"<<endl;
				InputBitData(addr,1);;
			}
				else 
					InputBitData(addr,data);
		}
	else
		if(RWFlag)
			InputBitData(addr,data);
		else
			data=OutBitData(addr);

	return(data);
}
int WDF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
		if(RWFlag==0)
			data=OutBitData(addr);
		else
		{
			
			if((RAM[addr]==0)&&(data==0))
			{
				cout<<"There is a 'WDF'!"<<endl;	
				InputBitData(addr,1);;
			}
			else if((RAM[addr]==1)&&(data==1))
			{
				cout<<"There is a 'WDF'!"<<endl;
				InputBitData(addr,0);
			}
			else InputBitData(addr,data);
		}
	else 
		if(RWFlag)
			InputBitData(addr,data);
		else
			data=OutBitData(addr);
	return(data);
}
int RDF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
		if(RWFlag==0)
		{
			if(RAM[addr]==0)
			{
				cout<<"There is a 'RDF'!"<<endl;
				InputBitData(addr,1);
				data=1;
			}
			else
			{
				cout<<"There is a 'RDF'!"<<endl;
				InputBitData(addr,0);
				data=0;
			}
			}
		else
			InputBitData(addr,data);
	else
		if (RWFlag)
			InputBitData(addr,data);
		else
			data=OutBitData(addr);
	return(data);
}
int DRDF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
		if(RWFlag==0)
			if(RAM[addr]==0)
			{
				cout<<"There is a 'DRDF'!"<<endl;
				InputBitData(addr,1);
				data=0;
			}
			else
			{
				cout<<"There is a 'DRDF'!"<<endl;
				InputBitData(addr,0);
				data=1;
			}
		else
			InputBitData(addr,data);
	else 
		if(RWFlag)
			InputBitData(addr,data);
		else 
			data=OutBitData(addr);
	return(data);
}
int IRF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
		if(RWFlag==0)
			if(RAM[addr]==0)
			{
				cout<<"There is a 'IRF'!"<<endl;
				InputBitData(addr,0);
				data=1;
			}
			else
			{
				cout<<"There is a 'IRF'!"<<endl;
				InputBitData(addr,1);
				data=0;
			}
		else
			InputBitData(addr,data);
	else
	{
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	return(data);
}
int CFst(int addr,int data,int RWFlag)
{
	if(addr==FAddr2)
	{
		LastAValue=RAM[addr];
		LastARW=RWFlag;
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	else 
	{
		if((LastAValue==0)&&(RAM[addr]==0))
			InputBitData(addr,1);
		if((LastAValue==0)&&(RAM[addr]==1))
			InputBitData(addr,0);
		if((LastAValue==1)&&(RAM[addr]==0))
			InputBitData(addr,1);
		if((LastAValue==1)&&(RAM[addr]==1))
			InputBitData(addr,0);
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
		LastVValue=RAM[addr];
		LastRW=RWFlag;
	}
	return(data);
}
int CFds(int addr,int data,int RWFlag)
{
	if(addr==FAddr2)
	{
		LastAValue=RAM[addr];
		LastARW=RWFlag;
		if(RWFlag)
			InputBitData(addr,data);
		else
			data=OutBitData(addr);
	}
	else 
	{
		if((AAddrFlag&&LastRW)&&(!RAM[addr]))
			InputBitData(addr,1);
		if((AAddrFlag&&LastRW)&&RAM[addr])
			InputBitData(addr,0);
		if((!LastRW)&&(!RAM[addr]))
			InputBitData(addr,1);
		if((!LastRW)&&RAM[addr])
			InputBitData(addr,0);
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
		LastVValue=RAM[addr];
		LastRW=RWFlag;

	}	
	return(data);
}
int CFtr(int addr,int data,int RWFlag)
{
	if(addr==FAddr2)
	{
		LastAValue=RAM[addr];
		LastARW=RWFlag;	
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	else 
	{
		if((LastAValue==0)&&(RAM[addr]==0)&&(data==1)&&RWFlag)
			InputBitData(addr,0);
		if((LastAValue==1)&&(RAM[addr]==0)&&(data==1)&&RWFlag)
			InputBitData(addr,0);
		if((LastAValue==0)&&(RAM[addr]==1)&&(data==0)&&RWFlag)
			InputBitData(addr,1);
		if((LastAValue==1)&&(RAM[addr]==1)&&(data==0)&&RWFlag)
			InputBitData(addr,1);
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);				
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;	
	}
	return(data);
}
int CFwd(int addr,int data,int RWFlag)
{
	if(addr==FAddr2)
	{
		LastAValue=RAM[addr];
		LastARW=RWFlag;	
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	else 
	{
		if((LastAValue==0)&&(RAM[addr]==0)&&(data==0)&&RWFlag)
			InputBitData(addr,1);
		if((LastAValue==1)&&(RAM[addr]==0)&&(data==0)&&RWFlag)
			InputBitData(addr,1);
		if((LastAValue==0)&&(RAM[addr]==1)&&(data==1)&&RWFlag)
			InputBitData(addr,0);
		if((LastAValue==1)&&(RAM[addr]==1)&&(data==1)&&RWFlag)
			InputBitData(addr,0);
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;	
	}
	return(data);
}
int CFrd(int addr,int data,int RWFlag)
{
	if(addr==FAddr2)
	{
		LastAValue=RAM[addr];
		LastARW=RWFlag;
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	else
	{
		if((LastAValue==0)&&(!RWFlag)&&(RAM[addr]==0))
		{
			InputBitData(addr,1);
			data=OutBitData(addr);
		}
		if((LastAValue==1)&&(!RWFlag)&&(RAM[addr]==0))
		{
			InputBitData(addr,1);
			data=OutBitData(addr);
		}
		if((LastAValue==0)&&(!RWFlag)&&(RAM[addr]==1))
		{
			InputBitData(addr,0);
			data=OutBitData(addr);
		}
		if((LastAValue==1)&&(!RWFlag)&&(RAM[addr]==1))
		{
			InputBitData(addr,0);
			data=OutBitData(addr);
		}
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;	
	}
	return(data);
}
int CFdrd(int addr,int data,int RWFlag)
{
	if(addr==FAddr2)
	{
		LastAValue=RAM[addr];
		LastARW=RWFlag;
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	else
	{
		if((LastAValue==0)&&(!RWFlag)&&(RAM[addr]==0))
		{
			InputBitData(addr,1);
			data=0;
		}
		if((LastAValue==1)&&(!RWFlag)&&(RAM[addr]==0))
		{
			InputBitData(addr,1);
			data=0;
		}
		if((LastAValue==0)&&(!RWFlag)&&(RAM[addr]==1))
		{
			InputBitData(addr,0);
			data=1;
		}
		if((LastAValue==1)&&(!RWFlag)&&(RAM[addr]==1))
		{
			InputBitData(addr,0);
			data=1;
		}
		else
		{
			if (RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;	
	}
	return(data);
}
int CFir(int addr,int data,int RWFlag)
{
	if(addr==FAddr2)
	{
		LastAValue=RAM[addr];
		LastARW=RWFlag;
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	else
	{
		if((LastAValue==0)&&(!RWFlag)&&(RAM[addr]==0))
		{
			InputBitData(addr,0);
			data=1;
		}
		if((LastAValue==1)&&(!RWFlag)&&(RAM[addr]==0))
		{
			InputBitData(addr,0);
			data=1;
		}
		if((LastAValue==0)&&(!RWFlag)&&(RAM[addr]==1))
		{
			InputBitData(addr,1);
			data=0;
		}
		if((LastAValue==1)&&(!RWFlag)&&(RAM[addr]==1))
		{
			InputBitData(addr,1);
			data=0;
		}
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;	
	}				
	return(data);
}
int dRDF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
	{
		if((LastVValue==0)&&(LastRW==1)&&(RAM[addr]==0)&&(!RWFlag))
		{
			InputBitData(addr,1);
			data=OutBitData(addr);
		}
		if((LastVValue==0)&&(LastRW==1)&&(RAM[addr]==1)&&(!RWFlag))
		{
			InputBitData(addr,0);
			data=OutBitData(addr);
		}
		if((LastVValue==1)&&(LastRW==0)&&(RAM[addr]==0)&&(!RWFlag))
		{
			InputBitData(addr,1);
			data=OutBitData(addr);
		}					
		if((LastVValue==1)&&(LastRW==1)&&(RAM[addr]==1)&&(!RWFlag))
		{
			InputBitData(addr,0);
			data=OutBitData(addr);
		}
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;
	}
	else
	{
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
		LastAValue=RAM[addr];
		LastARW=RWFlag;
	}
	return(data);
}
int dDRDF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
	{
		if((LastVValue==0)&&(LastRW==1)&&(RAM[addr]==0)&&(!RWFlag))
		{
			InputBitData(addr,1);
			data=0;
		}
		if((LastVValue==0)&&(LastRW==1)&&(RAM[addr]==1)&&(!RWFlag))
		{
			InputBitData(addr,0);
			data=1;
		}
		if((LastVValue==1)&&(LastRW==0)&&(RAM[addr]==0)&&(!RWFlag))
		{
			InputBitData(addr,1);
			data=0;
		}					
		if((LastVValue==1)&&(LastRW==1)&&(RAM[addr]==1)&&(!RWFlag))
		{
			InputBitData(addr,0);
			data=1;
		}
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;
	}
	else
	{
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
		LastAValue=RAM[addr];
		LastARW=RWFlag;
	}
	return(data);
}
int dIRF(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
	{
		if((LastVValue==0)&&(LastRW==1)&&(RAM[addr]==0)&&(!RWFlag))
		{
			InputBitData(addr,0);
			data=1;
		}
		if((LastVValue==0)&&(LastRW==1)&&(RAM[addr]==1)&&(!RWFlag))
		{
			InputBitData(addr,1);
			data=0;
		}
		if((LastVValue==1)&&(LastRW==0)&&(RAM[addr]==0)&&(!RWFlag))
		{
			InputBitData(addr,0);
			data=1;
		}					
		if((LastVValue==1)&&(LastRW==1)&&(RAM[addr]==1)&&(!RWFlag))
		{
			InputBitData(addr,1);
			data=0;
		}
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;
	}
	else
	{
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
		LastAValue=RAM[addr];
		LastARW=RWFlag;
	}
	return(data);
}
int dCFds(int addr,int data,int RWFlag)
{
	if(addr==FAddr2)
	{
		cout<<"The'aggressor'had been triggered!"<<endl;
		Last2AValue=LastAValue;
		LastAValue=RAM[addr];
		Last2ARW=LastARW;
		LastARW=RWFlag;
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	else
	{
		if((Last2AValue==0)&&Last2ARW&&(LastAValue==0)&&(!LastARW)&&(RAM[addr]==0))
			InputBitData(addr,1);
		if((Last2AValue==0)&&Last2ARW&&(LastAValue==1)&&(!LastARW)&&(RAM[addr]==0))
			InputBitData(addr,1);
		if((Last2AValue==1)&&Last2ARW&&(LastAValue==0)&&(!LastARW)&&(RAM[addr]==0))
			InputBitData(addr,1);
		if((Last2AValue==1)&&Last2ARW&&(LastAValue==1)&&(!LastARW)&&(RAM[addr]==0))
			InputBitData(addr,1);
		if((Last2AValue==0)&&Last2ARW&&(LastAValue==0)&&(!LastARW)&&(RAM[addr]==1))
			InputBitData(addr,0);
		if((Last2AValue==0)&&Last2ARW&&(LastAValue==1)&&(!LastARW)&&(RAM[addr]==1))
			InputBitData(addr,0);
		if((Last2AValue==1)&&Last2ARW&&(LastAValue==0)&&(!LastARW)&&(RAM[addr]==1))
			InputBitData(addr,0);
		if((Last2AValue==1)&&Last2ARW&&(LastAValue==1)&&(!LastARW)&&(RAM[addr]==1))
		{
			cout<<"There is a 'dCFds'!"<<endl;
			InputBitData(addr,0);
		}
		else
		{
			if(RWFlag)
				InputBitData(addr,data);
			else 
				data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;	
	}				
	return(data);
}
int dCFrd(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
	{
		if((LastVValue==0)&&LastRW&&(RAM[addr]==0)&&!RWFlag&&(data==0))
		{
			InputBitData(addr,1);
			data=OutBitData(addr);
		}
		if((LastVValue==0)&&LastRW&&(RAM[addr]==1)&&!RWFlag&&(data==1))
		{
			InputBitData(addr,0);
			data=OutBitData(addr);
		}
		if((LastVValue==1)&&LastRW&&(RAM[addr]==0)&&!RWFlag&&(data==0))
		{
			InputBitData(addr,1);
			data=OutBitData(addr);
		}
		if((LastVValue==1)&&LastRW&&(RAM[addr]==1)&&!RWFlag&&(data==1))
		{
			InputBitData(addr,0);
			data=OutBitData(addr);
		}
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;
	}
	else
	{
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	return(data);
}
int dCFdrd(int addr,int data,int RWFlag)
{
	if(addr==FAddr1)
	{
		if((LastVValue==0)&&LastRW&&(RAM[addr]==0)&&!RWFlag&&(data==0))
		{
			InputBitData(addr,1);
			data=0;
		}
		if((LastVValue==0)&&LastRW&&(RAM[addr]==1)&&!RWFlag&&(data==1))
		{
			InputBitData(addr,0);
			data=1;
		}
		if((LastVValue==1)&&LastRW&&(RAM[addr]==0)&&!RWFlag&&(data==0))
		{
			InputBitData(addr,1);
			data=0;
		}
		if((LastVValue==1)&&LastRW&&(RAM[addr]==1)&&!RWFlag&&(data==1))
		{
			InputBitData(addr,0);
			data=1;
		}
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;
	}
	else
	{
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	return(data);
}
int dCFir(int addr,int data,int RWFlag)
{ 			
	if(addr==FAddr1)
	{
		if((LastVValue==0)&&LastRW&&(RAM[addr]==0)&&!RWFlag&&(data==0))
		{
			InputBitData(addr,0);
			data=1;
		}
		if((LastVValue==0)&&LastRW&&(RAM[addr]==1)&&!RWFlag&&(data==1))
		{
			InputBitData(addr,1);
			data=0;
		}
		if((LastVValue==1)&&LastRW&&(RAM[addr]==0)&&!RWFlag&&(data==0))
		{
			InputBitData(addr,0);
			data=1;
		}
		if((LastVValue==1)&&LastRW&&(RAM[addr]==1)&&!RWFlag&&(data==1))
		{
			InputBitData(addr,1);
			data=0;
		}
		else
		{
			if(RWFlag) InputBitData(addr,data);
			else data=OutBitData(addr);
		}
		LastVValue=RAM[addr];
		LastRW=RWFlag;
	}
	else
	{
		if(RWFlag) InputBitData(addr,data);
		else data=OutBitData(addr);
	}
	return(data);
}
int normal(int addr,int data,int RWFlag)
{
	if(RWFlag) 
		InputBitData(addr,data);
	else 
		data=OutBitData(addr);
	LastAValue=0;
	LastVValue=0;
	LastRW=0;
	LastARW=0;
	Last2ARW=0;
	Last2AValue=0;
	return(data);
}