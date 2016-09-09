#include "StdAfx.h"
#include "RSAAlgo.h"
#include "BigInteger.h"
#include <cstdlib>
#include <ctime>

CRSAAlgo::CRSAAlgo(void)
{
	m_unFilterTable[0] = 2;
	m_unFilterTable[1] = 3;
	m_unFilterTable[2] = 5;
	m_unFilterTable[3] = 7;
	m_unFilterTable[4] = 11;
	m_unFilterTable[5] = 13;
	m_unFilterTable[6] = 17;
	m_unFilterTable[7] = 19;
	m_unFilterTable[8] = 23;
	m_unFilterTable[9] = 29;

	m_unFilterTable[10] = 31;
	m_unFilterTable[11] = 37;
	m_unFilterTable[12] = 41;
	m_unFilterTable[13] = 43;
	m_unFilterTable[14] = 47;
	m_unFilterTable[15] = 53;
	m_unFilterTable[16] = 59;
	m_unFilterTable[17] = 61;
	m_unFilterTable[18] = 67;
	m_unFilterTable[19] = 71;

	m_unFilterTable[20] = 73;
	m_unFilterTable[21] = 79;
	m_unFilterTable[22] = 83;
	m_unFilterTable[23] = 89;
	m_unFilterTable[24] = 97;
	m_unFilterTable[25] = 101;
	m_unFilterTable[26] = 103;
	m_unFilterTable[27] = 107;
	m_unFilterTable[28] = 109;
	m_unFilterTable[29] = 113;

	m_unFilterTable[30] = 127;
	m_unFilterTable[31] = 131;
	m_unFilterTable[32] = 137;
	m_unFilterTable[33] = 139;
	m_unFilterTable[34] = 149;
	m_unFilterTable[35] = 151;
	m_unFilterTable[36] = 157;
	m_unFilterTable[37] = 163;
	m_unFilterTable[38] = 167;
	m_unFilterTable[39] = 173;

	m_unFilterTable[40] = 179;
	m_unFilterTable[41] = 181;
	m_unFilterTable[42] = 191;
	m_unFilterTable[43] = 193;
	m_unFilterTable[44] = 197;
	m_unFilterTable[45] = 199;
	m_unFilterTable[46] = 211;
	m_unFilterTable[47] = 223;
	m_unFilterTable[48] = 227;
	m_unFilterTable[49] = 229;

	m_unFilterTable[50] = 233;
	m_unFilterTable[51] = 239;
	m_unFilterTable[52] = 241;
	m_unFilterTable[53] = 251;
	m_unFilterTable[54] = 257;
	m_unFilterTable[55] = 263;
	m_unFilterTable[56] = 269;
	m_unFilterTable[57] = 271;
	m_unFilterTable[58] = 277;
	m_unFilterTable[59] = 281;

	m_unFilterTable[60] = 283;
	m_unFilterTable[61] = 293;
	m_unFilterTable[62] = 307;
	m_unFilterTable[63] = 311;
	m_unFilterTable[64] = 313;
	m_unFilterTable[65] = 317;
	m_unFilterTable[66] = 331;
	m_unFilterTable[67] = 337;
	m_unFilterTable[68] = 347;
	m_unFilterTable[69] = 349;

	m_unFilterTable[70] = 353;
	m_unFilterTable[71] = 359;
	m_unFilterTable[72] = 367;
	m_unFilterTable[73] = 373;
	m_unFilterTable[74] = 379;
	m_unFilterTable[75] = 383;
	m_unFilterTable[76] = 389;
	m_unFilterTable[77] = 397;
	m_unFilterTable[78] = 401;
	m_unFilterTable[79] = 409;

	m_unFilterTable[80] = 419;
	m_unFilterTable[81] = 421;
	m_unFilterTable[82] = 431;
	m_unFilterTable[83] = 433;
	m_unFilterTable[84] = 439;
	m_unFilterTable[85] = 443;
	m_unFilterTable[86] = 449;
	m_unFilterTable[87] = 457;
	m_unFilterTable[88] = 461;
	m_unFilterTable[89] = 463;

	m_unFilterTable[90] = 467;
	m_unFilterTable[91] = 479;
	m_unFilterTable[92] = 487;
	m_unFilterTable[93] = 491;
	m_unFilterTable[94] = 499;
	m_unFilterTable[95] = 503;
	m_unFilterTable[96] = 509;
	m_unFilterTable[97] = 521;
	m_unFilterTable[98] = 523;
	m_unFilterTable[99] = 541;
}

