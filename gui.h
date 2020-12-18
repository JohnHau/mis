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
    
    uint8_t bat_volume;
    uint8_t bat_charging;
    
    uint8_t flag_ui_check;
    
    uint16_t cnt_push;
    uint16_t tcnt_overload_ma;
    
    uint8_t flag_warning_ma;
    uint8_t flag_warning_mb;
    uint8_t in_reset;
    
    uint8_t flag_wake_device;
    uint8_t flag_shut_device;
    
    uint32_t cnt_device_idle;
    
    uint8_t work_counter_drop;
    uint16_t stay_time_drop;
    
   // uint16_t sat;
    //uint16_t sbt;
    
   // uint16_t sa_old;
   // uint16_t sa_new;
    
   // uint16_t sb_old;
   // uint16_t sb_new;
     
    uint8_t needle_len;
    uint16_t inject_len;
    uint8_t tube_cap;
    uint16_t work_freq;
    
    uint16_t push_len;
    
    
    uint8_t acting_flag;
    
    uint8_t drops_sa;
    uint8_t drops_sb;
    uint8_t drops_push;
    
    uint8_t posrst;
    
    uint8_t posa;
    uint8_t posb;
  //  uint8_t posc;
    
    uint16_t cnt_posa;
    uint16_t cnt_posb;
   // uint16_t cnt_posc;
    
    int16_t cnt_pos_1mm;
    int16_t cnt_pos_2mm;
    int16_t cnt_pos_nmm;
    
    int16_t cnt_pos_1mm_target;
    int16_t cnt_pos_2mm_target;
    int16_t cnt_pos_nmm_target;
    
    //uint16_t cnt_posa_std;
    //uint16_t cnt_posb_std;
    
    //uint16_t cnt_posa_target;
    //uint16_t cnt_posb_target;
    
    
    
    uint16_t cnt_posrst;
    uint16_t cnt_target_posrst;
    //uint16_t qec;

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



#define DROPS_MODE_100_FREQ     (5*1000)
#define DROPS_MODE_150_FREQ     (4*1000)
#define DROPS_MODE_200_FREQ     (3*1000)
#define DROPS_MODE_250_FREQ     (2*1000)
#define DROPS_MODE_300_FREQ     (1*1000)















//#define INC_DOUBLE    300

//#define POS_13_RST   (300 * 4)
//#define POS_13_RST   (150 * 4)
//#define POS_13_RST   (100 * 4)
//#define POS_13_RST   (25 * 4)

//#define POS_13_RST   (8 * 4)  //ignored
#define POS_13_RST   (1)  //ignored

#define POS_13MM_SB   (156) 
//#define POS_13MM_SA   (156) 
#define POS_13MM_SA   (187) 

//#define POS_RST   (150 * 4)
#define POS_RST   (150 * 2)
//#define POS_4_RST   (150 * 2)
//#define POS_4_RST   (520 *2)
//#define POS_4_RST   (482 *2)
//#define POS_4_RST   (482 )
//#define POS_4_RST   (412 )
//#define POS_6_RST   (412 )


#define POS_4_RST   (789)
#define POS_6_RST   (614 )



#define POS_0MM_TARGET   (148)
#define POS_1MM_TARGET   (236)
#define POS_2MM_TARGET   (325)


#if 1
//0.001425
#define VOL_TUBE_1ML_PUSH_DROPS    (112*2)
#define VOL_TUBE_2P5ML_PUSH_DROPS  (112) //112 <->2.5ml
#define VOL_TUBE_5ML_PUSH_DROPS    (112/2)
#endif

#if 0
#define VOL_TUBE_1ML_PUSH    (56)
#define VOL_TUBE_2P5ML_PUSH  (56)
#define VOL_TUBE_5ML_PUSH    (56)
#endif


#if 1
//0.001425
#define VOL_TUBE_1ML_PUSH_C    (112*2*6)
#define VOL_TUBE_2P5ML_PUSH_C  (112*6) //112 <->2.5ml
#define VOL_TUBE_5ML_PUSH_C    (112/2*6)



//#define VOL_TUBE_1ML_PUSH_C    (112*2*5)
//#define VOL_TUBE_2P5ML_PUSH_C  (112*5) 
//#define VOL_TUBE_5ML_PUSH_C    (112/2*5)

#endif




#if 1
//0.001425
#define VOL_TUBE_1ML_PUSH_DROP    (112*2)
#define VOL_TUBE_2P5ML_PUSH_DROP  (112) //112 <->2.5ml
#define VOL_TUBE_5ML_PUSH_DROP    (112/2)
#endif




//#define POS_INJECT_F  (30 * 4 + 0)
//#define POS_INJECT_R  (30 * 4 + 0)
//#define POS_INJECT_R  (30 * 4 + 12)


//#define  STARTUP_PWM_MA   30
//#define  STARTUP_PWM_MB   30

//#define  STARTUP_PWM   10

//#define  STARTUP_THR_MA  12
//#define  STARTUP_THR_MB  12


//#define STARTUP_CNT_SA_MB   180//200//175//150//125//250//93 /*20*/ /*15*/  up
//#define STARTUP_CNT_SA_MB   80//93//200//175//150//125//250//93 /*20*/ /*15*/  up
//#define STARTUP_CNT_SB_MB   100 /*20*/ /*15*/
//#define STARTUP_CNT_MB   14 /*20*/ /*15*/



//#define STARTUP_CNT_MA_TEST   95 /*20*/ /*15*/
//#define STARTUP_CNT_MB_TEST   100 /*20*/ /*15*/



#define  INTERVAL_F    40/*20*/

//#define  PERIORD_DYNAMIC_UI   200000
#define  PERIORD_DYNAMIC_UI   2000

extern uint8_t flag_blink;
extern uint8_t focus;
extern uint8_t flip;
extern int8_t work_mode;
extern MENU menu[8];




void HG_device_init(void);
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



void enter_sleep(void);


void initial_para_setting(void);

void blink_mode(void);
void check_ui_blink(void);


void check_ui_status(void);
void check_wake_button(void);
void check_shut_device(void);
#endif