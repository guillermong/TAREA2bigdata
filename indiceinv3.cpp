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

vector <int> fbuscar(string palabra1 ,map <string  ,vector<int> > indice){
	
	return indice[palabra1];	
	
	}
	
vector <int> finterseccion(int i1, int f1, int i2, int f2,vector<int> lista1,vector<int> lista2){
	
			vector<int> inter;
			
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
			return inter;	
}
vector <int> funio(int i1, int f1, int i2, int f2,vector<int> lista3,vector<int> lista4 ){
				
			vector<int> unio;			
			while(i1 != f1 || i2 != f2)
			{		
					if(i2 == f2){
								unio.push_back(lista3[i1]);
								i1++;		
					}			
					else if(i1 == f1){
								unio.push_back(lista4[i2]);
								i2++;									
					}				
					else if(lista3[i1] == lista4[i2])
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
			return unio;	
}

int main(int argc, char **argv) {
	
	float tiempo=0,tbuscar,tunion,tinterseccion;	
	clock_t t1;
	map <string  ,vector<int> > indice;
	string buf ,palabra1,palabra2;;
	int pos=0,posting=0,k,i1=0,i2=0,f1,f2;
	char r[20];
	vector<string> vocabulario;
	srand (time(NULL));	
	vector<int> lista1;
	vector<int> lista2;	
	vector<int> inter;
	vector<int> unio;
	vector<int> buscar;

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
	
	for (map<string, vector<int> >::iterator it = indice.begin(); it != indice.end(); ++it) {  
			vocabulario.push_back(it->first);
			posting+= it->second.size();
	}
	/*	IMPRIMIR VOCABULARIO
	 * 
	 * for(unsigned int i = 0; i<vocabulario.size(); i++) {
			cout << vocabulario[i] <<" ";
	} 
	cout<<endl;
	*/	  	
	//**************TIEMPO, CANTIDAD DE PALABRAS Y POSTING*******************	
	cout<<"TIEMPO CONSTRUCCION INDCE INV=	"<<tiempo<<endl;	
	cout<<"POSTING=		"<<posting<<endl; //postings (parece)
	cout<<"CANTIDAD DE PALABRAS=	"<<indice.size()<<endl; // cantidad de palabras	
	
	//************BUSCAR PALABRAS*******************
	for (k=10;k<=20;k++){
		p = pow(2,k);
		tbuscar=0;
		for(pos=1; pos<=p ;pos++){
			palabra1=vocabulario[ rand() % vocabulario.size() ];
			//************BUSQUEDA***************
			t1 = clock();
			buscar=fbuscar(palabra1,indice);
			t1 = clock()-t1;
			tbuscar += ((float)t1)/CLOCKS_PER_SEC;
		   /*cout <<"buscar:"<<palabra1<<endl;
			for(unsigned int i = 0; i<buscar.size(); i++) {
				cout << buscar[i] <<" ";
			} 
			cout<<endl;*/
		}
		cout<<"PARA K="<<k<<endl;
		cout<<"TIEMPO BUSQUEDA:"<<tbuscar<<endl;
	}	
		
			
	//************UNION E INTERSECCION PALABRAS*******************	
		
	for (k=8;k<=16;k++){
		p = pow(2,k);
		tunion=0;tinterseccion=0;
		for(pos=1; pos<=p ;pos++){
			
			palabra1=vocabulario[ rand() % vocabulario.size() ];
			palabra2=vocabulario[ rand() % vocabulario.size() ];				
			lista1=indice[palabra1];	
			lista2=indice[palabra2];
			
			//IMPRIME LISTAS DE LA PALABRA UNION E INTERSECCION
			/*cout<<"lista1=";
			for(unsigned int i = 0; i<lista1.size(); i++) {
			cout << lista1[i] <<" ";
			}
			cout<<endl<<"lista2=";
			
			for(unsigned int i = 0; i<lista2.size(); i++) {
			cout << lista2[i] <<" ";			
			}	
			cout<<endl;*/
			
			f1=lista1.size(),f2=lista2.size();
						
			//************INTERSECCION***************
			t1 = clock();
			inter=finterseccion(i1,f1,i2,f2,lista1,lista2);
			t1 = clock()-t1;
			tunion += ((float)t1)/CLOCKS_PER_SEC;
			//************UNION***************
			t1 = clock();
			unio=funio(i1,f1,i2,f2,lista1,lista2);
			t1 = clock()-t1;
			tinterseccion += ((float)t1)/CLOCKS_PER_SEC;								
			
		//	IMPRIMIR RESULTADOS BUSQUEDAS		  
		/*  		  		
			cout <<"buscar INTERSECCION:"<<palabra1<<" y "<<palabra2<<endl;
			for(unsigned int i = 0; i<inter.size(); i++) {
					cout << inter[i] <<" ";
			} 
			cout<<endl;
			
			cout <<"buscar UNION:"<<palabra1<<" y "<<palabra2<<endl;
			for(unsigned int i = 0; i<unio.size(); i++) {
				cout << unio[i] <<" ";
			} 
			cout<<endl;
		*/			
		}
	//IMPRIMIR TIEMPOS EN K				
		cout<<"PARA K="<<k<<endl;
		cout<<"TIEMPO UNION:"<<tunion<<endl;
		cout<<"TIEMPO INTERSECCION:"<<tinterseccion<<endl;	
	}			
	return 0;
}
