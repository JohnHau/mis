#ifndef GUI_H
#define GUI_H



typedef struct xmenu
{
    uint8_t menu_no;
    uint8_t mode;
    uint8_t cur_mode;
    uint8_t frame;
    uint8_t value;
    
     void (*MsgHandlle)(uint8_t key);
    
}MENU;



extern uint8_t focus;
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