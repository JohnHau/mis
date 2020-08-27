#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <mcrypt.h>
#include <openssl/sha.h>

#include <mbedtls/aes.h>
#include <mbedtls/ssl.h>
#include <mbedtls/x509.h>

#include <math.h>



#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <pthread.h> 



#ifndef byte
typedef unsigned char byte;
#endif

#ifndef _octet
typedef unsigned char octet;
#define _octet
#endif

#ifndef _dword
typedef unsigned long dword;
#define _dword
#endif

#ifndef _word
typedef unsigned short word;
#define _word
#endif//	
#define	littleEndian	1   //PCs are littleEndian
#define LOGMESSAGE  printf

//#define false 0
//#define false 1




#define	BroadcastDNET			0xFFFF
#define	NSDUisNLmessage			0x80		//1==NL message, 0=APDU
//					0x40		//reserved
#define NSDUhasDNET			0x20		//1==DNET, DLEN, HopCount present
//							0x10			//reserved
#define NSDUhasSNET			0x08		//1==SNET, SLEN present
#define NSDUexpectsreply		0x04
#define NSDUpriority			0x03		//mask for priority field
#define NSDUnormalreply			0x00



#define	ASDUpdutype			0xF0	//mask for pdu type field
#define	ASDUpdutypeshr			4		//shift right this many times to get it
#define	ASDUissegmented			0x08		//all segmented types have this bit set
#define ASDUmoresegments		0x04		//1=more segments
#define ASDUsegmentrespaccepted         0x02			//1=segmented responses accepted
#define ASDUnak				0x02	//1=segmented NAK, 0=segmented ACK
#define ASDUserver			0x01	//1=from a server, 0=from a client
#define ASDUMaxResp			0x0F	//mask for max response
#define ASDUMaxSegs			0x70	//mask for max segments		***505




#define biggestmac	1500  





typedef enum { false, true } bool;


enum BACnetConfirmedService
{
	//Alarm and Event Services
	acknowledgeAlarm,						//0
	confirmedCOVNotification,				//1
	confirmedEventNotification,				//2
	getAlarmSummary,						//3
	getEnrollmentSummary,					//4
	subscribeCOV,							//5
	//File Access Services
	atomicReadFile,							//6
	atomicWriteFile,						//7
	//Object Access Services
	addListElement,							//8
	removeListElement,						//9
	createObject,							//10
	deleteObject,							//11
	readProperty,							//12
	service13,								//13	DEPRECATED	***1200
	readPropertyMultiple,					//14
	writeProperty,							//15
	writePropertyMultiple,					//16
	//Remote Device Management Services
	deviceCommunicationControl,				//17
	confirmedPrivateTransfer,				//18
	confirmedTextMessage,					//19
	reinitializeDevice,						//20
	//Virtual Terminal Services
	vtOpen,									//21
	vtClose,								//22
	vtData,									//23
	//Security Services
	authenticate,							//24
	requestKey,								//25
	readRange,								//26							***210 Begin
	lifeSafetyOperation,					//27
	subscribeCOVProperty,					//28
	getEventInformation						//29							***210 End
};




enum BACnetPDUTypes
{	CONF_REQ_PDU,							//0
	UNCONF_REQ_PDU,							//1
	SIMPLE_ACK_PDU,							//2
	COMPLEX_ACK_PDU,						//3
	SEGMENT_ACK_PDU,						//4
	ERROR_PDU,								//5
	REJECT_PDU,								//6
	ABORT_PDU								//7
} ;


enum BACnetUnconfirmedService
{
	IAm,									//0
	IHave,									//1
	unconfirmedCOVNotification,				//2
	unconfirmedEventNotification,			//3
	unconfirmedPrivateTransfer,				//4
	unconfirmedTextMessage,					//5
	timeSynchronization,					//6
	whoHas,									//7
	whoIs,									//8
	UTCtimeSynchronization,					//9								***004
	writeGroup								//10							***1400
};








typedef struct	_frSource {
	// Note: The srlen, sradr, snet have the SLEN, SADR and SNET from an incoming NPDU	***500
	//       The drlen, dradr, dnet have the DLEN, DADR and DNET from an incoming NPDU
	//       These get flipped for outgoing packets (ie. snet becomes DNET, dnet becomes SNET, etc.)
	word	snet;					///note native endian!			***1210
	word	dnet;					///note native endian!			***1210
	word	maxlen;					//max APDU len accepted
	word	maxsegs;				//max segments accepted			***505
	octet	port;					//the source port
	octet	slen;					//the length of sadr (or unknowndevice)
	octet	sadr[8];				//the source address
	octet	srlen;					//the length of sradr			***500 Begin
	octet	sradr[8];				//the the source routed address
	octet	drlen;					//the length of dradr
	octet	dradr[8];				//the the destination routed address
	octet	segmentation;			//0=no, 1=supports segmented receives		***507 End
	octet	reserved[3];			//round up to even dword boundary	***1411
} frSource;








typedef struct _frNpacket {
	struct _frNpacket *next;		//link to next one
#ifdef deinitrelease
	struct _frNpacket *deinit;		//link to next one		***423
#endif
	octet		*apdu;			//pointer into npdu		***507
	frSource	src;				//where it came from
	word		nlen;				//number of bytes in the bag
	octet		reply;			//0=no, 1=reply expected
	octet		nflag;		//(see defines in npool.h)		***423
	octet		netpriority;	//		***1414
	octet		npdu[biggestmac];	//bag for bytes
	octet       secureflag;
} frNpacket;






typedef struct _NPCI {								//NPCI
	octet	npciVersion;
	octet	npciControl;
	word	npciDNET;
	octet	npciDLEN;
	octet	npciDADR[8];
} NPCI;



typedef struct _NSRC {								//NSRC
	word	SNET;
	octet	SLEN;
	octet	SADR[8];
} NSRC;



typedef struct _ASDUREQ {	//ASDU for Confirmed Requests
	octet	asdureqPDUheader;
	octet	asdureqMaxResponse;
	octet	asdureqInvokeID;
	octet	asdureqServiceChoice;
	octet	asdureqPDU;
} ASDUREQ;


//Note:	these ASDU structs assume that segmented PDUs have been filtered out already!
typedef struct _ASDU {	//ASDU
	octet	asduPDUheader;
	octet	asduInvokeID;
	octet	asduServiceAckChoice; 				//ComplexACK
	octet	asduPDU;
} ASDU;







