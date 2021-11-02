/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Noto Sans Mono CJK SC:size=11", "FiraCode Nerd Font Mono:size=11" };
static const char dmenufont[]       = "Noto Mono:size=11";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#3c3836";
static const char col_gray3[]       = "#d5c4a1";
static const char col_gray4[]       = "#fbf1c7";
static const char col_cyan[]        = "#076678";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance    title       tags mask       switchtotag     isfloating  monitor */
	{ "firefox",            NULL,       NULL,       1 << 2,         1,              0,          -1 },
	{ "Microsoft-edge-dev", NULL,       NULL,       1 << 2,         1,              0,          -1 },
	{ "Microsoft-edge-beta",NULL,       NULL,       1 << 2,         1,              0,          -1 },
	{ "Microsoft-edge",     NULL,       NULL,       1 << 2,         1,              0,          -1 },
	{ "Google-chrome",      NULL,       NULL,       1 << 2,         1,              0,          -1 },
	{ "Virt-manager",       NULL,       NULL,       1 << 6,         1,              1           -1 },
	{ "Gimp",               NULL,       NULL,       1 << 7,         1,              1,          -1 },
	{ "zoom",               NULL,       NULL,       1 << 7,         1,              1,          -1 },
	{ "Minecraft Launcher", NULL,       NULL,       1 << 7,         1,              1,          -1 },
	{ "Wine",               NULL,       NULL,       1 << 8,         1,              1           -1 },
	{ "Spotify",            NULL,       NULL,       1 << 8,         1,              1           -1 },
	{ "Steam",              NULL,       NULL,       1 << 8,         1,              1,          -1 },
	{ "TelegremDesktop",    NULL,       NULL,       1 << 8,         1,              1,          -1 },
	{ "qBittorrent",        NULL,       NULL,       1 << 8,         1,              1,          -1 },
	{ "Uget-gtk",           NULL,       NULL,       1 << 8,         1,              1,          -1 },
	{ "OSD Lyrics",         NULL,       NULL,       0,              0,              1,          -1 },

};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[]D",      doubledeck },
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

/* commands */
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_history", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]            = { "target-app", "terminal", NULL };
static const char *lockcmd[]            = { "target-app", "locker", NULL };
static const char *browsercmd[]         = { "target-app", "browser", NULL };
static const char *finderguicmd[]       = { "target-app", "finder", "gui", NULL };
static const char *findertuicmd[]       = { "target-app", "finder", "tui", NULL };
static const char *mediaplaypausecmd[]  = { "media-control", "PlayPause", NULL };
static const char *medianextcmd[]       = { "media-control", "Next", NULL };
static const char *mediapreviouscmd[]   = { "media-control", "Previous", NULL };
static const char *mediavolupcmd[]      = { "media-control", "VolumeUp", NULL };
static const char *mediavoldowncmd[]    = { "media-control", "VolumeDown", NULL };
static const char *mediavolmutecmd[]    = { "media-control", "VolumeMute", NULL };
static const char *toggledisplaycmd[]   = { "toggle-display", NULL };
static const char *togglesoundcmd[]     = { "toggle-display-sound", NULL };
static const char *scareacmd[]          = { "flameshot", "gui", NULL };
static const char *scareadelaycmd[]     = { "flameshot", "gui", "-d", "3000", NULL };
static const char *scfullcmd[]          = { "flameshot", "full", "-c", NULL };
static const char *launchercmd[]        = { "launcher_misc", NULL };
static const char *powermenucmd[]       = { "menu_powermenu", NULL };

static Key keys[] = {
	/* modifier                     key                 function        argument */
    { MODKEY,                       XK_p,               spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,          spawn,          {.v = termcmd } },
	{ MODKEY|Mod1Mask,              XK_l,               spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_space,           spawn,          {.v = launchercmd} },
	{ MODKEY,                       XK_x,               spawn,          {.v = powermenucmd} },
	{ MODKEY,                       XK_b,               spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_e,               spawn,          {.v = finderguicmd } },
	{ MODKEY,                       XK_f,               spawn,          {.v = findertuicmd } },
	{ MODKEY,                       XK_t,               togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_backslash,       spawn,          {.v = mediaplaypausecmd } },
	{ MODKEY,                       XK_bracketright,    spawn,          {.v = medianextcmd } },
	{ MODKEY,                       XK_bracketleft,     spawn,          {.v = mediapreviouscmd } },
	{ MODKEY|ShiftMask,             XK_backslash,       spawn,          {.v = mediavolmutecmd } },
	{ MODKEY|ShiftMask,             XK_bracketright,    spawn,          {.v = mediavolupcmd } },
	{ MODKEY|ShiftMask,             XK_bracketleft,     spawn,          {.v = mediavoldowncmd } },
	{ MODKEY,                       XK_m,               spawn,          {.v = toggledisplaycmd } },
	{ MODKEY,                       XK_n,               spawn,          {.v = togglesoundcmd } },
	{ MODKEY,                       XK_s,               spawn,          {.v = scareacmd } },
	{ MODKEY|ShiftMask,             XK_s,               spawn,          {.v = scareadelaycmd } },
	{ MODKEY|Mod1Mask,              XK_s,               spawn,          {.v = scfullcmd } },
    { MODKEY|ShiftMask,             XK_b,               togglebar,      {0} },
	{ MODKEY,                       XK_j,               focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,               focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,               focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,               focusstackhid,  {.i = -1 } },
	{ MODKEY,                       XK_i,               incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,               incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,               setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,          zoom,           {0} },
	{ MODKEY,                       XK_Tab,             view,           {0} },
	{ MODKEY,                       XK_q,               killclient,     {0} },
	{ MODKEY|Mod1Mask,              XK_1,               setlayout,      {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,              XK_2,               setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_3,               setlayout,      {.v = &layouts[2]} },
	{ MODKEY|Mod1Mask,              XK_4,               setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,           togglefloating, {0} },
	{ MODKEY,                       XK_0,               view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,               tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,           focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,          focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,           tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,          tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_c,               show,           {0} },
	{ MODKEY,                       XK_c,               hide,           {0} },
	TAGKEYS(                        XK_1,                               0)
	TAGKEYS(                        XK_2,                               1)
	TAGKEYS(                        XK_3,                               2)
	TAGKEYS(                        XK_4,                               3)
	TAGKEYS(                        XK_5,                               4)
	TAGKEYS(                        XK_6,                               5)
	TAGKEYS(                        XK_7,                               6)
	TAGKEYS(                        XK_8,                               7)
	TAGKEYS(                        XK_9,                               8)
	{ MODKEY|ShiftMask,             XK_q,               quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
