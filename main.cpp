#include <bits/stdc++.h>
#include "csv.h"
string inputFile();
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
			file = inputFile();
			// If user select to exit
			if(file=="")
				break;
			// Opent the FIle
			if(!file1.open(file)){
				file1.error();
				break;
			}
			// To read the file
			file1.read();
			cout << "Total Records : " << file1.getRecord() << endl;
			// Add Column Name in csv File
			do{
				// Display Columns in DataSet = Columns in File + Other Added
				cout << "Columns : ";
				file1.getColumn();

				cout << "Enter Column Name (-1 => exit): ";
				cin >> colName;
				if(colName!="-1"){
					file1.addColumn(colName);
				}
			}while(colName!="-1");
			int isSave;
			cout << "Press 1 to save file 0 to exit : ";
			cin >> isSave;
			if(isSave==1){
				cout << "Press 1. To save in existing one; 2. To Save in new one : ";
				cin >> isSave;
				if(isSave==2){
					string name;
					cout << "Enter file name (with .csv extension) : ";
					cin >> name;
					file1.write(name);			
				}else{
					file1.write();	
				}
				
			}
		break;
		case 2:
			// IsSameStructure
			do{
				file = inputFile();
			}while(file!="");
		break;
		case 5:
			// Sort the data-set
			// Input File
			file = inputFile();
			if(file==""){	break;	}
			// Open the File
			if(!file1.open(file)){
				file1.error();
				break;
			}
			// Read the File
			file1.read();
				int totalColumn = file1.totalColumn();
				cout << "Total Records : " << file1.getRecord() << endl;
				cout << "Total Columns : " << file1.totalColumn() << endl;
				cout << "Columns : ";	file1.getColumn();	
				int colNum,count=0;
				do{	
					cout << "Enter the Column number (-1 => exit): ";
					cin >> colNum;
					if(colNum>totalColumn && colNum<-1){
						cout << "Please enter within Range (0-"<<totalColumn<<")"<<endl;
					}else{
						file1.sort(colNum);
						file1.print();
					}
					count++;
				}while(colNum!=-1 && count<=totalColumn);
		break;
	}
return 0;
}
string inputFile(){
	int errChoice=1;
	string file;
	do{
		cout << "Enter the File Name (-1 => exit): ";
		cin >> file;
		if(file=="-1"){
			file = "";
			break;
		}else if(file==""){
			continue;
		}
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
	if(errChoice==3){
		file = "";
	}
return file;
}