//====================================================================================
//function declaration
//====================================================================================
void ParsePrivateTransfer(frNpacket *am,octet *op,word apdulen);






//====================================================================================












#define dm_pt_a		1					//Device Management-Private Transfer-A (Confirmed/UnconfirmedPrivateTransfer initiate)

#define PORT     0xBAC0 
#define MAXLINE  1500 

#define  IV_SIZE   32 
#define aeskey_size   32

octet NpduHeader[20];
octet ApduInput[1476];
octet ApduOutput[1476];
octet ApduOutputtemp[1476];
octet npdutemp[1500];
octet ApduPackage[1476];
octet plain_decrypt[1476];
octet tb[1476];
octet myBuff[1476];


octet am_apdu[2048]={0};



frNpacket x_am;


uint8_t tkey[32] = {0};


int64_t timestamp =0;
int64_t timestampfromApdu =0;
int64_t timestampfromApdutmp=0;











int stn=0;

uint8_t bqr_whois[]={
	0x81,0x0a,0x00,0x0c,0x01,0x20,
	0xff,0xff,0x00,0xff,0x10,0x08

};


uint8_t brp_im[]={
	0x81,0x0b,0x00,0x19,0x01,0x20,0xff,0xff,0x00,0xff,0x10,0x00,0xc4,0x02,0x00,0x03,
	0xf1,0x22,0x04,0x00,0x91,0x03,0x22,0x01,0x04
};

#define DEVICE_IDH   bqr_rp[12]
#define DEVICE_IDM   bqr_rp[13]
#define DEVICE_IDL   bqr_rp[14]



//uint8_t bqr_rp[32]={
//octet bqr_rp[32]={
octet bqr_rp[2048]={
	0x81,0x0a,0x00,0x11,
	0x01,0x04,
	0x00,0x03,0x00,0x0c,0x0c,0x02,
	//0x00,0x03,0xeb,0x19,0x2c
	0x3f,0xff,0xfe,0x19,0x2c


};

word npdu_len= 0x11 - 4;
//word npdu_len= 0x11 - 6;


uint8_t test_package[1476]={0};




uint8_t s_bqr_rp[32]={0};


uint8_t sbuffer[32]={0};








MCRYPT td, td2;
int keysize = 16; /* 128 bits */
int buffer_len = 16;

uint8_t key1[32] = {
	0x03, 0x87, 0xb0, 0x67, 0x97,0x51, 0xa7,0x48,0x1f, 0xbe,0x5c,0x32 ,0x7c, 0x17, 0xff, 0xab,
	0x62, 0x1c, 0xc6 ,0x73, 0x3 ,0xe5, 0x28,0x40,0xf1, 0x16,0x84,0xc5 ,0x2d, 0xa4, 0x5d, 0xb3 
};

uint8_t keyAes128[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

uint8_t keyAes256[] = {
	'a','a','a','a','a','a','a','a','a','a','a','a','a', 'a','a','a',
	'a','a','a','a','a','a','a','a','a','a','a','a','a', 'a','a','a',
};




uint8_t plainAes128[] = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};

uint8_t cipherAes128[] = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97};

uint8_t ive[] =  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

uint8_t iven[] = {
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
};

uint8_t plainAes256[] = {
	'v','v','a','a','a','a','a','a','a','a','a','a','a', 'a','a','a',
	'a','a','a','a','a','a','a','a','a','a','a','a','a', 'a','a','a',
};

uint8_t cipherAes256[] = {
	0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
	0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97
};




int encrypt( void* buffer, int buffer_len, /* Because the plaintext could include null bytes*/ char* IV, char* key, int key_len )
{
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	//MCRYPT td = mcrypt_module_open("rijndael-256", NULL, "cbc", NULL);
	//MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "ecb", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, IV);
	mcrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}

int decrypt( void* buffer, int buffer_len, char* IV, char* key, int key_len )
{
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, IV);
	mdecrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}


int mencrypt( void* buffer, int buffer_len, /* Because the plaintext could include null bytes*/ char* IV, char* key, int key_len )
{
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "ecb", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, NULL);
	mcrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}


int xmain()
{

	//buffer = calloc(1, buffer_len);
	//strncpy(buffer, plaintext, buffer_len);
	//strncpy(buffer, plainAes128, buffer_len);

	//printf("==C==\n");
	//printf("plain:   %s\n", plaintext);
	//	encrypt(buffer, buffer_len, IV, key, keysize); 
	//encrypt(buffer, buffer_len, ive, keyAes128, keysize); 

	//keysize = 32;
	//encrypt(buffer, buffer_len, ive, keyAes256, keysize); 
	//mencrypt(buffer, buffer_len, NULL, keyAes128, keysize); 



	//printf("cipher:  "); display(buffer , buffer_len);
	//decrypt(buffer, buffer_len, IV, key, keysize);
	//printf("decrypt: %s\n", buffer);

	return 0;
}







/////////////////////////////////////////////////////////////////////// 
//	Encode an Application Tagged Octet String
//in:	op		points to an octet buffer to put the results in
//		os		points to the octet string to encode
//		n		has the number of octets to encode(0-65535)
//out:	return	advanced pointer to buffer

octet *eOCTETSTRING(octet *op, octet *os, word n)
{
	union { word w; byte b[2];} u;
	word	i;

	u.w=n;		//so we can get byte access
	if(n<=4)
		*op++=0x60+(octet)n;	//tag 6, length
	else
	{
		*op++=0x65;				//tag 6, extended length
		if(n<=253)
			*op++=(octet)n;
		else					//assume n<=65535
		{	*op++=0xFE;
#if littleEndian				//		***230 Begin
			*op++=(octet)u.b[1];	//msb of length first
			*op++=(octet)u.b[0];
#else
			*op++=(octet)u.b[0];	//msb of length first
			*op++=(octet)u.b[1];
#endif								//		***230 End
		}	
	}
	for(i=0;i<n;i++)				//store all octets in order
		*op++=*os++;			
	return op;
}




/////////////////////////////////////////////////////////////////////// 
//	Encode an Application Tagged 4 octet minimal encoding value
//in:	op		points to an octet buffer to put the results in
//		val		has the value to encode
//		utag	is the tag value to use, e.g. 0x20 is tag 2
//		sgnd	true if signed, false if unsigned
//out:	return	advanced pointer to buffer

