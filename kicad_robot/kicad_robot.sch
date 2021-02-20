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
Wire Wire Line
	4550 3850 3900 3850
Wire Wire Line
	4550 3950 3900 3950
Text GLabel 3900 1950 0    50   Input ~ 0
LIDAR_RX
Text GLabel 3900 2050 0    50   Input ~ 0
LIDAR_TX
Text GLabel 3900 2150 0    50   Input ~ 0
LIDAR_PWM
Wire Wire Line
	3900 2150 4550 2150
Text GLabel 4100 2650 0    50   Input ~ 0
GPIO_DISPLAY_1
Text GLabel 4100 2750 0    50   Input ~ 0
GPIO_DISPLAY_2
Wire Wire Line
	4100 2750 4550 2750
Wire Wire Line
	4550 2650 4100 2650
Text GLabel 4100 2850 0    50   Input ~ 0
X-BEE_RX
Text GLabel 4100 2950 0    50   Input ~ 0
X-BEE_TX
Wire Wire Line
	4100 2950 4550 2950
Wire Wire Line
	4100 2850 4550 2850
Text GLabel 4100 3350 0    50   Input ~ 0
TIRETTE_GPIO
Wire Wire Line
	4100 3350 4550 3350
$EndSCHEMATC
