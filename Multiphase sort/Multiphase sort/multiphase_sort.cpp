#include <fstream>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <string.h>

using namespace std;

fstream **f, source_file;
int n, number_sf, *a, *d, L, j, tmp; //n - number of files, number_sf - amount of numbers in source file

char **names, *name;

void main () {
	char error[20] = "Error of open files";
	cout << "Enter number of files: ";
	cin >> n;
	//Create an array of names
	getch();
	names = new char *[n];
	for ( int i = 0; i < n; i++)
	{
		names[i] = new char[8];
		strcpy(names[i],"f ");
		char c='0'+(i);
		names[i][1]=c;
		strcat( names[i],".txt\0" );
	}
	getch();
	//Create an array of files
	f=new fstream*[n];
	for( int i=0; i<n; i++) {
		f[i] = new fstream ( names[i],ios::out );
	}
	//Create the source file
	cout << "Enter amount of numbers in source file: ";
	cin >> number_sf;
	fstream source_file;
	source_file.open("sourcef.txt", ios::out);
	srand(time(0));
	for ( int i = 0; i < number_sf; i++ ) {
		source_file << rand()%100 << " ";
	}
	source_file.close();
	//Reading from source file
	int x, y;
	source_file.open( "sourcef.txt", ios::in );
	if (!source_file) {
		cout << error << endl;
		return;
	}
	source_file >> x >> y;
	while ( source_file ) {
		if ( x <= y ) {
			*f[n-1] << x << " ";
			x = y;
			source_file >> y;
		}
		else {
			*f[n-1] << x << " " << "-1" << " ";
			x = y;
			source_file >> y;
		}
	}
	*f[n-1] << x << " " << "-1" << " ";
	f[n-1]->close();
	source_file.close();
	//Phase of split
	f[n-1]->open(names[n-1], ios::in);
	a=new int[n];
	d=new int[n];
	for(int i=0;i<n-1;i++) {
		a[i]=1;
		d[i]=1;
	}
	d[n-1]=0;
	a[n-1]=0;
	int L=1,j=0;
	*f[n-1] >> x;
	while ( *f[n-1] ) {
		while ( x != -1 )
		{
			*f[j] << x <<" ";
			*f[n-1] >> x;
		}
		*f[j] << x << " ";
		d[j]--;
		if ( ( *f[n-1] >> x ) == NULL ) break;
		else {
			if(d[j]<d[j+1]) j++;
			else if(d[j]==0) {	
				L++;
				tmp=a[0];
				for ( int i = 0; i < n-1; i++ ) {
					d[i] = a[i+1]-a[i]+tmp;
					a[i] = a[i+1]+tmp;
				}
				j=0;
			}
			else j=0;
		}
	}			
for( int i = 0; i < n; i++ )
f[i] -> close();
f[n-1] -> clear();

}