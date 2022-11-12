//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    {"", "echo 🕉",        0,                      0},
    {"", "stat-music",        0,                      12},
    {"", "stat-battery",        5,                      0},
//    {"",          "stat-weather",        1200,                   0},
//    {"",          "stat-moon",        0,                   0},
//    {"",          "stat-updown",        1,                   0},
    {"",          "stat-wifi",           10,                     0},
    {"",          "stat-volume",         0,                     10},
    {"",      "stat-backlight",              0 ,   11},
//	{"💾",    "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	      1,	  	0},
//    {"🖥",             "stat-cpu",  1 ,   0},
	{"",             "stat-timedate",		60,		                0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "  ";
static unsigned int delimLen = 5;