octet *eDWORD(octet *op, dword val,octet utag,bool sgnd)
{
	union { dword dw; byte b[4];} u;
	int		i;
	bool 	ffndb=false;			//found first non-discardable byte
	bool	db;						//true if this is a discardable byte

	u.dw=val;						//so we can get at individual bytes
	*op++=utag+0x04;				//tag(utag), assume 4 octets(dword)
#if littleEndian							//	***230 Begin
	for(i=3;i>=0;i--)				//store all bytes from first non-0 ms byte, ms first, ls last
	{
		db=(u.b[i]==0);				//if 0, it's discardable
		if(sgnd&&(u.b[i]==0xFF)) db=true;			//also discardable if signed and it's FF
		//
		// The following code is added so that the following cases of SIGNED numbers are encoded properly:
		//		0x00000080	encoded as 32 00 80
		//		0xFFFFFF80	encoded as 31 80
		//		0xFFFFFF7F	encoded as 32 FF 7F
		//		etc.
		if(sgnd && db && !ffndb &&(i!=0))		//it's signed and possibly discardable
		{
			if((u.b[i]==0) &&((u.b[i-1]&0x80) != 0)) db=false;		//don't discard
			else if((u.b[i]==0xFF) &&((u.b[i-1]&0x80) == 0)) db=false;	//don't discard 
		}
		//
		if(!db||ffndb||i==0)
		{
			*op++=(octet)u.b[i];					//save byte
			ffndb=true;								//we found first non-discardable byte
		}
		else
			op[-1]--;								//one less digit than assumed
	}			
#else
	for(i=0;i<4;i++)								//store all bytes from first non-0 ms byte, ms first, ls last
	{
		db=(u.b[i]==0);												//if 0, it's discardable
		if(sgnd&&(u.b[i]==0xFF)) db=true;			//also discardable if signed and it's FF
		//
		// The following code is added so that the following cases of SIGNED numbers are encoded properly:
		//		0x00000080	encoded as 32 00 80
		//		0xFFFFFF80	encoded as 31 80
		//		0xFFFFFF7F	encoded as 32 FF 7F
		//		etc.
		if(sgnd && db && !ffndb &&(i!=3))			 //it's signed and possibly discardable	***303
		{
			if((u.b[i]==0) &&((u.b[i+1]&0x80) != 0)) db=false;		//don't discard
			else if((u.b[i]==0xFF) &&((u.b[i+1]&0x80) == 0)) db=false;	//don't discard 
		}
		//
		if(!db||ffndb||i==3)						//	***303
		{	*op++=(octet)u.b[i];					//save byte
			ffndb=true;								//we found first non-discardable byte
		}
		else
			op[-1]--;								//one less digit than assumed
	}			
#endif												//***230 End
	return op;
}


/////////////////////////////////////////////////////////////////////// 
//	Encode an Application Tagged Enumerated Value
//in:	op		points to an octet buffer to put the results in
//		eval	has the dword enumerated value to encode
//out:	return	advanced pointer to buffer

octet *eENUM(octet *op, dword eval)
{
	return eDWORD(op,eval,0x90,false);				//minimal encode using tag 9
}

///////////////////////////////////////////////////////////////////////
//	Encode the body of a Private Transfer request
//
// in:	tp			points to the buffer to encode into (assumes there's enough space)
//		vendorid	the vendor id of the private transfer
//		svc			the service code
//		params		pointer to the response/error parameters (or NULL if nbytes==0)
//		nbytes		the number of octets in params
// out:	tp			advanced or NULL if failed

octet *EncodePrivateTransfer(octet *tp,word vendorid,dword svc,octet *params,dword nbytes)
{
#if dm_pt_a				//	***206
	dword	i;

	tp=eDWORD(tp,vendorid,0x08,false);	//[0]vendorID
	tp=eDWORD(tp,svc,0x18,false);		//[1]serviceNumber
	if (nbytes&&(params!=NULL))
	{	//probably should check if we have enough space here!
		*tp++=0x2E;			//[2]opening tag serviceParameters
		for (i=0;i<nbytes;i++)
			*tp++=*params++;                        //serviceParameters
		*tp++=0x2F;			//[2]closing tag serviceParameters
	}
	return tp;
#else 						//		***206									
	return NULL;				//		***206
#endif //dm_pt_a
}





/////////////////////////////////////////////////////////////////////// 
//	Decode an Application Tagged 4 octet minimal encoded value
//
//in:	np		is the address of the pointer to the tag in an octet buffer
//		sgnd	true if signed, false if unsigned
//out:	return	the dword value
//		np		advanced

dword dDWORD(octet *(*np),bool sgnd)			//argument is passed by reference, ie. the address of a pointer
{
union { dword dw; byte b[4];} u;
	int		i,n;
	octet	utag;					//	***705
    
	utag=*(*np)&0xF0;				//	***705
	n=(*(*np)++)&7;
	if (n==0) return 0;				//	***300
	if (n>4) n=4;					//	***300
	if (utag==0xF0)					//we had an "extended tag" i.e. 0xF9 0x10 0x00 means tag 16, one byte value=0	***705
		*(*np)++;									//skip the extended tag...it's not included in the count n						***705
	u.dw=((sgnd)&&((*(*np)&0x80)!=0))?-1:0;	//initialize for signed or unsigned 
#if littleEndian					//									***230 Begin
	for(i=n-1;i>=0;i--)				//store bytes ms last, ls first
		u.b[i]=*(*np)++;
#else
	for(i=4-n;i<4;i++)				//store bytes ms last, ls first		***400 fixed "w" typo
		u.b[i]=*(*np)++;
#endif					//		***230 End
	return u.dw;
}


/////////////////////////////////////////////////////////////////////// 
//	Decode a Context Specific Tagged Value
//
//in:	np		is the address of the pointer to the tag in an octet buffer
//		sgnd	true if return value is to be signed
//out:	return	dword value
//		np		advanced

dword dCONTEXT(octet *(*np), bool sgnd)				//argument is passed by reference, ie. the address of a pointer
{
	return dDWORD(np,sgnd);							//minimal decode
}










