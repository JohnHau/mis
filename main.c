#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"




typedef enum _lpspi_clock_polarity
{
	kLPSPI_ClockPolarityActiveHigh = 0U, /*!< CPOL=0. Active-high LPSPI clock (idles low)*/
	kLPSPI_ClockPolarityActiveLow  = 1U  /*!< CPOL=1. Active-low LPSPI clock (idles high)*/
} lpspi_clock_polarity_t;









#if 1
char Json_Msg[]="{                                                                            \n\
		     \"C_UIO\" :                                                              \n\
                                 {                                                            \n\
	                               \"UIO_COUNT\"       :\"4\",                            \n\
		                       \"USER_CH_2_UIO_CH\":                                  \n\
		                                {                                             \n\
			                              \"CH0\"  :\"UIO_A\",                    \n\
				                      \"CH1\"  :\"UIO_B\",                    \n\
				                      \"CH2\"  :\"UIO_C\",                    \n\
				                      \"CH3\"  :\"UIO_D\",                    \n\
				                      \"CH4\"  :\"UIO_A\",                    \n\
				                      \"CH5\"  :\"UIO_B\",                    \n\
				                      \"CH6\"  :\"UIO_C\",                    \n\
				                      \"CH7\"  :\"UIO_D\",                    \n\
				                      \"CH8\"  :\"UIO_A\",                    \n\
				                      \"CH9\"  :\"UIO_B\",                    \n\
				                      \"CH10\" :\"UIO_C\",                    \n\
				                      \"CH11\" :\"UIO_D\",                    \n\
				                      \"CH12\" :\"UIO_A\",                    \n\
				                      \"CH13\" :\"UIO_B\",                    \n\
				                      \"CH14\" :\"UIO_C\",                    \n\
				                      \"CH15\" :\"UIO_D\"                     \n\
		                               },                                             \n\
	                            \"IOMUXC_GPIO_RESET_PC0_PIN\":                            \n\
	                                       {                                              \n\
		                                      \"gpioBase\"       :\"0x401C0000U\",    \n\
			                              \"gpioPin\"        :\"27U\",            \n\
			                              \"muxRegister\"    :\"0x401F80B8U\",    \n\
			                              \"muxMode\"        :\"0x5U\",           \n\
			                              \"inputRegister\"  :\"0\",              \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82A8U\"     \n\
	                                       },                                             \n\
	                           \"IOMUXC_GPIO_RESET_PC1_PIN\":                             \n\
	                                       {                                              \n\
		                                      \"gpioBase\"       :\"0x401C0000U\",    \n\
			                              \"gpioPin\"        :\"27U\",            \n\
			                              \"muxRegister\"    :\"0x401F80B8U\",    \n\
			                              \"muxMode\"        :\"0x5U\",           \n\
			                              \"inputRegister\"  :\"0\",              \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82A8U\"     \n\
	                                       },                                             \n\
	                          \"IOMUXC_GPIO_RESET_PC2_PIN\":                              \n\
                 	                       {                                              \n\
		                                      \"gpioBase\"       :\"0x401C0000U\",    \n\
			                              \"gpioPin\"        :\"27U\",            \n\
			                              \"muxRegister\"    :\"0x401F80B8U\",    \n\
			                              \"muxMode\"        :\"0x5U\",           \n\
			                              \"inputRegister\"  :\"0\",              \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82A8U\"     \n\
	                                       },                                             \n\
	                         \"IOMUXC_GPIO_RESET_PC3_PIN\":                               \n\
	                                       {                                              \n\
		                                      \"gpioBase\"       :\"0x401C0000U\",    \n\
			                              \"gpioPin\"        :\"27U\",            \n\
			                              \"muxRegister\"    :\"0x401F80B8U\",    \n\
			                              \"muxMode\"        :\"0x5U\",           \n\
			                              \"inputRegister\"  :\"0\",              \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82A8U\"     \n\
	                                       },                                             \n\
	                        \"IOMUXC_GPIO_LPSPI_SCK_PIN\":                                \n\
	                                       {                                              \n\
		                                      \"gpioBase\"       :\"0\",              \n\
			                              \"gpioPin\"        :\"0\",              \n\
			                              \"muxRegister\"    :\"0x401F80BCU\",    \n\
			                              \"muxMode\"        :\"0x7U\",           \n\
			                              \"inputRegister\"  :\"0x401F8510\",     \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82ACU\"     \n\
	                                       },                                             \n\
	                        \"IOMUXC_GPIO_LPSPI_SDO_PIN\":                                \n\
	                                       {                                              \n\
		                                      \"gpioBase\"       :\"0\",              \n\
			                              \"gpioPin\"        :\"0\",              \n\
			                              \"muxRegister\"    :\"0x401F80C0U\",    \n\
			                              \"muxMode\"        :\"0x7U\",           \n\
			                              \"inputRegister\"  :\"0x401F8518U\",    \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82B0U\"     \n\
	                                       },                                             \n\
	                       \"IOMUXC_GPIO_LPSPI_SDI_PIN\":                                 \n\
	                                       {                                              \n\
		                                      \"gpioBase\"       :\"0\",              \n\
			                              \"gpioPin\"        :\"0\",              \n\
			                              \"muxRegister\"    :\"0x401F80C4U\",    \n\
			                              \"muxMode\"        :\"0x7U\",           \n\
			                              \"inputRegister\"  :\"0x401F8514U\",    \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82B4U\"     \n\
	                                       },                                             \n\
	                       \"IOMUXC_GPIO_LPSPI_PCS0_PIN\":                                \n\
	                                       {                                              \n\
		                                      \"gpioBase\"       :\"0\",              \n\
			                              \"gpioPin\"        :\"0\",              \n\
			                              \"muxRegister\"    :\"0x401F80C8U\",    \n\
			                              \"muxMode\"        :\"0x7U\",           \n\
			                              \"inputRegister\"  :\"0x401F850CU\",    \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82B8U\"     \n\
	                                       },                                             \n\
	                      \"IOMUXC_GPIO_LPSPI_PCS1_PIN\":                                 \n\
	                                       {                                              \n\
		                                      \"gpioBase\"       :\"0\",              \n\
			                              \"gpioPin\"        :\"0\",              \n\
			                              \"muxRegister\"    :\"0x401F80CCU\",    \n\
			                              \"muxMode\"        :\"0x7U\",           \n\
			                              \"inputRegister\"  :\"0\",              \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82BCU\"     \n\
	                                      },                                              \n\
	                      \"IOMUXC_GPIO_LPSPI_PCS2_PIN\":                                 \n\
	                                      {                                               \n\
		                                      \"gpioBase\"       :\"0\",              \n\
			                              \"gpioPin\"        :\"0\",              \n\
			                              \"muxRegister\"    :\"0x401F80D0U\",    \n\
			                              \"muxMode\"        :\"0x7U\",           \n\
			                              \"inputRegister\"  :\"0\",              \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82C0U\"     \n\
	                                      },                                              \n\
	                      \"IOMUXC_GPIO_LPSPI_PCS3_PIN\":                                 \n\
	                                      {                                               \n\
		                                      \"gpioBase\"       :\"0\",              \n\
			                              \"gpioPin\"        :\"0\",              \n\
			                              \"muxRegister\"    :\"0x401F80D4U\",    \n\
			                              \"muxMode\"        :\"0x7U\",           \n\
			                              \"inputRegister\"  :\"0\",              \n\
			                              \"inputDaisy\"     :\"0\",              \n\
			                              \"configRegister\" :\"0x401F82C4U\"     \n\
	                                     },                                               \n\
	                      \"LPSPI_MASTER_CONFIG\":                                        \n\
	                                     {                                                \n\
		                                 \"UIO_LPSPI_BASE\"      :\"0x4039C000U\",                       \n\
			                         \"baudRate\"            :\"500000\",                            \n\
			                         \"bitsPerFrame\"        :\"8\",                                 \n\
			                         \"cpol\"                :\"kLPSPI_ClockPolarityActiveHigh\",    \n\
			                         \"cpha\"                :\"kLPSPI_ClockPhaseSecondEdge\",       \n\
			                         \"direction\"           :\"kLPSPI_MsbFirst\",                   \n\
			                         \"whichPcs\"            :\"kLPSPI_Pcs0\",                       \n\
			                         \"pcsActiveHighOrLow\"  :\"kLPSPI_PcsActiveLow\",               \n\
			                         \"pinCfg\"              :\"kLPSPI_SdiInSdoOut\",                \n\
			                         \"dataOutConfig\"       :\"kLpspiDataOutRetained\"              \n\
	                                     }                                                                   \n\
                                 }                                                                               \n\
	}";
