/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int user_bh            = 18;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Noto Sans:weight=bold:size=11", "Noto Color Emoji:size=12" };
static const char dmenufont[]       = "Fira Sans:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#eeeeee";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#7A0099";
static const char act_bor[]         = "#e6ede8";
static const char inact_bor[]       = "#041c0b";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, inact_bor },
	[SchemeSel]  = { col_gray4, col_cyan,  act_bor  },
	[SchemeStatus]={ col_cyan, col_gray1,  NULL  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"alacritty", "--class", "spterm", NULL };
const char *spcmd2[] = {"alacritty", "--class", "spfm", "-e", "ranger", NULL };
const char *spcmd3[] = {"alacritty", "--class", "spmpc", "-e", "ncmpcpp", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",    spcmd2},
	{"spmpc",   spcmd3},
};

/* status bar */
static const Block blocks[] = {
	/* fg     command				interval	signal */
	{ "#FF3080", "stat-timedate",		60,		1},
	{ "#3BFF30", "stat-volume",			0,	    2},
	{ "#3098FF", "stat-battery",		5,		3},
	{ "#FF9B30", "stat-backlight",		0,		4},
	{ "#FF3080", "stat-wifi",			5,		8},
	//{ "#FF9B30", "stat-weather",		0,		7},
	{ "#FFF130",  "stat-music",			5,		5},
/*	{ "#000001", "sb-moonphase",			0,		6},
	{ "#1F0077", "sb-forecast",			0,		7},
	{ "#000077", "sb-volume",			0,		8},
	{ "#F77000", "sb-pacpackages",			0,		9},
	{ "#177000", "sb-sync",				0,		10},
//	{ col_gray1, "sb-mpc",				0,		26},
	{ col_gray2, "sb-music",			0,		11},
//	{ col_gray3, "sb-tasks",			10,		12},
	{ col_gray4, "sb-notes",			0,		13},
	{ col_cyan, "echo '';cat /tmp/recordingicon",	0,		14}, */
};

/* inverse the order of the blocks, comment to disable */
#define INVERSED	1
/* delimeter between blocks commands. NULL character ('\0') means no delimeter. */
static char delimiter[] = "  ";
/* max number of character that one block command can output */
#define CMDLENGTH	50


/* tagging */
static const char *tags[] = { "α", "β", "γ", "δ", "ε", "ζ", "η", "θ", "ι" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           0,         0,          0,          -1,        -1 },
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Alacritty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
    { NULL,		 "spterm",		NULL,		SPTAG(0),		1,	1,              0,		 -1 },
	{ NULL,		 "spfm",		NULL,		SPTAG(1),		1,	1,              0,		 -1 },
	{ NULL,		 "spmpc",	NULL,		SPTAG(2),		1,	1,              0,		 -1 },
};

/* window following */
#define WFACTIVE '>'
#define WFINACTIVE 'v'
#define WFDEFAULT WFINACTIVE

/* layout(s) */
static const float mfact     = 0.53; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
    { "TTT",      bstack },

	{ "[@]",      spiral },
	{ "[\\]",     dwindle },

	{ "HHH",      grid },
	{ "|M|",      centeredmaster },
	{ "[M]",      monocle },

	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TERMINAL "$TERMINAL"
#define BROWSER "$BROWSER"

