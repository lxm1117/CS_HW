//********************************************************
//File:read_data.cc
//Author: David W. Juedes
//
//Purpose: This example program reads the data for homework #2
// It reads m q
// and then, a n x n matrix of integers 
// This code is not elegant, but it is sufficient for the
// purpose of this class.
//***********************************************************
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;


//***************************************************************
// Function read_q(istream &in) 
// Parameters: istream in --- 
// Return value: q
// Purpose: Read the value q (the modulus for the assigment)
//****************************************************************
int read_q(istream &in) {
  int q;
  in >> q;
  return q;
}
//***************************************************************
// Function read_m(istream &in) 
// Parameters: istream in --- 
// Return value: m
// Purpose: Read the value m (the number of values in the product)
//****************************************************************
int read_m(istream &in) {
  int m;
  in >> m;
  return m;
}
//***************************************************************
// Function read_M(istream &in) 
// Parameters: istream in --- 
// Return value: vector<vector<int> > M
// Purpose: Read the value M, the matrix, which exists to the end of the 
// input.
// Assumption: each row of the matrix is stored on a line by itself.
//****************************************************************
vector<vector<int> > read_M(istream &in) {
  string line;
  vector<vector<int> > M;
  while (!in.eof()) {
    getline(in,line);
    if (!in.fail()) {
      istringstream in1(line);
      vector<int> row;
      while (!in1.eof()) {
	int x;
	in1 >> x;
	if (!in1.fail()) {
	  row.push_back(x);
	}
      }
      M.push_back(row);
    }
  }

  return M;
}
 

//shoud I use input of M with a pointer as in C?
int mul_mod(int row, int col, int m, int q, int max_q, vector<vector<int> > M){

	int k1=1;
	int k2=1;
	int k3=1;
	int k4=1;
	//horizontal, t: col num, consider the right border
	if (col<=M.size()-m) {
		for(int t=col;t<col+m; t++){
		k1*=(M[row][t]%q);	
		}
	}

	//vertical, s: row num, consider the bottom border
	if(row<=M.size()-m){
		for(int s=row;s<row+m;s++){
			k2*=(M[s][col]%q);		
		}
	}

	//diagnoal, s: row num, t: col, consider both right and bottom border
	if(row<=M.size()-m && col<=M.size()) {
		for(int s=row, t=col; s<row+m && t<col+m; s++, t++){
			k3*=(M[s][t]%q);
		}
	}

	//antidiagonal, s: row num, t: col, consider both left and bottom border
	if(row<=M.size()-m && col>=m){
		if(int s=row, t=col;s<row+m;s++,t--){
			k4*=(M[s][t]%q);
		}
	}
	
	k1=k1%q;
	k2=k2%q;
	k3=k3%q;
	k4=k4%q;	 
	if(k1>max_q) { max_q=k1;}
	if(k2>max_q) { max_q=k2;}
	if(k3>max_q) { max_q=k3;}
	if(k4>max_q) { max_q=k4;}
	cout << max_q;
	return max_q;
}
  
int main() {
  int q;
  int m;
  int max_q;

  vector<vector<int> > M;
  m = read_m(cin);
  q = read_q(cin);
  string line;
  getline(cin,line);
  assert(line == "");

  M = read_M(cin);
  cout << M.size() << endl;
  cout << M[0][0] << endl;  
  max_q=0;	
 // for(int i=0;i<M.size();i++){
	max_q=mul_mod(0,0,m,q,max_q, M);	
 //}
  return max_q;
}

