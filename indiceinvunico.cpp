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
#include <iterator> 

using namespace std;

int main(int argc, char **argv) {
	
	float tiempo=0;	
	clock_t t1;
	map <string  ,vector<int> > indice;
	string buf ,palabra1,palabra2;;
	int pos=0,posting=0,k;
	char r[20];
	vector<string> vocabulario;

	for (k=10;k<=19;k++){
		pos=0;tiempo=0; indice.clear();posting=0;
		int p = pow(2,k);		
		t1 = clock();
		while(pos!=p){	

			sprintf(r,"TODOtokenizer/%d",pos+1);
			
			std::ifstream ifs(r);
			std::string text1((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
			
			stringstream ss(text1);
					
			while(ss >> buf)
			{			
				if(indice.count(buf)>0 && indice[buf].back() == (pos+1) ) continue;
				else	indice[buf].push_back(pos+1);        
			}		
			pos++; 		
			buf.clear();
			
		}
		t1 = clock()-t1;
		tiempo += ((float)t1)/CLOCKS_PER_SEC;
		
		/* IMPRIMIR INDICE INV
		 * 
		 * for (map<string, vector<int> >::iterator it = indice.begin(); it != indice.end(); ++it) {  
			for(unsigned int i = 0; i < it->second.size(); i++) {
				cout << it->first <<"->"<< it->second[i]  << endl;
			}   
		}	
		*/
		//*************GENERAR VOLCABULARIO DE BUSQUEDA******************			
		
		/*for (map<string, vector<int> >::iterator it = indice.begin(); it != indice.end(); ++it) {  
				vocabulario.push_back(it->first);
				posting+= it->second.size();
		}*/
		/*	IMPRIMIR VOCABULARIO
		 * 
		 * for(unsigned int i = 0; i<vocabulario.size(); i++) {
				cout << vocabulario[i] <<" ";
		} 
		cout<<endl;
		*/	  	
		//**************TIEMPO, CANTIDAD DE PALABRAS Y POSTING*******************	
		cout<<"K=	"<<k<<endl;
		cout<<"TIEMPO CONSTRUCCION INDCE INV=	"<<tiempo<<endl;	
		cout<<"POSTING=		"<<posting<<endl; //postings (parece)
		cout<<"CANTIDAD DE PALABRAS=	"<<indice.size()<<endl; // cantidad de palabras	
	}
	return 0;
}