#include <X11/XF86keysym.h>

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_s,      togglefollow,   {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },

	{ MODKEY,                       XK_p,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_p,      resetnmaster,   {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY|ControlMask,             XK_x,      killunsel,      {0} },
	{ MODKEY,                       XK_g,      reorganizetags, {0} },

    { MODKEY,                       XK_x,    unfloatvisible, {0} },
	{ MODKEY,		                XK_Tab,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab, cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglealwaysontop, {0} },
	{ MODKEY|ControlMask,           XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },

    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },//tile
    { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },//bottom tile
    { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },//spindle
    { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} },//dwindle
    { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} },//monocle
    { MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[5]} },//centered Master
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[6]} },//grid
    { MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[7]} },//floating
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_f,  togglefloating, {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY|ShiftMask,            	XK_Return, 	  togglescratch,  {.ui = 0 } },
	{ Mod1Mask|ShiftMask,           XK_Return,	  togglescratch,  {.ui = 1 } },
	{ MODKEY|Mod1Mask,            	XK_Return,	  togglescratch,  {.ui = 2 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask,           XK_q,      quit,           {1} }, 
	{ MODKEY,                       XK_Next, scratchpad_show, {0} },
	{ MODKEY,                       XK_Prior, scratchpad_hide, {0} },
	{ MODKEY,                       XK_End ,scratchpad_remove,{0} },

    { MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
    { MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
    { MODKEY|ShiftMask,             XK_equal,  togglegaps,     {0} },
    { MODKEY|ShiftMask,             XK_minus,  defaultgaps,    {0} },

	{ MODKEY|ControlMask,           XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_o,      incrogaps,      {.i = -1 } },

    { MODKEY|ControlMask,           XK_bracketleft,      shifttag,      { .i = -1 } },
    { MODKEY|ControlMask,           XK_bracketright,     shifttag,      { .i = +1 } },
    { MODKEY,                       XK_bracketleft,      shiftview,      { .i = -1 } },
    { MODKEY,                       XK_bracketright,     shiftview,      { .i = +1 } },
    { MODKEY|ShiftMask,             XK_bracketright,     shifttagclients,      { .i = +1 } },
    { MODKEY|ShiftMask,             XK_bracketleft,      shifttagclients,      { .i = -1 } },

	{ MODKEY|ShiftMask,             XK_i,      aspectresize,   {.i = +24} },
	{ MODKEY|ControlMask,           XK_i,      aspectresize,   {.i = -24} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

    { Mod1Mask|ControlMask,         XK_v,               spawn,      SHCMD(TERMINAL " -e pulsemixer") },
    { Mod1Mask|ShiftMask,           XK_s,               spawn,      SHCMD("maim -s ~/Data/screenshots/$(date +%Y-%m-%d-%s).png") },
    { ShiftMask,                    XK_Print,           spawn,      SHCMD("maim -s ~/Data/screenshots/$(date +%Y-%m-%d-%s).png") },
    { Mod1Mask,                     XK_s,               spawn,      SHCMD("maim ~/Data/screenshots/$(date +%Y-%m-%d-%s).png") },

    { 0, XK_Print,                                      spawn,      SHCMD("maim ~/Data/screenshots/$(date +%Y-%m-%d-%s).png") },
    { 0, XF86XK_AudioMute,                              spawn,      SHCMD("pamixer -t; kill -36 $(pidof dwm)") },
    { 0, XF86XK_AudioRaiseVolume,                       spawn,      SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +3%; kill -36 $(pidof dwm)") },
    { 0, XF86XK_AudioLowerVolume,                       spawn,      SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -3%; kill -36 $(pidof dwm)") },
    { 0, XF86XK_MonBrightnessUp,                        spawn,      SHCMD("xbacklight -inc 5%; kill -38 $(pidof dwm)") },
    { 0, XF86XK_MonBrightnessDown,                      spawn,      SHCMD("xbacklight -dec 5%; kill -38 $(pidof dwm)") },
    { 0, XF86XK_AudioPrev,                              spawn,      SHCMD("mpc prev; kill -39 $(pidof dwm)") },
    { 0, XF86XK_AudioNext,                              spawn,      SHCMD("mpc next; kill -39 $(pidof dwm)") },
    { 0, XF86XK_AudioPlay,                              spawn,      SHCMD("mpc toggle; kill -39 $(pidof dwm)") },
    { 0, XF86XK_HomePage,                               spawn,      SHCMD(BROWSER) },
    { Mod1Mask|MODKEY,              XK_equal,           spawn,      SHCMD("xbacklight -inc 5%; kill -38 $(pidof dwm)") },
    { Mod1Mask|MODKEY,              XK_minus,           spawn,      SHCMD("xbacklight -dec 5%; kill -38 $(pidof dwm)") },

    { Mod1Mask,                     XK_Up,              spawn,      SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +3%; kill -36 $(pidof dwm)") },
    { Mod1Mask,                     XK_Down,            spawn,      SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -3%; kill -36 $(pidof dwm)") },
    { Mod1Mask|ShiftMask,           XK_space,           spawn,      SHCMD("mpc toggle; kill -39 $(pidof dwm)") },
    { Mod1Mask|ShiftMask,           XK_Right,           spawn,      SHCMD("mpc next; kill -39 $(pidof dwm)") },
    { Mod1Mask|ShiftMask,           XK_Left,            spawn,      SHCMD("mpc prev; kill -39 $(pidof dwm)") },
    { Mod1Mask,                     XK_bracketleft,     spawn,      SHCMD("mpc seek -10") },
    { Mod1Mask|ShiftMask,           XK_bracketleft,     spawn,      SHCMD("mpc seek -60") },
    { Mod1Mask,                     XK_bracketright,    spawn,      SHCMD("mpc seek +10") },
    { Mod1Mask|ShiftMask,           XK_bracketright,    spawn,      SHCMD("mpc seek +60") },
    { Mod1Mask,                     XK_Left,            spawn,      SHCMD("mpc vol -5") },
    { Mod1Mask,                     XK_Right,           spawn,      SHCMD("mpc vol +5") },
    { Mod1Mask|ControlMask,         XK_space,           spawn,      SHCMD("mpc single") },
    { Mod1Mask,		                XK_apostrophe,	    spawn,		SHCMD("mpc seek 0%") },

    { Mod1Mask,		                XK_r,	            spawn,		SHCMD("radio-listen") },
    { Mod1Mask,		                XK_Menu,	        spawn,		SHCMD("radio-listen") },
    { MODKEY|ShiftMask,             XK_BackSpace,       spawn,      SHCMD("power") },
    { Mod1Mask,                     XK_BackSpace,       spawn,      SHCMD("vimmouse") },
    { MODKEY|ControlMask,           XK_w,               spawn,      SHCMD(TERMINAL " -e links") },

    { MODKEY,                       XK_n,               spawn,      SHCMD(TERMINAL " -e newsboat") },
    { Mod1Mask|ShiftMask,           XK_w,               spawn,      SHCMD("sxiv -q -o -t -r ~/Data/Media/wallpapers") },
    { MODKEY|ShiftMask,             XK_g,               spawn,      SHCMD("gimp") },
    { MODKEY,                       XK_grave,           spawn,      SHCMD("alacritty") },
    { MODKEY|ShiftMask,             XK_grave,           spawn,      SHCMD("libreoffice") },
    { MODKEY|ShiftMask,             XK_x,               spawn,      SHCMD("pcmanfm") },
    { MODKEY|ShiftMask,             XK_e,               spawn,      SHCMD(TERMINAL " -e htop") },
   // { MODKEY|ShiftMask,             XK_n,               spawn,      SHCMD(TERMINAL " -e newsboat") },
    { MODKEY,                       XK_w,               spawn,      SHCMD(BROWSER) },
    { MODKEY|ShiftMask,             XK_v,               spawn,      SHCMD("minitube") },

    { MODKEY,                       XK_m,               spawn,      SHCMD(TERMINAL " -e neomutt") },
    { MODKEY,                       XK_v,               spawn,      SHCMD("qbittorrent") },
//    { MODKEY|ShiftMask,             XK_n,               spawn,      SHCMD(TERMINAL " -e nvim $HOME/.cache/ScratchNote.md") },
    { MODKEY|ControlMask,           XK_z,               spawn,      SHCMD("slock") },
    { MODKEY,                       XK_c,               spawn,      SHCMD("galculator") },
    { MODKEY|ControlMask,           XK_r,               spawn,      SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam /dev/video0") },

    { Mod1Mask,                     XK_w,               spawn,      SHCMD(TERMINAL " -e nmtui") },
    { MODKEY,                       XK_e,               spawn,      SHCMD("emacsclient -c || emacs") },
    { MODKEY,                       XK_d,               spawn,      SHCMD("clipgrab") },
    { MODKEY|ShiftMask,             XK_d,               spawn,      SHCMD("rofi -show drun") },
    { MODKEY,                       XK_a,               spawn,      SHCMD(TERMINAL " -e ranger") },
    { MODKEY,                       XK_Menu,            spawn,      SHCMD("rofi -show emoji") },
    { MODKEY,                       XK_slash,           spawn,      SHCMD("web-search") },
    { MODKEY|ShiftMask,             XK_slash,           spawn,      SHCMD("browser-launch") },
    { MODKEY|ShiftMask,             XK_w,               spawn,      SHCMD("open-bookmarks") },
    { MODKEY,                       XK_apostrophe,      spawn,      SHCMD("notify-timedate") },
    { MODKEY|ShiftMask,             XK_apostrophe,      spawn,      SHCMD("notify-battery") },
    { MODKEY|ControlMask,           XK_apostrophe,      spawn,      SHCMD("notify-wifi") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },

	{ ClkStatusText,        0,              Button1,        sendstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sendstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sendstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sendstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sendstatusbar,   {.i = 5 } },
	{ ClkStatusText,        ShiftMask,      Button1,        sendstatusbar,   {.i = 6 } },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkFollowSymbol,      0,              Button1,        togglefollow,   {0} },
};

