# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= TTCALC
COMPRESSED  ?= NO
ICON        ?= iconc.png
DESCRIPTION ?= "Calculator for Tower Takeover by Vex Robotics"

# ----------------------------

include $(CEDEV)/include/.makefile
