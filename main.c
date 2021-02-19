#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"



//char Json_Msg[]="{\n    \"config_type\": \"SSID_PWD_UPD\",\n     \"config\":{\n        \"SSID\":\"Bacnet123\",\n        \"PASSWORD\":\"Honeywell@123\"\n    }\n}";
//char Json_Msg[]="{\n    \"config_type\": 0x25,\n     \"config\":{\n        \"SSID\":\"Bacnet123\",\n        \"PASSWORD\":\"Honeywell@123\"\n    }\n}";
//char Json_Msg[]="{\n    \"config_type\": 25.98,\n     \"config\":{\n        \"SSID\":\"Bacnet123\",\n        \"PASSWORD\":\"Honeywell@123\"\n    }\n}";



#if 0

char Json_Msg[]="{\n  \
                      \"config_type\": 25,\n \
                      \"config\":\
                                 {\n \
                                     \"SSID\":\"Bacnet123\",\n   \
                                     \"PASSWORD\":\"Honeywell@123\"\n  \
                                 }\n    \
                }";


#endif


#if 0
char Json_Msg[]="{\n  \
                      \"config_type\": 25,\n \
                      \"IOMUXC_GPIO_RESET_PIN\":\
                                 {\n \
                                     \"muxRegister\":\"0x401F80B8U\",\n   \
                                     \"muxMode\":\"0x5U\"    \n  \
                                     \"inputRegister\":\"0\"   \n  \
                                     \"inputDaisy\":\"0\"   \n  \
                                     \"configRegister\":\"0x401F82A8U\"\n  \
                                 }\n    \
                }";

#endif




#if 1
char Json_Msg[]="{                                                           \n\
                   \"C_UIO\"        :                                        \n\
                   {                                                         \n\
		      \"UIO_STATUS\":\"TRUE\",                               \n\
                      \"UIO_COUNT\"           :\"4\",                        \n\
                      \"UIO_LPSPI_BASE\"      :\"0x401F80B8U\",              \n\
                      \"USER_CH_2_UIO_CH\":                                  \n\
                                 {                                           \n\
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
                                 },                                          \n\
                      \"IOMUXC_GPIO_RESET_PIN\":                             \n\
                                 {                                           \n\
                                     \"gpioBase\"       :\"0x401F80B8U\",    \n\
                                     \"gpioPin\"        :\"0x401F80B8U\",    \n\
                                     \"muxRegister\"    :\"0x401F80B8U\",    \n\
                                     \"muxMode\"        :\"0x5U\",           \n\
                                     \"inputRegister\"  :\"0\",              \n\
                                     \"inputDaisy\"     :\"0\",              \n\
                                     \"configRegister\" :\"0x401F82A8U\"     \n\
                                 },                                          \n\
                      \"IOMUXC_GPIO_LPSPI_SCK_PIN\":                         \n\
                                 {                                           \n\
                                     \"gpioBase\"       :\"0x401F80B8U\",    \n\
                                     \"gpioPin\"        :\"0x401F80B8U\",    \n\
                                     \"muxRegister\"    :\"0x401F80B8U\",    \n\
                                     \"muxMode\"        :\"0x5U\",           \n\
                                     \"inputRegister\"  :\"0\",              \n\
                                     \"inputDaisy\"     :\"0\",              \n\
                                     \"configRegister\" :\"0x401F82A8U\"     \n\
                                 },                                          \n\
                     \"IOMUXC_GPIO_LPSPI_SDO_PIN\":                          \n\
                                 {                                           \n\
                                     \"gpioBase\"       :\"0x401F80B8U\",    \n\
                                     \"gpioPin\"        :\"0x401F80B8U\",    \n\
                                     \"muxRegister\"    :\"0x401F80B8U\",    \n\
                                     \"muxMode\"        :\"0x5U\",           \n\
                                     \"inputRegister\"  :\"0\",              \n\
                                     \"inputDaisy\"     :\"0\",              \n\
                                     \"configRegister\" :\"0x401F82A8U\"     \n\
                                 },                                          \n\
                    \"IOMUXC_GPIO_LPSPI_SDI_PIN\":                           \n\
                                 {                                           \n\
                                     \"gpioBase\"       :\"0x401F80B8U\",    \n\
                                     \"gpioPin\"        :\"0x401F80B8U\",    \n\
                                     \"muxRegister\"    :\"0x401F80B8U\",    \n\
                                     \"muxMode\"        :\"0x5U\",           \n\
                                     \"inputRegister\"  :\"0\",              \n\
                                     \"inputDaisy\"     :\"0\",              \n\
                                     \"configRegister\" :\"0x401F82A8U\"     \n\
                                 },                                          \n\
                   \"IOMUXC_GPIO_LPSPI_PCS0_PIN\":                           \n\
                                 {                                           \n\
                                     \"gpioBase\"       :\"0x401F80B8U\",    \n\
                                     \"gpioPin\"        :\"0x401F80B8U\",    \n\
                                     \"muxRegister\"    :\"0x401F80B8U\",    \n\
                                     \"muxMode\"        :\"0x5U\",           \n\
                                     \"inputRegister\"  :\"0\",              \n\
                                     \"inputDaisy\"     :\"0\",              \n\
                                     \"configRegister\" :\"0x401F82A8U\"     \n\
                                 },                                          \n\
                      \"IOMUXC_GPIO_LPSPI_PCS1_PIN\":                        \n\
                                 {                                           \n\
                                     \"gpioBase\"       :\"0x401F80B8U\",    \n\
                                     \"gpioPin\"        :\"0x401F80B8U\",    \n\
                                     \"muxRegister\"    :\"0x401F80B8U\",    \n\
                                     \"muxMode\"        :\"0x5U\",           \n\
                                     \"inputRegister\"  :\"0\",              \n\
                                     \"inputDaisy\"     :\"0\",              \n\
                                     \"configRegister\" :\"0x401F82A8U\"     \n\
                                 },                                          \n\
                     \"IOMUXC_GPIO_LPSPI_PCS2_PIN\":                         \n\
                                 {                                           \n\
                                     \"gpioBase\"       :\"0x401F80B8U\",    \n\
                                     \"gpioPin\"        :\"0x401F80B8U\",    \n\
                                     \"muxRegister\"    :\"0x401F80B8U\",    \n\
                                     \"muxMode\"        :\"0x5U\",           \n\
                                     \"inputRegister\"  :\"0\",              \n\
                                     \"inputDaisy\"     :\"0\",              \n\
                                     \"configRegister\" :\"0x401F82A8U\"     \n\
                                 },                                          \n\
                    \"IOMUXC_GPIO_LPSPI_PCS3_PIN\":                          \n\
                                 {                                           \n\
                                     \"gpioBase\"       :\"0x401F80B8U\",    \n\
                                     \"gpioPin\"        :\"0x401F80B8U\",    \n\
                                     \"muxRegister\"    :\"0x401F80B8U\",    \n\
                                     \"muxMode\"        :\"0x5U\",           \n\
                                     \"inputRegister\"  :\"0\",              \n\
                                     \"inputDaisy\"     :\"0\",              \n\
                                     \"configRegister\" :\"0x401F82A8U\"     \n\
                                 },                                          \n\
                   \"LPSPI_MASTER_CONFIG\":                                  \n\
                                 {                                           \n\
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
		   }                                                                                 \n\
                }";