int EncrypteApdu(word apduLen)
{
	int ret =0;
	int i=0;
	octet iv[IV_SIZE];
	octet digest[32];

	memset(iv, 0x55, IV_SIZE);
	mbedtls_aes_context aes_ctx;
	mbedtls_md_context_t sha_ctx;
	mbedtls_aes_init( &aes_ctx );
	ret |= mbedtls_aes_setkey_enc( &aes_ctx, tkey, aeskey_size * 8);
	ret |= mbedtls_aes_crypt_cbc( &aes_ctx, MBEDTLS_AES_ENCRYPT, apduLen, iv,ApduInput,ApduOutput );
	if( ret != 0 )
	{
		goto exit;
	}
	//LOGMESSAGE("after encryption,start to add hamc sign\n");
	printf("after encryption,start to add hamc sign\n");
#if 0
	//LOGMESSAGE("*********** after the encryption\n");
	printf("*********** after the encryption\n");
	for(i=0;i<apduLen;i++)
		//LOGMESSAGE("0x%x ",ApduOutput[i]);
		printf("0x%x ",ApduOutput[i]);
	//LOGMESSAGE("\n");
	printf("\n");
#endif
	mbedtls_md_init(&sha_ctx);
	memset(digest, 0x00, sizeof(digest));
	if((ret = mbedtls_md_setup(&sha_ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 1))!=0)
	{
		goto cleanup;
	}
	if((ret =mbedtls_md_hmac_starts(&sha_ctx, tkey, aeskey_size))!=0)
	{
		goto cleanup;
	}
	if((ret =mbedtls_md_hmac_update(&sha_ctx, ApduOutput, apduLen))!=0)
	{
		goto cleanup;
	}
	if((ret =mbedtls_md_hmac_finish(&sha_ctx, digest))!=0)
	{
		goto cleanup;
	}
#if 0
	//LOGMESSAGE("HMAC: \n");
	printf("HMAC: \n");
	for(i=0;i<32;i++)
		//LOGMESSAGE("0x%x ",digest[i]);
		printf("0x%x ",digest[i]);
	//LOGMESSAGE("\n");
	printf("\n");
#endif
	//LOGMESSAGE("have add sign\n");
	printf("have add sign\n");
	memcpy(ApduOutput+apduLen,digest,32);

	/*mbedtls_aes_setkey_dec(&aes_ctx, tkey(), aeskey_size*8);//  set decrypt key
	  memset(iv, 0, IV_SIZE);
	  mbedtls_aes_crypt_cbc(&aes_ctx, MBEDTLS_AES_DECRYPT, apduLen, iv, ApduOutput, plain_decrypt);
	//LOGMESSAGE("*********** decrypted\n");
	printf("*********** decrypted\n");
	for(i=0;i<apduLen;i++)
	//LOGMESSAGE("0x%x ",plain_decrypt[i]);
	printf("0x%x ",plain_decrypt[i]);
	//LOGMESSAGE("\n");
	printf("\n");*/


cleanup:
	mbedtls_md_free( &sha_ctx);
exit:
	mbedtls_aes_free(&aes_ctx);
	return ret;
}



///////////////////////////////////////////jf////////////////////////////////////////
bool GetApdu(word len,word *NpduHeaderLen,word *ApduLen)
{	
	NPCI		*np;
	union {
#if alignedMachine					//	***507 Begin
		_unaligned NSRC *sp;
#else
		NSRC		*sp;
#endif							//	***507 End
		octet 	*rap;
	}		u;

	union {
		ASDUREQ	*ap;
		ASDU		*asp;
		octet 	*rap;
	}		apdu_struct;

	int			pdutype;
	octet		service;
	dword		svcnum;
	word		vendorid;
	octet		*op;

	np=(NPCI *)npdutemp;
	if(np->npciVersion!=1) 
		return false;				//pitch this one	***500
	u.rap=(octet *)&np->npciDNET;								//figure out where ASDU begins
	if(np->npciControl&NSDUhasDNET)
	{						//	***500 End
		u.rap=((octet *)np->npciDADR)+np->npciDLEN;		//point past dadr and dlen and dnet
	}
	if(np->npciControl&NSDUhasSNET)
	{	
		u.rap=((octet *)u.sp->SADR)+u.sp->SLEN;		//point past sadr and slen and snet
	}
	if(np->npciControl&NSDUhasDNET) 
		u.rap++;						//skip hopcount
	*NpduHeaderLen =u.rap-(octet *)np ;
	*ApduLen =len -(u.rap -(octet *)np);
	//frcpy(NpduHeader,np,*NpduHeaderLen);
	//frcpy(ApduInput,u.rap,*ApduLen);
	memcpy(NpduHeader,np,*NpduHeaderLen);
	memcpy(ApduInput,u.rap,*ApduLen);

	apdu_struct.rap=ApduInput;			//point to apdu
	pdutype=((apdu_struct.asp->asduPDUheader&ASDUpdutype)>>ASDUpdutypeshr); //get the pdu type field
	LOGMESSAGE("GetApdu: pdu=%2.2X\n",pdutype);
	switch(pdutype)
	{
		case UNCONF_REQ_PDU: //1
			LOGMESSAGE("UNCONF_REQ_PDU send ");
			switch(ApduInput[1])
			{
				case IAm: LOGMESSAGE("IAm");	break;								//0
				case IHave:	LOGMESSAGE("IHave");	break;								//1
				case unconfirmedCOVNotification:	LOGMESSAGE("unconfirmedCOVNotification");	break;		//2
				case unconfirmedEventNotification:	LOGMESSAGE("unconfirmedEventNotification");	break;		//3
				case unconfirmedPrivateTransfer:	LOGMESSAGE("unconfirmedPrivateTransfer");		break;	//4
				case unconfirmedTextMessage:	LOGMESSAGE("unconfirmedTextMessage");	break;				//5
				case timeSynchronization:	LOGMESSAGE("timeSynchronization");	break;		//6
				case whoHas:	LOGMESSAGE("whoHas");	break;						//7
				case whoIs:		LOGMESSAGE("whoIs");	break;					//8
				case UTCtimeSynchronization:	LOGMESSAGE("UTCtimeSynchronization");	break;		//9	***004
				case writeGroup:	LOGMESSAGE("writeGroup");	break;				//10
			}
			LOGMESSAGE("\n");
			break;
		case CONF_REQ_PDU:    //0
			LOGMESSAGE("CONF_REQ_PDU send \n");
			op=(octet *)ApduInput;
			op+=4;
			vendorid=(word)dCONTEXT(&op,false);
			svcnum=dCONTEXT(&op,false);
			if((vendorid ==17)&&((svcnum>=80)&&(svcnum<=100)))
			{
				return false;
			}

			break;
		case SEGMENT_ACK_PDU: //4
			LOGMESSAGE("SEGMENT_ACK_PDU send \n");break;
		case COMPLEX_ACK_PDU:  //3
			LOGMESSAGE("COMPLEX_ACK_PDU send \n");
			service=apdu_struct.asp->asduServiceAckChoice;
			switch(service)
			{
				case acknowledgeAlarm:	
					LOGMESSAGE("acknowledgeAlarm\n");	break;				//0
				case confirmedCOVNotification:	
					LOGMESSAGE("confirmedCOVNotification\n");	break;			//1
				case confirmedEventNotification:	LOGMESSAGE("confirmedEventNotification\n");	break;		//2
				case getAlarmSummary:	LOGMESSAGE("getAlarmSummary");		break;			//3
				case getEnrollmentSummary:		LOGMESSAGE("getEnrollmentSummary\n");	break;			//4
				case subscribeCOV:	LOGMESSAGE("subscribeCOV\n");		break;					//5
							//File Access Services
				case atomicReadFile:	LOGMESSAGE("atomicReadFile\n");	break;						//6
				case atomicWriteFile:		LOGMESSAGE("atomicWriteFile\n");	break;			//7
								//Object Access Services
				case addListElement:	LOGMESSAGE("addListElement\n");	break;						//8
				case removeListElement:		LOGMESSAGE("removeListElement\n");	break;				//9
				case createObject:		LOGMESSAGE("createObject\n");		break;			//10
				case deleteObject:		LOGMESSAGE("deleteObject\n");		break;			//11
				case readProperty:		LOGMESSAGE("readProperty\n");		break;			//12
				case service13:		LOGMESSAGE("service13\n");	break;			//13	DEPRECATED	***1200
				case readPropertyMultiple:	LOGMESSAGE("readPropertyMultiple\n");		break;		//14
				case writeProperty:		LOGMESSAGE("writeProperty\n");	break;					//15
				case writePropertyMultiple:		LOGMESSAGE("writePropertyMultiple\n");	break;		//16
									//Remote Device Management Services
				case deviceCommunicationControl:	LOGMESSAGE("deviceCommunicationControl\n");	break;		//17
				case confirmedPrivateTransfer:

									op=(octet *)ApduInput;
									op+=3;
									LOGMESSAGE("confirmedPrivateTransfer\n");
									vendorid=(word)dCONTEXT(&op,false);
									svcnum=dCONTEXT(&op,false);
									if((vendorid ==17)&&((svcnum>=80)&&(svcnum<=100)))
									{
										return false;
									}

									break;//18
				case confirmedTextMessage:		LOGMESSAGE("confirmedTextMessage\n");		break;	//19
				case reinitializeDevice:		LOGMESSAGE("reinitializeDevice\n");		break;		//20
									//Virtual Terminal Services
				case vtOpen:	LOGMESSAGE("vtOpen\n");		break;						//21
				case vtClose:	LOGMESSAGE("vtClose\n");		break;					//22
				case vtData:	LOGMESSAGE("vtData\n");		break;						//23
						//Security Services
				case authenticate:	LOGMESSAGE("authenticate\n");		break;				//24
				case requestKey:	LOGMESSAGE("requestKey\n");		break;						//25
				case readRange:		LOGMESSAGE("readRange\n");		break;				//26		***210 Begin
				case lifeSafetyOperation:		LOGMESSAGE("lifeSafetyOperation\n");		break;	//27
				case subscribeCOVProperty:		LOGMESSAGE("subscribeCOVProperty\n");		break;	//28
				case getEventInformation:		LOGMESSAGE("getEventInformation\n");		break;			//29
			}
			LOGMESSAGE("\n");
			break;
		case SIMPLE_ACK_PDU:   //2
			LOGMESSAGE("SIMPLE_ACK_PDU send \n");
			return false;
			break;
		case ERROR_PDU:     //5
			LOGMESSAGE("ERROR_PDU send \n");
			return false;
			break;
		case REJECT_PDU:     //6
			LOGMESSAGE("REJECT_PDU send \n");
			return false;
			break;
		case ABORT_PDU:     //7
			LOGMESSAGE("ABORT_PDU send \n");
			return false;
			break;
	}
	return true;			//	***500
}



