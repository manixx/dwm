/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2;  /* border pixel of windows */
static const unsigned int gappx    = 7;  /* gaps between windows */
static const unsigned int snap     = 32; /* snap pixel */
static const int showbar           = 1;  /* 0 means no bar */
static const int topbar            = 1;  /* 0 means bottom bar */
static const char *fonts[]         = { "Bitstream Vera Sans:size=8:style=Bold" };
static const char dmenufont[]      = "Bitstream Vera Sans:size=8";
static const char col_white[]      = "#c5cdd9";
static const char col_black[]      = "#2c2e34";
static const char col_gray[]       = "#414550";
static const char col_magenta[]    = "#d38aea";
static const char col_red[]        = "#ec7279";
static const char col_yellow[]     = "#deb974";
static const char *colors[][3]     = {
	/*                 fg         bg         border    */
	[SchemeNorm]   = { col_gray,  col_black,  col_black }, /* tags normal */
	[SchemeSel]    = { col_white, col_black,  col_white }, /* tags selected */
	[SchemeBar]    = { col_white, col_gray,   col_black }, /* bar selected mon */
	[SchemeStatic] = { col_white, col_black,  col_black }, /* status */
	[SchemeWarn]   = { col_black, col_yellow, col_red   }, /* custom status color */
	[SchemeUrgent] = { col_red,   col_black,  col_red   }, /* custom status color */
};

/* tagging */
static const char *tags[] = { "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class instance            title tags mask     isfloating   monitor */
	{  NULL, "chromium",         NULL, 1 << 1,       0,           -1 },
	{  NULL, "web.whatsapp.com", NULL, 1 << 3,       0,           -1 },
	{  NULL, "matterhorn",       NULL, 1 << 3,       0,           -1 },
	{  NULL, "telegram-desktop", NULL, 1 << 3,       0,           -1 },
	{  NULL, "st-float",         NULL, -1,           0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu-desktop",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", col_black,
	"-nf", col_white,
	"-sb", col_white,
	"-sf", col_black,
	NULL
};
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_s,      togglecanfocusfloating,   {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0}  },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	{ MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
	{ MODKEY,                       XK_plus,  scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_plus,  scratchpad_hide, {0} },
	{ MODKEY,                       XK_minus,scratchpad_remove,{0} },
};

/* button definitions */
/* click can be
 * 		ClkTagBar,
 * 		ClkLtSymbol,
 * 		ClkStatusText,
 * 		ClkWinTitle,
 * 		ClkClientWin,
 * 		ClkRootWin
 */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