#endif

//char Json_Msg[]="{\n  \"config_type\": \"SSID_PWD_UPD\",\n     \"config\":{\n        \"SSID\":\"Bacnet123\",\n        \"PASSWORD\":\"Honeywell@123\"\n    }\n}";


#if 0
char Json_Msg[]="{                                         \n\
		 \"UIO\":\"0x8\",                          \n\
		 \"IOMUXC_GPIO_RESET_PIN\":                \n\
                        {                                   \n\
		             \"gpioPin\":\"0x8\",           \n\
		       	     \"muxRegister\":\"0x8\",        \n\
		             \"mM\":\"0x5\"                  \n\
			},                                    \n\
		\"test_item\":                            \n\
                        {                                      \n\
	                     \"test-a\":\"88\",               \n\
                             \"test-b\":\"99\"                 \n\
			}                                       \n\
		}";
#endif





int main(int argc, char*argv[])
{


cJSON *json;
cJSON *jsonV;
json = cJSON_Parse(Json_Msg);

if(json == NULL)
printf("error json\n");

#if 0
cJSON *arrayItem = cJSON_GetObjectItem(json,"config_type");
//printf("config type is %s\n",arrayItem->valuestring);
printf("config type is %d\n",arrayItem->valueint);
//printf("config type is %f\n",arrayItem->valuedouble);
printf("cjson type is %d\n",arrayItem->type);
#endif



//cJSON *arrayItemA = cJSON_GetObjectItem(json,"IOMUXC_GPIO_RESET_PIN");
//cJSON *arrayItemA = cJSON_GetObjectItem(json,"LPSPI_MASTER_CONFIG");
cJSON *arrayItemA = cJSON_GetObjectItem(json,"C_UIO");



if(arrayItemA == NULL)
printf("error arrayItemA\n");




//cJSON *arrayItemB = cJSON_GetObjectItem(arrayItemA,"muxRegister");
//jsonV = cJSON_GetObjectItem(arrayItemA,"muxRegister");
//jsonV = cJSON_GetObjectItem(arrayItemA,"baudRate");
//jsonV = cJSON_GetObjectItem(arrayItemA,"UIO_COUNT");
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
