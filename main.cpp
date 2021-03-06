#include <bits/stdc++.h>
#include "csv.h"
#include "fun.h"
int main(){
	int option,flag;
	char ch;
	string file,colName;
	CSV file1,file2,file3;
	int caseS,dupInfo,isSave;
	string f1,f2;
	string col1,col2;
	vector <col> d1,d2,d3;
	string str;
	do{
		// Menus
		cout <<"Menus : "<<endl;
		cout <<"1. Create"<<endl;
		cout <<"2. IsSameStructure"<<endl;
		cout <<"3. IsDuplicate"<<endl;
		cout <<"4. RemoveDuplicate"<<endl;
		cout <<"5. Sort"<<endl;
		cout <<"6. Union"<<endl;
		cout <<"7. Intersection"<<endl;
		cout <<"8. Exit"<<endl;
		cout <<"Enter the Choice : ";
		cin >> option;
		switch(option){
			case 1:
				file = inputFile();
				// If user select to exit
				if(file==""){
					break;
				}
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
				isSave=checkSave(isSave);
				if(isSave==1){
					cout << "Press 1. To save in existing one; 2. To Save in new one : ";
					cin >> isSave;
					isSave=Save2(isSave);
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
				f1 = inputFile();
				f2 = inputFile();
				file1.open(f1);
				file2.open(f2);
				flag = checkSameStructure(file1,file2);
				if(flag){
					cout << "Hurrey! Same Structure" <<endl;				
				}
				else if(flag=-1);
				else{
					cout << "Oops! Not Same Structure" <<endl;
				}			
				break;

			case 3:
				// Check is duplicate
				file=inputFile();
				file1.open(file);
				file1.read();
				do{
					cout << "Case-Sensitive (0 => Yes, 1 => No, -1 => Exit): ";
					cin >> caseS;
					caseS=checkcaseS(caseS);
				}while(caseS!=1 && caseS!=0 && caseS!=-1);
				if(caseS==-1){
					break;
				}
				file1.sort();
				// Check duplicate info
				// Show does not have duplicate
				int dupInfo;
				dupInfo = file1.IsDuplicate(caseS);
				cout << "Duplicate Found : "<<dupInfo<<endl;
			break;

			case 4:		
				// Remove Duplicate
				file =  inputFile();
				file1.open(file);
				file1.read();
				do{
					cout << "Case-Sensitive (0 => Yes, 1 => No, -1 => Exit): ";
					cin >> caseS;
					caseS=checkcaseS(caseS);
				}while(caseS!=1 && caseS!=0 && caseS!=-1);
				if(caseS==-1){  break;  }
				file1.sort();
				// Check duplicate info
				// 0 show does not have duplicate
				dupInfo = file1.removeDuplicate(caseS);
				cout << "Duplicate Found and Removed : "<<dupInfo<<endl;

				cout << "Press 1 to save file 0 to exit : ";
				cin >> isSave;
				isSave=checkSave(isSave);
				if(isSave==1){
					cout << "Press 1. To save in existing one; 2. To Save in new one : ";
					cin >> isSave;
					isSave=Save2(isSave);
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
				cout << "Enter the Column number (-1 => exit): ";
				cin >> colNum;
				if(colNum==-1){break;}
				if(!(colNum<tColumn && colNum>-1)){
					cout << "Please enter within Range (0-"<<tColumn<<")"<<endl;
				}else{
					int sortType;
					do{
						cout << "Enter the Sort type (0 => int , 1 => string sensitive , 2 => string in-sensitive) : ";
						cin >> sortType;
						//sortType=checkSortType(sortType);
					}while(sortType!=0 && sortType!=1 && sortType!=2 && sortType!=-1);

					file1.sort(colNum,sortType);
					file1.print();
				}
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

			case 6:
				// union
				int ind1,ind2;
				// IsSameStructure
				int flag;
				f1 = inputFile();
				f2 = inputFile();
				file1.open(f1);
				file2.open(f2);
				flag = checkSameStructure(file1,file2);
				cout << "File1 Columns : "; file1.printColumn();		
				cout << "File2 Columns : "; file2.printColumn();
				if(flag==0){
					cout << "Not Same Structure "<<endl;
					break;
				}
				do{
					cout << "Enter Column Name in File1 : ";
					cin >> col1;
					ind1 = file1.getIndexNo(col1);
				}while(ind1==-1);
				do{
					cout << "Enter Column Name in File2 : ";
					cin >> col2;
					ind2 = file2.getIndexNo(col2);
				}while(ind1==-1);

				d1 = file1.getData();
				d2 = file2.getData();
				for(int i=1;i<d1.size();i++){
					d3.push_back(d1[i]);
				}
				int temp;
				for(int i=1;i<d2.size();i++){
					col cl1;
					for(int j=0;j<d1[0].d.size();j++){
						temp = file2.getIndexNo(d1[0].d[j]);
						cout << temp <<" ";
						cl1.d.push_back(d2[i].d[temp]);
					}
					cout << endl;
					d3.push_back(cl1);
				}
				/*
				for(int i=1;i<d3.size();i++){
					cout << d3[i].d[0]<<endl;
				}
				*/	
				cout << "Enter the File to save : "<<endl;
				file =  inputFile();
				file3.open(file);
				file3.setData(d3);
				file3.sort(ind1);
				file3.removeDuplicateCol(ind1);
				file3.write();
			break;
		
			case 7:

			break;
			case 8: break;
			default:
				cout <<" Hurrey! No Work GO Away" << endl;

		}
		if(option!=8){
			cout << "Do you want to continue 'Y/N': ";
			fflush(stdin);
			cin >> ch; 
		}
	}while(toupper(ch)=='Y' && option!=8);
return 0;
}

