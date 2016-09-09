#pragma once

#define BI_MAXLEN 255//80//40
#define DEC 10
#define HEX 16

class CBigInteger
{
public:
	int m_nSign;  //�����ķ���λ��֧�ָ�ֵ����
	int m_nLength; //��¼0x100000000���Ƶ�λ����0 ��40֮�䣬�൱��2���Ƶ�0��1280λ��
	unsigned long m_ulvalue[BI_MAXLEN];  //��¼ÿһλ�ġ����֡�

public:
	CBigInteger(void);
	~CBigInteger(void);

	//��������ֵΪ��һ������
	CBigInteger& Mov(CBigInteger& A);

	//��������ֵΪ�������ܹ������κ����γ��������
	CBigInteger& Mov(unsigned __int64 A);

	//�Ƚ�����������С
	int Cmp(CBigInteger& A);

	//�Ƚ����������ľ���ֵ��С
	int AbsoluteCmp(CBigInteger& A);

	//�������������ĺ�
	CBigInteger Add(CBigInteger& A);

	//���غ�����֧�ִ�������ͨ�������
	CBigInteger Add(unsigned long A);

	//�������������Ĳ�
	CBigInteger Sub(CBigInteger& A);

	//���غ�����֧�ִ�������ͨ�������
	CBigInteger Sub(unsigned long A);

	//�������������Ļ�
	CBigInteger Mul(CBigInteger& A);

	//���غ�����֧�ִ�������ͨ�������
	CBigInteger Mul(unsigned long A);

	//����������������
	CBigInteger Div(CBigInteger& A);

	//���غ�����֧�ִ�������ͨ�������
	CBigInteger Div(unsigned long A);

	//���������������������
	CBigInteger Mod(CBigInteger& A);
	
	//���غ�����֧�ִ�������ͨ�������
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

	//ŷ������㷨��: Y = X.Euc(A)��ʹ����YX mod A = 1
	//CBigInteger Euc(CBigInteger& A);

	//�ɸ������㷨��: Y=X.Mon(A,B)��ʹ����X^A mod B = Y
	//CBigInteger Mon(CBigInteger& A,CBigInteger& B);


	//�������10���ƻ�16�����ַ���ת���ɴ���
	int InPutFromHexStr(CString& str);

	//��������10���ƻ�16���Ƹ�ʽ������ַ���
	int OutPutToHexStr(CString& str);

	BOOL IsNumbericDigit(CHAR ch);

	BOOL IsHexnumberDigit(CHAR ch);

	int Power(int x,int y);

};
