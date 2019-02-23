#include "../include/api.h"
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
/*void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);*/
#ifdef __cplusplus
}
#endif

static int screeni;
static char (*ptr)[8];
static char arr[8] = {"abc.def"};

static int autoModeBtn[6] = {0,0,0,0,0,0};

enum autoMode
{
  none,
  red1,
  blue1,
  red2,
  blue2,
  red3,
  blue3,
  red4,
  blue4,
  red5,
  blue5,
  red6,
  blue6,
};

static autoMode selectedAutoMode = none;



/*
 * Style Declarations
 */

static lv_style_t style_page_background;
static lv_style_t style_page_backgroundGold;
static lv_style_t style_page_transpGoldBorder;
static lv_style_t style_page_transpGoldBorderWhite;
static lv_style_t style_font_comicsans18;
static lv_style_t style_font_pyroblack18;
static lv_style_t style_font_pyrowhite18;
static lv_style_t style_font_pyrogold18;
static lv_style_t style_font_pyrogold24;
static lv_style_t style_font_pyroblack24;
static lv_style_t style_font_whiteplain;
static lv_style_t style_font_whiteplaintiny;
static lv_style_t style_font_blackplain;
static lv_style_t style_font_warning;
static lv_style_t style_font_pyrologo;
static lv_color_t LV_COLOR_PYROGOLD = LV_COLOR_HEX(0xFDC527);
static lv_style_t style_button_pyrobutton;
static lv_style_t style_button_autoWhite;
static lv_style_t style_button_autoRed;
static lv_style_t style_button_autoBlue;

/*
 * Screen Object Declarations
 */

lv_obj_t * screen_background;
lv_obj_t * text_title_PYRO;
lv_obj_t * text_title_bar;
lv_obj_t * text_title_Robotics;

lv_obj_t * text_title_description;


lv_obj_t * button_title_continue;

lv_obj_t * text_title_loaded;

lv_obj_t * page_main_header;

lv_obj_t * page_main_headerTeleopMode;
lv_obj_t * page_main_headerPYRO;
lv_obj_t * page_main_headerAutoMode;

lv_obj_t * button_main_runAuto;
lv_obj_t * button_main_Auto1;
lv_obj_t * button_main_Auto2;
lv_obj_t * button_main_Auto3;
lv_obj_t * button_main_Auto4;
lv_obj_t * button_main_Auto5;
lv_obj_t * button_main_Auto6;

lv_obj_t * page_main_autoDesc;
lv_obj_t * page_text_autoDesc;

lv_obj_t * button_main_resetIMU;
lv_obj_t * page_main_IMUData;

lv_obj_t * page_text_IMUData;


/*
 * Button On-press Function Definitions
 */

 void resetAutoModeBtn()
 {
   for(int screeni= 0;screeni< 6; screeni++)
   {
     autoModeBtn[screeni] = 0;
   }
   lv_obj_set_style(button_main_Auto1, &style_button_autoWhite);
   lv_obj_set_style(button_main_Auto2, &style_button_autoWhite);
   lv_obj_set_style(button_main_Auto3, &style_button_autoWhite);
   lv_obj_set_style(button_main_Auto4, &style_button_autoWhite);
   lv_obj_set_style(button_main_Auto5, &style_button_autoWhite);
   lv_obj_set_style(button_main_Auto6, &style_button_autoWhite);
 }