void macEncryptionTransmit(word *dlen, octet *np)
{
	word ApduLen,NpduHeaderLen,NpduLen,Apdulentmp;
	octet	*tp;
	word vendorid =17;
	dword svc =0x90;
	int i=0;



	octet *encodedOctetString = NULL;
	encodedOctetString = tb;
	int TotalLength = 0;
	memset(npdutemp,0x00,1500);
	memcpy(npdutemp,np,*dlen);
	memset(ApduInput,0,1476);
	memset(ApduOutput,0,1476);

	if(GetApdu(*dlen,&NpduHeaderLen,&ApduLen)==false)
	{

		printf("GetApdu returned\n");

		return;
	}

	//	NpduHeaderLen = 2;
	//	ApduLen =  0x11-4-2;
	//	memcpy(NpduHeader,bqr_rp + 4,2);
	//	memcpy(ApduInput,bqr_rp + 4 + 2,11);



#if 1
	/*
	//LOGMESSAGE("NpduHeaderLen %d\n",NpduHeaderLen);
	printf("NpduHeaderLen %d\n",NpduHeaderLen);
	for(i=0;i<NpduHeaderLen;i++)
	//LOGMESSAGE("0x%x ",NpduHeader[i]);
	printf("0x%x ",NpduHeader[i]);

	//LOGMESSAGE("\n");
	printf("\n");
	*/

	//LOGMESSAGE("ApduLen %d\n",ApduLen);
	printf("ApduLen %d\n",ApduLen);
	//LOGMESSAGE("Apdu :\n");
	printf("Apdu :\n");
	for(i=0;i<ApduLen;i++)
		//LOGMESSAGE("0x%x ",ApduInput[i]);
		printf("0x%x ",ApduInput[i]);
	//	LOGMESSAGE("\n");
	printf("\n");
#endif
	//LOGMESSAGE("get apdu response,start to add time and encrypt\n");
	printf("get apdu response,start to add time and encrypt\n");
	//timestamp++;
	timestamp=0x00;
	Apdulentmp =ApduLen;

	memcpy(ApduInput+ApduLen,&timestamp,8);
	ApduLen = ApduLen+8;
	if(ApduLen%16 !=0)
		ApduLen =ApduLen +16-ApduLen%16;
	if((ApduLen +32 +2 )<1472)
	{
		EncrypteApdu(ApduLen);
		ApduLen =ApduLen+32;
#if 1
		//LOGMESSAGE("after add HAMC signature:\n");
		//printf("after add HAMC signature:\n");
		//LOGMESSAGE("after add HAMC signature:\n");
		printf("after add HAMC signature:\n");
		for(i=0;i<ApduLen;i++)
		{
			//LOGMESSAGE("0x%02x ",ApduOutput[i]);
			printf("0x%02x ",ApduOutput[i]);
			if((i+1)%8 == 0)
				printf("\n");
		}
		//LOGMESSAGE("\n");
		printf("\n");
#endif
		memset(npdutemp,0,1500);
		memcpy(npdutemp,NpduHeader,NpduHeaderLen);
		tp=npdutemp + NpduHeaderLen;
		//*tp++=UNCONF_REQ_PDU<<4;
		//*tp++=unconfirmedPrivateTransfer;

		memcpy(ApduOutputtemp,&Apdulentmp,2);
		memcpy(ApduOutputtemp +2,ApduOutput,ApduLen);
#if 0
		//LOGMESSAGE("after add lengh :\n");
		printf("after add lengh :\n");
		for(i=0;i<ApduLen+2;i++)
			//LOGMESSAGE("0x%x ",ApduOutputtemp[i]);
			printf("0x%x ",ApduOutputtemp[i]);
		//LOGMESSAGE("\n");
		printf("\n");
#endif
		encodedOctetString = eOCTETSTRING(encodedOctetString,ApduOutputtemp,ApduLen+2);
		TotalLength = (dword)(encodedOctetString - tb);
		*tp++=UNCONF_REQ_PDU<<4;
		*tp++=unconfirmedPrivateTransfer;
		tp =EncodePrivateTransfer(tp,vendorid,svc,tb,TotalLength);
		NpduLen =tp -npdutemp;
		//LOGMESSAGE("transmit NPDU,length %d\n",NpduLen);
		printf("transmit NPDU,length %d\n",NpduLen);
#if 0

		for(i=0;i<NpduLen;i++)
			//LOGMESSAGE("0x%x ",npdutemp[i]);
			printf("0x%x ",npdutemp[i]);
		//LOGMESSAGE("\n");
		printf("\n");
#endif
		memcpy(np,npdutemp,NpduLen);
		*dlen =NpduLen;


		printf("at last npdu is\n");
		for(i=0;i<NpduLen;i++)
		{
			//LOGMESSAGE("0x%02x ",ApduOutput[i]);
			//printf("0x%02x ",np[i]);
			printf("0x%02x ",npdutemp[i]);
			if((i+1)%8 == 0)
				printf("\n");
		}
		//LOGMESSAGE("\n");
		printf("\n");















	}
}

