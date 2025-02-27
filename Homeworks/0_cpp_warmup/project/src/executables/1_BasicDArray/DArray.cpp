#include <iostream>
#include <cassert>
#include "DArray.h"
// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) 
	: m_pData (new double[nSize]),  m_nSize (nSize)
{
	for(int i=0; i<nSize; i++){
		m_pData[i] = dValue;
	}
}

DArray::DArray(const DArray& arr) 
	: m_pData( new double[arr.GetSize()]), m_nSize (arr.GetSize())
{
	for(int i=0; i<m_nSize; i++){
		m_pData[i] = arr.m_pData[i];
	}
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	std::cout << "size=" << GetSize() << ":";

	for(int i = 0; i<m_nSize; i++){
		std::cout << "" << GetAt(i)<< ",";
	}
	std::cout << std::endl;
}

// initilize the array
void DArray::Init() {
	m_pData = nullptr;
	m_nSize = 0;
}

// free the array
void DArray::Free() {
	delete[] m_pData;
	m_pData=nullptr;
	m_nSize=0;
}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize; // you should return a correct value
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if(m_nSize == nSize) return;
	
	double* pData = new double[nSize];
	int copyNum = m_nSize < nSize ?  m_nSize : nSize;
	for(int i=0; i < copyNum; i++){
		pData[i] = m_pData[i];
	}
	for(int i=copyNum; i<nSize; i++){
		pData[i]= 0;
	}

	delete[] m_pData;
	m_nSize = nSize;
	m_pData = pData;
	pData = nullptr;

	return;
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	assert(nIndex>=0 && nIndex<m_nSize);
	return m_pData[nIndex]; 
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	assert(nIndex>=0 && nIndex<m_nSize);
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
double& DArray::operator[](int nIndex) {
	assert(nIndex>=0 && nIndex<m_nSize);
	return m_pData[nIndex];
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	assert(nIndex>=0 && nIndex<m_nSize);
	return m_pData[nIndex];
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	SetSize(m_nSize+1);
	m_pData[m_nSize-1] = dValue;
	return;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	assert(nIndex>=0 && nIndex<m_nSize);
	double* tmpPointer = new double[m_nSize-1];
	for(int i=0; i<nIndex; i++){
		tmpPointer[i] = m_pData[i];
	}
	for(int i=nIndex; i<m_nSize-1; i++){
		tmpPointer[i] = m_pData[i+1];
	}
	delete[] m_pData;
	m_pData=tmpPointer;
	m_nSize--;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	assert(nIndex>=0 && nIndex<=m_nSize);
	PushBack(dValue);
	for(int i=m_nSize-1; i>nIndex && i>=1; i--){
		double tmp = m_pData[i-1];
		m_pData[i-1] = m_pData[i];
		m_pData[i] = tmp;
		//Print();	
	}
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	delete[] m_pData;
	m_nSize = arr.m_nSize;
	m_pData = new double[m_nSize];

	for (int i = 0; i < m_nSize; i++)
		m_pData[i] = arr[i];

	return *this;
}
