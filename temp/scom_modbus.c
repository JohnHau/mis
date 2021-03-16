#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

#include <pthread.h>
#include <mqueue.h>
#include <semaphore.h>

int tty_fd = -1 ;


mqd_t  mqd;
struct mq_attr attr;

char msg[8192]={0};






struct msg_frame
{

uint8_t s_addr;
uint8_t fun_code;



};


const uint16_t polynom = 0xA001;
 
uint16_t crc16bitbybit(uint8_t *ptr, uint16_t len)
{
	uint8_t i;
	uint16_t crc = 0xffff;
 
	if (len == 0) {
		len = 1;
	}
	while (len--) {
		crc ^= *ptr;
		for (i = 0; i<8; i++)
		{
			if (crc & 1) {
				crc >>= 1;
				crc ^= polynom;
			}
			else {
				crc >>= 1;
			}
		}
		ptr++;
	}
	return(crc);
}
 
/* Table of CRC values for high???order byte */
const uint8_t crctablehi[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40
};


/* Table of CRC values for low???order byte */
const uint8_t crctablelo[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
};
 
uint16_t crc16table(uint8_t *ptr, uint16_t len)
{
	uint8_t crchi = 0xff;
	uint8_t crclo = 0xff; 
	uint16_t index;
	while (len--) 
	{
		index = crclo ^ *ptr++; 
		crclo = crchi ^ crctablehi[index];
		crchi = crctablelo[index];
	}
	return (crchi << 8 | crclo);
}
 
const uint16_t crctalbeabs[] = { 
	0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401, 
	0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400 
};
 
uint16_t crc16tablefast(uint8_t *ptr, uint16_t len) 
{
	uint16_t crc = 0xffff; 
	uint16_t i;
	uint8_t ch;
 
	for (i = 0; i < len; i++) {
		ch = *ptr++;
		crc = crctalbeabs[(ch ^ crc) & 15] ^ (crc >> 4);
		crc = crctalbeabs[((ch >> 4) ^ crc) & 15] ^ (crc >> 4);
	} 
	
	return crc;
}













typedef unsigned char byte;
typedef unsigned char octet;
typedef unsigned long dword;
typedef unsigned short word;

///////////////////////////////////////////////////////////////////////
//    Module Options

///////////////////////////////////////////////////////////////////////
//    Module Constants
#define Npoll             50    //number of tokens recieved or used before Poll for Master (fixed)
#define Nretrytoken       1     //number of retries on sending the token (fixed)
#define Nminoctets        4     //number of "events (octets) for active line (fixed)
#define Tframeabort       100   //(60 bit times) 100 ms max (fixed)
#define Tframegap         20    //(20 bit times) (fixed) 
#define Tnotoken          500   //silence time for loss of token (fixed)
#define Tpostdrive        15    //(15 bit times) (fixed)
#define Treplydelay       200   //200 ms (fixed)...to be safe  ***511
#define Treplytimeout     300   //255-300 ms (fixed)
#define Tslot             10    //10 ms (fixed)
#define TusagetimeoutTP   40    //20-100 ms (fixed)    Note: Alerton's is in 30-35 range
#define TusagetimeoutPFM  25    //20-100 ms (fixed)    ***705A End    




///////////////////////////////////////////////////////////////////////
//    Module variables

//mstpVars    mstpvars[nMSTPports];

#define   receivedinvalidframe       ((byte)  4)
#define   receivedvalidframe         ((byte  )8)
#define   solemaster                 ((byte) 16)
#define   receivedvalidframeNotForUs ((byte)128)



//Module Constants
#define Npoll                  50  //number of tokens recieved or used before Poll for Master (fixed)
#define Nretrytoken            1   //number of retries on sending the token (fixed)
#define Nminoctets             4   //number of "events (octets) for active line (fixed)
#define Tframeabort            100 //(60 bit times) 100 ms max (fixed)
#define Tframegap              20  //(20 bit times) (fixed) 
#define Tnotoken               500 //silence time for loss of token (fixed)
#define Tpostdrive             15  //(15 bit times) (fixed)
#define Treplydelay            200 //200 ms (fixed)...to be safe   ***511
#define Treplytimeout          300 //255-300 ms (fixed)
#define Tslot                  10  //10 ms (fixed)
#define TusagetimeoutTP        40  //20-100 ms (fixed)  Note: Alerton's is in 30-35 range
#define TusagetimeoutPFM       25  //20-100 ms (fixed)  ***705A End    

