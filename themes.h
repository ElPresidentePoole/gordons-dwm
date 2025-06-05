#ifndef THEMES_H_
#define THEMES_H_

#if THEME == CATPPUCCIN
#include "catppuccin.h"
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_text, col_base, col_mantle},
    [SchemeSel] = {col_mauve, col_crust, col_mauve},
};
#endif

#endif // THEMES_H_