CRSAAlgo::~CRSAAlgo(void)
{
}

BOOL CRSAAlgo::CheckIsInterPrime(CBigInteger X, CBigInteger Y)
{
	CBigInteger T,Temp;
	Temp.Mov(0);

	while (Y.AbsoluteCmp(Temp)!=0)
	{
		T.Mov(X);
		X.Mov(Y);
		Y.Mov(T.Mod(Y));
	}

	Temp.Mov(1);
	if (X.AbsoluteCmp(Temp) == 0)
	{
		return TRUE;  // gcd(X,Y) = 1
	}
	else
	{
		return FALSE;
	}
}

CBigInteger CRSAAlgo::ExeuclideanGCD(CBigInteger& A, CBigInteger& B, CBigInteger& X,CBigInteger& Y)
{
	CBigInteger X1,Y1,X0,Y0;
	CBigInteger Temp,Tempresult;
	CBigInteger Remainder;
	CBigInteger Quotient;
	CBigInteger TempA,TempB;

	X1.Mov(0);
	Y1.Mov(1);
	X0.Mov(1);
	Y0.Mov(0);
	X.Mov(0);
	Y.Mov(1);
	TempA.Mov(A);
	TempB.Mov(B);

	Temp.Mov(0);

	Remainder.Mov(TempA.Mod(TempB)); // Remainder = A % B;
	Tempresult.Mov(TempA.Sub(Remainder));
	Quotient.Mov(Tempresult.Div(TempB)); // Quotient = (A-Remainder)/B;

    while(Remainder.AbsoluteCmp(Temp) !=0)
	{
		Tempresult.Mov(Quotient.Mul(X1));  // Tempresult = Quotient*X1;
		X.Mov(X0.Sub(Tempresult)); // X = X0 - Tempresult;

		Tempresult.Mov(Quotient.Mul(Y1));  // Tempresult = Quotient*Y1;
		Y.Mov(Y0.Sub(Tempresult)); // Y = Y0 - Tempresult;

		X0.Mov(X1);
		Y0.Mov(Y1);
		X1.Mov(X);
		Y1.Mov(Y);

		TempA.Mov(TempB);
		TempB.Mov(Remainder);
		Remainder.Mov(TempA.Mod(TempB)); 
		Tempresult.Mov(TempA.Sub(Remainder));
		Quotient.Mov(Tempresult.Div(TempB));
	}

	return TempB;
}

BOOL CRSAAlgo::LinearEquationExeuclidean(CBigInteger& A, CBigInteger& B, CBigInteger& C,CBigInteger& X,CBigInteger& Y)
{
	CBigInteger gcd;
	CBigInteger TempMod,TempDiv,Temp;
	CBigInteger DivValue;
	CBigInteger T;

	gcd = ExeuclideanGCD(A,B,X,Y);

	Temp.Mov(1);
	T.Mov(1);

	TempMod.Mov(C.Mod(gcd));

	if (TempMod.Cmp(Temp) == 0)
	{
		return FALSE;
	}

	DivValue.Mov(C.Div(gcd));

	X.Mov(X.Mul(DivValue));
	Y.Mov(Y.Mul(DivValue));

	while(X.m_nSign == 0)
	{
		TempDiv.Mov(B.Div(gcd));
        Temp.Mov(TempDiv.Mul(T));
		X.Mov(X.Add(Temp));

		TempDiv.Mov(A.Div(gcd));
		Temp.Mov(TempDiv.Mul(T));
		Y.Mov(Y.Sub(Temp));

		T.Mov(T.Add(1));
	}

	return TRUE;

}