//MSTP frame types
#define	mftToken                	0x00
#define	mftPollForMaster		0x01
#define	mftReplyToPollForMaster		0x02
#define	mftTestRequest			0x03
#define	mftTestResponse			0x04
#define	mftBACnetDataExpectingReply	0x05
#define	mftBACnetDataNotExpectingReply	0x06
#define	mftReplyPostponed		0x07
#define mftUnknown			0x08

//Low Level Receive State Machine states
#define lrsmIdle			0
#define lrsmPreamble			1
#define	lrsmHeader			2
#define	lrsmData			3
//Master Node State Machine states
#define	mnsmInitialize		       0
#define mnsmIdle		       1
#define mnsmUseToken		       2
#define mnsmWaitForReply	       3
#define mnsmDoneWithToken	       4
#define mnsmPassToken		       5
#define mnsmNoToken		       6
#define mnsmPollForMaster	       7
#define mnsmAnswerDataRequest	       8
#define mnsmZeroConfigrationIdle       9
#define mnsmZeroConfigrationToken      11
#define mnsmZeroConfigrationPFM        10
#define mnsmZeroConfigrationConfirm    12



#define	maxrx 501 //max chars in rx buffer (NPDU size)	***008
#define	maxtx 501 //max chars transmitted		***008

typedef struct _mstpFrame {
struct _mstpFrame *next;
	word	plen;						//transmit length
	octet	req;						//0=no reply expected, 1=reply expected
	octet	pre[2];						//preamble 55 FF
	octet	type;						//frame type
	octet	da;							//dest addr
	octet	sa;							//source addr
	octet	dlenhi;						//big endian data length
	octet	dlenlo;
	octet	hcrc;
	octet	data[maxtx+3];				//data+2CRC+pad
	} mstpFrame;



typedef struct _mstpVars { //	***507 Begin
	mstpFrame *TxQfront;
	mstpFrame *TxQrear;
	word   PFMTimer; // Introduced for automac
	dword  LastPFM;  // [GBA] 1. Aug. 2013: usec timestamp of last poll for master
	dword	rxid;
	word	dcrc;
	word	maxapdu; //init to maxrx-12	***004
	word	hindex;	//header index
	word	eventcount;	//	***507
	word	framecount;	//frames sent during token hold			***507***705A
	word	ReplyTimer;	//***507***705A
	word	SilenceTimer;	//***507***705A
	word	c5ms;//		***507
	word	rlen;
	word	tlen;//number of octets in tbuf to transmit (excluding header) ***006
	word	elen;
	word	TxQcount;
	byte	lrstate;	//low level receive machine state
	byte	lastrsm;
	byte	lastmsm;
	byte	mnstate;	//master node state machine
	octet	hcrc;
	byte	mflag;	//various flags:
	byte    transmitting;
	octet	hb[6];	//header buffer for  receive	***006
				// [0]=type
				// [1]=D.A.
				// [2]=S.A.
				// [3]=lenhi
				// [4]=lenlo
				// [5]=crc
	octet	ns;	//next station to get token
	octet	ps;	//last station to which we send Poll for Master
	byte	havetoken;//	***300
	byte	lasttoken;//	***300
	byte	retrycount;//	***507
	byte	tokencount;//tokens received by us ***507
	octet	tda;	//destination to transmit to
	octet	rbuf[maxrx];//	***507 End

	byte    xmit_ff_state;
        byte    bZeroConfigurationMode;
        byte    bFixedMAC;
        byte    No_ValidMAC;
} mstpVars;


#if 0

