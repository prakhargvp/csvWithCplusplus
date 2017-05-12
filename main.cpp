#include <bits/stdc++.h>
#include "csv.h"
string inputFile();
int main(){

	int option;
	string file,colName;
	CSV file1,file2;
	int caseS;
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
				file1.printColumn();

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
				int tColumn;
				int colNum,count;
				count = 0;
				tColumn= file1.totalColumn();
				cout << "Total Records : " << file1.getRecord() << endl;
				cout << "Total Columns : " << tColumn << endl;
				cout << "Columns : ";	file1.printColumn();	
				do{	
					cout << "Enter the Column number (-1 => exit): ";
					cin >> colNum;
					if(colNum>tColumn && colNum<-1){
						cout << "Please enter within Range (0-"<<tColumn<<")"<<endl;
					}else{
						int sortType;
						do{
							cout << "Enter the Sort type (0 => int , 1 => string sensitive , 2 => string in-sensitive) : ";
							cin >> sortType;
						}while(sortType!=0 && sortType!=1 && sortType!=2 && sortType!=-1);
						file1.sort(colNum,sortType);
						file1.print();
					}
					count++;
				}while(colNum!=-1 || count<=tColumn);
		break;

		case 3:
		
		// Check is duplicate
		file =  inputFile();
		file1.open(file);
		file1.read();
		do{
			cout << "Case-Sensitive (0 => Yes, 1 => No, -1 => Exit): ";
			cin >> caseS;
		}while(caseS!=1 && caseS!=0 && caseS!=-1);
		if(caseS==-1){
			break;
		}
		file1.sort();
		// Check duplicate info
		// 0 show does not have duplicate
		// 

			int dupInfo;
			dupInfo = file1.IsDuplicate(caseS);
			cout << "Duplicate Found : "<<dupInfo<<endl;
		break;

		case 2:
			// IsSameStructure
			string f1,f2;

			f1 = inputFile();
			f2 = inputFile();
			file1.open(f1);
			file2.open(f2);
			file1.read();
			file2.read();
			cout << "File1 Columns : "; file1.printColumn();		
			cout << "File2 Columns : "; file2.printColumn();
			// Temporary implement
			col colm1 = file1.getColumn();
			col colm2 = file2.getColumn();
			sort(colm1.d.begin(),colm1.d.end(),ccompare(2));
			sort(colm2.d.begin(),colm2.d.end(),ccompare(2));

			do{
				do{
					cout << "Case-Sensitive (0 => Yes, 1 => No, -1 => Exit): ";
					cin >> caseS;
				}while(caseS!=0 && caseS!=1 && caseS!=-1);
				if(caseS==-1){
					break;
				}
				int flag=1;
				if(file1.totalColumn() == file2.totalColumn()){
					for(int i=0;i<file1.totalColumn();i++){
						if(CSV::toLower(colm1.d[i],caseS)!=CSV::toLower(colm2.d[i],caseS)){
							flag = 0;						
						}
					}
				}else{
					flag = 0;
				}

				if(flag){
					cout << "Hurrey! Same Structure" <<endl;				
				}else{
					cout << "Oops! Not Same Structure" <<endl;
				}

			}while(caseS!=-1);
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
