#include "StdAfx.h"
#include "BigInteger.h"
#include <math.h>

CBigInteger::CBigInteger(void)
{
	m_nSign = 1;   // 1:positive, 0:negative
	m_nLength = 1;
	for (int i =0; i<BI_MAXLEN;i++)
	{
		m_ulvalue[i] = 0;
	}
}

CBigInteger::~CBigInteger(void)
{
}

int CBigInteger::Cmp(CBigInteger& A)
{
	if (m_nSign > A.m_nSign)  // Positive  > Negative
	{
		return 1;
	}
	else if (m_nSign < A.m_nSign) // Negative < Positive
	{
		return -1;
	}
	else
	{
		if (A.m_nSign == 1) // both positive
		{
			if (m_nLength > A.m_nLength)
			{
				return 1;
			}

			if (m_nLength < A.m_nLength)
			{
				return -1;
			}

			for (int i = m_nLength-1;i>=0;i--)
			{
				if (m_ulvalue[i] > A.m_ulvalue[i])
				{
					return 1;
				}

				if (m_ulvalue[i] < A.m_ulvalue[i])
				{
					return -1;
				}
			}
		}
		else                // both negative
		{
			if (m_nLength > A.m_nLength)
			{
				return -1;
			}

			if (m_nLength < A.m_nLength)
			{
				return 1;
			}

			for (int i = m_nLength-1;i>=0;i--)
			{
				if (m_ulvalue[i] > A.m_ulvalue[i])
				{
					return -1;
				}

				if (m_ulvalue[i] < A.m_ulvalue[i])
				{
					return 1;
				}
			}
		}
	}
	
	return 0; // Equal
}

int CBigInteger::AbsoluteCmp(CBigInteger& A)
{
	if (m_nLength > A.m_nLength)
	{
		return 1;
	}

	if (m_nLength < A.m_nLength)
	{
		return -1;
	}

	for (int i = m_nLength-1;i>=0;i--)
	{
		if (m_ulvalue[i] > A.m_ulvalue[i])
		{
			return 1;
		}

		if (m_ulvalue[i] < A.m_ulvalue[i])
		{
			return -1;
		}
	}
	
	return 0; // Equal
}

CBigInteger& CBigInteger::Mov(CBigInteger& A)
{
	m_nSign = A.m_nSign;
	m_nLength = A.m_nLength;

	int i = 0;
	
	for (i=0; i < BI_MAXLEN;i++)
	{
		m_ulvalue[i]=A.m_ulvalue[i];
	}
	
	if (m_nLength != 1)
	{
		i = m_nLength -1;
		while(m_ulvalue[i] ==0)
		{
			i--;
		}
		m_nLength = i + 1;
	}
	

	return *this;
}

CBigInteger& CBigInteger::Mov(unsigned __int64 A)
{
	m_nSign = 1;
	if(A>0xFFFFFFFF)
	{
		m_nLength=2;
		m_ulvalue[1]=(unsigned long)(A>>32);
		m_ulvalue[0]=(unsigned long)A;
	}
	else
	{
		m_nLength=1;
		m_ulvalue[0]=(unsigned long)A;
	}
	for(int i=m_nLength;i<BI_MAXLEN;i++)
	{
		m_ulvalue[i]=0;
	}

	return *this;
}

CBigInteger CBigInteger::Add(CBigInteger& A)
{
	CBigInteger X,Y;
	X.Mov(*this);
	if (X.m_nSign == A.m_nSign)  // same sign
	{
		X.Mov(*this);
		int carry = 0;
		unsigned __int64 sum =0;
		if (X.m_nLength < A.m_nLength)
		{
			X.m_nLength = A.m_nLength;
		}

		for (int i=0; i < X.m_nLength;i++)
		{
			sum = A.m_ulvalue[i];
			sum = sum + X.m_ulvalue[i] + carry;
			X.m_ulvalue[i] = (unsigned long)sum;

			if (sum >0xFFFFFFFF)
			{
				carry = 1;
			}
			else
			{
				carry = 0;
			}
		}

		if (X.m_nLength < BI_MAXLEN)
		{
			X.m_ulvalue[X.m_nLength] = carry;
			X.m_nLength += carry;
		}

		return X;
	}
	else         // different sign
	{
		if (X.m_nSign == 1) // Positive + Negative
		{
			X.Mov(A);
			X.m_nSign = 1 - X.m_nSign; 
			return Sub(X);  // Change to Positive - Positive
		}
		else				// Negative + Positive
		{
			X.m_nSign = 1 - X.m_nSign;
			return A.Sub(X);
		}
		
	}
}

