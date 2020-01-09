#include<iostream>
#include<algorithm>
#include<string>
#include "list.h"
#include "square_templ"
#include"allocator"

void print_menu(){
	std::cout
	<<"1. insert square at number"<<std::endl
	<<"2. remove square at number"<<std::endl
	<<"3. print information about all square"<<std::endl
	<<"4. print number of elemets with square less then"<<std::endl
	<<"5. print information of one square at number"<<std::endl
	<<"6. save list to file"<<std::endl
	<<"7. load list from file"<<std::endl
	<<"0. exit"<<std::endl;
}

bool is_number(std::string& str){
	for(int i=0; i<str.size(); ++i)
		if( !( (str[i] <= '9') && (str[i] >= '0')  || str[i]=='.') )
			return false;
	return true;
}

int main(){
	 
	List<Square<int>, Allocator<Square<int>, 500>> list;
	std::cout<<"Program for working with square in list."<<std::endl<<std::endl;
	print_menu();
	while(true){
		try{
		std::string buf;
		std::cout<<">>";
		std::cin>>buf;
		if(!is_number(buf)){
			std::cout<<"wrong input!"<<std::endl;
			continue;
		}
		int cmd=atoi(buf.c_str());
		switch(cmd){
			case 0:
				std::cout<<"exit"<<std::endl;
				return 0;
			case 1 :{
				std::cout<<"input 2 square vertexes"<<std::endl<<">>";
				std::string b2, b3, b4;
				std::cin>>buf>>b2>>b3>>b4;
				if(!is_number(buf) || !is_number(b2) || !is_number(b3) || !is_number(b4)){
					std::cout<<"wrong input!"<<std::endl;
					continue;
				}
				std::cout<<"input index"<<std::endl<<">>";
				std::string ind;
				std::cin>>ind;
				if(!is_number(ind)){
					std::cout<<"wrong input!"<<std::endl;
					continue;
				}
				list.insert(
					std::next( list.begin() , atoi( ind.c_str() ) ), 
					Square( std::pair{ atoi( buf.c_str() ) , atoi( b2.c_str() ) } ,
							std::pair{ atoi( b3.c_str()  ) , atoi( b4.c_str() ) } )
				);
				break;
			}
			case 2 :{
				std::cout<<"input 2 square vertexes"<<std::endl<<">>";
				std::string b2, b3, b4;
				std::cin>>buf>>b2>>b3>>b4;
				if(!is_number(buf) || !is_number(b2) || !is_number(b3) || !is_number(b4)){
					std::cout<<"wrong input!"<<std::endl;
					continue;
				}
				std::cout<<"input index"<<std::endl<<">>";
				std::cin>>buf;
				if(!is_number(buf)){
					std::cout<<"wrong input!"<<std::endl;
					continue;
				}
				list.erase( std::next( list.begin() , atoi( buf.c_str() ) ) );
				break;
			}
			case 3 :{
				int i=0;
				std::for_each(list.begin(), list.end(), 
					[&i](const Square<int>& t){ 
						std::cout<<i++<<": "<<t<<std::endl
								 <<"square "<<t.square()<<std::endl
								 <<"center "<<t.center()<<std::endl<<std::endl;
						});
				break;
			}
			case 4 :{
				std::cout<<"input maximum square"<<std::endl<<">>";
				std::cin>>buf;
				if(!is_number(buf)){
					std::cout<<"wrong input!"<<std::endl;
					continue;
				}
				double sq=atoi(buf.c_str());
				std::cout<<"number of squares with square less then " << sq <<" is "<<std::count_if(list.begin(), list.end(), [sq](const Square<int>& t){ return sq>=t.square(); })<<std::endl;
				break;
			}
			case 5 :{
				std::cout<<"input index"<<std::endl<<">>";
				std::cin>>buf;
				if(!is_number(buf)){
					std::cout<<"wrong input!"<<std::endl;
					continue;
				}
				int ind=atoi(buf.c_str());
				std::cout<<ind<<": "<<list[ind]<<std::endl
						 <<"square "<<list[ind].square()<<std::endl
						 <<"center "<<list[ind].center()<<std::endl
						 <<std::endl;
						
				break;
			}
			case 6 : {
				std::cout<<"input file name"<<std::endl<<">>";
				std::cin>>buf;
				list.save(buf);
				break;
			}
			case 7 : {
				std::cout<<"input file name"<<std::endl<<">>";
				std::cin>>buf;
				list.load(buf);
				break;
			}
			default: 
				std::cout<<"Wrong Comand"<<std::endl;	
		}
	}catch(std::exception& e){
		std::cerr<<"ERROR "<<e.what()<<std::endl;
	}
	}
	return 0;
}