CBigInteger CRSAAlgo::RSAEP(CBigInteger n, CBigInteger e, CBigInteger m)
{
	CBigInteger Result;
	CBigInteger Temp,TempResult;
	CBigInteger Product;

	Result.Mov(1);
	TempResult.Mov(m.Mod(n));

	Temp.Mov(0);
	
	while(e.Cmp(Temp) > 0)  // e > 0 ?
	{
		if (e.CheckIsOddNumber()) // Is odd number
		{
			Product.Mov(Result.Mul(TempResult));
			Result.Mov(Product.Mod(n));
			e.Mov(e.Sub(1));
		}
		else  // Is even number
		{
			Product.Mov(TempResult.Mul(TempResult));
			TempResult.Mov(Product.Mod(n));
			e.Mov(e.Div(2));
		}
	}

	return Result;
}
CBigInteger CRSAAlgo::RSADPwithType1privateKey(CBigInteger n, CBigInteger d, CBigInteger c)
{
	CBigInteger Result;
	CBigInteger Temp,TempResult;
	CBigInteger Product;

	Result.Mov(1);
	TempResult.Mov(c.Mod(n));

	Temp.Mov(0);

	while(d.Cmp(Temp) > 0)  // d > 0 ?
	{
		if (d.CheckIsOddNumber()) // Is odd number
		{
			Product.Mov(Result.Mul(TempResult));
			Result.Mov(Product.Mod(n));
			d.Mov(d.Sub(1));
		}
		else  // Is even number
		{
			Product.Mov(TempResult.Mul(TempResult));
			TempResult.Mov(Product.Mod(n));
			d.Mov(d.Div(2));
		}
	}

	return Result;
}
CBigInteger CRSAAlgo::RSADPwithType2privateKey(CBigInteger p, CBigInteger q, CBigInteger dP,CBigInteger dQ,CBigInteger qInv, CBigInteger c)
{
	CBigInteger m1,m2,h;
	CBigInteger Temp;
	CBigInteger Result;

	m1.Mov(RSADPwithType1privateKey(p,dP,c));
	m2.Mov(RSADPwithType1privateKey(q,dQ,c));
	Temp.Mov(m1.Sub(m2));
	Temp.Mov(Temp.Mul(qInv));
	h.Mov(Temp.Mod(p));

	Temp.Mov(h.Mul(q));
	Result.Mov(m2.Add(Temp));

	return Result;
	
}

CBigInteger CRSAAlgo::GenBigRandomNumber(int bitsize)
{
	CBigInteger X;
	X.m_nSign = 1;
	X.Mov(0);
	X.m_nLength = bitsize/32;

	unsigned char randnumber;
	srand((unsigned)time(NULL));
	for (int i =0; i < (bitsize/8); i++)
	{
		randnumber = (rand()%255) + 1;
        X.m_ulvalue[i/4] += randnumber << ((i%4)*8);
	}

	return X;
}