CBigInteger CBigInteger::Add(unsigned long A)
{
	CBigInteger X;
	//if((m_nSign*A)>=0)
	if(m_nSign ==1) // Positive + Positive
	{
		X.Mov(*this);
		unsigned __int64 sum;
		sum = A;
		sum = sum + X.m_ulvalue[0];
		X.m_ulvalue[0]=(unsigned long)sum;
		if(sum>0xFFFFFFFF)
		{
			int i=1;
			while(X.m_ulvalue[i]==0xFFFFFFFF)
			{
				X.m_ulvalue[i]=0;
				i++;
			}

			X.m_ulvalue[i]++;

			if((i<BI_MAXLEN)&&(i==X.m_nLength))
			{
				X.m_nLength=i+1;
			}
		}
		return X;
	}
	else   // Negative + Positive
	{
		X.Mov(A);
		return Add(X);
	}
}

CBigInteger CBigInteger::Sub(CBigInteger& A)
{
	CBigInteger X;
	X.Mov(*this);

	if (X.m_nSign == A.m_nSign) // same sign
	{
		X.Mov(*this);
		//int cmp = X.Cmp(A);
		int cmp = X.AbsoluteCmp(A);
		if (cmp == 0)
		{
			X.Mov(0);
			return X;
		}
		
		int len =0;
		unsigned int carry = 0;
		unsigned __int64 num;
		unsigned long *s,*d;
		unsigned int temp = 0;

		if (X.m_nSign == 1) // both positive
		{
			if (cmp >0)
			{
				s=X.m_ulvalue;
				d=A.m_ulvalue;
				len = X.m_nLength;
			}

			if (cmp <0)
			{
				s=A.m_ulvalue;
				d=X.m_ulvalue;
				len = A.m_nLength;
				X.m_nSign = 1 - X.m_nSign; // change to negative
			}
		}
		else                // both negative
		{
			if (cmp >0)
			{
				s=X.m_ulvalue;
				d=A.m_ulvalue;
				len = X.m_nLength;
			}

			if (cmp <0)
			{
				s=A.m_ulvalue;
				d=X.m_ulvalue;
				len = A.m_nLength;
				X.m_nSign = 1 - X.m_nSign; // change to positive
			}
		}


		for (int i = 0; i < len; i++)
		{
			// Fix 1 0 0 0 - 80000000 80000000 80000000 bug
			if (carry == 0)
			{
				if (s[i] >= d[i])
				{
					X.m_ulvalue[i]= s[i] - carry - d[i];
					carry = 0;
				}
				else
				{
					num = 0x100000000 + s[i];
					X.m_ulvalue[i] = (unsigned long)(num - carry - d[i]);
					carry = 1;
				}
			}
			else
			{
				if (s[i] < carry)
				{
					num = 0x100000000 + s[i];
					X.m_ulvalue[i] = (unsigned long)(num - carry - d[i]);
					carry = 1;
				}
				else
				{
					temp = s[i]-carry;
					if (temp >= d[i])
					{
						X.m_ulvalue[i]= s[i] - carry - d[i];
						carry = 0;
					}
					else
					{
						num = 0x100000000 + s[i];
						X.m_ulvalue[i] = (unsigned long)(num - carry - d[i]);
						carry = 1;
					}
				}
			}
		}

		while (X.m_ulvalue[len-1] == 0)
		{
			len--;
		}
		X.m_nLength = len;

		return X;
	}
	else
	{
		X.Mov(A);
		X.m_nSign = 1 - X.m_nSign;
		return Add(X);
	}
}

