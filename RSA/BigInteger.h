#pragma once

#define BI_MAXLEN 255//80//40
#define DEC 10
#define HEX 16

class CBigInteger
{
public:
	int m_nSign;  //大数的符号位，支持负值运算
	int m_nLength; //记录0x100000000进制的位数，0 ～40之间，相当于2进制的0～1280位。
	unsigned long m_ulvalue[BI_MAXLEN];  //记录每一位的‘数字’

public:
	CBigInteger(void);
	~CBigInteger(void);

	//将大数赋值为另一个大数
	CBigInteger& Mov(CBigInteger& A);

	//将大数赋值为编译器能够理解的任何整形常数或变量
	CBigInteger& Mov(unsigned __int64 A);

	//比较两个大数大小
	int Cmp(CBigInteger& A);

	//比较两个大数的绝对值大小
	int AbsoluteCmp(CBigInteger& A);

	//计算两个大数的和
	CBigInteger Add(CBigInteger& A);

	//重载函数以支持大数与普通整数相加
	CBigInteger Add(unsigned long A);

	//计算两个大数的差
	CBigInteger Sub(CBigInteger& A);

	//重载函数以支持大数与普通整数相减
	CBigInteger Sub(unsigned long A);

	//计算两个大数的积
	CBigInteger Mul(CBigInteger& A);

	//重载函数以支持大数与普通整数相乘
	CBigInteger Mul(unsigned long A);

	//计算两个大数的商
	CBigInteger Div(CBigInteger& A);

	//重载函数以支持大数与普通整数相除
	CBigInteger Div(unsigned long A);

	//计算两个大数相除的余数
	CBigInteger Mod(CBigInteger& A);
	
	//重载函数以支持大数与普通整数相除
	unsigned long Mod(unsigned long A);

	CBigInteger ShiftRight(unsigned long A);

	CBigInteger ShiftOneBit();

	CBigInteger ShiftMod(unsigned long A);

	int FindFirstMSB();

	BOOL IsNumber1at(unsigned int arraylen, unsigned int indexlen);

	//Is Odd Number
	BOOL CheckIsOddNumber();

	//Is Even Number
	BOOL CheckIsEvenNumber();

	//欧几里德算法求: Y = X.Euc(A)，使满足YX mod A = 1
	//CBigInteger Euc(CBigInteger& A);

	//蒙哥马利算法求: Y=X.Mon(A,B)，使满足X^A mod B = Y
	//CBigInteger Mon(CBigInteger& A,CBigInteger& B);


	//将输入的10进制或16进制字符串转换成大数
	int InPutFromHexStr(CString& str);

	//将大数按10进制或16进制格式输出到字符串
	int OutPutToHexStr(CString& str);

	BOOL IsNumbericDigit(CHAR ch);

	BOOL IsHexnumberDigit(CHAR ch);

	int Power(int x,int y);

};