// Bruce Test:
void print_mstp_recv_frame(byte port)
{
    if(mstpvars[port].hb[0] == 0 || mstpvars[port].hb[0] == 1)
    {
      return;
    }

    iprintf("\n================= Data Received ===============");
    iprintf("\n| Raw         : 55ff");
    for(int i = 0; i < 6; i++)
    {
        print_byte(mstpvars[port].hb[i]);
    }
    if(mstpvars[port].rlen > 0)
    {
        for(int i = 0; i < mstpvars[port].rlen+2; i++)
        {
            print_byte(mstpvars[port].rbuf[i]);
        }
    }

    iprintf("\n| Frame Type  : ");
    switch(mstpvars[port].hb[0])
    {
        case 0x00: iprintf("00 (Token)"); break;
        case 0x01: iprintf("01 (Poll For Master)"); break;
        case 0x02: iprintf("02 (Reply To Poll For Master)"); break;
        case 0x03: iprintf("03 (Test_Request)"); break;
        case 0x04: iprintf("04 (Test_Response)"); break;
        case 0x05: iprintf("05 (Data Expecting Reply)"); break;
        case 0x06: iprintf("06 (Data Not Expecting Reply)"); break;
        case 0x07: iprintf("07 (Reply Postponed)"); break;
        default: print_byte(mstpvars[port].hb[0]); iprintf(" (Unknown Type)");
    }
    iprintf("\n| Dest Addr   : "); print_byte(mstpvars[port].hb[1]);
    iprintf("\n| Src Addr    : "); print_byte(mstpvars[port].hb[2]);
    iprintf("\n| Data Length : ");
    print_byte(mstpvars[port].hb[3]);
    print_byte(mstpvars[port].hb[4]);
    iprintf(" (%d bytes)", (mstpvars[port].hb[3] << 8) | mstpvars[port].hb[4]);
    iprintf("\n| Header CRC  : "); print_byte(mstpvars[port].hb[5]);
    if(mstpvars[port].rlen > 0)
    {
        iprintf("\n| Data        : ");
        for(int i = 0; i < mstpvars[port].rlen; i++)
        {
            print_byte(mstpvars[port].rbuf[i]);
        }
        iprintf("\n| Data CRC    : ");
        print_byte(mstpvars[port].rbuf[mstpvars[port].rlen]);
        print_byte(mstpvars[port].rbuf[mstpvars[port].rlen+1]);
    }
    iprintf("\n===============================================\n");
}


#endif


///////////////////////////////////////////////////////////////////////
//    Receive Frame State Machine
//
// Note: When a conplete frame has been received, this machine leaves the
//       recieved frame in hb and rbuf with receivedvalidframe==true OR 
//       receivedinvalidframe==true. It's then up to MasterNodeStateMachine
//         to process the frame.








mstpVars mstpvars={0};


void mstpInit(void)// ***206 Begin
{

	mstpvars.maxapdu = 510 - 21;
	mstpvars.bZeroConfigurationMode = 1;//true;
	mstpvars.bFixedMAC = 0;//false;
	mstpvars.No_ValidMAC = 1;//true;


	mstpvars.lrstate=lrsmIdle;//low level receive machine state
	mstpvars.lastrsm=255;
	mstpvars.lastmsm=255;
	mstpvars.dcrc=0;
	mstpvars.rxid=0;
	mstpvars.hindex=0;//header index
	mstpvars.hcrc=0;
	mstpvars.mflag=0; //various flags:
	mstpvars.eventcount=0;
	mstpvars.framecount=0; //frames sent during token hold
	mstpvars.ns=0;         //next station to get token
	mstpvars.ps=0;         //last station to which we send Poll for Master
	mstpvars.ReplyTimer=0;
	mstpvars.retrycount=0;
	mstpvars.SilenceTimer=0;

	mstpvars.tokencount=0;//tokens received by us
	mstpvars.c5ms=0;
	mstpvars.rlen=0;
	mstpvars.tlen=0; //number of octets in tbuf to transmit (excluding header) ***006
	mstpvars.elen=0;
	mstpvars.tda=0;


	mstpvars.havetoken=0;//false; //   ***300
	mstpvars.lasttoken=0;//false; //   ***300



}


















#if 1