CBigInteger CBigInteger::Sub(unsigned long A)
{
	CBigInteger X;
	//if((m_nSign*A)>=0)

	if(m_nSign ==1) // Positive - positive
	{
		X.Mov(*this);
		if(X.m_ulvalue[0]>=(unsigned long)A)
		{
			X.m_ulvalue[0] -=A;
			return X;
		}

		if(X.m_nLength==1)
		{
			X.m_ulvalue[0]=A-X.m_ulvalue[0];
			X.m_nSign=1-X.m_nSign;
			return X;
		}

		unsigned __int64 num=0x100000000+X.m_ulvalue[0];
		X.m_ulvalue[0]=(unsigned long)(num-A);
		int i=1;
		while(X.m_ulvalue[i]==0)
		{
			X.m_ulvalue[i]=0xFFFFFFFF;
			i++;
		}

		if(X.m_ulvalue[i]==1)
		{
			X.m_nLength--;
		}

		X.m_ulvalue[i]--;

		return X;
	}
	else  // Negative - positive
	{
		X.Mov(A);
		X.m_nSign = 1 - X.m_nSign;
		return Add(X);
	}
}

CBigInteger CBigInteger::Mul(CBigInteger& A)
{
	CBigInteger X,Y;
	unsigned __int64 mul;
	unsigned long carry;
	for (int i = 0; i< A.m_nLength; i++)
	{
		Y.m_nLength = m_nLength;
		carry = 0;

		for (int j=0; j < m_nLength;j++)
		{
			mul = m_ulvalue[j];
			mul = mul*A.m_ulvalue[i] + carry;
			Y.m_ulvalue[j] = (unsigned long)mul;
			carry = (unsigned long)(mul >>32);
		}

		if (carry &&(Y.m_nLength < BI_MAXLEN))
		{
			Y.m_nLength ++;
			Y.m_ulvalue[Y.m_nLength - 1] = carry;
		}

		if (Y.m_nLength  < BI_MAXLEN - i)
		{
			Y.m_nLength +=i;
			for (int k= Y.m_nLength-1; k>=i;k--)
			{
				Y.m_ulvalue[k] = Y.m_ulvalue[k-i];
			}

			for (int k=0;k<i;k++)
			{
				Y.m_ulvalue[k] = 0;
			}
		}

		X.Mov(X.Add(Y));
		Y.Mov(0);//Clear Temp Y value to fix bug
	}

	if (m_nSign + A.m_nSign ==1) // same signs to positive, different to negative
	{
		X.m_nSign = 0;
	}
	else
	{
		X.m_nSign = 1;
	}

	return X;
}

CBigInteger CBigInteger::Mul(unsigned long A)
{
	CBigInteger X;
	unsigned __int64 mul;
	unsigned long carry=0;
	X.Mov(*this);

	for(int i=0;i<m_nLength;i++)
	{
		mul=m_ulvalue[i];
		mul=mul*A+carry;
		X.m_ulvalue[i]=(unsigned long)mul;
		carry=(unsigned long)((mul-X.m_ulvalue[i])>>32);
	}

	if(carry&&(X.m_nLength<BI_MAXLEN))
	{
		X.m_nLength++;
		X.m_ulvalue[X.m_nLength-1]=carry;
	}

    /*
	if(A<0)
	{
		X.m_nSign=1-X.m_nSign;
	}*/

	return X;
}

