#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
// static const char *fonts[] = {"Spleen 8x16:pixelsize=16"};
static const char *fonts[] = {"Adwaita Mono:size=10",
                              "CaskaydiaCove Nerd Font:size=10"};
// static const char dmenufont[] = "CaskaydiaCove Nerd Font:size=14";
#define THEME CATPPUCCIN
#include "themes.h"

// 󱙧 w/e tag
// 󰅄 emacs tag
//  games tag
// 󰖟 web tag
//  terminal tag?
// 
// 󰊓
// 󰛓
/* tagging */
// static const char *tags[] = {"󱙧", "", "󰗋", "", "", "󰖟"};
static const char *tags[] = {"etc",   "emacs", "mail", "voip",
                             "steam", "games", "web"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 6, 0, -1},
    {"steam", NULL, NULL, 1 << 4, 0, -1},
    {"Emacs", NULL, NULL, 1 << 1, 0, -1},
    {"vesktop", NULL, NULL, 1 << 3, 0, -1},
    {"Godot", NULL, NULL, 0, 1, -1},
    {"Thunderbird", NULL, NULL, 1 << 2, 1, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"", tile},  /* first entry is default */
    {"󰛓", NULL}, /* no layout function means floating behavior */
    {"", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
    {MODKEY, KEY, view, {.ui = 1 << TAG}},                                     \
        {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},             \
        {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                      \
        {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
    {                                                                          \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                   \
    }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = {
// "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
// "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *dmenucmd[] = {"j4-dmenu-desktop", NULL};
static const char *termcmd[] = {"st", NULL};
static const char *webcmd[] = {"firefox", NULL};
static const char *emacscmd[] = {"emacs", NULL};
static const char *lock[] = {"slock", NULL};
static const char *up_vol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@",
                               "+10%", NULL};
static const char *down_vol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@",
                                 "-10%", NULL};
static const char *mute_vol[] = {"pactl", "set-sink-mute", "@DEFAULT_SINK@",
                                 "toggle", NULL};
static const char *brighter[] = {"brightnessctl", "set", "10%+", NULL};
static const char *dimmer[] = {"brightnessctl", "set", "10%-", NULL};
static const char *quitfrcmd[] = {"killall", "xinit", NULL};
static const char *powerctl[] = {"powerprofilesctl-dmenu", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_w, spawn, {.v = webcmd}},
    {MODKEY | ShiftMask, XK_p, spawn, {.v = powerctl}},
    {MODKEY | ShiftMask, XK_q, spawn, {.v = quitfrcmd}},
    {MODKEY | ShiftMask, XK_x, spawn, {.v = lock}},
    {MODKEY, XK_e, spawn, {.v = emacscmd}},
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {0, XF86XK_AudioMute, spawn, {.v = mute_vol}},        // Media keys
    {0, XF86XK_AudioLowerVolume, spawn, {.v = down_vol}}, // Media keys
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = up_vol}},   // Media keys
    {0, XF86XK_MonBrightnessDown, spawn, {.v = dimmer}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brighter}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_r, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
