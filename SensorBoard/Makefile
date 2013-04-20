# MPLAB IDE generated this makefile for use with GNU make.
# Project: HackSensorBoard.mcp
# Date: Sat Apr 20 14:15:24 2013

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

HackSensorBoard.cof : main.o serial.o ADC.o
	$(LD) /p18F26K22 /l"C:\Program Files\Microchip\mplabc18\v3.45\lib" "main.o" "serial.o" "ADC.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"HackSensorBoard.cof" /M"HackSensorBoard.map" /W

main.o : main.c C:/Program\ Files/Microchip/mplabc18/v3.45/h/stdio.h C:/Program\ Files/Microchip/mplabc18/v3.45/h/string.h main.c C:/Program\ Files/Microchip/mplabc18/v3.45/h/stdarg.h C:/Program\ Files/Microchip/mplabc18/v3.45/h/stddef.h C:/Program\ Files/Microchip/mplabc18/v3.45/h/p18f26k22.h system.h serial.h ADC.h
	$(CC) -p=18F26K22 "main.c" -fo="main.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

serial.o : serial.c C:/Program\ Files/Microchip/mplabc18/v3.45/h/string.h serial.c C:/Program\ Files/Microchip/mplabc18/v3.45/h/p18f26k22.h C:/Program\ Files/Microchip/mplabc18/v3.45/h/stddef.h serial.h
	$(CC) -p=18F26K22 "serial.c" -fo="serial.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

ADC.o : ADC.c C:/Program\ Files/Microchip/mplabc18/v3.45/h/p18f26k22.h ADC.h
	$(CC) -p=18F26K22 "ADC.c" -fo="ADC.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "serial.o" "ADC.o" "HackSensorBoard.cof" "HackSensorBoard.hex"

