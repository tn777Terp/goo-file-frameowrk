#pragma once
// NOTES:
// Everything below orange is only available on  systems
// that supports 256 colors

#define CLR_SCREEN "\033[H\033[J"

/* ANSI color codes */
#define NOC "\033[0m"

/* Foreground colors */
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define ORANGE "\033[0;33m"     
#define PINK "\033[38;5;206m"

/* Bold Foreground colors */
#define B_BLACK "\033[1;30m"
#define B_RED "\033[1;31m"
#define B_GREEN "\033[1;32m"
#define B_YELLOW "\033[1;33m"
#define B_BLUE "\033[1;34m"
#define B_MAGENTA "\033[1;35m"
#define B_CYAN "\033[1;36m"
#define B_WHITE "\033[1;37m"
#define B_ORANGE "\033[1;33m"
#define B_PINK "\033[1;38;5;206m"

/* Intense Foreground colors */
#define I_BLACK "\033[0;90m"
#define I_RED "\033[0;91m"
#define I_GREEN "\033[0;92m"
#define I_YELLOW "\033[0;93m"
#define I_BLUE "\033[0;94m"
#define I_MAGENTA "\033[0;95m"
#define I_CYAN "\033[0;96m"
#define I_WHITE "\033[0;97m"
#define I_ORANGE "\033[0;38;5;208m"
#define I_PINK "\033[0;38;5;213m"

/* Bold Intense Foreground colors */
#define BI_BLACK "\033[1;90m"
#define BI_RED "\033[1;91m"
#define BI_GREEN "\033[1;92m"
#define BI_YELLOW "\033[1;93m"
#define BI_BLUE "\033[1;94m"
#define BI_MAGENTA "\033[1;95m"
#define BI_CYAN "\033[1;96m"
#define BI_WHITE "\033[1;97m"
#define BI_ORANGE "\033[1;38;5;208m"
#define BI_PINK "\033[1;38;5;213m"