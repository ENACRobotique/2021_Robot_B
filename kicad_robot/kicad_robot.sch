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
P 9250 4150
F 0 "U?" H 9250 6783 60  0000 C CNN
F 1 "Teensy3.5" H 9250 6677 60  0000 C CNN
F 2 "" H 9150 6400 60  0000 C CNN
F 3 "https://www.pjrc.com/teensy/card8a_rev2.pdf" H 9250 6571 60  0000 C CNN
F 4 "https://www.pjrc.com/teensy/pinout.html" H 9250 6473 50  0000 C CNN "Pinouts"
	1    9250 4150
	1    0    0    -1  
$EndComp
Text GLabel 7450 2100 0    50   Input ~ 0
LIDAR_RX
Text GLabel 7450 2200 0    50   Input ~ 0
LIDAR_TX
Text GLabel 7450 2300 0    50   Input ~ 0
LIDAR_PWM
Text GLabel 7650 2800 0    50   Input ~ 0
GPIO_DISPLAY_1
Text GLabel 7650 2900 0    50   Input ~ 0
GPIO_DISPLAY_2
Text GLabel 7650 3000 0    50   Input ~ 0
X-BEE_RX
Text GLabel 7650 3100 0    50   Input ~ 0
X-BEE_TX
Text GLabel 7650 3500 0    50   Input ~ 0
TIRETTE_GPIO
$Comp
L power:GND #PWR?
U 1 1 60316113
P 7450 2000
F 0 "#PWR?" H 7450 1750 50  0001 C CNN
F 1 "GND" V 7455 1872 50  0000 R CNN
F 2 "" H 7450 2000 50  0001 C CNN
F 3 "" H 7450 2000 50  0001 C CNN
	1    7450 2000
	0    1    1    0   
$EndComp
Text GLabel 10750 5500 2    50   Input ~ 0
ALIM_5V
Wire Wire Line
	10750 5500 10400 5500
Text GLabel 7650 3600 0    50   Input ~ 0
COULEUR_GPIO
Text GLabel 7450 4000 0    50   Input ~ 0
FTM_2_phA
Text GLabel 7450 4100 0    50   Input ~ 0
FTM_2_phB
Text GLabel 7700 4900 0    50   Input ~ 0
Moteur_1_GPIO
Text GLabel 7700 5000 0    50   Input ~ 0
MOTEUR_2_GPIO
Text GLabel 7700 5100 0    50   Input ~ 0
Moteur_2_PWM
Text GLabel 7700 5200 0    50   Input ~ 0
MOTEUR_1_PWM
Text GLabel 7700 5300 0    50   Input ~ 0
PAVILLON_PWM
Text GLabel 7700 5400 0    50   Input ~ 0
BAR_MANCH_PWM
Text GLabel 7750 6200 0    50   Input ~ 0
FTM_1_phA
Text GLabel 7750 6300 0    50   Input ~ 0
FTM_1_phB
Wire Wire Line
	7750 6300 8100 6300
Text GLabel 10800 6300 2    50   Input ~ 0
I2C_SDAO
Text GLabel 10800 6200 2    50   Input ~ 0
I2C_SCLO
Wire Wire Line
	10400 6300 10800 6300
Wire Wire Line
	10800 6200 10400 6200
$Comp
L power:GND #PWR?
U 1 1 6033D90A
P 10750 5600
F 0 "#PWR?" H 10750 5350 50  0001 C CNN
F 1 "GND" V 10755 5472 50  0000 R CNN
F 2 "" H 10750 5600 50  0001 C CNN
F 3 "" H 10750 5600 50  0001 C CNN
	1    10750 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10750 5600 10400 5600
NoConn ~ 10400 4300
NoConn ~ 10400 4200
NoConn ~ 10400 4100
NoConn ~ 10400 4000
Wire Wire Line
	7450 2100 8100 2100
Wire Wire Line
	7450 2200 8100 2200
Wire Wire Line
	7450 4000 8100 4000
Wire Wire Line
	7450 4100 8100 4100
Wire Wire Line
	7450 2300 8100 2300
Wire Wire Line
	7650 2900 8100 2900
Wire Wire Line
	7650 2800 8100 2800
Wire Wire Line
	7650 3100 8100 3100
