#include<iostream>

typedef enum bapi_E_BoChannel_{

	bapi_bo_Ch_1 =1,
	bapi_bo_Ch_2 =2,
	bapi_bo_Ch_3 =3,
	bapi_bo_Ch_4 =4,
	bapi_bo_Ch_5 =5,
	bapi_E_Ch_Count

}bapi_E_BoChannel;




int main(int argc,char*argv[])
{


	bapi_E_BoChannel bo_ch;
	bo_ch = bapi_bo_Ch_3;
	//bo_ch = bapi_E_Ch_Count;

	char array[bapi_E_Ch_Count]={0};

	std::cout<<"hello world c++ 14"<<std::endl;
	std::cout<<"size is "<<sizeof(array)<<std::endl;
	std::cout<<"bo_ch is "<<bo_ch<<std::endl;
	std::cout<<"bapi_E_Ch_Count is "<<bapi_E_Ch_Count<<std::endl;
	return 0;



}