CBigInteger CBigInteger::Div(CBigInteger& A)
{
	CBigInteger X,Y,Z,AbsoluteA;
	int len;
	unsigned __int64 num,div;
	unsigned long carry = 0;

	Y.Mov(*this);
	Y.m_nSign = 1; // Change to absolute value;

	AbsoluteA.Mov(A); 
	AbsoluteA.m_nSign = 1; // Change to absolute value;

	while (Y.AbsoluteCmp(AbsoluteA) >0)
	{
		if (Y.m_ulvalue[Y.m_nLength-1] > AbsoluteA.m_ulvalue[AbsoluteA.m_nLength-1])
		{
			len = Y.m_nLength - AbsoluteA.m_nLength;
			div = Y.m_ulvalue[Y.m_nLength-1]/(AbsoluteA.m_ulvalue[AbsoluteA.m_nLength-1]+1);
		}
		else if (Y.m_nLength >AbsoluteA.m_nLength)
		{
			len= Y.m_nLength - AbsoluteA.m_nLength -1;
			num = Y.m_ulvalue[Y.m_nLength - 1];
			num = (num <<32) + Y.m_ulvalue[Y.m_nLength - 2];
			if (AbsoluteA.m_ulvalue[AbsoluteA.m_nLength-1] == 0xFFFFFFFF)
			{
				div =(num >>32);
			}
			else
			{
				div =num/(AbsoluteA.m_ulvalue[AbsoluteA.m_nLength-1] + 1);
			}
		}
		else
		{
			X.Mov(X.Add(1));
			break;
		}

		Z.Mov(div);
		Z.m_nLength +=len;
		for (int i=Z.m_nLength-1;i>=len;i--)
		{
			Z.m_ulvalue[i] = Z.m_ulvalue[i-len];
		}
		for (int i=0;i<len;i++)
		{
			Z.m_ulvalue[i] = 0;
		}
		X.Mov(X.Add(Z));
		Z.Mov(Z.Mul(AbsoluteA));
		Y.Mov(Y.Sub(Z));
	}

	if (Y.AbsoluteCmp(AbsoluteA) ==0)
	{
		X.Mov(X.Add(1));
	}

	if (m_nSign + A.m_nSign ==1)
	{
		X.m_nSign = 0;
	}
	else
	{
		X.m_nSign = 1;
	}

	return X;
}

CBigInteger CBigInteger::Div(unsigned long A)
{
	CBigInteger X;
	X.Mov(*this);
	if(X.m_nLength==1)
	{
		X.m_ulvalue[0]=X.m_ulvalue[0]/A;
		return X;
	}
	unsigned __int64 div,mul;
	unsigned long carry=0;
	for(int i=X.m_nLength-1;i>=0;i--)
	{
		div=carry;
		div=(div<<32)+X.m_ulvalue[i];
		X.m_ulvalue[i]=(unsigned long)(div/A);
		mul=(div/A)*A;
		carry=(unsigned long)(div-mul);
	}

	if(X.m_ulvalue[X.m_nLength-1]==0)
	{
		X.m_nLength--;
	}

	/*if(A<0)
	{
		X.m_nSign=1-X.m_nSign;
	}*/

	return X;
}

CBigInteger CBigInteger::Mod(CBigInteger& A)
{
	CBigInteger X,Y,AbsoluteA;
	int len;
	int orignalsign;
	unsigned __int64 num,div;
	unsigned long carry=0;

	X.Mov(*this);
	orignalsign = X.m_nSign; // Backup original sign
	X.m_nSign = 1; // Change to absolute value

	AbsoluteA.Mov(A); 
	AbsoluteA.m_nSign = 1; // Change to absolute value

	while(X.AbsoluteCmp(AbsoluteA)>0)
	{       
		if(X.m_ulvalue[X.m_nLength-1]>AbsoluteA.m_ulvalue[AbsoluteA.m_nLength-1])
		{
			len=X.m_nLength-AbsoluteA.m_nLength;
			div=X.m_ulvalue[X.m_nLength-1]/(AbsoluteA.m_ulvalue[AbsoluteA.m_nLength-1]+1);
		}
		else if(X.m_nLength>AbsoluteA.m_nLength)
		{
			len=X.m_nLength-AbsoluteA.m_nLength-1;
			num=X.m_ulvalue[X.m_nLength-1];
			num=(num<<32)+X.m_ulvalue[X.m_nLength-2];
			if(AbsoluteA.m_ulvalue[AbsoluteA.m_nLength-1]==0xFFFFFFFF)
			{
				div=(num>>32);
			}
			else
			{
				div=num/(AbsoluteA.m_ulvalue[AbsoluteA.m_nLength-1]+1);
			}
		}
		else
		{
			X.Mov(X.Sub(AbsoluteA));
			break;
		}
		Y.Mov(div);
		Y.Mov(Y.Mul(AbsoluteA));
		Y.m_nLength+=len;
		for(int i=Y.m_nLength-1;i>=len;i--)
		{
			Y.m_ulvalue[i]=Y.m_ulvalue[i-len];
		}

		for(int i=0;i<len;i++)
		{
			Y.m_ulvalue[i]=0;
		}

		X.Mov(X.Sub(Y));
	}

	if(X.AbsoluteCmp(AbsoluteA)==0)
	{
		X.Mov(0);
	}

	X.m_nSign = orignalsign; // Restore original sign
	return X;
}

