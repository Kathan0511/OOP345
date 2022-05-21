//==============================================
//Name: Kathan Patel           
//Student ID: 148609191       
//Email: kjpatel30@myseneca.ca            
//Section: NEE        
//Date: 23/01/2022               
//==============================================


//I have done mostly all the coding by myselfand took some help for understanding some scopes from
//my personal tutor only copied the code that my professor provided to complete my workshopsand assignments.  
// (can provide tutor details upon request.)


#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <string>
#include "foodorder.h"


using namespace std;
double g_taxrate;
double g_dailydiscount;


namespace sdds
{
	FoodOrder::FoodOrder() {
		//Default constructor
	}

	istream& FoodOrder::read(istream& istr) {
		char Special = ' ';
		if (!istr.fail()) {
			istr.get(CxName, 10, ',');
			istr.ignore();
			getline(istr, OrderDesc, ',');
			istr >> Total_Price;
			istr.ignore();
			istr >> Special;
			if (Special == 'Y') {
				theSpecialPrice = true;
			}
			else {
				theSpecialPrice = false;
			}
		}
		return istr;
	}

	void FoodOrder::display() {
		static int Time = 1;
		double Foodprice = Total_Price * g_taxrate + Total_Price;
		if (CxName[0] != '\0') {
			cout.width(2);
			cout.setf(ios::left);
			cout << Time;
			cout << ". ";
			cout.width(10);
			cout << CxName;
			cout << "|";
			cout.width(25);
			cout << OrderDesc;
			cout << "|";
			cout.width(12);
			cout.precision(2);
			cout.setf(ios::fixed);
			cout << Foodprice;
			cout.unsetf(ios::fixed);
			cout << "|";
			cout.unsetf(ios::left);
			cout.setf(ios::right);
			cout.width(13);
			if (theSpecialPrice) {
				cout.precision(2);
				cout.setf(ios::fixed);
				cout << Foodprice - g_dailydiscount << endl;
				cout.unsetf(ios::fixed);
			}
			else {
				cout.fill(' ');
				cout << endl;
			}
			cout.unsetf(ios::right);
		}
		else {
			cout.width(2);
			cout.setf(ios::left);
			cout << Time << ". No Order" << endl;
		}
		Time++;
	}
}