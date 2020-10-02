#ifndef GUI_H
#define GUI_H



typedef struct xmenu
{
    uint8_t menu_no;
    uint8_t mode;
    uint8_t cur_mode;
    uint8_t frame;
    uint8_t value;
    uint8_t parameter;
     void (*MsgHandlle)(uint8_t key);
    
}MENU;






typedef struct _hg_op
{
    uint8_t working_mode;
    uint8_t working_op;
    uint8_t status_powerup;

}HG_OP;

extern HG_OP  hg_op;
#define STATUS_SLEEP   0x00
#define STATUS_WAKE    0x01




#define WORK_MODE_C  0x00
#define WORK_MODE_DROPS  0x01
#define WORK_MODE_DROP  0x02

extern uint8_t focus;
extern uint8_t flip;
extern uint8_t work_mode;
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