static lv_res_t btn_click_goToScreen1(lv_obj_t * btn)
{
  lv_obj_set_hidden(text_title_PYRO, true);
  lv_obj_set_hidden(text_title_bar, true);
  lv_obj_set_hidden(text_title_Robotics, true);
  lv_obj_set_hidden(text_title_description, true);
  lv_obj_set_hidden(button_title_continue, true);
  lv_obj_set_hidden(text_title_loaded, true);

  lv_obj_set_hidden(page_main_header, false);
  lv_obj_set_hidden(page_main_headerTeleopMode, false);
  //lv_obj_set_hidden(page_main_headerPYRO, false);
  lv_obj_set_hidden(page_main_headerAutoMode, false);
  lv_obj_set_hidden(button_main_runAuto, false);
  lv_obj_set_hidden(button_main_Auto1, false);
  lv_obj_set_hidden(button_main_Auto2, false);
  lv_obj_set_hidden(button_main_Auto3, false);
  lv_obj_set_hidden(button_main_Auto4, false);
  lv_obj_set_hidden(button_main_Auto5, false);
  lv_obj_set_hidden(button_main_Auto6, false);
  lv_obj_set_hidden(page_main_autoDesc, false);
  lv_obj_set_hidden(button_main_resetIMU, false);
  lv_obj_set_hidden(page_main_IMUData, false);

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_cycleColor(lv_obj_t * btn)
{

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_doNothing(lv_obj_t * btn)
{
  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_Auto1(lv_obj_t * btn)
{
  lv_obj_set_style(page_main_headerAutoMode, &style_font_blackplain);

  switch(autoModeBtn[0])
  {
    case 0:
      resetAutoModeBtn();
      autoModeBtn[0] = 1;
      lv_obj_set_style(button_main_Auto1, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 1 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 1 RED.");
      selectedAutoMode = red1;
      break;
    case 1:
      resetAutoModeBtn();
      autoModeBtn[0] = 2;
      lv_obj_set_style(button_main_Auto1, &style_button_autoBlue);
      lv_label_set_text(page_main_headerAutoMode, "Auto 1 Blue Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 1 BLUE.");
      selectedAutoMode = blue1;
      break;
    case 2:
      resetAutoModeBtn();
      autoModeBtn[0] = 1;
      lv_obj_set_style(button_main_Auto1, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 1 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 1 RED.");
      selectedAutoMode = red1;
      break;
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_Auto2(lv_obj_t * btn)
{
  lv_obj_set_style(page_main_headerAutoMode, &style_font_blackplain);

  switch(autoModeBtn[1])
  {
    case 0:
      resetAutoModeBtn();
      autoModeBtn[1] = 1;
      lv_obj_set_style(button_main_Auto2, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 2 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 2 RED.");
      selectedAutoMode = red2;
      break;
    case 1:
      resetAutoModeBtn();
      autoModeBtn[1] = 2;
      lv_obj_set_style(button_main_Auto2, &style_button_autoBlue);
      lv_label_set_text(page_main_headerAutoMode, "Auto 2 Blue Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 2 BLUE.");
      selectedAutoMode = blue2;
      break;
    case 2:
      resetAutoModeBtn();
      autoModeBtn[1] = 1;
      lv_obj_set_style(button_main_Auto2, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 2 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 2 RED.");
      selectedAutoMode = red2;
      break;
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_Auto3(lv_obj_t * btn)
{
  lv_obj_set_style(page_main_headerAutoMode, &style_font_blackplain);

  switch(autoModeBtn[2])
  {
    case 0:
      resetAutoModeBtn();
      autoModeBtn[2] = 1;
      lv_obj_set_style(button_main_Auto3, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 3 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 3 RED.");
      selectedAutoMode = red3;
      break;
    case 1:
      resetAutoModeBtn();
      autoModeBtn[2] = 2;
      lv_obj_set_style(button_main_Auto3, &style_button_autoBlue);
      lv_label_set_text(page_main_headerAutoMode, "Auto 3 Blue Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 3 BLUE.");
      selectedAutoMode = blue3;
      break;
    case 2:
      resetAutoModeBtn();
      autoModeBtn[2] = 1;
      lv_obj_set_style(button_main_Auto3, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 3 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 3 RED.");
      selectedAutoMode = red3;
      break;
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_Auto4(lv_obj_t * btn)
{
  lv_obj_set_style(page_main_headerAutoMode, &style_font_blackplain);

  switch(autoModeBtn[3])
  {
    case 0:
      resetAutoModeBtn();
      autoModeBtn[3] = 1;
      lv_obj_set_style(button_main_Auto4, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 4 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 4 RED.");
      selectedAutoMode = red4;
      break;
    case 1:
      resetAutoModeBtn();
      autoModeBtn[3] = 2;
      lv_obj_set_style(button_main_Auto4, &style_button_autoBlue);
      lv_label_set_text(page_main_headerAutoMode, "Auto 4 Blue Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 4 BLUE.");
      selectedAutoMode = blue4;
      break;
    case 2:
      resetAutoModeBtn();
      autoModeBtn[3] = 1;
      lv_obj_set_style(button_main_Auto4, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 4 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 4 RED.");
      selectedAutoMode = red4;
      break;
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_Auto5(lv_obj_t * btn)
{
  lv_obj_set_style(page_main_headerAutoMode, &style_font_blackplain);

  switch(autoModeBtn[4])
  {
    case 0:
      resetAutoModeBtn();
      autoModeBtn[4] = 1;
      lv_obj_set_style(button_main_Auto5, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 5 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 5 RED.");
      selectedAutoMode = red5;
      break;
    case 1:
      resetAutoModeBtn();
      autoModeBtn[4] = 2;
      lv_obj_set_style(button_main_Auto5, &style_button_autoBlue);
      lv_label_set_text(page_main_headerAutoMode, "Auto 5 Blue Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 5 BLUE.");
      selectedAutoMode = blue5;
      break;
    case 2:
      resetAutoModeBtn();
      autoModeBtn[4] = 1;
      lv_obj_set_style(button_main_Auto5, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 5 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 5 RED.");
      selectedAutoMode = red5;
      break;
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_Auto6(lv_obj_t * btn)
{
  lv_obj_set_style(page_main_headerAutoMode, &style_font_blackplain);

  switch(autoModeBtn[5])
  {
    case 0:
      resetAutoModeBtn();
      autoModeBtn[5] = 1;
      lv_obj_set_style(button_main_Auto6, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 6 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 6 RED.");
      selectedAutoMode = red6;
      break;
    case 1:
      resetAutoModeBtn();
      autoModeBtn[5] = 2;
      lv_obj_set_style(button_main_Auto6, &style_button_autoBlue);
      lv_label_set_text(page_main_headerAutoMode, "Auto 6 Blue Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 6 BLUE.");
      selectedAutoMode = blue6;
      break;
    case 2:
      resetAutoModeBtn();
      autoModeBtn[5] = 1;
      lv_obj_set_style(button_main_Auto6, &style_button_autoRed);
      lv_label_set_text(page_main_headerAutoMode, "Auto 6 Red Selected");
      lv_label_set_text(page_text_autoDesc, "Description: AUTO 6 RED.");
      selectedAutoMode = red6;
      break;
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_runAuto(lv_obj_t * btn)
{
  lv_obj_set_style(button_main_runAuto, &style_button_autoWhite);
  //autonomous();
  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t btn_click_resetIMU(lv_obj_t * btn)
{
  lv_obj_set_style(button_main_resetIMU, &style_button_autoWhite);

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

/*
 * Screen Function Definitions
 */

 void Screen_Init_SetStlyes()
 {
   LV_FONT_DECLARE(comicsans_18);
   LV_FONT_DECLARE(ethnocentric_8);
   LV_FONT_DECLARE(ethnocentric_10);
   LV_FONT_DECLARE(ethnocentric_12);
   LV_FONT_DECLARE(ethnocentric_18);
   LV_FONT_DECLARE(ethnocentric_24);
   LV_FONT_DECLARE(ethnocentric_logo_72);

   // White Alex Font (12)
   lv_style_copy(&style_font_comicsans18, &lv_style_plain);
   style_font_comicsans18.text.font = &comicsans_18;
   style_font_comicsans18.text.color = LV_COLOR_WHITE;

   // Black PYRO Font (18)
   lv_style_copy(&style_font_pyroblack18, &lv_style_plain);
   style_font_pyroblack18.text.font = &ethnocentric_18;
   style_font_pyroblack18.text.color = LV_COLOR_BLACK;
   style_font_pyroblack18.text.letter_space = 0;

   // White PYRO Font (18)
   lv_style_copy(&style_font_pyrowhite18, &lv_style_plain);
   style_font_pyrowhite18.text.font = &ethnocentric_18;
   style_font_pyrowhite18.text.color = LV_COLOR_WHITE;

   // Gold PYRO Font (18)
   lv_style_copy(&style_font_pyrogold18, &lv_style_plain);
   style_font_pyrogold18.text.font = &ethnocentric_18;
   style_font_pyrogold18.text.color = LV_COLOR_PYROGOLD;

   // Black PYRO Font (24)
   lv_style_copy(&style_font_pyrogold24, &lv_style_plain);
   style_font_pyrogold24.text.font = &ethnocentric_24;
   style_font_pyrogold24.text.color = LV_COLOR_PYROGOLD;
   style_font_pyrogold24.text.letter_space = 3;

   // Black PYRO Font (24)
   lv_style_copy(&style_font_pyroblack24, &lv_style_plain);
   style_font_pyroblack24.text.font = &ethnocentric_24;
   style_font_pyroblack24.text.color = LV_COLOR_BLACK;
   style_font_pyroblack24.text.letter_space = 0;

   // Page Background (Base Black Background)
   lv_style_copy(&style_page_background, &lv_style_plain);
   style_page_background.body.main_color = LV_COLOR_BLACK;
   style_page_background.body.grad_color = LV_COLOR_MARRON;
   style_page_background.body.border.color = LV_COLOR_BLACK;

   // Gold Background (Gold Background)
   lv_style_copy(&style_page_backgroundGold, &lv_style_plain);
   style_page_backgroundGold.body.main_color = LV_COLOR_PYROGOLD;
   style_page_backgroundGold.body.grad_color = LV_COLOR_PYROGOLD;
   style_page_backgroundGold.body.border.color = LV_COLOR_PYROGOLD;

   lv_style_copy(&style_button_pyrobutton, &lv_style_btn_rel);
   style_button_pyrobutton.body.main_color = LV_COLOR_BLACK;
   style_button_pyrobutton.body.grad_color = LV_COLOR_BLACK;
   style_button_pyrobutton.body.border.color = LV_COLOR_PYROGOLD;
   style_button_pyrobutton.body.border.width = 2;
   style_button_pyrobutton.body.radius = 5;
   style_button_pyrobutton.text.color = LV_COLOR_WHITE;
   //style_button_pyrobutton.body.empty = 1;


   lv_style_copy(&style_font_whiteplain, &lv_style_plain);
   style_font_whiteplain.text.color = LV_COLOR_WHITE;

   lv_style_copy(&style_font_blackplain, &lv_style_plain);
   style_font_blackplain.text.color = LV_COLOR_BLACK;

   lv_style_copy(&style_font_warning, &lv_style_plain);
   style_font_warning.text.color = LV_COLOR_RED;

   // Gold PYRO Logo (72)
   lv_style_copy(&style_font_pyrologo, &lv_style_plain);
   style_font_pyrologo.text.font = &ethnocentric_logo_72;
   style_font_pyrologo.text.color = LV_COLOR_PYROGOLD;

   lv_style_copy(&style_button_autoWhite, &lv_style_btn_rel);
   style_button_autoWhite.body.main_color = LV_COLOR_WHITE;
   style_button_autoWhite.body.grad_color = LV_COLOR_WHITE;
   style_button_autoWhite.body.border.color = LV_COLOR_WHITE;
   style_button_autoWhite.body.radius = 1;
   style_button_autoWhite.body.padding.hor = 20;
   style_button_autoWhite.body.padding.ver = 15;
   style_button_autoWhite.text.color = LV_COLOR_BLACK;

   lv_style_copy(&style_button_autoRed, &style_button_autoWhite);
   style_button_autoRed.body.main_color = LV_COLOR_RED;
   style_button_autoRed.body.grad_color = LV_COLOR_RED;
   style_button_autoRed.body.border.color = LV_COLOR_RED;
   style_button_autoRed.text.color = LV_COLOR_WHITE;

   lv_style_copy(&style_button_autoBlue, &style_button_autoRed);
   style_button_autoBlue.body.main_color = LV_COLOR_BLUE;
   style_button_autoBlue.body.grad_color = LV_COLOR_BLUE;
   style_button_autoBlue.body.border.color = LV_COLOR_BLUE;
   style_button_autoBlue.body.border.width = 5;

   lv_style_copy(&style_page_transpGoldBorder, &lv_style_plain);
   style_page_transpGoldBorder.body.main_color = LV_COLOR_BLACK;
   style_page_transpGoldBorder.body.grad_color = LV_COLOR_BLACK;
   style_page_transpGoldBorder.body.border.color = LV_COLOR_PYROGOLD;
   style_page_transpGoldBorder.body.border.width = 2;
   style_page_transpGoldBorder.body.radius = 5;
   style_page_transpGoldBorder.text.color = LV_COLOR_PYROGOLD;

   lv_style_copy(&style_page_transpGoldBorderWhite, &style_page_transpGoldBorder);
   style_page_transpGoldBorderWhite.body.border.color = LV_COLOR_WHITE;
   style_page_transpGoldBorderWhite.text.color = LV_COLOR_WHITE;



 }

 void Screen_Background_Init()
 {
   screen_background = lv_page_create(lv_scr_act(), NULL);
   lv_obj_set_size(screen_background, 480, 272);
   lv_obj_align(screen_background, NULL, LV_ALIGN_CENTER, 0, 0);
   lv_page_set_style(screen_background, LV_PAGE_STYLE_BG, &style_page_background);           /*Set the scrollbar style*/
   lv_page_set_sb_mode(screen_background, LV_SB_MODE_AUTO);                     /*Show scroll bars is scrolling is possible*/
 }

 void Screen_Title_Title()
 {
   text_title_PYRO = lv_label_create(lv_scr_act(), NULL);
   lv_label_set_text(text_title_PYRO, "PYRO");
   lv_obj_align(text_title_PYRO, NULL, LV_ALIGN_IN_TOP_MID, -111, -5);
   lv_label_set_style(text_title_PYRO, &style_font_pyrologo);

   text_title_bar = lv_page_create(lv_scr_act(), NULL);
   lv_obj_set_size(text_title_bar, 272, 3);
   lv_obj_align(text_title_bar, text_title_PYRO, LV_ALIGN_IN_TOP_MID, -2, 66);
   lv_page_set_style(text_title_bar, LV_PAGE_STYLE_BG, &style_page_backgroundGold);           //Set the scrollbar style
   lv_page_set_sb_mode(text_title_bar, LV_SB_MODE_OFF);                     //Show scroll bars is scrolling is possible

   text_title_Robotics = lv_label_create(lv_scr_act(), NULL);
   lv_label_set_text(text_title_Robotics, "Robotics");
   lv_obj_align(text_title_Robotics, text_title_PYRO, LV_ALIGN_IN_TOP_MID, -55, 70);
   lv_label_set_style(text_title_Robotics, &style_font_pyrogold24);

   text_title_description = lv_label_create(lv_scr_act(), NULL);
   lv_label_set_recolor(text_title_description, true);
   lv_label_set_text(text_title_description, "Built Proudly by #FDC527 19# Dedicated Students at\nARIZONA STATE UNIVERSITY");
   lv_obj_align(text_title_description, text_title_PYRO, LV_ALIGN_IN_TOP_MID, 28, 100);
   lv_label_set_style(text_title_description, &style_font_comicsans18);
   lv_label_set_align(text_title_description, LV_LABEL_ALIGN_CENTER);


   button_title_continue = lv_btn_create(lv_scr_act(), NULL);
   lv_cont_set_fit(button_title_continue, true, true); //Enable resizing horizontally and vertically
   lv_obj_align(button_title_continue, text_title_PYRO, LV_ALIGN_OUT_BOTTOM_MID, 0, 63);
   lv_obj_set_style(button_title_continue, &style_button_pyrobutton);
   lv_obj_set_free_num(button_title_continue, 0);   //Set a unique number for the button
   lv_btn_set_action(button_title_continue, LV_BTN_ACTION_CLICK, btn_click_goToScreen1);


   lv_obj_t * label = lv_label_create(button_title_continue, NULL);
   lv_label_set_text(label, "Continue");

   text_title_loaded = lv_label_create(lv_scr_act(), NULL);
   lv_label_set_text(text_title_loaded, "Finished loading PROS project: [PYROGUIFinal]");
   lv_obj_align(text_title_loaded, text_title_PYRO, LV_ALIGN_IN_TOP_MID, -25, 220);
   lv_label_set_style(text_title_loaded, &style_font_whiteplain);


   /////////////////////////////////////////////////////////////////////////////

    page_main_header = lv_page_create(lv_scr_act(), NULL);
    lv_obj_set_size(page_main_header, 480, 30);
    lv_obj_align(page_main_header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_page_set_style(page_main_header, LV_PAGE_STYLE_BG, &style_page_backgroundGold);           /*Set the scrollbar style*/
    lv_page_set_sb_mode(page_main_header, LV_SB_MODE_OFF);                     /*Show scroll bars is scrolling is possible*/

    lv_obj_set_hidden(page_main_header, true);

    page_main_headerTeleopMode = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(page_main_headerTeleopMode, "Not Connected to Field!");
    lv_obj_set_style(page_main_headerTeleopMode, &style_font_warning);                    /*Set the created style*/
    lv_obj_align(page_main_headerTeleopMode, page_main_header, LV_ALIGN_IN_LEFT_MID, 8, 0);  /*Align to the top*/

    lv_obj_set_hidden(page_main_headerTeleopMode, true);

    page_main_headerAutoMode = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(page_main_headerAutoMode, "Please select an Auto");
    lv_obj_set_style(page_main_headerAutoMode, &style_font_warning);                    /*Set the created style*/
    lv_obj_align(page_main_headerAutoMode, page_main_header, LV_ALIGN_IN_RIGHT_MID, -8, 0);  /*Align to the top*/

    lv_obj_set_hidden(page_main_headerAutoMode, true);

    page_main_headerPYRO = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(page_main_headerPYRO, "PYRO");
    lv_obj_set_style(page_main_headerPYRO, &style_font_pyroblack24);                    /*Set the created style*/
    lv_obj_align(page_main_headerPYRO, page_main_header, LV_ALIGN_CENTER, 4, 0);  /*Align to the top*/

    lv_obj_set_hidden(page_main_headerPYRO, true);


    button_main_runAuto = lv_btn_create(lv_scr_act(), NULL);
    lv_cont_set_fit(button_main_runAuto, true, true); /*Enable resizing horizontally and vertically*/
    lv_obj_align(button_main_runAuto, page_main_header, LV_ALIGN_OUT_BOTTOM_LEFT, -18, 0);
    lv_obj_set_style(button_main_runAuto, &style_button_autoWhite);
    lv_obj_set_free_num(button_main_runAuto, 0);   /*Set a unique number for the button*/
    lv_btn_set_action(button_main_runAuto, LV_BTN_ACTION_CLICK, btn_click_runAuto);

    /*Add a label to the button*/
    label = lv_label_create(button_main_runAuto, NULL);
    lv_label_set_text(label, "Run\nAuto");

    lv_obj_set_hidden(button_main_runAuto, true);

    button_main_Auto1 = lv_btn_create(lv_scr_act(), NULL);
    lv_cont_set_fit(button_main_Auto1, true, true); /*Enable resizing horizontally and vertically*/
    lv_obj_align(button_main_Auto1, button_main_runAuto, LV_ALIGN_CENTER, 90, -11);
    lv_obj_set_style(button_main_Auto1, &style_button_autoWhite);
    lv_obj_set_free_num(button_main_Auto1, 0);   /*Set a unique number for the button*/
    lv_btn_set_action(button_main_Auto1, LV_BTN_ACTION_CLICK, btn_click_Auto1);

    /*Add a label to the button*/
    label = lv_label_create(button_main_Auto1, NULL);
    lv_label_set_text(label, "1");

    lv_obj_set_hidden(button_main_Auto1, true);

    button_main_Auto2 = lv_btn_create(lv_scr_act(), button_main_Auto1);
    lv_obj_align(button_main_Auto2, button_main_Auto1, LV_ALIGN_CENTER, 60, 0);
    lv_obj_set_free_num(button_main_Auto2, 0);   /*Set a unique number for the button*/
    lv_btn_set_action(button_main_Auto2, LV_BTN_ACTION_CLICK, btn_click_Auto2);

    /*Add a label to the button*/
    label = lv_label_create(button_main_Auto2, NULL);
    lv_label_set_text(label, "2");

    lv_obj_set_hidden(button_main_Auto2, true);

    button_main_Auto3 = lv_btn_create(lv_scr_act(), button_main_Auto1);
    lv_obj_align(button_main_Auto3, button_main_Auto2, LV_ALIGN_CENTER, 60, 0);
    lv_obj_set_free_num(button_main_Auto3, 0);   /*Set a unique number for the button*/
    lv_btn_set_action(button_main_Auto3, LV_BTN_ACTION_CLICK, btn_click_Auto3);

    /*Add a label to the button*/
    label = lv_label_create(button_main_Auto3, NULL);
    lv_label_set_text(label, "3");

    lv_obj_set_hidden(button_main_Auto3, true);

    button_main_Auto4 = lv_btn_create(lv_scr_act(), button_main_Auto1);
    lv_obj_align(button_main_Auto4, button_main_Auto3, LV_ALIGN_CENTER, 60, 0);
    lv_obj_set_free_num(button_main_Auto4, 0);   /*Set a unique number for the button*/
    lv_btn_set_action(button_main_Auto4, LV_BTN_ACTION_CLICK, btn_click_Auto4);

    /*Add a label to the button*/
    label = lv_label_create(button_main_Auto4, NULL);
    lv_label_set_text(label, "4");

    lv_obj_set_hidden(button_main_Auto4, true);

    button_main_Auto5 = lv_btn_create(lv_scr_act(), button_main_Auto1);
    lv_obj_align(button_main_Auto5, button_main_Auto4, LV_ALIGN_CENTER, 60, 0);
    lv_obj_set_free_num(button_main_Auto5, 0);   /*Set a unique number for the button*/
    lv_btn_set_action(button_main_Auto5, LV_BTN_ACTION_CLICK, btn_click_Auto5);

    /*Add a label to the button*/
    label = lv_label_create(button_main_Auto5, NULL);
    lv_label_set_text(label, "5");

    lv_obj_set_hidden(button_main_Auto5, true);

    button_main_Auto6 = lv_btn_create(lv_scr_act(), button_main_Auto1);
    lv_obj_align(button_main_Auto6, button_main_Auto5, LV_ALIGN_CENTER, 60, 0);
    lv_obj_set_free_num(button_main_Auto6, 0);   /*Set a unique number for the button*/
    lv_btn_set_action(button_main_Auto6, LV_BTN_ACTION_CLICK, btn_click_Auto6);

    /*Add a label to the button*/
    label = lv_label_create(button_main_Auto6, NULL);
    lv_label_set_text(label, "6");

    lv_obj_set_hidden(button_main_Auto6, true);


    page_main_autoDesc = lv_page_create(lv_scr_act(), NULL);
    lv_obj_set_size(page_main_autoDesc, 351, 100);
    lv_obj_align(page_main_autoDesc, page_main_header, LV_ALIGN_IN_BOTTOM_MID, 45, 165);
    lv_page_set_style(page_main_autoDesc, LV_PAGE_STYLE_BG, &style_page_transpGoldBorder);           /*Set the scrollbar style*/
    lv_page_set_sb_mode(page_main_autoDesc, LV_SB_MODE_OFF);                     /*Show scroll bars is scrolling is possible*/

    page_text_autoDesc = lv_label_create(page_main_autoDesc, NULL);
    lv_label_set_long_mode(page_text_autoDesc, LV_LABEL_LONG_BREAK);             /*Automatically break long lines*/
    lv_obj_set_width(page_text_autoDesc, lv_page_get_scrl_width(page_main_autoDesc));          /*Set the width. Lines will break here*/
    lv_label_set_text(page_text_autoDesc, "Description: Please select an auto "
                                          "mode (listed 1-6) above.");

    lv_obj_set_hidden(page_main_autoDesc, true);

     button_main_resetIMU = lv_btn_create(lv_scr_act(), NULL);
     lv_cont_set_fit(button_main_resetIMU, true, true); /*Enable resizing horizontally and vertically*/
     lv_obj_align(button_main_resetIMU, button_main_runAuto, LV_ALIGN_OUT_BOTTOM_MID, -5, 50);
     lv_obj_set_style(button_main_resetIMU, &style_button_autoWhite);
     lv_obj_set_free_num(button_main_resetIMU, 0);   /*Set a unique number for the button*/
     lv_btn_set_action(button_main_resetIMU, LV_BTN_ACTION_CLICK, btn_click_resetIMU);

     /*Add a label to the button*/
     label = lv_label_create(button_main_resetIMU, NULL);
     lv_label_set_text(label, "Reset\nIMU");

     lv_obj_set_hidden(button_main_resetIMU, true);


     page_main_IMUData = lv_page_create(lv_scr_act(), NULL);
     lv_obj_set_size(page_main_IMUData, 351, 35);
     lv_obj_align(page_main_IMUData, page_main_autoDesc, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
     lv_page_set_style(page_main_IMUData, LV_PAGE_STYLE_BG, &style_page_transpGoldBorderWhite);           /*Set the scrollbar style*/
     lv_page_set_sb_mode(page_main_IMUData, LV_SB_MODE_OFF);                     /*Show scroll bars is scrolling is possible*/

     std::string str;

    screeni= 0;

     char *cstr = new char[10];
     sprintf(cstr, "lolol");
     strcpy(cstr, str.c_str());

     //(*ptr)[8];
     //arr[8] = {"abc.def"};
     ptr = &arr;



     page_text_IMUData = lv_label_create(page_main_IMUData, NULL);
     lv_label_set_long_mode(page_text_IMUData, LV_LABEL_LONG_BREAK);
     lv_obj_set_width(page_text_IMUData, lv_page_get_scrl_width(page_main_IMUData));
     lv_label_set_text(page_text_IMUData, *ptr);
     sprintf(arr, "text");
     lv_label_set_text(page_text_IMUData, *ptr);

/*
     str = "lololol";
     cstr = new char[str.length() + 1];
     strcpy(cstr, str.c_str());

     lv_label_set_text(label, cstr);*/



     lv_obj_set_hidden(page_main_IMUData, true);

 }
