#include "../include/screen.hpp"
#include "../include/api.h"


void styleInit()
{
  // BaseObject_MainBackground //
  lv_style_copy(&style_BaseObject_MainBackground, &lv_style_scr);
  style_BaseObject_MainBackground.body.main_color = LV_COLOR_BLACK;
  style_BaseObject_MainBackground.body.grad_color = LV_COLOR_BLACK;

  COLOR_ASU_MAROON.red = 140;
  COLOR_ASU_MAROON.green = 15;
  COLOR_ASU_MAROON.blue = 32;

  COLOR_ASU_GOLD.red = 255;
  COLOR_ASU_GOLD.green = 198;
  COLOR_ASU_GOLD.blue = 39;

  lv_style_copy(&style_Button_Main, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
  style_Button_Main.body.main_color = COLOR_ASU_GOLD;
  style_Button_Main.body.grad_color = COLOR_ASU_GOLD;
  style_Button_Main.body.radius = 15;
  style_Button_Main.body.border.color = COLOR_ASU_MAROON;
  style_Button_Main.body.border.width = 4;
  style_Button_Main.body.border.opa = LV_OPA_COVER;
  style_Button_Main.body.opa = LV_OPA_COVER;
  style_Button_Main.body.padding.hor = 22;            /*Horizontal padding, used by the bar indicator below*/
  style_Button_Main.body.padding.ver = 22;            /*Vertical padding, used by the bar indicator below*/
  style_Button_Main.body.padding.inner = 10;
  style_Button_Main.text.color = LV_COLOR_BLACK;

  lv_style_plain.body.main_color = LV_COLOR_BLACK;
  lv_style_plain.body.grad_color = LV_COLOR_BLACK;
  lv_style_plain.body.border.color = LV_COLOR_BLACK;
  lv_style_plain.text.color = COLOR_ASU_GOLD;



  lv_style_pretty.body.main_color = COLOR_ASU_GOLD;
  lv_style_pretty.body.grad_color = COLOR_ASU_GOLD;
  lv_style_pretty.body.radius = 15;
  lv_style_pretty.body.border.color = COLOR_ASU_MAROON;
  lv_style_pretty.body.border.width = 5;
  lv_style_pretty.body.border.opa = LV_OPA_COVER;
  lv_style_pretty.body.opa = LV_OPA_COVER;
  lv_style_pretty.body.padding.hor = 20;            /*Horizontal padding, used by the bar indicator below*/
  lv_style_pretty.body.padding.ver = 20;            /*Vertical padding, used by the bar indicator below*/
  lv_style_pretty.text.color = LV_COLOR_BLACK;


}

void screenInit()
{
  // BaseObject_MainBackground //
  BaseObject_MainBackground = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(BaseObject_MainBackground, 480, 240);
  lv_obj_set_style(BaseObject_MainBackground, &style_BaseObject_MainBackground);
  lv_obj_align(BaseObject_MainBackground, NULL, LV_ALIGN_CENTER, 0, 0);


  autonSelectBtnMatrix = lv_btnm_create(lv_scr_act(), NULL);
  lv_btnm_set_map(autonSelectBtnMatrix, btnm_map);
  lv_btnm_set_action(autonSelectBtnMatrix, btnm_action);
  lv_obj_set_size(autonSelectBtnMatrix, LV_HOR_RES, LV_VER_RES / 2);
  lv_obj_align(autonSelectBtnMatrix, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_obj_set_hidden(autonSelectBtnMatrix, 1);
  lv_obj_set_style(autonSelectBtnMatrix, &lv_style_plain);



  LV_IMG_DECLARE(Image_PYRO_Gold);
  LV_IMG_DECLARE(Image_ASU_White);
  LV_IMG_DECLARE(Image_RRR_White);
  LV_IMG_DECLARE(Image_PYRO_License_Plate);



  PYRO_Gold = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(PYRO_Gold, &Image_PYRO_Gold);
  lv_obj_align(PYRO_Gold, NULL, LV_ALIGN_CENTER, 0, -35);


  ASU_White = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(ASU_White, &Image_ASU_White);
  lv_obj_align(ASU_White, NULL, LV_ALIGN_IN_BOTTOM_MID, 160, -25);


  RRR_White = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(RRR_White, &Image_RRR_White);
  lv_obj_align(RRR_White, NULL, LV_ALIGN_IN_BOTTOM_MID, -160, -25);



  /*Create a title label*/
  label_TitleBlock = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label_TitleBlock, "PYRO Robotics VEX U - Arizona State University");
  lv_obj_align(label_TitleBlock, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

  /*Create a normal button*/
  Button_Continue = lv_btn_create(lv_scr_act(), NULL);
  lv_cont_set_fit(Button_Continue, true, true); /*Enable resizing horizontally and vertically*/
  lv_obj_align(Button_Continue, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
  lv_obj_set_free_num(Button_Continue, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(Button_Continue, LV_BTN_ACTION_CLICK, btn_main_cont_action);
  lv_obj_set_style(Button_Continue, &style_Button_Main);

  /*Add a label to the button*/
  label_btnLabel = lv_label_create(Button_Continue, NULL);
  lv_label_set_text(label_btnLabel, "Continue");


}

void screenCompetitionInit()
{

  /*Create a default button matrix*/

}





void screenPrintPosition(int left, int right) // BROKEN - DONT USE
{
  LV_IMG_DECLARE(Image_VEX_Field);

  lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img1, &Image_VEX_Field);
  lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, 0);

  BaseObject_PositionIndicator = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(BaseObject_PositionIndicator, 20, 20);
  lv_obj_set_style(BaseObject_PositionIndicator, &style_BaseObject_MainBackground);

  lv_obj_align(BaseObject_PositionIndicator, NULL, LV_ALIGN_CENTER, left, right);

}


void animationTesting()
{
  /*Create a title label*/
lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(label, "Default buttons");
lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

/*Create a normal button*/
lv_obj_t * Button_Continue = lv_btn_create(lv_scr_act(), NULL);
lv_cont_set_fit(Button_Continue, true, true); /*Enable resizing horizontally and vertically*/
lv_obj_align(Button_Continue, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
lv_obj_set_free_num(Button_Continue, 1);   /*Set a unique number for the button*/
//lv_btn_set_action(Button_Continue, LV_BTN_ACTION_CLICK, btn_click_action);

/*Add a label to the button*/
label = lv_label_create(Button_Continue, NULL);
lv_label_set_text(label, "Normal");



  lv_anim_t a;
  a.var = Button_Continue;                             /*Variable to animate*/
  a.start = 0;                                 /*Start value*/
  a.end = 10;                                 /*End value*/
  a.fp = (lv_anim_fp_t)lv_obj_set_height;                                 /*Function to be used to animate*/
  a.path = lv_anim_path_linear;                                            /*Path of animation*/
  a.end_cb = NULL;                               /*Callback when the animation is ready*/
  a.act_time = 0;                                 /*Set < 0 to make a delay [ms]*/
  a.time = 200;                                 /*Animation length [ms]*/
  a.playback = 0;                                 /*1: animate in reverse direction too when the normal is ready*/
  a.playback_pause = 0;                                 /*Wait before playback [ms]*/
  a.repeat = 0;                                 /*1: Repeat the animation (with or without playback)*/
  a.repeat_pause = 1000;                             /*Wait before repeat [ms]*/

  lv_anim_create(&a);                          /*Start the animation*/
}
