##
## Makefile for GUIslice library - LINUX
## - Calvin Hass
## - https://www.impulseadventure.com/elec/guislice-gui.html
## - https://github.com/ImpulseAdventure/GUIslice
##
## NOTE: This Makefile handles both SDL1.2 and SDL2 compilation.
##       A simpler Makefile can be used if this flexibility is
##       not required.

# ---------------------------------------------------------------------------
# Define compiler flags for GUIslice
# - In some cases, the makefile compilation options must match
#   settings in the GUIslice_config_linux.h configuration file.
#
# GRAPHICS DRIVER
# - make parameter: GSLC_DRV=(SDL1,SDL2)
# - On the makefile command-line, pass the GSLC_DRV parameter to select
#   the graphics driver matching the #define DRV_DISP_* setting in
#   GUIslice_config_linux.h, eg:
#     GUIslice_config_linux.h:  #define DRV_DISP_SDL1
#     Makefile:                 make <target> GSLC_DRV=SDL1
#
#
# TOUCH DRIVER
# - make parameter: GSLC_TOUCH=(TSLIB,SDL,NONE)
# - On the makefile command-line, pass the GSLC_TOUCH parameter to
#   indicate whether or not DRV_TOUCH_TSLIB is #defined in the
#   GUIslice_config_linux.h, eg:
#     GUIslice_config_linux.h:  #define DRV_TOUCH_TSLIB
#     Makefile:                 make <target> GSLC_TOUCH=TSLIB
#
#     GUIslice_config_linux.h:  #define DRV_TOUCH_SDL (or DRV_TOUCH_NONE)
#     Makefile:                 make <target> GSLC_TOUCH=NONE
# - Note that the makefile only checks to see if DRV_TOUCH=TSLIB and
#   will ignore any other values.
#
# NOTES:
# - Note that multiple parameters may be passed, for example:
#     make ex04_lnx_ctrls
#     make ex06_lnx_callback GSLC_TOUCH=TSLIB GSLC_DRV=SDL2
#     make all GSLC_TOUCH=TSLIB
#

WARNINGS = 

ifneq ($(DEBUG), )
	BUILD_TYPE := DEBUG
	OPT := -O0 -ggdb
else
	BUILD_TYPE := RELEASE
	OPT := -Os
	WARNINGS += -Werror
endif

# Warnings for ALL C code (including libraries)
WARNINGS  += -Wno-unused -Wno-unused-parameter
WARNINGS += -Wformat -Wformat-security
#WARNINGS += -Wmisleading-indentation  -Wno-implicit-fallthrough
#WARNINGS += -Wall
#WARNINGS += -Wextra
WARNINGS += -Wshadow
#WARNINGS += -Wconversion

CC = gcc
INCLUDE = -I/usr/local/include
CFLAGS += $(OPT) $(WARNINGS) $(INCLUDE) -pipe -g -std=gnu99
LDFLAGS = -L/usr/local/lib

GSLC_BASEDIR = GUIslice

GSLC_CORE = $(GSLC_BASEDIR)/src/GUIslice.c $(GSLC_BASEDIR)/src/GUIslice_hmi.c $(GSLC_BASEDIR)/src/GUIslice_config.h $(GSLC_BASEDIR)/src/elem/*.c

# Define default compiler flags which may be overridden by command line

# Define graphics driver (overridden by command line GSLC_DRV)
# GSLC_DRV := SDL1
GSLC_DRV := SDL2

# Define any extra linker settings (overridden by command line GSLC_TOUCH_TSLIB)
GSLC_LDLIB_EXTRA := -lm
#GSLC_LDLIB_EXTRA := -lm -lts

# ifndef GSLC_TOUCH
#   GSLC_LDLIB_EXTRA := -lm -lts
#   $(info GUIslice touch mode: tslib enabled by default - GUIslice config should use DRV_TOUCH_TSLIB mode)
# else
#   ifeq (TSLIB,${GSLC_TOUCH})
#     $(info GUIslice touch mode: tslib enabled - GUIslice config should use DRV_TOUCH_TSLIB mode)
#     GSLC_LDLIB_EXTRA := -lm -lts
#   else
#     $(info GUIslice touch mode: tslib not enabled - GUIslice config should use DRV_TOUCH_SDL mode)
#     GSLC_LDLIB_EXTRA := -lm
#   endif
# endif

$(info GUIslice driver mode: SDL2)
GSLC_SRCS = $(GSLC_BASEDIR)/src/GUIslice_drv_sdl.c
# - Add extra linker libraries if needed
LDLIBS = -lSDL2 -lSDL2_ttf ${GSLC_LDLIB_EXTRA}

# === Adafruit-GFX ===
# No makefile for Arduino as most users will use the IDE for compilation

# ---------------------------------------------------------------------------

# Examples that operate in all driver modes
SRC = Arduino_TX_Display_Linux.c serial.c

build: 
	@echo "**** ${BUILD_TYPE} build *****"
	@$(CC) $(CFLAGS) $(SRC) $(GSLC_CORE) $(GSLC_SRCS) $(LDFLAGS) $(LDLIBS) -I . -I $(GSLC_BASEDIR)/src -o Arduino_TX_Display_Linux

clean:
	@echo "Cleaning directory..."
	$(RM) Arduino_TX_Display_Linux


