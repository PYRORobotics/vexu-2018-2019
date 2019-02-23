#include "api.h"

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

extern void Screen_Init_SetStlyes();
extern void Screen_Background_Init();
extern void Screen_Title_Title();

static int screeni;
extern lv_obj_t * page_text_IMUData;
extern char *cstr;

static char (*ptr)[8];
static char arr[8] = {"abc.def"};

static int autoModeBtn[6];

extern lv_obj_t * page_main_headerTeleopMode;

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
