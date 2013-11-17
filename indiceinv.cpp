#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>
#include <time.h>

using namespace std;

int main(int argc, char **argv) {
	
	float tiempo=0;	
	clock_t t1;
	map <string  ,vector<int> > indice;
	string buf ;
	int pos=0,posting=0;
	char r[20];

	if (argc != 2) {
		cout << "usage: " << argv[0] << "<2potencia>" << endl;
		return 0;
	}

	int m;
	{
    stringstream ss;
    ss << argv[1];
    ss >> m;
	}
	
	int p = pow(2,m);	
	
	
	while(pos!=p){	

		sprintf(r,"TODO/%d",pos+1);
		
		std::ifstream ifs(r);
		std::string text1((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		
	//	cout<<text1<<endl;
		
		stringstream ss(text1);
		
		t1 = clock();
		while(ss >> buf)
		{			
			if(indice.count(buf)>0 && indice[buf].back() == (pos+1) ) continue;
			else	indice[buf].push_back(pos+1);        
		}

		t1 = clock()-t1;
		
		tiempo += ((float)t1)/CLOCKS_PER_SEC;
		//cout<<"Tiempo promedio(pos/(m+1)):"<< tiempo/(pos/(m+1)) <<endl;
		pos++; 		
		buf.clear();
		
	}
	
	/*for (map<string, vector<int> >::iterator it = indice.begin(); it != indice.end(); ++it) {  
		for(unsigned int i = 0; i < it->second.size(); i++) {
			cout << it->first <<"->"<< it->second[i]  << endl;
		}   
	}
	

	cout<<"Tiempo promedio(10000):"<< tiempo/10000 <<endl;
    cout<<"Tiempo promedio(pos/(m+1)):"<< tiempo/(pos/(m+1)) <<endl;
	
	*/
	
	
	//************BUSCARRRRRRRRRR PALABRAS*******************
	
	//FALTA GENERAR PALABRAS ALEATORIAS
	string palabra="was";
	vector<int> lista=indice[palabra];
	
	/*for(unsigned int i = 0; i<lista.size(); i++) {
			cout << lista[i] <<" ";
	} 
	cout<<endl;
	*/
	
	//*************INTERSECCION********************************
	string palabra1="as";
	string palabra2="was";
	
	vector<int> lista1=indice[palabra1];
	vector<int> lista2=indice[palabra2];
	vector<int> inter;
	
	int i1=0,i2=0,f1=lista1.size(),f2=lista2.size();
	
	
	while(i1 != f1 && i2 != f2)
	{
			if(lista1[i1] == lista2[i2])
			{
					inter.push_back(lista1[i1]);
					i1++;i2++;
			}else{
					if(lista1[i1] < lista2[i2]) i1++;
					else if(lista1[i1] > lista2[i2]) i2++;
			}
	}
	
	/*for(unsigned int i = 0; i<inter.size(); i++) {
			cout << inter[i] <<" ";
	} 
	cout<<endl;*/
	
	//***************UNION***********************************
	palabra1="as";
	palabra2="was";
	
	vector<int> lista3=indice[palabra1];
	vector<int> lista4=indice[palabra2];
	vector<int> unio;
	
	i1=0,i2=0,f1=lista3.size(),f2=lista4.size();
	
	while(i1 != f1 || i2 != f2)
	{		
			if(i2 == f2){
						unio.push_back(lista3[i1]);
						i1++;
						continue;			
			}			
			if(i1 == f1){
						unio.push_back(lista4[i2]);
						i2++;
						continue;			
			}				
			if(lista3[i1] == lista4[i2])
			{
						unio.push_back(lista3[i1]);
						i1++;
						i2++;
			}else if(lista3[i1] < lista4[i2]){ 
						
						unio.push_back(lista3[i1]);
						i1++;												
			}else if(lista3[i1] > lista4[i2])
			{ 
						unio.push_back(lista4[i2]);
						i2++;											
			}
			
	}
	
	
	/*for(unsigned int i = 0; i<unio.size(); i++) {
			cout << unio[i] <<" ";
	} 
	cout<<endl;
	*/
	
	  
	  
	  
	  	
	//**************CANTIDAD DE PALABRAS Y POSTING*******************
	
	for (map<string, vector<int> >::iterator it = indice.begin(); it != indice.end(); ++it) 
			posting+= it->second.size();
	
	cout<<"POSTING=		"<<posting<<endl; //postings (parece)
	cout<<"CANTIDAD DE PALABRAS=	"<<indice.size()<<endl; // cantidad de palabras
		
	return 0;
}