/////////////////////////////////////////////////////////////////////// 
//	Decode an Application Tagged Octet String(Tag 6)
//
//in:	np		is the address of the pointer to the tag in an octet buffer
//		os		points to the octet string to decode into
//		max		has the max number of octets to decode(0-65535)
//out:	return	number of octets decoded(0-65535)
//		np		advanced

word dOCTETSTRING(octet *(*np),octet *os,word max)
{
	union { word w; byte b[2];} u;
	word	i,n;

	if((*(*np)&7)<=4)
		n=(*(*np)++)&7;				//tag 6, length
	else
	{
		(*np)++;				//tag 6, extended length	***1211
		if(*(*np)<=253)
			n=*(*np)++;
		else					//assume n<=65535
		{
			(*np)++;			//		***1211
#if littleEndian					//		***230 Begin
			u.b[1]=(byte)*(*np)++;		//msb of length first
			u.b[0]=(byte)*(*np)++;  
#else
			u.b[0]=(byte)*(*np)++;		//msb of length first
			u.b[1]=(byte)*(*np)++;  
#endif							//		***230 End
			n=u.w;
		}	
	}
	for(i=0;i<n;i++)	//store all octets in order
	{
		if (i<max)
			*os++=*(*np)++;
		else
			*(*np)++;		//consume it
	}
	return n;//		***703 End
}







