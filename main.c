#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"


extern char Json_Msg[];
extern const char jsonmsg[];


cJSON *json= NULL;
uint8_t cf_config_init(void)
{
	json = cJSON_Parse(Json_Msg);

	if(json)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}



int main(int argc,char*argv[])
{
#if 0
	uint8_t rv = cf_config_init();

	printf("rv is %d\n",rv);
	printf("doulbe quote is %x\n",'"');
#endif


	json = cJSON_Parse(jsonmsg);


	if(json == NULL)
	{
		printf("error\n");

	}
	else
	{

		printf("ok\n");

	}


	return 0;

}