void ReceiveFrameStateMachine(void)
{
	//int aChar;
	uint8_t aChar;
	int rrv=0xff;

	while(1) {

		if ((mstpvars.SilenceTimer > Tframeabort) && (mstpvars.lrstate != lrsmIdle))   //timed out waiting
		{

			printf("catch\n");
			goto ResetToIDLE;
		}

		rrv = read(tty_fd, &aChar, 1);

	//	printf("rrv is %d\n",rrv);

		if (rrv <= 0) break;

		switch (mstpvars.lrstate)       //handle it based on present state
		{

			//[IDLE]---------------------------------------------------------------------------
			case lrsmIdle: // 0
				mstpvars.SilenceTimer = 0;
				mstpvars.eventcount++;
				if (aChar == 0x55)              //preamble start
					mstpvars.lrstate = lrsmPreamble;//PREAMBLE state

				mstpvars.hindex = 0;   //not a preamble start
			break;





			//[PREAMBLE]-----------------------------------------------------------------------
			case lrsmPreamble: // 1
				mstpvars.SilenceTimer = 0;

				mstpvars.eventcount++;

				if(aChar == 0x55) break;  //preamble was repeated


				if (aChar != 0xFF)              //not the second preamble octet
				{

					mstpvars.lrstate = lrsmIdle; //reset our state to IDLE
					mstpvars.hindex = 0;
					mstpvars.SilenceTimer = 0;

					break;

				}

				mstpvars.hcrc = 0xFF;
				mstpvars.hindex = 0;
				mstpvars.lrstate = lrsmHeader;    //HEADER state

			break;



			//[HEADER]-----------------------------------------------------------------------
			case lrsmHeader: // 2

				mstpvars.SilenceTimer = 0;
				mstpvars.eventcount++;
				mstpvars.hb[mstpvars.hindex++] = (octet) (aChar & 0xFF);

				if (mstpvars.hindex == 6)      //got a header
				{

					//got the valid header
					mstpvars.rlen = (mstpvars.hb[3] << 8)+ mstpvars.hb[4]; //get data length

					if(mstpvars.rlen == 0) 
					{
						goto ResetToIDLE;
					}
					else // Have Data
					{
						mstpvars.hindex = 0;
						mstpvars.dcrc = 0xFFFF;
						mstpvars.elen = mstpvars.rlen + 2; //data+2 CRC octets
						mstpvars.lrstate = lrsmData;  //DATA state
					}
				}
			break;


			case lrsmData: // 3
				mstpvars.SilenceTimer = 0;

				mstpvars.eventcount++;


				mstpvars.rbuf[mstpvars.hindex++] = (octet) (aChar & 0xFF);

				if (mstpvars.hindex == mstpvars.elen) //got a complete frame
				{
					static uint32_t fcnt =0;
					time_t timep;
					time(&timep);
					
					char* ptrtime = (char*)malloc(32);
					strcpy(ptrtime,ctime(&timep));
					ptrtime[24]='\0';
					printf("ctime is %d\n",strlen(ctime(&timep)));

                                        printf("%s: got a frame %d\n",ptrtime,++fcnt);

					free(ptrtime);
					goto ResetToIDLE;

				}
			break;

		}




	} /* while(true) */





ResetToIDLE:
	mstpvars.lrstate = lrsmIdle; //reset our state to IDLE
	mstpvars.hindex = 0;
	mstpvars.SilenceTimer = 0;


	//		break;// and execute idle state the next time
	// when we receive a byte
	// if we would go on here, we would deal with aChar twice
	// GBA, 31. March 2017


}

#endif    



///////////////////////////////////////////////////////////////////////
//    calculate Header CRC (from BACnet Appendix G)
//in:    dv    data value to accumulate
//        cv    current crc value
//out:    new crc


#if 0
octet CalcHeaderCRC(octet dv,octet cv)
{    word    crc;

	crc=cv^dv;
	crc=crc^(crc<<1)^(crc<<2)^(crc<<3)^(crc<<4)^(crc<<5)^(crc<<6)^(crc<<7);
	return (octet)((crc&0xFE)^((crc>>8)&1));
}
#endif






///////////////////////////////////////////////////////////////////////
//    calculate Data CRC (from BACnet Appendix G)
//in:    dv    data value to accumulate
//        cv    current crc value
//out:    new crc



#if 0
word CalcDataCRC(octet dv,word cv)
{    word    crcLow;
	crcLow=(cv&0xFF)^dv;
	return (cv>>8)^(crcLow<<8)^(crcLow<<3)^(crcLow<<12)^(crcLow>>4)^(crcLow&0x0F)^((crcLow&0x0F)<<7);
}

#endif



