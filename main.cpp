#include <bits/stdc++.h>
#include "csv.h"
int main(){

	int option;
	string file,colName;
	CSV file1;
	// Menus
	cout <<"Menus : "<<endl;
	cout <<"1. Add Column"<<endl;
	cout <<"2. IsSameStructure"<<endl;
	cout <<"3. IsDuplicate"<<endl;
	cout <<"4. RemoveDuplicate"<<endl;
	cout <<"5. sort"<<endl;
	cout <<"6. union"<<endl;
	cout <<"7. intersection"<<endl;
	cout <<"8. Exit"<<endl;
	cout <<"Enter the Choice : ";
	cin >> option;
	switch(option){
		case 1:
			int errChoice=1;
			do{
				cout << "Enter the File Name : ";
				cin >> file;
				// Check the File Status is already exist or not
				// a. If file already exist ask to open
				// b. If file not exist ask for create
				if(CSV::isExist(file)){
					cout << "File Already Exist "<<endl;
					cout << "1. Open ; 2. New File Name ; 3. Exit"<<endl;

				}else{
					cout << "File Not Exist " <<endl;
					cout << "1. Create ; 2. New File Name ; 3. Exit"<<endl; 
				}
				cout << "Enter Choice : ";
				cin >> errChoice;
			}while(errChoice==2);
			// If user select to exit
			if(errChoice==3)
				break;
			// Opent the FIle
			if(!file1.open(file)){
				file1.error();
				break;
			}
			// To read the file
			file1.read();
			cout << "Total Records : " << file1.getRecord() <<endl;
			// Add Column Name in csv File
			string colName;
			do{
				// Display Columns in DataSet = Columns in File + Other Added
				cout << "Columns : ";
				file1.getColumn();

				cout << "Enter Column Name (-1 => exit): ";
				cin >> colName;
				if(colName!="-1"){
					// Check is column name already exist
					file1.addColumn(colName);
				}
			}while(colName!="-1");
			int isSave;
			cout << "Press 1 to save file 0 to exit : ";
			cin >> isSave;
			if(isSave==1){
				string name;
				cout << "Enter file name with .csv extension by which you want to save file : ";
				getline(cin,name);
				file1.write("name");
			}
		break;
	}
return 0;
}