#endif




#define CMP_STRING(A,B)            (strcmp(A,B) == 0)
#define IS_STRA_EQUAL_STRB(A,B)    (strcmp(A,B) == 0)




typedef enum c_unit{HAS_UIO=1,HAS_BI=2,HAS_BO=3}C_UNIT;

typedef struct rt_pin_property
{
	uint32_t muxRegister;
	uint32_t muxMode;
	uint32_t inputRegister;
	uint32_t inputDaisy; 
	uint32_t configRegister;

	uint32_t gpioBase;   
	uint32_t gpioPin;

}rt_pin_property_t;



typedef struct rt_lpspi_master_cfg
{

	uint32_t baudRate;
	uint8_t bitsPerFrame;
	uint8_t cpol;
	uint8_t cpha;
	uint8_t direction;
	uint8_t whichPcs;
	uint8_t pcsActiveHighOrLow;
	uint8_t pinCfg;
	uint8_t dataOutConfig;

}rt_lpspi_master_cfg_t;



uint32_t parse_lpspi_cfg(cJSON* json,rt_lpspi_master_cfg_t* lpspi_cfg)
{

	cJSON * jsonV = NULL;
	uint32_t val_int = 0;

	jsonV = cJSON_GetObjectItem(json,"cpol");
	//	printf("now gpioBase is %s\n",jsonV->valuestring);
	
	if (CMP_STRING(jsonV->valuestring,"kLPSPI_ClockPolarityActiveHigh")) 
	{

		lpspi_cfg->cpol = kLPSPI_ClockPolarityActiveHigh;
		printf("cpol value is  %d\n",lpspi_cfg->cpol);
		printf("cpol is  %s\n",jsonV->valuestring);
	}



	return 0;

}