uint32_t timer_cnt=0;
void on_timer(int signum)
{

	signal(SIGALRM,on_timer);
	mstpvars.SilenceTimer += 5; 
	ReceiveFrameStateMachine();

	//printf("timer_cnt is %d\n",++timer_cnt);
	
	timer_cnt++;

	//printf("timer_cnt is %d\n",timer_cnt);


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





pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;


void* thread_transmit(void *arg)
{


	srand(time(NULL));

	while(1)
	{
#if 0
		pthread_mutex_lock(&mutex_a);
		printf("thread_TA\n");
		sleep(rand()%3 + 1);
		printf("thread_TB\n");
		printf("\n");
		pthread_mutex_unlock(&mutex_a);
#endif

		sleep(3);

		strcpy(msg,"hello");

		//if(mq_send(mqd,msg,strlen(msg),1) == -1)
		if(mq_send(mqd,msg,8,1) == -1)
		{
			perror("failed send msg\n");
			exit(EXIT_FAILURE);

		}


		//	sleep(1);
	}


}



char rmsg[8192]={0};

void* thread_receive(void *arg)
{

	unsigned int prio=0;

	srand(time(NULL));

	while(1)
	{


#if 0
		pthread_mutex_lock(&mutex_a);
		printf("thread_RA\n");
		sleep(rand()%3 + 1);
		printf("thread_RB\n");
		printf("\n");
#endif


		if(mq_receive(mqd,rmsg,8192,&prio) == -1)
		{
			perror("failed receive msg\n");
			exit(EXIT_FAILURE);

		}

		printf("got message = %s\n",rmsg);
		memset(msg,0,16);

		//pthread_mutex_unlock(&mutex_a);
		//	sleep(1);
	}


}
















int main(int argc, char *argv[])
{

	//==================================
#if 0
	sem_init(&sem1,0,0);
	sem_init(&sem2,0,1);
	sem_wait(&sem1);
	sem_post(&sem1);
#endif







#if 0
	uint8_t mb_msg[32]={0x23,0x45,0x21,0x22,0x23,0x24,0x25,0x26};

	uint16_t crv = crc16table(mb_msg, 8);
	uint16_t crvf = crc16tablefast(mb_msg, 8);



	printf("crv  is %x\n",crv);
	printf("crvf is %x\n",crvf);
	exit(EXIT_SUCCESS);

#endif














	pthread_t  tpida; 
	pthread_t  tpidb; 
#if 1


	mqd = mq_open("/mq.q",O_RDWR | O_CREAT,0777,NULL);
	//mqd = mq_open("/mq.q",O_RDWR);

	if(mqd == -1)
	{
		perror("failed open mq.q\n");
		exit(EXIT_FAILURE);
	}


	mq_getattr(mqd,&attr);
	printf("msg attr:max msg is %ld\n max bytes is %ld\n currently is %ld\n",\
			attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);

#endif



	pthread_create(&tpida,NULL,thread_transmit,NULL);
	pthread_create(&tpidb,NULL,thread_receive,NULL);


	pthread_join(tpida,NULL);
	pthread_join(tpidb,NULL);

	printf("gotcha\n");












	//===================================


	int rv = -1 ;

	char r_buf[128];
	char w_buf[128];

	struct termios options;
	fd_set rset;
	tty_fd = open("/dev/ttyS19",O_RDWR|O_NOCTTY|O_NDELAY) ; //打开串口设备

	if(tty_fd < 0)
	{
		printf("open tty failed:%s\n", strerror(errno)) ;
		goto cleanup ;
	}

	printf("open devices sucessful!\n") ;
	memset(&options, 0, sizeof(options)) ;
	rv = tcgetattr(tty_fd, &options); //获取原有的串口属性的配置

	if(rv!=0)
	{
		printf("tcgetattr() failed:%s\n",strerror(errno)) ;
		goto cleanup;
	}



	options.c_cflag|=(CLOCAL|CREAD ); // CREAD 开启串行数据接收，CLOCAL并打开本地连接模式
	options.c_cflag &=~CSIZE;// 先使用CSIZE做位屏蔽  
	options.c_cflag |= CS8; //设置8位数据位
	options.c_cflag &= ~PARENB; //无校验位
	/* 设置115200波特率  */

	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	options.c_cflag &= ~CSTOPB;/* 设置一位停止位; */
	options.c_cc[VTIME]= 1;/* 非规范模式读取时的超时时间；*/
	options.c_cc[VMIN]= 1; /* 非规范模式读取时的最小字符数*/
	tcflush(tty_fd ,TCIFLUSH);/* tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来 */

	if((tcsetattr(tty_fd, TCSANOW,&options))!=0)
	{
		printf("tcsetattr failed:%s\n", strerror(errno));
		goto cleanup ;
	}

	w_buf[0]='h'; 
	w_buf[1]='e'; 
	w_buf[2]='l'; 
	w_buf[3]='l'; 
	w_buf[4]='o'; 
	w_buf[5]='\0'; 
	w_buf[6]='\n'; 

	uint32_t in_cnt =0;

	int rlen = 0;
	int wlen = 0;

	mstpInit();
	set_timer(5);//5ms
	//set_timer(1000);//1s
	signal(SIGALRM,on_timer);



	w_buf[0] = 0x55;
	w_buf[1] = 0xff;


	w_buf[2] = 0x65;
	w_buf[3] = 0x66;
	w_buf[4] = 0x67;


	w_buf[5] = 0x00;
	w_buf[6] = 0x02;
	w_buf[7] = 0xf1;

	w_buf[8] = 0x38;
	w_buf[9] = 0x39;
	w_buf[10] = 0xf2;
	w_buf[11] = 0xf3;


	//rv = write(tty_fd, w_buf, 12) ;


	while(1)
	{

		//rv = write(tty_fd, w_buf, 12);
		//sleep(1);
		//usleep(3000000);
		//
		//
		if(timer_cnt > 70) 
		{
			rv = write(tty_fd, w_buf, 12);
			timer_cnt =0;

		}

	}



	while(1)
	{


#if 1
		usleep(30000);
		rlen = read(tty_fd, r_buf, sizeof(r_buf)) ;
		printf("rlen is %d\n",rlen);


		usleep(30000);
		rlen = read(tty_fd, r_buf, sizeof(r_buf)) ;
		printf("rlen is %d\n",rlen);


		//		usleep(30000);
		perror("rlen error");
#endif		
		exit(EXIT_FAILURE);

	}

	while(0)
	{

		rv = write(tty_fd, w_buf, 7) ;
		FD_ZERO(&rset) ;
		FD_SET(tty_fd, &rset) ;
		rv = select(tty_fd+1, &rset, NULL, NULL, NULL) ;

		if(rv < 0)
		{
			printf("select() failed: %s\n", strerror(errno)) ;
			goto cleanup ;
		}


		if(rv == 0)
		{
			printf("select() time out!\n") ;
			goto cleanup ;
		}


		memset(r_buf, 0, sizeof(r_buf)) ;

		rv = read(tty_fd, r_buf, sizeof(r_buf)) ;

		if(rv < 0)
		{
			printf("Read() error:%s\n",strerror(errno)) ;
			goto cleanup ;
		}

		printf("in_cnt is %d\n",++in_cnt);

		if(r_buf[0] !='h' ||  r_buf[1] != 'e' || r_buf[2] != 'l' || r_buf[3] != 'l'  || r_buf[4] !='o')
		{

			perror("serial com error");
			exit(EXIT_FAILURE);

		}

		//printf("Read from tty: %s\n",r_buf) ;
		//sleep(1);
		//usleep(100000);//100 ms
		usleep(40000);//100 ms
	}



cleanup:
	close(tty_fd);

	return 0;


}









#if 0

#include <stdio.h>

#include <string.h>

#include <errno.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <termios.h>

#include <unistd.h>


#define W_BUF   "WuYuJun<540726307@qq.com>"


int main(int argc, char **argv)

{

	    int     tty_fd = -1 ;

	    int     rv = -1 ;

	    struct termios options;



	    tty_fd = open("/dev/ttyUSB0",O_RDWR|O_NOCTTY|O_NDELAY) ; //打开串口设备

	    if(tty_fd < 0)

		    {

			        printf("open tty failed:%s\n", strerror(errno)) ;

			        goto cleanup ;

			    }

	    printf("open devices sucessful!\n") ;

	    

		    memset(&options, 0, sizeof(options)) ;

	    rv = tcgetattr(tty_fd, &options); //获取原有的串口属性的配置

	    if(rv != 0)

		    {

			        printf("tcgetattr() failed:%s\n",strerror(errno)) ;

			        goto cleanup ;

			    }

	    options.c_cflag|=(CLOCAL|CREAD ); // CREAD 开启串行数据接收，CLOCAL并打开本地连接模式

	    options.c_cflag &=~CSIZE;// 先使用CSIZE做位屏蔽  

	    options.c_cflag |= CS8; //设置8位数据位

	    options.c_cflag &= ~PARENB; //无校验位



	    /* 设置115200波特率  */

		    cfsetispeed(&options, B115200);

	    cfsetospeed(&options, B115200);



	    options.c_cflag &= ~CSTOPB;/* 设置一位停止位; */



	    options.c_cc[VTIME] = 0;/* 非规范模式读取时的超时时间；*/

	    options.c_cc[VMIN]  = 0; /* 非规范模式读取时的最小字符数*/

	    tcflush(tty_fd ,TCIFLUSH);/* tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来 */



	    if((tcsetattr(tty_fd, TCSANOW,&options))!=0)

		    {

			        printf("tcsetattr failed:%s\n", strerror(errno));

			        goto cleanup ;

			    }



	    while(1)

		    {

			        rv = write(tty_fd, W_BUF,strlen(W_BUF)) ;

			        if(rv < 0)

				        {

					            printf("Write() error:%s\n",strerror(errno)) ;

					            goto cleanup ;

					        }

			        sleep(3) ;

			    }



cleanup:

	    close(tty_fd) ;

	    return 0 ;

}
 
#endif
