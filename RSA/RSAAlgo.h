#pragma once

#include "BigInteger.h"

class CRSAAlgo
{
public:
	unsigned int m_unFilterTable[100];

public:
	CRSAAlgo(void);
	~CRSAAlgo(void);
public:
	CBigInteger GenBigRandomNumber(int bitsize);
	BOOL RoughCheckIsBigPrime(CBigInteger X);
	BOOL CheckIsBigPrimewithMillerRabin(CBigInteger X);
	BOOL MillerRabinCheck(CBigInteger a,CBigInteger n,CBigInteger m,CBigInteger r);
	CBigInteger mult_mod(CBigInteger A,CBigInteger B,CBigInteger N);
	CBigInteger pow_mod(CBigInteger a,CBigInteger b,CBigInteger n);

	BOOL CheckIsBigPrimewithMillerRabinWithMontgomery(CBigInteger X);
	BOOL MillerRabinCheckWithMontgomery(CBigInteger a,CBigInteger n,CBigInteger m,CBigInteger r);

	BOOL CheckIsInterPrime(CBigInteger X, CBigInteger Y); // Check gcd(X,Y) = 1
	CBigInteger ExeuclideanGCD(CBigInteger& A, CBigInteger& B, CBigInteger& X,CBigInteger& Y);
	BOOL LinearEquationExeuclidean(CBigInteger& A, CBigInteger& B, CBigInteger& C,CBigInteger& X,CBigInteger& Y);
	CBigInteger RSAEP(CBigInteger n, CBigInteger e, CBigInteger m); 
	CBigInteger RSADPwithType1privateKey(CBigInteger n, CBigInteger d, CBigInteger c);
	CBigInteger RSADPwithType2privateKey(CBigInteger p, CBigInteger q, CBigInteger dP,CBigInteger dQ,CBigInteger qInv, CBigInteger c);


	CBigInteger GetRvalueforMontgomeryAlgo(CBigInteger n);
	unsigned long GetRbase2valueforMontgomeryAlgo(CBigInteger n);
	CBigInteger GetMontogeryProduct(CBigInteger A,CBigInteger B,CBigInteger N,CBigInteger R,CBigInteger Ninv,unsigned long index);
	CBigInteger ProductModualwithMontgomeryAlgo(CBigInteger A,CBigInteger B,CBigInteger N);

	CBigInteger ProductModualwithMontgomeryAlgoWithoutCalc(CBigInteger A,CBigInteger B,CBigInteger N,CBigInteger R,CBigInteger Ninv,unsigned long index);
	CBigInteger PowerModualwithMontgomeryAlgo(CBigInteger A,CBigInteger B,CBigInteger N);// A^B mod N

	CBigInteger NewPowerModualwithMontgomeryAlgo(CBigInteger A,CBigInteger B,CBigInteger N);
	CBigInteger MontgomeryPro(CBigInteger A, CBigInteger B,CBigInteger N,CBigInteger R,CBigInteger Ninv,unsigned long index);
};