uint32_t parse_uio_lpspi_cfg(char* jsonMsg,char*item,rt_lpspi_master_cfg_t* lpspi_cfg)
{


	cJSON *json;
	cJSON *json_uio_root;
	cJSON *jsonV;
	cJSON *json_sdk_lpspi_master_cfg;
	int uio_count=0;

	uint32_t temp_val =0;

	json = cJSON_Parse(jsonMsg);

	json_uio_root = cJSON_GetObjectItem(json,"C_UIO");


	jsonV = cJSON_GetObjectItem(json_uio_root,"UIO_COUNT");

	uio_count = strtol(jsonV->valuestring,NULL,16);

	printf("uio count is %d\n",uio_count);

	if(uio_count)
	{

		json_sdk_lpspi_master_cfg = cJSON_GetObjectItem(json_uio_root,item);

		parse_lpspi_cfg(json_sdk_lpspi_master_cfg,lpspi_cfg);
	}


	return uio_count;




}










uint32_t parse_pin_property(cJSON* json,rt_pin_property_t * pin_property)
{
	cJSON * jsonV = NULL;
	uint32_t val_int = 0;

	jsonV = cJSON_GetObjectItem(json,"gpioBase");
	//	printf("now gpioBase is %s\n",jsonV->valuestring);
	pin_property->gpioBase = strtol(jsonV->valuestring,NULL,16);
	printf("now gpioBase value is %#x\n",pin_property->gpioBase);



	jsonV = cJSON_GetObjectItem(json,"gpioPin");
	//	printf("now gpioPin is %s\n",jsonV->valuestring);
	pin_property->gpioPin= strtol(jsonV->valuestring,NULL,10);
	printf("now gpioPinvalue is %d\n",pin_property->gpioPin);





	jsonV = cJSON_GetObjectItem(json,"muxRegister");
	//	printf("now muxRegister is %s\n",jsonV->valuestring);
	pin_property->muxRegister= strtol(jsonV->valuestring,NULL,16);
	printf("now muxRegister value is %#x\n",pin_property->muxRegister);




	jsonV = cJSON_GetObjectItem(json,"muxMode");
	//	printf("now muxMode is %s\n",jsonV->valuestring);
	pin_property->muxMode= strtol(jsonV->valuestring,NULL,16);
	printf("now muxMode value is %#x\n",pin_property->muxMode);


	jsonV = cJSON_GetObjectItem(json,"inputRegister");
	//	printf("now inputRegister is %s\n",jsonV->valuestring);
	pin_property->inputRegister = strtol(jsonV->valuestring,NULL,16);
	printf("now inputRegister value is %#x\n",pin_property->inputRegister);


	jsonV = cJSON_GetObjectItem(json,"configRegister");
	//	printf("now configRegister is %s\n",jsonV->valuestring);
	pin_property->configRegister= strtol(jsonV->valuestring,NULL,16);
	printf("now configRegister value is %#x\n",pin_property->configRegister);

	return 0;

}