unsigned long CBigInteger::Mod(unsigned long A)
{
	if(m_nLength==1)
	{
		return (m_ulvalue[0]%A);
	}
	unsigned __int64 div;
	unsigned __int64 temp;
	unsigned long carry=0;
	for(int i=m_nLength-1;i>=0;i--)
	{
		div=carry*0x100000000 + m_ulvalue[i];
		temp = (div/A)*A;
		carry=(unsigned long)(div-temp);
	}

	return carry;
}

//重载函数以支持大数与普通整数相除
CBigInteger CBigInteger::ShiftRight(unsigned long A)
{
	CBigInteger X;
	X.Mov(*this);

	int a,b;
	a = A/32;
	b = A%32;

	int i;

	for(i= 0; i < (X.m_nLength-a);i++)
	{
		X.m_ulvalue[i]=X.m_ulvalue[i+a];
	}

	for (int k = (X.m_nLength -a); k < X.m_nLength; k++)
	{
		X.m_ulvalue[k] = 0;
	}

	X.m_nLength -= a;

	for (int i = 0;i < b;i++)
	{
		X.Mov(X.ShiftOneBit());
	}

	return X;
}

CBigInteger CBigInteger::ShiftOneBit()
{
	CBigInteger X;
	X.Mov(*this);

	unsigned long shiftrightcarry;
	unsigned __int64 temp;

	int i;
	
	shiftrightcarry = 0;
	for (i = m_nLength -1;i>=0;i--)
	{
		temp = X.m_ulvalue[i] + shiftrightcarry * 0x100000000;
		shiftrightcarry = X.m_ulvalue[i] & 0x01;
		X.m_ulvalue[i] = (unsigned long)(temp >> 1);
	}
	
	i = X.m_nLength - 1;
	while(X.m_ulvalue[i] == 0)
	{
		i--;
	}

	X.m_nLength = i + 1;

	return X;
}

CBigInteger CBigInteger::ShiftMod(unsigned long A)
{
	CBigInteger X;

	unsigned long mask;

	X.m_nSign = 1;

	int a,b;
	a = A/32;
	b = A%32;

	int i;

	for(i= 0; i < a;i++)
	{
		X.m_ulvalue[i]= m_ulvalue[i];
	}

	X.m_nLength = a;

	if (b!=0)
	{
		mask = Power(2,b) - 1;
		X.m_ulvalue[i] = (m_ulvalue[i] & mask);
		X.m_nLength ++;
	}

	return X;
}

int CBigInteger::FindFirstMSB()
{
	CBigInteger X;
	X.Mov(*this);

	unsigned long temp = 0;
	int i;
	
	for (i = 31; i >=0; i--)
	{
		temp = (m_ulvalue[m_nLength - 1]) >> i;
		if (temp & 0x01)
		{
			return i;
		}
	}

	return 0;
}