Wire Wire Line
	7650 3000 8100 3000
Wire Wire Line
	7650 3500 8100 3500
Wire Wire Line
	7450 2000 8100 2000
Wire Wire Line
	7650 3600 8100 3600
Wire Wire Line
	7700 5400 8100 5400
Wire Wire Line
	7700 5300 8100 5300
Wire Wire Line
	7700 5200 8100 5200
Wire Wire Line
	7700 5100 8100 5100
Wire Wire Line
	7700 5000 8100 5000
Wire Wire Line
	7700 4900 8100 4900
Wire Wire Line
	7750 6200 8100 6200
NoConn ~ 10400 3900
NoConn ~ 10400 3800
NoConn ~ 10400 3700
NoConn ~ 10400 3600
NoConn ~ 10400 3500
NoConn ~ 10400 3400
NoConn ~ 10400 3300
NoConn ~ 10400 3200
NoConn ~ 10400 3100
NoConn ~ 10400 3000
NoConn ~ 10400 2900
NoConn ~ 10400 2800
NoConn ~ 10400 2700
NoConn ~ 10400 2600
NoConn ~ 10400 2500
NoConn ~ 10400 2400
NoConn ~ 10400 2300
NoConn ~ 10400 2000
NoConn ~ 10400 2100
NoConn ~ 10400 2200
NoConn ~ 8100 2400
NoConn ~ 8100 2500
NoConn ~ 8100 2600
NoConn ~ 8100 2700
NoConn ~ 8100 3200
NoConn ~ 8100 3300
NoConn ~ 8100 3400
NoConn ~ 8100 3700
NoConn ~ 8100 3800
NoConn ~ 8100 3900
NoConn ~ 8100 4200
NoConn ~ 8100 4300
NoConn ~ 8100 4400
NoConn ~ 8100 4500
NoConn ~ 8100 4600
NoConn ~ 8100 4700
NoConn ~ 8100 4800
NoConn ~ 8100 5500
NoConn ~ 8100 5600
NoConn ~ 8100 5700
NoConn ~ 8100 5900
NoConn ~ 8100 6000
NoConn ~ 8100 6100
NoConn ~ 10400 6100
NoConn ~ 10400 6000
NoConn ~ 10400 5900
NoConn ~ 10400 5800
NoConn ~ 10400 5700
NoConn ~ 10400 5400
NoConn ~ 10400 5300
NoConn ~ 10400 5200
NoConn ~ 10400 5100
NoConn ~ 10400 4700
NoConn ~ 10400 4600
NoConn ~ 10400 4500
NoConn ~ 10400 4400
$Comp
L power:GND #PWR?
U 1 1 6036B9DC
P 7700 5800
F 0 "#PWR?" H 7700 5550 50  0001 C CNN
F 1 "GND" V 7705 5672 50  0000 R CNN
F 2 "" H 7700 5800 50  0001 C CNN
F 3 "" H 7700 5800 50  0001 C CNN
	1    7700 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 5800 8100 5800
$Comp
L Regulator_Switching:R-78E5.0-1.0 U12->5
U 1 1 6037B063
P 7750 1000
F 0 "U12->5" H 7750 1242 50  0000 C CNN
F 1 "R-78E5.0-1.0" H 7750 1151 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_RECOM_R-78E-0.5_THT" H 7800 750 50  0001 L CIN
F 3 "https://www.recom-power.com/pdf/Innoline/R-78Exx-1.0.pdf" H 7750 1000 50  0001 C CNN
	1    7750 1000
	1    0    0    -1  
$EndComp
Text GLabel 8300 1000 2    50   Input ~ 0
ALIM_5V
Wire Wire Line
	8300 1000 8050 1000
$Comp
L power:GND #PWR?
U 1 1 6037D422
P 7750 1400
F 0 "#PWR?" H 7750 1150 50  0001 C CNN
F 1 "GND" H 7755 1227 50  0000 C CNN
F 2 "" H 7750 1400 50  0001 C CNN
F 3 "" H 7750 1400 50  0001 C CNN
	1    7750 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 1400 7750 1300
Text GLabel 7150 1000 0    50   Input ~ 0
ALIM_12V
Wire Wire Line
	7150 1000 7450 1000
$EndSCHEMATC