uint32_t parse_uio_pin_cfg(char* jsonMsg,char*item,rt_pin_property_t * pin_property)
{

	cJSON *json;
	cJSON *json_uio_root;
	cJSON *jsonV;
	cJSON *json_sdk_pin;
	int uio_count=0;

	uint32_t temp_val =0;

	json = cJSON_Parse(jsonMsg);

	json_uio_root = cJSON_GetObjectItem(json,"C_UIO");


	jsonV = cJSON_GetObjectItem(json_uio_root,"UIO_COUNT");

	uio_count = strtol(jsonV->valuestring,NULL,16);

	printf("uio count is %d\n",uio_count);

	if(uio_count)
	{


		json_sdk_pin = cJSON_GetObjectItem(json_uio_root,item);
		parse_pin_property(json_sdk_pin,pin_property);

	}

	return uio_count;
}













int main(int argc, char*argv[])
{



#if 0
	if (CMP_STRING("hello","hello")) 
	{
		printf("string identical\n");

	}
	exit(EXIT_SUCCESS);
#endif



	rt_pin_property_t   reset_pin; 
	parse_uio_pin_cfg(Json_Msg,"IOMUXC_GPIO_RESET_PC0_PIN",&reset_pin);
	printf("\n");

	parse_uio_pin_cfg(Json_Msg,"IOMUXC_GPIO_RESET_PC1_PIN",&reset_pin);
	printf("\n");

	printf("====================\n");

        rt_lpspi_master_cfg_t uio_lpspi_cfg;
        parse_uio_lpspi_cfg(Json_Msg,"LPSPI_MASTER_CONFIG",&uio_lpspi_cfg);

	exit(EXIT_SUCCESS);

	cJSON *json;
	cJSON *jsonV;
	json = cJSON_Parse(Json_Msg);

	if(json == NULL)
		printf("error json\n");



	cJSON *arrayItemA = cJSON_GetObjectItem(json,"C_UIO");



	if(arrayItemA == NULL)
		printf("error arrayItemA\n");




	//cJSON *arrayItemB = cJSON_GetObjectItem(arrayItemA,"muxRegister");
	//jsonV = cJSON_GetObjectItem(arrayItemA,"muxRegister");
	//jsonV = cJSON_GetObjectItem(arrayItemA,"baudRate");
	//jsonV = cJSON_GetObjectItem(arrayItemA,"UIO_COUNT");

	cJSON *arrayItemB = cJSON_GetObjectItem(arrayItemA,"IOMUXC_GPIO_RESET_PIN");

	jsonV = cJSON_GetObjectItem(arrayItemB,"muxRegister");



	if(jsonV == NULL)
	{
		printf("error jsonV\n");
	}
	else
	{
		printf("config type is %s\n",jsonV->valuestring);
	}

	//char *mt  = "0x567";


	//uint32_t val = strtol(jsonV->valuestring,NULL,0);
	//uint32_t val = strtol(mt,NULL,16);
	//printf("val is %x\n",val);
	//printf("config type is %s\n",arrayItemB->valuestring);
	//printf("config type is %s\n",jsonV->valuestring);
	//printf("config type is %d\n",jsonV->type);
	return 0;
}
