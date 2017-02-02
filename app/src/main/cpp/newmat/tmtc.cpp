/// \ingroup newmat
///@{

/// \file tmtc.cpp
/// Part of matrix library test program.


//#define WANT_STREAM


#include "include.h"
#include "newmatap.h"

#include "tmt.h"

#ifdef use_namespace
using namespace NEWMAT;
#endif

// test SP_eq with Generic Matrices
void test_SP_eq(const GenericMatrix& GX, const GenericMatrix& GY)
{
   GenericMatrix GZ = SP(GX, GY); GenericMatrix GX1 = GX;
   GX1.SP_eq(GY); Matrix Z = GX1 - GZ; Print(Z);
   GX1 = GX; GX1.SP_eq(2 * GY); Z = GX1 - 2 * GZ; Print(Z);
   GX1 = GX; GX1.SP_eq(GX1); Z = GX1 - SP(GX,GX); Print(Z);
}


void trymatc()
{
//   cout << "\nTwelfth test of Matrix package\n";
   Tracer et("Twelfth test of Matrix package");
   Tracer::PrintTrace();
   DiagonalMatrix D(15); D=1.5;
   Matrix A(15,15);
   int i,j;
   for (i=1;i<=15;i++) for (j=1;j<=15;j++) A(i,j)=i*i+j-150;
   { A = A + D; }
   ColumnVector B(15);
   for (i=1;i<=15;i++) B(i)=i+i*i-150.0;
   {
      Tracer et1("Stage 1");
      ColumnVector B1=B;
      B=(A*2.0).i() * B1;
      Matrix X = A*B-B1/2.0;
      Clean(X, 0.000000001); Print(X);
      A.ReSize(3,5);
      for (i=1; i<=3; i++) for (j=1; j<=5; j++) A(i,j) = i+100*j;

      B = A.AsColumn()+10000;
      RowVector R = (A+10000).AsColumn().t();
      Print( RowVector(R-B.t()) );
   }

   {
      Tracer et1("Stage 2");
      B = A.AsColumn()+10000;
      Matrix XR = (A+10000).AsMatrix(15,1).t();
      Print( RowVector(XR-B.t()) );
   }

   {
      Tracer et1("Stage 3");
      B = (A.AsMatrix(15,1)+A.AsColumn())/2.0+10000;
      Matrix MR = (A+10000).AsColumn().t();
      Print( RowVector(MR-B.t()) );

      B = (A.AsMatrix(15,1)+A.AsColumn())/2.0;
      MR = A.AsColumn().t();
      Print( RowVector(MR-B.t()) );
   }

   {
      Tracer et1("Stage 4");
      B = (A.AsMatrix(15,1)+A.AsColumn())/2.0;
      RowVector R = A.AsColumn().t();
      Print( RowVector(R-B.t()) );
   }

   {
      Tracer et1("Stage 5");
      RowVector R = (A.AsColumn()-5000).t();
      B = ((R.t()+10000) - A.AsColumn())-5000;
      Print( RowVector(B.t()) );
   }

   {
      Tracer et1("Stage 6");
      B = A.AsColumn(); ColumnVector B1 = (A+10000).AsColumn() - 10000;
      Print(ColumnVector(B1-B));
   }

   {
      Tracer et1("Stage 7");
      Matrix X = B.AsMatrix(3,5); Print(Matrix(X-A));
      for (i=1; i<=3; i++) for (j=1; j<=5; j++) B(5*(i-1)+j) -= i+100*j;
      Print(B);
   }

   {
      Tracer et1("Stage 8");
      A.ReSize(7,7); D.ReSize(7);
      for (i=1; i<=7; i++) for (j=1; j<=7; j++) A(i,j) = i*j*j;
      for (i=1; i<=7; i++) D(i,i) = i;
      UpperTriangularMatrix U; U << A;
      Matrix X = A; for (i=1; i<=7; i++) X(i,i) = i;
      A.Inject(D); Print(Matrix(X-A));
      X = U; U.Inject(D); A = U; for (i=1; i<=7; i++) X(i,i) = i;
      Print(Matrix(X-A));
   }

   {
      Tracer et1("Stage 9");
      A.ReSize(7,5);
      for (i=1; i<=7; i++) for (j=1; j<=5; j++) A(i,j) = i+100*j;
      Matrix Y = A; Y = Y - ((const Matrix&)A); Print(Y);
      Matrix X = A;
      Y = A; Y = ((const Matrix&)X) - A; Print(Y); Y = 0.0;
      Y = ((const Matrix&)X) - ((const Matrix&)A); Print(Y);
   }

   {
      Tracer et1("Stage 10");
      // some tests on submatrices
      UpperTriangularMatrix U(20);
      for (i=1; i<=20; i++) for (j=i; j<=20; j++) U(i,j)=100 * i + j;
      UpperTriangularMatrix V = U.SymSubMatrix(1,5);
      UpperTriangularMatrix U1 = U;
      U1.SubMatrix(4,8,5,9) /= 2;
      U1.SubMatrix(4,8,5,9) += 388 * V;
      U1.SubMatrix(4,8,5,9) *= 2;
      U1.SubMatrix(4,8,5,9) += V;
      U1 -= U; UpperTriangularMatrix U2 = U1;
      U1 << U1.SubMatrix(4,8,5,9);
      U2.SubMatrix(4,8,5,9) -= U1; Print(U2);
      U1 -= (777*V); Print(U1);

      U1 = U; U1.SubMatrix(4,8,5,9) -= U.SymSubMatrix(1,5);
      U1 -= U;  U2 = U1; U1 << U1.SubMatrix(4,8,5,9);
      U2.SubMatrix(4,8,5,9) -= U1; Print(U2);
      U1 += V; Print(U1);

      U1 = U;
      U1.SubMatrix(3,10,15,19) += 29;
      U1 -= U;
      Matrix X = U1.SubMatrix(3,10,15,19); X -= 29; Print(X);
      U1.SubMatrix(3,10,15,19) *= 0; Print(U1);

      LowerTriangularMatrix L = U.t();
      LowerTriangularMatrix M = L.SymSubMatrix(1,5);
      LowerTriangularMatrix L1 = L;
      L1.SubMatrix(5,9,4,8) /= 2;
      L1.SubMatrix(5,9,4,8) += 388 * M;
      L1.SubMatrix(5,9,4,8) *= 2;
      L1.SubMatrix(5,9,4,8) += M;
      L1 -= L; LowerTriangularMatrix L2 = L1;
      L1 << L1.SubMatrix(5,9,4,8);
      L2.SubMatrix(5,9,4,8) -= L1; Print(L2);
      L1 -= (777*M); Print(L1);

      L1 = L; L1.SubMatrix(5,9,4,8) -= L.SymSubMatrix(1,5);
      L1 -= L; L2 =L1; L1 << L1.SubMatrix(5,9,4,8);
      L2.SubMatrix(5,9,4,8) -= L1; Print(L2);
      L1 += M; Print(L1);

      L1 = L;
      L1.SubMatrix(15,19,3,10) -= 29;
      L1 -= L;
      X = L1.SubMatrix(15,19,3,10); X += 29; Print(X);
      L1.SubMatrix(15,19,3,10) *= 0; Print(L1);
   }

   {
      Tracer et1("Stage 11");
      // more tests on submatrices
      Matrix M(20,30);
      for (i=1; i<=20; i++) for (j=1; j<=30; j++) M(i,j)=100 * i + j;
      Matrix M1 = M;

      for (j=1; j<=30; j++)
         { ColumnVector CV = 3 * M1.Column(j); M.Column(j) += CV; }
      for (i=1; i<=20; i++)
         { RowVector RV = 5 * M1.Row(i); M.Row(i) -= RV; }

      M += M1; Print(M);
 
   }

   {
      Tracer et1("Stage 12");
      // more tests on Release
      Matrix M(20,30);
      for (i=1; i<=20; i++) for (j=1; j<=30; j++) M(i,j)=100 * i + j;
      Matrix M1 = M;
      M.Release();
      Matrix M2 = M;
      Matrix X = M;   Print(X);
      X = M1 - M2;    Print(X);

#ifndef DONT_DO_NRIC
      nricMatrix N = M1;
      nricMatrix N1 = N;
      N.Release();
      nricMatrix N2 = N;
      nricMatrix Y = N;   Print(Y);
      Y = N1 - N2;        Print(Y);
      
      N = M1 / 2; N1 = N * 2; N.Release(); N2 = N * 2; Y = N; Print(N);
      Y = (N1 - M1) | (N2 - M1); Print(Y);
#endif

   }
   
   {
      Tracer et("Stage 13");
      // test sum of squares of rows or columns
      MultWithCarry mwc;
      DiagonalMatrix DM; Matrix X;
      // rectangular matrix
      Matrix A(20, 15);
      FillWithValues(mwc, A);
      // sum of squares of rows
      DM << A * A.t();
      ColumnVector CV = A.sum_square_rows();
      X = CV - DM.AsColumn(); Clean(X, 0.000000001); Print(X);
      DM << A.t() * A;
      RowVector RV = A.sum_square_columns();
      X = RV - DM.AsRow(); Clean(X, 0.000000001); Print(X);
      X = RV - A.t().sum_square_rows().t(); Clean(X, 0.000000001); Print(X);
      X = CV - A.t().sum_square_columns().t(); Clean(X, 0.000000001); Print(X);
      // UpperTriangularMatrix
      A.ReSize(17,17); FillWithValues(mwc, A);
      UpperTriangularMatrix UT; UT << A;
      Matrix A1 = UT;
      X = UT.sum_square_rows() - A1.sum_square_rows(); Clean(X, 0.00000000000001); Print(X);
      X = UT.sum_square_columns() - A1.sum_square_columns(); Clean(X, 0.00000000000001); Print(X);
      // LowerTriangularMatrix
      LowerTriangularMatrix LT; LT << A;
      A1 = LT;
      X = LT.sum_square_rows() - A1.sum_square_rows(); Clean(X, 0.00000000000001); Print(X);
      X = LT.sum_square_columns() - A1.sum_square_columns(); Clean(X, 0.00000000000001); Print(X);
      // SymmetricMatrix
      SymmetricMatrix SM; SM << A;
      A1 = SM;
      X = SM.sum_square_rows() - A1.sum_square_rows(); Clean(X, 0.00000000000001); Print(X);
      X = SM.sum_square_columns() - A1.sum_square_columns(); Clean(X, 0.00000000000001); Print(X);
      // DiagonalMatrix
      DM << A;
      A1 = DM;
      X = DM.sum_square_rows() - A1.sum_square_rows(); Clean(X, 0.00000000000001); Print(X);
      X = DM.sum_square_columns() - A1.sum_square_columns(); Clean(X, 0.00000000000001); Print(X);
      // BandMatrix
      BandMatrix BM(17, 3, 5); BM.Inject(A);
      A1 = BM;
      X = BM.sum_square_rows() - A1.sum_square_rows(); Clean(X, 0.00000000000001); Print(X);
      X = BM.sum_square_columns() - A1.sum_square_columns(); Clean(X, 0.00000000000001); Print(X);
      // SymmetricBandMatrix
      SymmetricBandMatrix SBM(17, 4); SBM.Inject(A);
      A1 = SBM;
      X = SBM.sum_square_rows() - A1.sum_square_rows(); Clean(X, 0.00000000000001); Print(X);
      X = SBM.sum_square_columns() - A1.sum_square_columns(); Clean(X, 0.00000000000001); Print(X);
      // IdentityMatrix
      IdentityMatrix IM(29);
      X = IM.sum_square_rows() - 1; Clean(X, 0.00000000000001); Print(X);
      X = IM.sum_square_columns() - 1; Clean(X, 0.00000000000001); Print(X);
      // Matrix with zero rows
      A1.ReSize(0,10);
      X.ReSize(1,10); X = 0; X -= A1.sum_square_columns(); Clean(X, 0.00000000000001); Print(X);
      X.ReSize(0,1); X -= A1.sum_square_rows(); Clean(X, 0.00000000000001); Print(X);
      // Matrix with zero columns
      A1.ReSize(10,0);
      X.ReSize(10,1); X = 0; X -= A1.sum_square_rows(); Clean(X, 0.00000000000001); Print(X);
      X.ReSize(1,0); X -= A1.sum_square_columns(); Clean(X, 0.00000000000001); Print(X);
      
   }
   
   {
      Tracer et("Stage 14");
      // test extend orthonormal
      MultWithCarry mwc;
      Matrix A(20,5); FillWithValues(mwc, A);
      // Orthonormalise
      UpperTriangularMatrix R;
      Matrix A_old = A;
      QRZ(A,R);
      // Check decomposition
      Matrix X = A * R - A_old; Clean(X, 0.000000001); Print(X);
      // Check orthogonality
      X = A.t() * A - IdentityMatrix(5);
      Clean(X, 0.000000001); Print(X);
      // Try orthonality extend 
      SquareMatrix A1(20);
      A1.Columns(1,5) = A;
      extend_orthonormal(A1,5);
      // check columns unchanged
      X = A - A1.Columns(1,5); Print(X);
      // Check orthogonality
      X = A1.t() * A1 - IdentityMatrix(20);
      Clean(X, 0.000000001); Print(X); 
      X = A1 * A1.t() - IdentityMatrix(20);
      Clean(X, 0.000000001); Print(X);
      // Test with smaller number of columns 
      Matrix A2(20,15);
      A2.Columns(1,5) = A;
      extend_orthonormal(A2,5);
      // check columns unchanged
      X = A - A2.Columns(1,5); Print(X);
      // Check orthogonality
      X = A2.t() * A2 - IdentityMatrix(15);
      Clean(X, 0.000000001); Print(X);
      // check it works with no columns to start with
      A2.ReSize(100,100);
      extend_orthonormal(A2,0);
      // Check orthogonality
      X = A2.t() * A2 - IdentityMatrix(100);
      Clean(X, 0.000000001); Print(X);
      X = A2 * A2.t() - IdentityMatrix(100);
      Clean(X, 0.000000001); Print(X);
   }

   {
      Tracer et("Stage 15");
      // test extend orthonormal for SVD
      MultWithCarry mwc;
      Matrix A(15,40); FillWithValues(mwc, A);
      Matrix U, V; DiagonalMatrix D;
      SVD(A.t(),D,V,U);
      Matrix VE(40,40); VE.columns(1,15) = V;
      extend_orthonormal(VE,15);
      Matrix DE(15,40); DE = 0; DE.columns(1,15) = D;
      Matrix B = U * DE * VE.t();
      B -= A;
      Clean(B, 0.000000001); Print(B);
   }
      
   {
      Tracer et("Stage 16");
      // test sum of rows or columns
      MultWithCarry mwc;
      ColumnVector CVX; Matrix X;
      // rectangular matrix
      Matrix A(20, 15);
      FillWithValues(mwc, A);
      // sum of rows
      ColumnVector Ones(15); Ones = 1;
      CVX = A * Ones;
      ColumnVector CV = A.sum_rows();
      X = CV - CVX; Clean(X, 0.000000001); Print(X);
      Ones.resize(20); Ones = 1;
      CVX << A.t() * Ones;
      RowVector RV = A.sum_columns();
      X = RV - CVX.AsRow(); Clean(X, 0.000000001); Print(X);
      X = RV - A.t().sum_rows().t(); Clean(X, 0.000000001); Print(X);
      X = CV - A.t().sum_columns().t(); Clean(X, 0.000000001); Print(X);
      // UpperTriangularMatrix
      A.ReSize(17,17); FillWithValues(mwc, A);
      UpperTriangularMatrix UT; UT << A;
      Matrix A1 = UT;
      X = UT.sum_rows() - A1.sum_rows(); Print(X);
      X = UT.sum_columns() - A1.sum_columns(); Print(X);
      // LowerTriangularMatrix
      LowerTriangularMatrix LT; LT << A;
      A1 = LT;
      X = LT.sum_rows() - A1.sum_rows(); Print(X);
      X = LT.sum_columns() - A1.sum_columns(); Print(X);
      // SymmetricMatrix
      SymmetricMatrix SM; SM << A;
      A1 = SM;
      X = SM.sum_rows() - A1.sum_rows(); Print(X);
      X = SM.sum_columns() - A1.sum_columns(); Print(X);
      // DiagonalMatrix
      DiagonalMatrix DM; DM << A;
      A1 = DM;
      X = DM.sum_rows() - A1.sum_rows(); Print(X);
      X = DM.sum_columns() - A1.sum_columns(); Print(X);
      // BandMatrix
      BandMatrix BM(17, 3, 5); BM.Inject(A);
      A1 = BM;
      X = BM.sum_rows() - A1.sum_rows(); Print(X);
      X = BM.sum_columns() - A1.sum_columns(); Print(X);
      // SymmetricBandMatrix
      SymmetricBandMatrix SBM(17, 4); SBM.Inject(A);
      A1 = SBM;
      X = SBM.sum_rows() - A1.sum_rows(); Print(X);
      X = SBM.sum_columns() - A1.sum_columns(); Print(X);
      // IdentityMatrix
      IdentityMatrix IM(29);
      X = IM.sum_rows() - 1; Print(X);
      X = IM.sum_columns() - 1; Print(X);
      // Matrix with zero rows
      A1.ReSize(0,10);
      X.ReSize(1,10); X = 0; X -= A1.sum_columns(); Print(X);
      X.ReSize(0,1); X -= A1.sum_rows(); Print(X);
      // Matrix with zero columns
      A1.ReSize(10,0);
      X.ReSize(10,1); X = 0; X -= A1.sum_rows(); Print(X);
      X.ReSize(1,0); X -= A1.sum_columns(); Print(X);
      
   }
   
   {
      Tracer et("Stage 17");
      // SP_eq on submatrices
      MultWithCarry mwc;
      Matrix A(37, 23); Matrix B(17,11);
      FillWithValues(mwc, A); FillWithValues(mwc, B);
      Matrix X = A; X.submatrix(5,21,3,13).SP_eq(B);
      Matrix Y = A; Y.submatrix(5,21,3,13) = SP(Y.submatrix(5,21,3,13),B);
      Y -= X; Print(Y);
      
      UpperTriangularMatrix UT(33);
      FillWithValues(mwc, UT);
      UpperTriangularMatrix UTX = UT;
      UTX.submatrix(5,21,3,13).SP_eq(B);
      Y = UT; Y.submatrix(5,21,3,13) = SP(Y.submatrix(5,21,3,13),B);
      Y -= UTX; Print(Y);
      
      UT.resize(10);
      FillWithValues(mwc, UT);
      X = A; X.submatrix(5,14,3,12).SP_eq(UT);
      Y = A; Y.submatrix(5,14,3,12) = SP(Y.submatrix(5,14,3,12),UT);
      Y -= X; Print(Y);
      
      SymmetricMatrix SM(30), SM1(10);
      FillWithValues(mwc, SM); FillWithValues(mwc, SM1);
      SymmetricMatrix SMX = SM;
      // This doesn't work - gets caught as illegal conversion
      //SMX.sym_submatrix(5,14) += SM1;
      //Y = SM; Y.submatrix(5,14,5,14) = Y.submatrix(5,14,5,14) + SM1;
      //Y -= SMX; Print(Y);
      
      SMX = SM;
      SMX.submatrix(5,14,5,14).SP_eq(SM1);
      Y = SM; Y.submatrix(5,14,5,14) = SP(Y.submatrix(5,14,5,14),SM1);
      Y -= SMX; Print(Y);
      
      BandMatrix BM(50, 10, 12);
      X.resize(50,50); FillWithValues(mwc, X);
      BM.inject(X); X = BM;
      B.resize(7, 10); FillWithValues(mwc, B);
      BM.submatrix(2,8,4,13) += B;
      X.submatrix(2,8,4,13) = X.submatrix(2,8,4,13) + B;
      X -= BM; Print(X);

      X.resize(50,50); FillWithValues(mwc, X);
      BM.inject(X); X = BM;
      B.resize(7, 10); FillWithValues(mwc, B);
      BM.submatrix(2,8,4,13).SP_eq(B);
      X.submatrix(2,8,4,13) = SP(X.submatrix(2,8,4,13), B);
      X -= BM; Print(X);
      
      X.resize(50,50); FillWithValues(mwc, X);
      BM.inject(X); X = BM;
      B.resize(21, 23); FillWithValues(mwc, B);
      BM.submatrix(2,22,4,26).SP_eq(B);
      X.submatrix(2,22,4,26) = SP(X.submatrix(2,22,4,26), B);
      X -= BM; Print(X);
      
   }
   
   {   
      Tracer et("Stage 18");
      // += real on submatrices of symmetric matrices
      // these don't work either
      //MultWithCarry mwc;
      //SymmetricMatrix SM(30);
      //FillWithValues(mwc, SM);
      //SymmetricMatrix SMX = SM;
      //SMX.sym_submatrix(7,11) += 5;
      //Matrix X = SM; X.sym_submatrix(7,11) += 5;
      //X -= SMX; Print(X);
      
   }
   
   {
      Tracer et("Stage 19");
      // SQ_eq on matrices
      MultWithCarry mwc;
      
      Matrix X(10,13), Y(10,13);
      FillWithValues(mwc, X); FillWithValues(mwc, Y);
      Matrix Z = X; Z.SP_eq(Y);
      Z -= SP(X, Y); Print(Z);
      
      Z = X; Z.SP_eq(2 * Y);
      Z -= 2 * SP(X, Y); Print(Z);
      
      Z = X; Z.SP_eq(Z);
      Z -= SP(X, X); Print(Z);
      
      GenericMatrix GX = X, GY = Y; test_SP_eq(GX, GY); test_SP_eq(GX, GX);
      
      X.resize(17,17); Y.resize(17,17);
      FillWithValues(mwc, X); FillWithValues(mwc, Y);
      UpperTriangularMatrix UT; UT << Y;
      LowerTriangularMatrix LT; LT << Y;
      DiagonalMatrix D; D << Y;
      Matrix ZUT = X; ZUT.SP_eq(UT);
      Matrix ZLT = X; ZLT.SP_eq(LT);
      Matrix ZD = X; ZD.SP_eq(D);
      Z = ZUT + ZLT - ZD - SP(X, Y);
      Clean(Z, 0.000000001); Print(Z);

      UpperTriangularMatrix UX(19), UY(19);
      FillWithValues(mwc, UX); FillWithValues(mwc, UY);
      
      GX = UX; GY = UY; test_SP_eq(GX, GY); test_SP_eq(GX, GY.t());

      UpperTriangularMatrix UZ = UX; UZ.SP_eq(UY);
      UZ -= SP(UX, UY); Print(UZ);
      
      UZ = UX; UZ.SP_eq(2 * UY);
      UZ -= 2 * SP(UX, UY); Print(UZ);
      
      UT << UY; LT << UY; D << UY;
      UpperTriangularMatrix UZUT = UX; UZUT.SP_eq(UT);
      UpperTriangularMatrix UZLT = UX; UZLT.SP_eq(LT);
      UpperTriangularMatrix UZD = UX; UZD.SP_eq(D);
      Z = UZUT + UZLT - UZD - SP(UX, UY);
      Clean(Z, 0.000000001); Print(Z);
      
      SymmetricMatrix SM(13), SM1(13), SMX, SM2;
      FillWithValues(mwc, SM); FillWithValues(mwc, SM1);
      SMX = SP(SM, SM1); SM2 = SM;
      SM2.SP_eq(SM1); SM2 -= SMX; Print(SM2);
      GX = SM; GY = SM1; test_SP_eq(GX, GY);
      
      X.resize(13,13); FillWithValues(mwc, X);
      Z = SP(X,SM); SM2 = SM;
      X.SP_eq(SM); X -= Z; Print(X);

      FillWithValues(mwc, X);
      GX = X; GY = SM; test_SP_eq(GX, GY);
      GX = SM; GY = X; test_SP_eq(GX, GY);
      
      BandMatrix BMX(13, 5,9); BMX.inject(X);
      SymmetricBandMatrix SBM(13,6); SBM.inject(SM);
      GX = BMX; GY = SBM; test_SP_eq(GX, GY);
      GX = SBM; GY = BMX; test_SP_eq(GX, GY);
      BandMatrix BMX1 = BMX; BMX1.SP_eq(SBM); Z = BMX1 - SP(BMX,SBM); Print(Z);
      BandMatrix BMX2 = SBM;
      GX = BMX; GY = BMX2; test_SP_eq(GX, GY);
      BMX1 = BMX; BMX1.SP_eq(BMX2); Z = BMX1 - SP(BMX,BMX2); Print(Z);
      
      
   }
   
 

//   cout << "\nEnd of twelfth test\n";
}


///@}
