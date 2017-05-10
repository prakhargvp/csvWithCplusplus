#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int main(){
 vector <vector <string> > data;
  ifstream infile( "example.csv" );

  while (infile)
  {
    string s;
    if (!getline( infile, s )) break;

    istringstream ss( s );
    vector <string> record;

    while (ss)
    {
      string s;
      if (!getline( ss, s, ',' )) break;
      record.push_back( s );
    }

    data.push_back( record );
  }
  for(int i=0;i<data.size();i++){
	for(int j=0;j<data[i].size();j++){
  		cout << data[i][j] << " ";
	}
	cout << endl;
  }
  if (!infile.eof())
  {
    cerr << "Fooey!\n";
  }
 return 0;
}
