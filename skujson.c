char Json_Msg[]="{\"type\": \"skuconfig\",\
  \"ver\"  :1,\
  \"sku\"  :1,\
  \"brand\":\"nova\",\
  \"t1l\"  : 0,\
  \"usb\"  : 1,\
  \"spi\"  :\
           [\
               {\
                  \"baud\": \"3000000\",\
                  /* spi3*/\
                  \"base\": \"0x403A0000u\",\
                  \"sck\":\
                           {\
                               \"muxReg\": \"0x401F8148U\",\
                               \"muxMode\": \"0x3U\",\
                               \"inputReg\": \"0x401F8520U\",\
                               \"inputDaisy\": \"0\",\
                               \"configReg\": \"0x401F8338U\"\
                           },\
      \"sdo\": {\
        \"muxReg\": \"0x401F8144U\",\
        \"muxMode\": \"0x3U\",\
        \"inputReg\": \"0x401F8528U\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F8334U\"\
      },\
      \"sdi\": {\
        \"muxReg\": \"0x401F8140U\",\
        \"muxMode\":\"0x3U\",\
        \"inputReg\": \"0x401F8524U\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F8330U\"\
      },\
      \"cs\": [\
        {\
          \"muxReg\": \"0x401F813CU\",\
          \"muxMode\": \"0x3U\",\
          \"inputReg\": \"0x401F851CU\",\
          \"inputDaisy\": \"0\",\
          \"configReg\": \"0x401F832CU\" \
        },\
     {\
          \"muxReg\": \"0x401F8188U\",\
          \"muxMode\": \"0x2U\",\
          \"inputReg\": \"0\",\
          \"inputDaisy\": \"0\",\
          \"configReg\": \"0x401F8378U\" \
        },\
   {\
          \"muxReg\": \"0x401F8184U\",\
          \"muxMode\": \"0x2U\",\
          \"inputReg\": \"0\",\
          \"inputDaisy\": \"0\",\
          \"configReg\": \"0x401F8374U\" \
        },\
        {\
          \"muxReg\": \"0x401F81A8U\",\
          \"muxMode\": \"0x6U\",\
          \"inputReg\": \"0\",\
          \"inputDaisy\": \"0\",\
          \"configReg\": \"0x401F8398U\"\
        }\
      ]\
    }\
   \"spi\": [\
    {\
      \"baud\": \"3000000\",\
	  \"base\": \"0x403A0000u\",\
      \"sck\": {\
        \"muxReg\": \"0x401F8148U\",\
        \"muxMode\": \"0x3U\",\
        \"inputReg\": \"0x401F8520U\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F8338U\"\
      },\
      \"sdo\": {\
        \"muxReg\": \"0x401F8144U\",\
        \"muxMode\": \"0x3U\",\
        \"inputReg\": \"0x401F8528U\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F8334U\"\
      },\
      \"sdi\": {\
        \"muxReg\": \"0x401F8140U\",\
        \"muxMode\":\"0x3U\",\
        \"inputReg\": \"0x401F8524U\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F8330U\"\
      },\
      \"cs\": [\
        {\
          \"muxReg\": \"0x401F813CU\",\
          \"muxMode\": \"0x3U\",\
          \"inputReg\": \"0x401F851CU\",\
          \"inputDaisy\": \"0\",\
          \"configReg\": \"0x401F832CU\" \
        },\
		{\
          \"muxReg\": \"0x401F8188U\",\
          \"muxMode\": \"0x2U\",\
          \"inputReg\": \"0\",\
          \"inputDaisy\": \"0\",\
          \"configReg\": \"0x401F8378U\" \
        },\
		{\
          \"muxReg\": \"0x401F8184U\",\
          \"muxMode\": \"0x2U\",\
          \"inputReg\": \"0\",\
          \"inputDaisy\": \"0\",\
          \"configReg\": \"0x401F8374U\" \
        },\
        {\
          \"muxReg\": \"0x401F81A8U\",\
          \"muxMode\": \"0x6U\",\
          \"inputReg\": \"0\",\
          \"inputDaisy\": \"0\",\
          \"configReg\": \"0x401F8398U\"\
        }\
      ]\
    }\
  ], \
 ], \
	\"uiochip\": {\
    \"rstpin\": [\
       {\
        \"port\": \"0x401C0000u\",\
        \"pin\": \"17U\",\
        \"muxReg\": \"0x401F81D0U\",\
        \"muxMode\": \"0x5U\",\
        \"inputReg\": \"0\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F83C0U\"\
      },\
		{\
        \"port\": \"0x401BC000u\",\
        \"pin\": \"31U\",\
        \"muxReg\": \"0x401F81B8U\",\
        \"muxMode\": \"0x5U\",\
        \"inputReg\": \"0\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F83A8U\"\
      },\
		{\
        \"port\": \"0x401B8000u\",\
        \"pin\": \"11U\",\
        \"muxReg\": \"0x401F80E8U\",\
        \"muxMode\": \"0x5U\",\
        \"inputReg\": \"0\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F82D8U\"\
      },\
		{\
        \"port\": \"0x401B8000u\",\
        \"pin\": \"24U\",\
        \"muxReg\": \"0x401F811CU\",\
        \"muxMode\": \"0x5U\",\
        \"inputReg\": \"0\",\
        \"inputDaisy\": \"0\",\
        \"configReg\": \"0x401F830CU\"\
      }\
    ]\
  },\
  \"bi\": {\
		    \"pop\": 65535,\
		    \"cfg\": [\
		      {\
		        \"ChannelNum\": 0,\
	            \"port\": \"0x401BC000U\",\
		        \"pin\": 25,\
		        \"muxReg\": \"0x401F81A0U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F8390U\"\
		      },\
			  {\
		        \"ChannelNum\": 1,\
	            \"port\": \"0x401BC000u\",\
		        \"pin\": 24,\
		        \"muxReg\": \"0x401F819CU\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F838CU\"\
		      },\
              {\
		        \"ChannelNum\": 2,\
	            \"port\": \"0x401C0000U\",\
		        \"pin\": 16,\
		        \"muxReg\": \"0x401F81CCU\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F83BCU\"\
		      },\
		      {\
		        \"ChannelNum\": 3,\
	            \"port\": \"0x401BC000U\",\
		        \"pin\": 30,\
		        \"muxReg\": \"0x401F81B4U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F83A4U\"\
		      },\
		      {\
		        \"ChannelNum\": 4,\
	            \"port\": \"0x401C0000U\",\
		        \"pin\": 17,\
		        \"muxReg\": \"0x401F81D0U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F83C0U\"\
		      },\
		      {\
		        \"ChannelNum\": 5,\
	            \"port\": \"0x401BC000U\",\
		        \"pin\": 31,\
		        \"muxReg\": \"0x401F81B8U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F83A8U\"\
		      },\
		      {\
		        \"ChannelNum\": 6,\
	            \"port\": \"0x401B8000U\",\
		        \"pin\": 11,\
		        \"muxReg\": \"0x401F80E8U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F82D8U\"\
		      },\
		      {\
		        \"ChannelNum\": 7,\
	            \"port\": \"0x401B8000U\",\
		        \"pin\": 24,\
		        \"muxReg\": \"0x401F811CU\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F830CU\"\
		      },\
		      {\
		        \"ChannelNum\": 8,\
	            \"port\": \"0x401B8000U\",\
		        \"pin\": 14,\
		        \"muxReg\": \"0x401F80F4U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F82E4U\"\
		      },\
			  {\
		        \"ChannelNum\": 9,\
	            \"port\": \"0x401C0000U\",\
		        \"pin\": 26,\
		        \"muxReg\": \"0x401F80B4U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F82A4U\"\
		      },\
		      {\
		        \"ChannelNum\": 10,\
	            \"port\": \"0x401C0000U\",\
		        \"pin\": 13,\
		        \"muxReg\": \"0x401F81C0U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F83B0U\"\
		      },\
		      {\
		        \"ChannelNum\": 11,\
	            \"port\": \"0x401C0000U\",\
		        \"pin\": 12,\
		        \"muxReg\": \"0x401F81BCU\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F83ACU\"\
		      },\
		      {\
		        \"ChannelNum\": 12,\
	            \"port\": \"0x401C0000U\",\
		        \"pin\": 15,\
		        \"muxReg\": \"0x401F81C8U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F83B8U\"\
		      },\
		      {\
		        \"ChannelNum\": 13,\
	            \"port\": \"0x401C0000U\",\
		        \"pin\": 14,\
		        \"muxReg\": \"0x401F81C4U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F83B4U\"\
		      },\
		      {\
		        \"ChannelNum\": 14,\
	            \"port\": \"0x401BC000U\",\
		        \"pin\": 18,\
		        \"muxReg\": \"0x401F8184U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F8374U\"\
		      },\
		      {\
		        \"ChannelNum\": 15,\
	            \"port\": \"0x401BC000U\",\
		        \"pin\": 27,\
		        \"muxReg\": \"0x401F81A8U\",\
		        \"muxMode\": \"0x5U\",\
		        \"inputReg\": 0,\
		        \"inputDaisy\": 0,\
		        \"configReg\": \"0x401F8398U\"\
		      }\
		    ],\
		\"irqcfg\": [\
			{\
                \"irqtype\": 88\
			},\
		    {\
				\"irqtype\": 80\
			},\
			{\
                \"irqtype\": 81\
			},\
		    {\
                \"irqtype\": 83\
			},\
		    {\
                \"irqtype\": 84\
			},\
		    {\
                \"irqtype\": 85\
			}\
		   ]\
		  },\
  \"bo\": {\
		    \"pop\": \"65535\",\
		    \"relay\": [\
		      {\
		        \"port\": \"0x401B8000U\",\
		        \"pin\": 1,\
		        \"portInvert\": 1,\
		        \"pwmBase\": \"0x403DC000U\",\
		        \"pwmSub\": 2,\
				\"pwmControlModule\": 4,\
				\"pwmChannel\": 1,\
		        \"muxReg\": \"0x401F81CCU\",\
		        \"muxMode\": \"0x1U\",\
		        \"inputReg\": \"0x401F8460U\",\
		        \"inputDaisy\":  \"0x4U\",\
		        \"configReg\": \"0x401F83BCU\"\
		      },\
		      {\
				\"port\": \"0x401B8000U\",\
				\"pin\": 1,\
				\"portInvert\": 1,\
		        \"pwmBase\": \"0x403E8000U\",\
		        \"pwmSub\": 2,\
				\"pwmControlModule\": 4,\
				\"pwmChannel\": 1,\
		        \"muxReg\": \"0x401F81B4U\",\
		        \"muxMode\": \"0x1U\",\
		        \"inputReg\": \"0x401F849CU\",\
		        \"inputDaisy\": \"0x1U\",\
		        \"configReg\": \"0x401F83A4U\"\
		      },\
			  {\
				\"port\": \"0x401B8000U\",\
				\"pin\": 1,\
				\"portInvert\": 1,\
		        \"pwmBase\": \"0x403DC000U\",\
		        \"pwmSub\": 2,\
				\"pwmControlModule\": 4,\
				\"pwmChannel\": 0,\
		        \"muxReg\": \"0x401F81D0U\",\
		        \"muxMode\": \"0x1U\",\
		        \"inputReg\": \"0x401F8470U\",\
		        \"inputDaisy\": \"0x1U\",\
		        \"configReg\": \"0x401F83C0U\"\
		      },\
		      {\
				\"port\": \"0x401B8000U\",\
				\"pin\": 1,\
				\"portInvert\": 1,\
		        \"pwmBase\": \"0x403DC000U\",\
		        \"pwmSub\": 3,\
				\"pwmControlModule\": 8,\
				\"pwmChannel\": 0,\
		        \"muxReg\": \"0x401F80E8U\",\
		        \"muxMode\": \"0x1U\",\
		        \"inputReg\": \"0x401F8464U\",\
		        \"inputDaisy\": \"0x3U\",\
		        \"configReg\": \"0x401F82D8U\"\
		      },\
			  {\
		        \"port\": \"0x401B8000U\",\
		        \"pin\": 3,\
		        \"portInvert\": 1,\
				\"pwmBase\": \"0x403E8000U\",\
				\"pwmSub\": 3,\
				\"pwmControlModule\": 8,\
				\"pwmChannel\": 1,\
		        \"muxReg\": \"0x401F81B8U\",\
		        \"muxMode\": \"0x1U\",\
		        \"inputReg\": \"0x401F84A0U\",\
		        \"inputDaisy\": \"0x1U\",\
		        \"configReg\": \"0x401F83A8U\"\
		      },\
			  {\
				\"port\": \"0x401B8000U\",\
				\"pin\": 1,\
				\"portInvert\": 1,\
		        \"pwmBase\": \"0x403E8000U\",\
		        \"pwmSub\": 0,\
				\"pwmControlModule\": 1,\
				\"pwmChannel\": 1,\
		        \"muxReg\": \"0x401F811CU\",\
		        \"muxMode\": \"0x1U\",\
		        \"inputReg\": \"0x401F8494U\",\
		        \"inputDaisy\": \"0x1U\",\
		        \"configReg\": \"0x401F830CU\"\
		      },\
			  {\
				\"port\": \"0x401B8000U\",\
				\"pin\": 1,\
				\"portInvert\": 1,\
		        \"pwmBase\": \"0x403E0000U\",\
		        \"pwmSub\": 3,\
				\"pwmControlModule\": 8,\
				\"pwmChannel\": 0,\
		        \"muxReg\": \"0x401F8188U\",\
		        \"muxMode\": \"0x6U\",\
		        \"inputReg\": \"0x401F8484U\",\
		        \"inputDaisy\": \"0x3U\",\
		        \"configReg\": \"0x401F8378U\"\
		      },\
			  {\
				\"port\": \"0x401B8000U\",\
				\"pin\": 1,\
				\"portInvert\": 1,\
		        \"pwmBase\": \"0x403E0000U\",\
		        \"pwmSub\": 3,\
				\"pwmControlModule\": 8,\
				\"pwmChannel\": 1,\
		        \"muxReg\": \"0x401F8184U\",\
		        \"muxMode\": \"0x6U\",\
		        \"inputReg\": \"0x401F8474U\",\
		        \"inputDaisy\": \"0x4U\",\
		        \"configReg\": \"0x401F8374U\"\
		      }\
		    ],\
		\"triac\": [\
				    ]\
		  },\
  \"ecc608\": {\
	\"cfg\": [\
		{\
		 \"I2CbaseAddr\": \"0x403FC000U\",\
		 \"pinConfig\": 2,\
		 \"baudrate\": 100000\
		}\
		]\
	},\
  \"ai\": {\
    \"pop\": 255,\
    \"cfg\": [\
      {\
        \"muxReg\": 1,\
        \"muxMode\": 1,\
        \"inputReg\": 1,\
        \"inputDaisy\": 1,\
        \"configReg\": 1,\
        \"inputOnfield\": 1,\
        \"configValue\": 1,\
        \"mcuAdcChannelNo\": 1,\
        \"mcuAdcInstance\": 1,\
        \"VENBase\": 1,\
        \"VENPin\": 1\
      },\
      {\
        \"muxReg\": 1,\
        \"muxMode\": 1,\
        \"inputReg\": 1,\
        \"inputDaisy\": 1,\
        \"configReg\": 1,\
        \"inputOnfield\": 1,\
        \"configValue\": 1,\
        \"mcuAdcChannelNo\": 1,\
        \"mcuAdcInstance\": 1,\
        \"VENBase\": 1,\
        \"VENPin\": 1\
      }\
    ]\
  },\
		 \"ao\": {\
    \"pop\": 255,\
    \"cfg\": [\
      {\
        \"maxVoltage\": 1,\
        \"ftm\": 1,\
        \"ftmChannel\": 1\
      },\
      {\
        \"maxVoltage\": 1,\
        \"ftm\": 1,\
        \"ftmChannel\": 1\
      }\
    ]\
  },\
 \"uio\": {\
    \"pop\": 255,\
  \"spi\": 0,\
    \"cfg\": [\
      {\
        \"spi\": 1,\
        \"cs\": 0,\
        \"ch\": 1\
      },\
      {\
        \"spi\": 1,\
        \"cs\": 0,\
        \"ch\": 2\
      },\
      {\
        \"spi\": 1,\
        \"cs\": 0,\
        \"ch\": 3\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 0,\
        \"ch\": 4\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 1,\
        \"ch\": 1\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 1,\
        \"ch\": 2\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 1,\
        \"ch\": 3\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 1,\
        \"ch\": 4\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 2,\
        \"ch\": 1\
      },\
      {\
        \"spi\": 1,\
        \"cs\": 2,\
        \"ch\": 2\
      },\
      {\
        \"spi\": 1,\
        \"cs\": 2,\
        \"ch\": 3\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 2,\
        \"ch\": 4\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 3,\
        \"ch\": 1\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 3,\
        \"ch\": 2\
      },\
		{\
        \"spi\": 1,\
        \"cs\": 3,\
        \"ch\": 3\
      },\
      \
      /* this is the comment*/\
      /* this is the comment*/\
      {\
        \"spi\": 1,\
        \"cs\": 3,\
        \"ch\": 4\
      }\
    ]\
  }\
		}";