BOOL CBigInteger::IsNumber1at(unsigned int arraylen, unsigned int indexlen)
{
	unsigned long temp;
	temp = m_ulvalue[arraylen];

	temp = temp >> indexlen;

	if (temp&0x01)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//Is Odd Number
BOOL CBigInteger::CheckIsOddNumber()
{
	if ((m_ulvalue[0] & 1) == 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//Is Even Number
int CBigInteger::CheckIsEvenNumber()
{
	if ((m_ulvalue[0] & 1) == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
CBigInteger CBigInteger::Euc(CBigInteger& A)
{
	CBigInteger X,Y;
	X.Mov(*this);
	Y.Mov(A);
	if((X.m_nLength==1)&&(X.m_ulvalue[0]==1))
	{
		return X;
	}

	if((Y.m_nLength==1)&&(Y.m_ulvalue[0]==1))
	{
		X.Mov(X.Sub(1));
		return X;
	}

	if(X.Cmp(Y)==1)
	{
		X.Mov(X.Mod(Y));
	}
	else
	{
		Y.Mov(Y.Mod(X));
	}

	X.Mov(X.Euc(Y));
	Y.Mov(*this);
	if(Y.Cmp(A)==1)
	{
		X.Mov(X.Mul(Y));
		X.Mov(X.Sub(1));
		X.Mov(X.Div(A));
	}
	else
	{
		X.Mov(X.Mul(A));
		X.Mov(X.Add(1));
		X.Mov(X.Div(Y));
	}
	return X;
}
*/

int CBigInteger::InPutFromHexStr(CString& str)
{
	CString strtemp;
	int cnt;
	CHAR ch;
	unsigned int num;
	CHAR numvalue;
	int i;

	int len = str.GetLength();

	if (len%8==0)
	{
		m_nLength = len/8;
	}
	else
	{
		m_nLength = len/8 + 1;
	}

	m_nSign = 1;

	for (i=0; i<len/8; i++)
	{
		strtemp = str.Mid(8*i,8);
        
		num = 0;
		for (cnt=7;cnt>=0;cnt--)
		{
			ch = strtemp.GetAt(cnt);
			if (IsNumbericDigit(ch))
			{
				numvalue = ch - 48;
			}

			if (IsHexnumberDigit(ch))
			{
				numvalue = ch - 55;
			}

			num += numvalue*Power(16,(7-cnt));
		}

		m_ulvalue[m_nLength - 1 - i] = num;
	}

	return 0;
}


int CBigInteger::OutPutToHexStr(CString& str)
{

	str = "";
	char ch;
	CBigInteger X;
	X.Mov(*this);
	char temp;
	unsigned int a;
	int charcnt;

	for (int i = 0 ; i < X.m_nLength; i++)
	{
		charcnt = 0;
		a = X.m_ulvalue[i];
		while (a > 0)
		{
			temp = (char)(a%16);
			if (temp < 10)
			{
				ch = temp + 48;
			}
			else
			{
				ch = temp + 55;
			}

			str.Insert(0,ch);
			charcnt ++;
			a = a/16;
		}

		if (charcnt < 8)
		{
			for (int k = 0;k<(8-charcnt);k++)
			{
				str.Insert(0,'0');
			}

			charcnt = 0;
		}
	}

	/*
	while (X.m_ulvalue[X.m_nLength - 1] >0)
	{
		temp = (char)(X.Mod(16));
		if (temp < 10)
		{
			ch = temp + 48;
		}
		else
		{
			ch = temp + 55;
		}
		
		str.Insert(0,ch);
		X.Mov(X.Div(16));
	}
	*/

	return 0;
}

BOOL CBigInteger::IsNumbericDigit(CHAR ch)
{
	if ((ch >= 48) && (ch <=57))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CBigInteger::IsHexnumberDigit(CHAR ch)
{
	if ((ch >= 65) && (ch <=70))
	{
		return TRUE;
	}

	return FALSE;
}

int CBigInteger::Power(int x,int y)
{
	int temp;
	temp = 1;
	for (int i=1; i<= y;i++)
	{
		temp *=x;
	}

	return temp;
}