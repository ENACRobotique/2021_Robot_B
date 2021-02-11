EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L teensy:Teensy3.5 U?
U 1 1 6026B470
P 5700 4000
F 0 "U?" H 5700 6633 60  0000 C CNN
F 1 "Teensy3.5" H 5700 6527 60  0000 C CNN
F 2 "" H 5600 6250 60  0000 C CNN
F 3 "https://www.pjrc.com/teensy/card8a_rev2.pdf" H 5700 6421 60  0000 C CNN
F 4 "https://www.pjrc.com/teensy/pinout.html" H 5700 6323 50  0000 C CNN "Pinouts"
	1    5700 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1950 3900 1950
Wire Wire Line
	4550 2050 3900 2050
Text Label 3900 1950 0    50   ~ 0
UART_1_RX
Text Label 3900 2050 0    50   ~ 0
UART_1_TX
Wire Wire Line
	4550 2850 3900 2850
Wire Wire Line
	4550 2950 3900 2950
Text Label 3900 2850 0    50   ~ 0
UART_2_RX
Text Label 3900 2950 0    50   ~ 0
UART_2_TX
Wire Wire Line
	4550 3850 3900 3850
Wire Wire Line
	4550 3950 3900 3950
$EndSCHEMATC
