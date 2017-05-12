int checkcaseS(int caseS){
	while(caseS!=0 && caseS!=1 && caseS!=-1){
		cout << "Wrong Choice Entered" << endl;
		cout << "Enter choice from (0 | 1 | -1)" << endl;
		cout << "Case-Sensitive (0 => Yes, 1 => No, -1 => Exit): ";
		cin >> caseS;
	}
	return caseS;
}

int checkErrChoice(int errChoice){
	while(errChoice!=1 && errChoice!=2 && errChoice!=3){
		cout << "Wrong Choice Entered" << endl;
		cout << "Enter choice from (1 | 2 | 3)" << endl;
		cin >> errChoice;
	}
	return errChoice;
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
		errChoice=checkErrChoice(errChoice);
	}while(errChoice==2);
	if(errChoice==3){
		file = "";
	}
return file;
}

int checkSameStructure(CSV &file1,CSV &file2){
	int caseS,flag=0;
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
			cout << "Case-Sensitive (0 => Yes, 1 => No, -1 => Exit): ";
			cin >> caseS;
			caseS=checkcaseS(caseS);
		}while((caseS!=0) && (caseS!=1) && caseS!=-1);
		if(caseS!=-1){
			flag=1;
			if(file1.totalColumn() == file2.totalColumn()){
				for(int i=0;i<file1.totalColumn();i++){
					if(CSV::toLower(colm1.d[i],caseS)!=CSV::toLower(colm2.d[i],caseS)){
						flag = 0;						
					}
				}
			}else{
				flag = 0;
			}
		}
	return flag;
}

int checkSave(int isSave){
	while(isSave!=1 && isSave!=0){
		cout << "Wrong Choice Entered" << endl;
		cout << "Enter choice from (0 | 1)" << endl;
		cin >> isSave;	
	}
	return isSave;
}

int Save2(int isSave){
	while(isSave!=1 && isSave!=2){
		cout << "Wrong Choice Entered" << endl;
		cout << "Enter choice from (0 | 1)" << endl;
		cin >> isSave;	
	}
	return isSave;
}

int checkSortType(int sortType){
	while(sortType!=0 && sortType!=1 && sortType!=2 && sortType!=-1){
		cout << "Wrong Choice Entered" << endl;
		cout << "Enter choice from (0 | 1 | 2 | -1)" << endl;
		cin >> sortType;
	}
	return sortType;
}