BOOL CRSAAlgo::RoughCheckIsBigPrime(CBigInteger X)
{
	CBigInteger Y;
	CBigInteger Temp;
	CBigInteger T;

	Y.m_nSign = 1;
	Y.m_nLength = 1;

	Temp.Mov(0);

	for (int i = 0; i < 100; i++)
	{
		Y.Mov(m_unFilterTable[i]);
		T.Mov(X.Mod(Y));
		if (T.Cmp(Temp) == 0)  
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CRSAAlgo::CheckIsBigPrimewithMillerRabin(CBigInteger X)
{
	CBigInteger m;
	CBigInteger r;
	CBigInteger a;
	CBigInteger Temp,Temp1;
	int length;
	BOOL bTrue;

	length = X.m_nLength;
	length = length*32;//bit numbers

	if (X.CheckIsEvenNumber()) // X is even number
	{
		return FALSE;
	}

	m.Mov(X.Sub(1)); // m = X -1;
	r.Mov(0); // r = 0;
	while (m.CheckIsEvenNumber())
	{
		m.Mov(m.Div(2));
		r.Mov(r.Add(1));
	}


	for (int i = 0; i < 1000; i++)
	{
		bTrue = FALSE;
		while (!bTrue)
		{
			//int randnumber = rand();
			//Temp.Mov(randnumber);

			Temp = GenBigRandomNumber(length);// generate 256bit random number

			Temp1.Mov(X.Sub(1)); 
			Temp.Mov(Temp.Mod(Temp1));
			a.Mov(Temp.Add(1));

			bTrue = CheckIsInterPrime(X,a);  
		}

		if (!MillerRabinCheck(a,X,m,r))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CRSAAlgo::CheckIsBigPrimewithMillerRabinWithMontgomery(CBigInteger X)
{
	CBigInteger m;
	CBigInteger r;
	CBigInteger a;
	CBigInteger Temp,Temp1;
	int length;
	BOOL bTrue;

	int checkloopcnt;


	length = X.m_nLength;
	length = length*32;//bit numbers

	if (length <=64)
	{
		checkloopcnt = 20;
	}
	else if ((length > 64) && (length <=256))
	{
		checkloopcnt = 50;
	}
	else 
	{
		checkloopcnt = 100;
	}

	if (X.CheckIsEvenNumber()) // X is even number
	{
		return FALSE;
	}

	m.Mov(X.Sub(1)); // m = X -1;
	r.Mov(0); // r = 0;

	while (m.CheckIsEvenNumber())
	{
		m.Mov(m.Div(2));
		r.Mov(r.Add(1));
	}


	for (int i = 0; i < checkloopcnt; i++)
	{

		bTrue = FALSE;
		while (!bTrue)
		{
			//unsigned int randnumber = rand();
			//Temp.Mov(randnumber);
			Temp = GenBigRandomNumber(length);// generate 256bit random number

			// Test start
			/*
			CString AddQtestStr;
			Temp.OutPutToHexStr(AddQtestStr);
			AfxMessageBox(AddQtestStr);
			*/
			// Test end

			Temp1.Mov(X.Sub(1)); 
			Temp.Mov(Temp.Mod(Temp1));
			a.Mov(Temp.Add(1));

			bTrue = CheckIsInterPrime(X,a);

			Sleep(1000);
		}

		if (!MillerRabinCheckWithMontgomery(a,X,m,r))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CRSAAlgo::MillerRabinCheck(CBigInteger a,CBigInteger n,CBigInteger m,CBigInteger r)
{
	CBigInteger ret;
	CBigInteger last;
	CBigInteger index,Temp;
	CBigInteger Temp1;

	ret = pow_mod(a,m,n);
	last.Mov(ret);

	Temp.Mov(n);
	Temp.Mov(Temp.Sub(1));
	Temp1.Mov(1);

	if ((ret.Cmp(Temp1) == 0) || (ret.Cmp(Temp) == 0))
	{
		return TRUE;// prime
	}
	else
	{
		index.Mov(1);
		while (index.Cmp(r) != 0)
		{
			ret = mult_mod(ret,ret,n);
			if (ret.Cmp(Temp) == 0)
			{
				return TRUE; // prime
			}
			else
			{
				index.Mov(index.Add(1));
			}
		}
	}

	return FALSE; // No prime

	/*
	index.Mov(1);
	while (index.Cmp(r) <= 0)
	{
		ret = mult_mod(ret,ret,n);
		if ((ret.Cmp(Temp1)==0)&&(last.Cmp(Temp1) !=0)&&(last.Cmp(Temp) != 0)) // ret =1 && last !=0 && last !=n-1
		{
			return TRUE;
		}

		index.Mov(index.Add(1));
	}

	if (ret.Cmp(Temp1) !=0) // ret !=1
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	*/
}

BOOL CRSAAlgo::MillerRabinCheckWithMontgomery(CBigInteger a,CBigInteger n,CBigInteger m,CBigInteger r)
{
	CBigInteger ret;
	CBigInteger last;
	CBigInteger index,Temp;
	CBigInteger Temp1;

	ret = NewPowerModualwithMontgomeryAlgo(a,m,n);//PowerModualwithMontgomeryAlgo(a,m,n);

	last.Mov(ret);

	Temp.Mov(n);
	Temp.Mov(Temp.Sub(1));

	Temp1.Mov(1);

	if ((ret.Cmp(Temp1) == 0) || (ret.Cmp(Temp) == 0))
	{
		return TRUE;// prime
	}
	else
	{
		index.Mov(1);
		while (index.Cmp(r) != 0)
		{
			ret = ProductModualwithMontgomeryAlgo(ret,ret,n);
			if (ret.Cmp(Temp) == 0)
			{
				return TRUE; // prime
			}
			else
			{
				index.Mov(index.Add(1));
			}
		}
	}

	return FALSE; // No prime



	/*
	index.Mov(1);
	while (index.Cmp(r) <= 0)
	{
		ret = ProductModualwithMontgomeryAlgo(ret,ret,n);

		if ((ret.Cmp(Temp1)==0)&&(last.Cmp(Temp1) !=0)&&(last.Cmp(Temp) != 0)) // ret =1 && last !=0 && last !=n-1
		{
			return TRUE;
		}

		index.Mov(index.Add(1));
	}

	if (ret.Cmp(Temp1) !=0) // ret !=1
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	*/
}

CBigInteger CRSAAlgo::mult_mod(CBigInteger A,CBigInteger B,CBigInteger N)
{
	// A*B mod N

	CBigInteger X;

	X.Mov(A);
	X.Mov(X.Mul(B));  // X = A*B;
	X.Mov(X.Mod(N));  // X = X % N;

	return X;
}

CBigInteger CRSAAlgo::pow_mod(CBigInteger a,CBigInteger b,CBigInteger n)
{
	// a^b mod n

	CBigInteger ans;
	CBigInteger Temp;

	ans.Mov(1);
	a.Mov(a.Mod(n));
	Temp.Mov(0);

	while(b.Cmp(Temp) != 0)  
	{
		if (b.CheckIsOddNumber()) // Is odd number
		{
			ans = mult_mod(ans,a,n);
		}

		a = mult_mod(a,a,n);
		b.Mov(b.Div(2));
	}

	return ans;
}

CBigInteger CRSAAlgo::GetRvalueforMontgomeryAlgo(CBigInteger n)
{
   CBigInteger r,Temp;

   r.m_nSign = 1;
   r.m_nLength = 1;
   r.Mov(1);

   Temp.Mov(r.Div(2));
   
   while(n.Cmp(Temp) >= 0)  // n >= r/2
   {
		r.Mov(r.Mul(2));
		Temp.Mov(r.Div(2));
		
		if (r.Cmp(n) > 0)  // r > n
		{
			if (CheckIsInterPrime(r,n))  // gcd(r,n) = 1
			{
				return r;
			}
		}
   }

   r.Mov(0);

   return r;
}

unsigned long CRSAAlgo::GetRbase2valueforMontgomeryAlgo(CBigInteger n)
{
	CBigInteger r,Temp;

	unsigned long index ;

	index = 0;
	r.m_nSign = 1;
	r.m_nLength = 1;
	r.Mov(1);

	Temp.Mov(r.Div(2));

	while(n.Cmp(Temp) >= 0)  // n >= r/2
	{
		r.Mov(r.Mul(2));
		index +=1;
		Temp.Mov(r.Div(2));

		if (r.Cmp(n) > 0)  // r > n
		{
			if (CheckIsInterPrime(r,n))  // gcd(r,n) = 1
			{
				return index;
			}
		}
	}

	index = 0;

	return index;
}

CBigInteger CRSAAlgo::GetMontogeryProduct(CBigInteger A,CBigInteger B,CBigInteger N,CBigInteger R,CBigInteger Ninv,unsigned long index)
{
	// S = Mon(A,B,N)=A*B*R^(-1) mod N
	CBigInteger S,T;
	CBigInteger Temp;

	/*
	CBigInteger Aplus,Bplus;
	Aplus.Mov(A.Mul(R));
	Aplus.Mov(Aplus.Mod(N)); // A`= A*R mod N

	Bplus.Mov(B.Mul(R));
	Bplus.Mov(Bplus.Mod(N)); // B`= B*R mod N

	T.Mov(Aplus.Mul(Bplus)); // T = A`*B`;
	*/

	T.Mov(A.Mul(B));  // T = A*B;

	// S = {T + [(T mod R)*N` mod R]*N} / R
	Temp.Mov(T.ShiftMod(index));//Temp.Mov(T.Mod(R));      
	Temp.Mov(Temp.Mul(Ninv));
	Temp.Mov(Temp.ShiftMod(index));//Temp.Mov(Temp.Mod(R));
	Temp.Mov(Temp.Mul(N));
	Temp.Mov(Temp.Add(T));
	S.Mov(Temp.ShiftRight(index));//S.Mov(Temp.Div(R));

	if (S.Cmp(N) >= 0)  // S >= N
	{
		S.Mov(S.Sub(N)); // S = S - N;
	}
	
	return S;
}

CBigInteger CRSAAlgo::ProductModualwithMontgomeryAlgo(CBigInteger A,CBigInteger B,CBigInteger N)
{
	// A*B mod N

	CBigInteger  S,FinalValue;
	CBigInteger Constant1;

	Constant1.m_nSign = 1;
	Constant1.m_nLength = 1;
	Constant1.Mov(1);

	CBigInteger R;
	CBigInteger Rinv;
	CBigInteger Ninv;

	unsigned long index;

	R = GetRvalueforMontgomeryAlgo(N); // Get R value
	index = GetRbase2valueforMontgomeryAlgo(N);// 2^index = R;

	N.m_nSign = 0;
	BOOL result = LinearEquationExeuclidean(R,N,Constant1,Rinv,Ninv); // R*Rinv - N*Ninv = 1;
	N.m_nSign = 1;

	CBigInteger Aplus,Bplus;

	Aplus.Mov(A.Mul(R));
	Aplus.Mov(Aplus.Mod(N)); // A`= A*R mod N

	Bplus.Mov(B.Mul(R));
	Bplus.Mov(Bplus.Mod(N)); // B`= B*R mod N

	S = GetMontogeryProduct(Aplus,Bplus,N,R,Ninv,index); // S= MonPro(A,B,N)=A`*B`*R^(-1) mod N

	FinalValue = GetMontogeryProduct(S,Constant1,N,R,Ninv,index); // Final=MonPro(S,1,N) = S*1*R^(-1) mod N

	return FinalValue;
}

CBigInteger CRSAAlgo::PowerModualwithMontgomeryAlgo(CBigInteger A,CBigInteger B,CBigInteger N)
{
	// A^B mod N

	CBigInteger Index;
	CBigInteger X;
	CBigInteger Constant0;
	Constant0.Mov(0);
	CBigInteger Constant1;

	Constant1.m_nSign = 1;
	Constant1.m_nLength = 1;
	Constant1.Mov(1);

	CBigInteger R;
	CBigInteger Rinv;
	CBigInteger Ninv;

	unsigned long index;

	// PreCalculate to get R,Rinv,Ninv
	R = GetRvalueforMontgomeryAlgo(N); // Get proper R value
	index = GetRbase2valueforMontgomeryAlgo(N);

	N.m_nSign = 0;
	BOOL result = LinearEquationExeuclidean(R,N,Constant1,Rinv,Ninv); // R*Rinv - N*Ninv = 1;
	N.m_nSign = 1;


	X.Mov(1);
	A.Mov(A.Mod(N));
	while(B.Cmp(Constant0) != 0)  
	{
		if (B.CheckIsOddNumber()) // Is odd number
		{
			X = ProductModualwithMontgomeryAlgoWithoutCalc(X,A,N,R,Ninv,index);
		}

		A = ProductModualwithMontgomeryAlgoWithoutCalc(A,A,N,R,Ninv,index);
		B.Mov(B.Div(2));
	}

	return X;
}	

CBigInteger CRSAAlgo::NewPowerModualwithMontgomeryAlgo(CBigInteger A,CBigInteger B,CBigInteger N)
{
	// A^B mod N

	CBigInteger Index;
	CBigInteger X;
	CBigInteger Constant0;
	Constant0.Mov(0);
	CBigInteger Constant1;

	Constant1.m_nSign = 1;
	Constant1.m_nLength = 1;
	Constant1.Mov(1);

	CBigInteger R;
	CBigInteger Rinv;
	CBigInteger Ninv;

	CBigInteger RRmodN;

	unsigned long index;

	// PreCalculate to get R,Rinv,Ninv
	R = GetRvalueforMontgomeryAlgo(N); // Get proper R value
	index = GetRbase2valueforMontgomeryAlgo(N); // 2^index = R;

	N.m_nSign = 0;
	BOOL result = LinearEquationExeuclidean(R,N,Constant1,Rinv,Ninv); // R*Rinv - N*Ninv = 1;
	N.m_nSign = 1;

	R.Mov(R.Mul(R));
	RRmodN.Mov(R.Mod(N)); // RR mod N value

    
	CBigInteger MessagePlus,Xtemp;
	MessagePlus = MontgomeryPro(A,RRmodN,N,R,Ninv,index);
	Xtemp.Mov(MessagePlus);

	//Find the first MSB
	
	unsigned int firstmsb;
	firstmsb = B.FindFirstMSB();

	int i;
	BOOL bTrue;

	for (i = firstmsb - 1 ;i >= 0;i--)
	{
		Xtemp = MontgomeryPro(Xtemp,Xtemp,N,R,Ninv,index);
		bTrue = B.IsNumber1at(B.m_nLength -1,i);
		if (bTrue)
		{
			Xtemp = MontgomeryPro(MessagePlus,Xtemp,N,R,Ninv,index);
		}
	}

	for (int k = B.m_nLength - 2; k>=0; k--)
	{
		for (int j = 31;j >= 0;j--)
		{
			Xtemp = MontgomeryPro(Xtemp,Xtemp,N,R,Ninv,index);
			bTrue = B.IsNumber1at(k,j);
			if (bTrue)
			{
				Xtemp = MontgomeryPro(MessagePlus,Xtemp,N,R,Ninv,index);
			}
		}
	}

	X = MontgomeryPro(Xtemp,Constant1,N,R,Ninv,index);
	
	return X;
}	

CBigInteger CRSAAlgo::MontgomeryPro(CBigInteger A, CBigInteger B,CBigInteger N,CBigInteger R,CBigInteger Ninv,unsigned long index)
{
	CBigInteger S,T;
	CBigInteger Temp;

	T.Mov(A.Mul(B));  // T = A*B;

	// S = {T + [(T *N` mod R]*N} / R    
	Temp.Mov(T.Mul(Ninv));
	Temp.Mov(Temp.ShiftMod(index));//Temp.Mov(Temp.Mod(R));
	Temp.Mov(Temp.Mul(N));
	Temp.Mov(Temp.Add(T));
	S.Mov(Temp.ShiftRight(index));//S.Mov(Temp.Div(R));

	if (S.Cmp(N) >= 0)  // S >= N
	{
		S.Mov(S.Sub(N)); // S = S - N;
	}
	
	return S;
}

CBigInteger CRSAAlgo::ProductModualwithMontgomeryAlgoWithoutCalc(CBigInteger A,CBigInteger B,CBigInteger N,CBigInteger R,CBigInteger Ninv,unsigned long index)
{
	// A*B mod N

	CBigInteger  S,FinalValue;
	CBigInteger Constant1;

	Constant1.m_nSign = 1;
	Constant1.m_nLength = 1;
	Constant1.Mov(1);

	CBigInteger Aplus,Bplus;

	Aplus.Mov(A.Mul(R));
	Aplus.Mov(Aplus.Mod(N)); // A`= A*R mod N

	Bplus.Mov(B.Mul(R));
	Bplus.Mov(Bplus.Mod(N)); // B`= B*R mod N

	S = GetMontogeryProduct(Aplus,Bplus,N,R,Ninv,index); // S= MonPro(A,B,N)=A`*B`*R^(-1) mod N

	FinalValue = GetMontogeryProduct(S,Constant1,N,R,Ninv,index); // Final=MonPro(S,1,N) = S*1*R^(-1) mod N

	return FinalValue;
}