void ParsePrivateTransfer(frNpacket *am,octet *op,word apdulen)
	//void ParsePrivateTransfer(octet *op,word apdulen)
{
	octet digest[32];
	octet buffer[32];
	octet key[32];


	int diff,i,len,ret;
	mbedtls_aes_context aes_ctx;
	mbedtls_md_context_t sha_ctx;
	octet iv[IV_SIZE];
	word apdulentmp;


	//myBuff[0]=0x81;
	//myBuff[1]=0x0a;
	//myBuff[2]=0x00;
	//myBuff[3]=0x52;

	memcpy(myBuff ,op + 13,32);

//	dword myBuffLen = dOCTETSTRING(&op, myBuff, apdulen);
	//memcpy(myBuff,op + 11,66);
	dword myBuffLen = 64;

	printf("==========mybufflen is %d\n",myBuffLen);

	//len =apdulen-32 -2;
	len =myBuffLen-32 -2;
	memcpy(&apdulentmp,myBuff,2);
	memcpy(ApduPackage,myBuff +2,len);

//==========================================================
//
	len =32;
	memcpy(ApduPackage,myBuff,len);

printf("apdu package is ========================\n");
for( i = 0; i < 32; i++ )
{
	printf("0x%02x ",ApduPackage[i]);
	if((i+1)%8 == 0)
		printf("\n");
}
printf("\n");





//==========================================================


	mbedtls_md_init(&sha_ctx);
	memset(digest, 0x00, sizeof(digest));














	if((ret = mbedtls_md_setup(&sha_ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 1))!=0)
	{
		goto exit;
	}
	if((ret =mbedtls_md_hmac_starts(&sha_ctx, tkey, aeskey_size))!=0)
	{
		goto exit;
	}
	if((ret =mbedtls_md_hmac_update(&sha_ctx, ApduPackage, len))!=0)
	{
		goto exit;
	}
	if((ret =mbedtls_md_hmac_finish(&sha_ctx, digest))!=0)
	{
		goto exit;
	}

//===========================================================================
printf("digest is ========================\n");
for( i = 0; i < 32; i++ )
{
	printf("0x%02x ",digest[i]);
	if((i+1)%8 == 0)
		printf("\n");
}
printf("\n");



//===========================================================================

LOGMESSAGE("########get buff################\n");
memcpy(buffer,myBuff+len +2,32);
diff = 0;
for( i = 0; i < 32; i++ )
diff |= digest[i] ^ buffer[i];


printf("=============================== diff is %d\n=====================",diff);



























if( diff != 0 )
{
	for(i=0;i<myBuffLen;i++)
		LOGMESSAGE("0x%x ",myBuff[i]);
	LOGMESSAGE("\n");
	LOGMESSAGE("signature from  message\n");
	//memcpy(buffer,myBuff+len +2,32);
	for(i=0;i<32;i++)
		LOGMESSAGE("0x%x ",buffer[i]);
	LOGMESSAGE("\n");
	LOGMESSAGE("signature calculated from  message\n");
	for(i=0;i<32;i++)
		LOGMESSAGE("0x%x ",digest[i]);
	LOGMESSAGE("\n");
	LOGMESSAGE("key: \n");
	memcpy(key,tkey,32);
	for(i=0;i<32;i++)
		LOGMESSAGE("0x%x ",key[i]);
	LOGMESSAGE("\n");
	goto exit;
}

mbedtls_aes_init( &aes_ctx );
mbedtls_aes_setkey_dec(&aes_ctx, tkey, aeskey_size*8);//  set decrypt key
memset(iv, 0x55, IV_SIZE);
memset(plain_decrypt,0,1476);
mbedtls_aes_crypt_cbc(&aes_ctx, MBEDTLS_AES_DECRYPT, len, iv, ApduPackage, plain_decrypt);
#if 0
LOGMESSAGE("plain_decrypt\n");
for(i=0;i<len;i++)
LOGMESSAGE("0x%x ",plain_decrypt[i]);
LOGMESSAGE("\n");
#endif
//LOGMESSAGE("apdu len is %d,decrypted len is %d\n",apdulentmp,len);
#if LCH_SYS_ENABLE_bacnet
iprintf_LchBacnetApp(LCHP_MEDIUM, "apdu len is %d,decrypted len is %d\n",apdulentmp,len);
#endif
if(apdulentmp <len)
	{
		memcpy(&timestampfromApdu,plain_decrypt +apdulentmp,8);
		if(timestampfromApdu >=timestampfromApdutmp)
		{
			memcpy(am->apdu,plain_decrypt,apdulentmp);
			timestampfromApdutmp =timestampfromApdu;
			am->nlen =apdulentmp;
		}
		else
		{
			goto cleanup;
		}
	}
	else
	{
		goto cleanup;
	}
	//LOGMESSAGE("put apdu to q ,len %d\n\n",am->nlen);
#if LCH_SYS_ENABLE_bacnet
	iprintf_LchBacnetApp(LCHP_MEDIUM, "put apdu to q ,len %d\n\n",am->nlen);
#endif
	if(am->nlen <500)
	{
		for(i=0;i<am->nlen;i++)
		{
			//LOGMESSAGE("0x%x ",am->apdu[i]);
#if LCH_SYS_ENABLE_bacnet
			iprintf_LchBacnetApp(LCHP_MEDIUM, "0x%x ",am->apdu[i]);
#endif
		}
#if LCH_SYS_ENABLE_bacnet
		iprintf_LchBacnetApp(LCHP_MEDIUM, "\n\n");
#endif
		//LOGMESSAGE("\n\n");
	}
	//InsertQ(am);
cleanup:
	mbedtls_aes_free(&aes_ctx);
exit:
	mbedtls_md_free( &sha_ctx);
}



extern int32_t make_internet_address(int8_t * hostname,int32_t port,struct sockaddr_in *addrp);

int sockfd; 
char hname[128]={0};
uint8_t  buffer[MAXLINE]; 
char *hello = "Hello from server"; 
struct sockaddr_in servaddr, cliaddr; 
struct hostent *hent=NULL;


char *sip=NULL;






int8_t cmd_str[1024];




int32_t make_internet_address(int8_t * hostname,int32_t port,struct sockaddr_in *addrp)
{

	struct hostent *hp;

	bzero((void*)addrp,sizeof(struct sockaddr_in));


	hp = gethostbyname(hostname);

	if(hp == NULL)
		return -1;

	bcopy((void*)hp->h_addr,(void*)&addrp->sin_addr,hp->h_length);
	addrp->sin_port = htons(port);
	addrp->sin_family= AF_INET;

	return 0;


}


uint32_t vvcnt=0;
void on_timer(int signum)
{
	signal(SIGALRM,on_timer);
	make_internet_address(sip,PORT,&cliaddr);
	if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
	{
		perror("udp send failed\n");
		exit(EXIT_FAILURE);		
	}
	vvcnt++;


	if(vvcnt == 100)
	{
		vvcnt=0;

		sleep(100);
	}


	//printf("hello timer\n");

}

int set_timer(uint32_t nms)
{

	struct itimerval ts;

	ts.it_interval.tv_sec = nms/1000;
	ts.it_interval.tv_usec = (nms%1000)*1000L;


	ts.it_value.tv_sec = nms/1000;
	ts.it_value.tv_usec = (nms%1000)*1000L;


	return setitimer(ITIMER_REAL,&ts,NULL);
}

//=========================================================================================
//

uint8_t list_array[1024][4]={0};
uint32_t rv_cnt =0;


void *read_udp(void *arg_r)
{


	int n=0;
	int len=0; 
	uint32_t bid=0;
	uint32_t acnt=0;
	uint32_t bcnt=0;
	uint32_t ccnt=0;
	uint32_t vcnt=0;


	len = sizeof(cliaddr);  //len is value/resuslt 


	FILE *fp;
	fp = fopen("object-list.log","w");


	if(fp == NULL)
	{

		printf("failed open object-list.log");
		exit(EXIT_FAILURE);

	}




	while(1)
	{
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, &len); 
		//n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, sizeof(struct sockaddr)); 


		keysize = 32;
		//memcpy(sbuffer,buffer,32);
		decrypt(buffer, 32, iven, keyAes256, keysize);
#if 0
		//		printf("==========rec len is %d\n",n);

		printf("rec data is \r\n");
		for(int i=0;i<n;i++)
		{

			printf("0x%02x ",buffer[i]);

			if((i + 1)%8 == 0)
				printf("\r\n");

		}

		printf("\r\n");

#endif


		//printf("==========rec len is %d\n",n);
		//printf("\n==ip %s\n",(char*)inet_ntoa(cliaddr.sin_addr));




		//printf("\n==rec len is %d\n",n);


		if(buffer[12]== 0xc4 && buffer[13] == 0x02)
		{
			bid=(uint32_t)(buffer[14]<<16|buffer[15]<<8|buffer[16]);

#if 0
			if(bid == 4194302)
			{
				acnt++;
				printf("I am %d\t%d\n",bid,acnt);
			}

			if(bid == 12)
			{
				bcnt++;
				printf("I am %d\t%d\n",bid,bcnt);
			}
			if(bid == 1000)
			{
				ccnt++;
				printf("I am %d\t%d\n",bid,ccnt);
			}

#endif
			printf("I am %d\n",bid);
			bid=0;

		}
#if 0
		if(buffer[10]== 0x10 && buffer[11] == 0x08)
		{

			//printf("I am 5006\n");
		}
#endif



		if(strcmp(buffer,"whois\n") == 0)
		{

			//printf("I am: %d\n",1009);
			//printf("%s\r\n","world");
			//write(pfd[1],ts,strlen(ts));
		}


		if(buffer[16] == 0x3e  && buffer[27]==0x3f)
		{
			vcnt++;

			printf("%c%c%c%c%c%c%c\t%d\n",buffer[20],buffer[21],buffer[22],buffer[23],buffer[24],buffer[25],buffer[26],vcnt);
		}


		if(strcmp(buffer,"tx-quit\n") == 0)
		{
			printf("good-bye\n");
			exit(EXIT_SUCCESS);		

		}





		memset(buffer,0,sizeof(buffer));
		//		sleep(1);
	}

}


