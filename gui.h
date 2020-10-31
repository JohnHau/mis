#ifndef GUI_H
#define GUI_H

#define TEST_MODE    0

typedef struct xmenu
{
    uint8_t menu_no;
    uint8_t mode;
    uint8_t cur_mode;
    uint8_t frame;
    uint8_t value;
    int8_t parameter;
     void (*MsgHandlle)(uint8_t key);
    
}MENU;






typedef struct _hg_op
{
    uint8_t working_mode;
    uint8_t cur_working_mode;
    uint8_t working_op;
    uint8_t status_powerup;
    uint8_t status_charging;
    uint8_t need_reset;
    uint8_t status_hit_lp;
    
    uint8_t needle_len;
    uint8_t inject_len;
    uint8_t tube_cap;
    uint8_t work_freq;
    
    uint8_t push_len;
    
    
    uint8_t acting_flag;
    
    uint8_t drops_sa;
    uint8_t drops_sb;
    uint8_t drops_push;
    
    uint8_t posrst;
    
    uint8_t posa;
    uint8_t posb;
    uint8_t posc;
    
    uint16_t cnt_posa;
    uint16_t cnt_posb;
    uint16_t cnt_posc;
    
    uint16_t cnt_posrst;
    uint16_t cnt_target_posrst;
    uint16_t qec;

}HG_OP;

extern HG_OP  hg_op;
extern uint8_t test_mode;
extern uint8_t flag_test_mode_break;

#define STATUS_SLEEP   0x00
#define STATUS_WAKE    0x01




#define WORK_MODE_C           0x00
#define WORK_MODE_DROPS       0x01
#define WORK_MODE_DROP        0x02
#define WORK_MODE_STOP        0x03
#define WORK_MODE_TEST        0x04



#define NEEDLE_LEN_4_MM       4
#define NEEDLE_LEN_6_MM       6
#define NEEDLE_LEN_9_MM       9
#define NEEDLE_LEN_13_MM     13



#define INJECT_LEN_0_MM  0
#define INJECT_LEN_1_MM  1
#define INJECT_LEN_2_MM  2
#define INJECT_LEN_3_MM  3
#define INJECT_LEN_4_MM  4




#define TUBE_CAP_2P5_ML   0
#define TUBE_CAP_1P5_ML   1
#define TUBE_CAP_5_ML     2



#define DROPS_MODE_100_FREQ     80
#define DROPS_MODE_150_FREQ     70
#define DROPS_MODE_200_FREQ     60
#define DROPS_MODE_250_FREQ     50
#define DROPS_MODE_300_FREQ     40















#define INC_DOUBLE    300

//#define POS_13_RST   (300 * 4)
//#define POS_13_RST   (150 * 4)
//#define POS_13_RST   (100 * 4)
//#define POS_13_RST   (25 * 4)

//#define POS_13_RST   (8 * 4)  //ignored
#define POS_13_RST   (1)  //ignored

#define POS_13MM_SB   (156) 
#define POS_13MM_SA   (156) 

//#define POS_RST   (150 * 4)
#define POS_RST   (150 * 2)
//#define POS_4_RST   (150 * 2)
//#define POS_4_RST   (520 *2)
//#define POS_4_RST   (482 *2)
//#define POS_4_RST   (482 )
#define POS_4_RST   (412 )
#define POS_6_RST   (412 )


#define POS_INJECT_F  (30 * 4 + 0)
#define POS_INJECT_R  (30 * 4 + 0)
//#define POS_INJECT_R  (30 * 4 + 12)


#define  STARTUP_PWM_MA   30
#define  STARTUP_PWM_MB   30

#define  STARTUP_PWM   10

#define  STARTUP_THR_MA  12
#define  STARTUP_THR_MB  12


#define STARTUP_CNT_MA   15 /*20*/ /*15*/
#define STARTUP_CNT_MB   15 /*20*/ /*15*/
//#define STARTUP_CNT_MB   14 /*20*/ /*15*/


#define  INTERVAL_F    40/*20*/


extern uint8_t focus;
extern uint8_t flip;
extern int8_t work_mode;
extern MENU menu[8];

void init_menu(void);
void HG_interface(void);

void menu0_MsgHandlle(uint8_t key);
void menu1_MsgHandlle(uint8_t key);
void menu2_MsgHandlle(uint8_t key);
void menu3_MsgHandlle(uint8_t key);
void menu4_MsgHandlle(uint8_t key);
void menu5_MsgHandlle(uint8_t key);
void menu6_MsgHandlle(uint8_t key);
void menu7_MsgHandlle(uint8_t key);


#endif