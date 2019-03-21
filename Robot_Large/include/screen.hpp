#include "api.h"
#include "robot.hpp"
#include "autonRoutines.hpp"

#ifndef SCREEN_HPP
#define SCREEN_HPP




// Static objects used throughout program //
static lv_obj_t * BaseObject_MainBackground;
static lv_obj_t * BaseObject_PositionIndicator;
static lv_obj_t * PYRO_Gold;
static lv_obj_t * autonSelectBtnMatrix;
static lv_obj_t * Button_Continue;
static lv_obj_t * ASU_White;
static lv_obj_t * RRR_White;
static lv_obj_t * PYRO_License_Plate;
static lv_obj_t * label_TitleBlock;
static lv_obj_t * label_btnLabel;


// Static Const colors //
static lv_color_t COLOR_ASU_MAROON;
static lv_color_t COLOR_ASU_GOLD;



// Static styles used by objects //
static lv_style_t style_BaseObject_MainBackground;
static lv_style_t style_Button_Main;
static lv_style_t style_plate_red;
static lv_style_t style_plate_blue;


// Static colors used by styles//
//lv_color1_t COLOR_BLACK;



// Functions called by Robot //
void styleInit();
void screenInit();
void screenPrintPosition(int,int); // BROKEN - DONT USE
void screenCompetitionInit();


// Static functions called by buttons //
static lv_res_t btn_main_cont_action(lv_obj_t * btn)
{
  // Hide the Pyro Logo
  lv_obj_set_hidden(PYRO_Gold, 1);
  lv_obj_set_hidden(RRR_White, 1);
  lv_obj_set_hidden(ASU_White, 1);

  lv_obj_set_hidden(btn, 1);


  lv_obj_set_hidden(autonSelectBtnMatrix, 0);

  if(pros::competition::is_connected())
  {
    lv_label_set_text(label_TitleBlock, "CONNECTED TO FIELD: Choose an Autonomous!");
  }
  else
  {
    lv_label_set_text(label_TitleBlock, "NOT CONNECTED TO FIELD: Choose an Autonomous!");
  }

  return LV_RES_INV; /*Return OK if the button is not deleted*/
}


/*Called when a button is released ot long pressed*/
static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt)
{
  std::string str(txt);

  printf("Button: %s released\n", txt);
  if(str == "Red 1")
  {
    autonomousIDNum = 0;
    if(pros::competition::is_connected())
      lv_label_set_text(label_TitleBlock, "CONNECTED TO FIELD: Autonomous Red 1 Selected");
    else
      lv_label_set_text(label_TitleBlock, "NOT CONNECTED TO FIELD: Autonomous Red 1 Selected");
  }
  else if(str == "Blue 1")
  {
    autonomousIDNum = 1;
    if(pros::competition::is_connected())
      lv_label_set_text(label_TitleBlock, "CONNECTED TO FIELD: Autonomous Blue 1 Selected");
    else
      lv_label_set_text(label_TitleBlock, "NOT CONNECTED TO FIELD: Autonomous Blue 1 Selected");
  }



  printf("autonomousIDNum = %d",autonomousIDNum);

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static const char * btnm_map[] = {"Red 1","Blue 1","Red 1","Blue 1",""};

#endif