uint8_t cmd_buf[128]={0};

void *write_udp(void *arg_w)
{

	int nrcmd=0;
	int fd;
	int m=0;
	make_internet_address(sip,PORT,&cliaddr);
	fd = open("udp-fifo",O_RDONLY | O_NONBLOCK);

	while(1)
	{



		//nrcmd = read(fd,cmd_buf,sizeof(cmd_buf));
		nrcmd = read(fd,cmd_buf,PIPE_BUF);

		//printf("====== nrcmd is %d\n",nrcmd);
		//printf("cmd_buf is %s\n",cmd_buf);
		//
		//
		if(nrcmd == 0)
		{
			//	sleep(1);
		}


		if(strcmp(cmd_buf,"send rv\n") == 0)
		{


			//if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			if((stn = sendto(sockfd,s_bqr_rp,sizeof(s_bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

			//	printf("-------send rv\n");
			m++;
#if 0
			if(m>100)
				exit(0);
#endif
			//	sleep(3);

		}



		memset(cmd_buf,0,sizeof(cmd_buf));
		//sleep(1);

	}

}


//=========================================================================================
//msg='a','b','c'
//sha256=ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad


uint8_t hash_bqr_rp[32]={0};

uint8_t hsab[32]={0};
uint8_t sab[]={

	'a','b','c','d'

};

uint8_t skey[32]={0};


int main(int argc, char* argv[])
{    




	x_am.apdu = am_apdu;
	x_am.nlen = 1024;


#if 0
	mbedtls_x509_crt cacert;
	mbedtls_x509_crt_init( &cacert );

	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, sab, 4);
	//SHA256_Update(&ctx, hash_bqr_rp, 32);
	SHA256_Final(hsab, &ctx);
	//SHA256_Final(hash_bqr_rp, &ctx);

	for(int is=0;is<32;is++)
	{

		printf("%02x ",hsab[is]);
		//	printf("%02x ",plainAes128[is]);
	}

	printf("\n");

	return 0;

#endif






	macEncryptionTransmit(&npdu_len, bqr_rp + 4);
	//ParsePrivateTransfer(frNpacket *am,octet *op,word apdulen)
	ParsePrivateTransfer(&x_am,npdutemp,78);




	return 0;




	printf("==C==\n");
	//encrypt(buffer, buffer_len, ive, keyAes128, keysize); 
	keysize = 32;
	//encrypt(plainAes256, 32, iven, keyAes256, keysize); 
	//
	//
	memcpy(s_bqr_rp,bqr_rp,32);	
	encrypt(s_bqr_rp, 32, iven, keyAes256, keysize); 






	for(int is=0;is<32;is++)
	{

		printf("%02x ",plainAes256[is]);
		//printf("%c ",plainAes256[is]);
	}


	printf("\n");
	keysize = 32;
	decrypt(plainAes256, 32, iven, keyAes256, keysize);

	for(int is=0;is<32;is++)
	{

		printf("%02x ",plainAes256[is]);
		//printf("%c ",plainAes256[is]);
	}


	printf("\n");



#if 0
	keysize = 16;
	encrypt(plainAes128, 16, NULL, keyAes256, keysize); 
	for(int is=0;is<16;is++)
	{

		//printf("%02x ",hsab[is]);
		printf("%02x ",plainAes128[is]);
	}

#endif



	//mencrypt(buffer, buffer_len, NULL, keyAes128, keysize); 

	//printf("cipher:  "); display(buffer , buffer_len);
	//decrypt(buffer, buffer_len, IV, key, keysize);
	//printf("decrypt: %s\n", buffer);


#if 0
	//for(int is=0;is<32;is++)
	for(int is=0;is<16;is++)
	{

		//printf("%02x ",hsab[is]);
		printf("%02x ",plainAes128[is]);
	}


	printf("\n");

#endif
	return 0;



	if(argc <3)
	{

		printf("err:parameters\n");
		exit(EXIT_FAILURE);
	}

	sip = argv[2];
	uint32_t temp_id = atoi(argv[3]);
	DEVICE_IDL= temp_id & 0x000000ff;
	DEVICE_IDM= (temp_id & 0x0000ff00)>>8;
	DEVICE_IDH= (temp_id & 0x00ff0000)>>16;

	gethostname(hname,sizeof(hname));
	hent = gethostbyname(hname);

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 


	int optval =1;
	//setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST|SO_REUSEADDR,&optval,sizeof(int));

	struct timeval timeout;
	timeout.tv_sec = 6;
	timeout.tv_usec = 0;
	//setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 


	const char localip[]="192.168.2.10";

	// Filling server information 
	servaddr.sin_family    = AF_INET; // IPv4 
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	//servaddr.sin_addr.s_addr = inet_addr(localip); 
	servaddr.sin_port = htons(PORT); 
	//servaddr.sin_port = PORT; 

	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 


#if 0
	set_timer(atoi(argv[1]));
	signal(SIGALRM,on_timer);
#endif

	memset(buffer,0,sizeof(buffer));

	pthread_t thread_id_read;
	pthread_t thread_id_write;
	pthread_create(&thread_id_read,NULL,read_udp,NULL);
	pthread_create(&thread_id_write,NULL,write_udp,NULL);



	pthread_join(thread_id_read,NULL);
	pthread_join(thread_id_write,NULL);


	printf("after thread\r\n");


	exit(0);

}
