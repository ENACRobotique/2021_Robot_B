EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
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
L Driver_LED:PCA9685PW U?
U 1 1 6026F584
P 3950 2850
F 0 "U?" H 3950 4031 50  0000 C CNN
F 1 "PCA9685PW" H 3950 3940 50  0000 C CNN
F 2 "Package_SO:TSSOP-28_4.4x9.7mm_P0.65mm" H 3975 1875 50  0001 L CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCA9685.pdf" H 3550 3550 50  0001 C CNN
	1    3950 2850
	1    0    0    -1  
$EndComp
$Comp
L Analog_ADC:ADC128D818 U?
U 1 1 60270620
P 3850 5600
F 0 "U?" H 3850 6581 50  0000 C CNN
F 1 "ADC128D818" H 3850 6490 50  0000 C CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 3850 5600 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/adc128d818.pdf" H 3850 5600 50  0001 C CNN
	1    3850 5600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3250 2150 1850 2150
Wire Wire Line
	3250 2250 1850 2250
Text Label 1850 2150 0    50   ~ 0
EXT_SCL
Text Label 1850 2250 0    50   ~ 0
EXT_SDA
Wire Wire Line
	3950 1850 3100 1850
Wire Wire Line
	3950 3950 3100 3950
Wire Wire Line
	4650 2150 5450 2150
Wire Wire Line
	4650 2250 5450 2250
Wire Wire Line
	4650 2350 5450 2350
Wire Wire Line
	4650 2450 5450 2450
Wire Wire Line
	4650 2550 5450 2550
Wire Wire Line
	4650 2650 5450 2650
Wire Wire Line
	4650 2750 5450 2750
Wire Wire Line
	4650 2850 5450 2850
Text Label 5450 2150 2    50   ~ 0
SERVO_1
Text Label 5450 2250 2    50   ~ 0
SERVO_2
Text Label 5450 2350 2    50   ~ 0
SERVO_3
Text Label 5450 2450 2    50   ~ 0
SERVO_4
Text Label 5450 2550 2    50   ~ 0
SERVO_5
Text Label 5450 2650 2    50   ~ 0
POMPE_1
Text Label 5450 2750 2    50   ~ 0
POMPE_2
Text Label 5450 2850 2    50   ~ 0
POMPE_3
Wire Wire Line
	4650 2950 5450 2950
Wire Wire Line
	4650 3050 5450 3050
Wire Wire Line
	4650 3150 5450 3150
Wire Wire Line
	4650 3250 5450 3250
Wire Wire Line
	4650 3350 5450 3350
Wire Wire Line
	4650 3450 5450 3450
Wire Wire Line
	4650 3550 5450 3550
Text Label 5450 2950 2    50   ~ 0
POMPE_4
Text Label 5450 3050 2    50   ~ 0
POMPE_5
Text Label 5450 3150 2    50   ~ 0
EV_1
Text Label 5450 3250 2    50   ~ 0
EV_2
Text Label 5450 3350 2    50   ~ 0
EV_3
Text Label 5450 3450 2    50   ~ 0
EV_4
Text Label 5450 3550 2    50   ~ 0
EV_5
Wire Wire Line
	3350 5000 1450 5000
Text Label 1450 5000 0    50   ~ 0
EXT_SDA
Text Label 1450 5100 0    50   ~ 0
EXT_SCL
Wire Wire Line
	3850 4800 3100 4800
Wire Wire Line
	3350 5100 1450 5100
Wire Wire Line
	3850 6400 3050 6400
Wire Wire Line
	4350 5000 5000 5000
Wire Wire Line
	4350 5100 5000 5100
Wire Wire Line
	4350 5200 5000 5200
Wire Wire Line
	4350 5300 5000 5300
Wire Wire Line
	4350 5400 5000 5400
Text Label 5000 5000 2    50   ~ 0
ADC_1
Text Label 5000 5100 2    50   ~ 0
ADC_2
Text Label 5000 5200 2    50   ~ 0
ADC_3
Text Label 5000 5300 2    50   ~ 0
ADC_4
Text Label 5000 5400 2    50   ~ 0
ADC_5
$Comp
L Sensor_Current:ACS722xLCTR-05AB U?
U 1 1 6034F076
P 9700 8200
F 0 "U?" H 9700 8781 50  0000 C CNN
F 1 "ACS722xLCTR-05AB" H 9700 8690 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9800 7850 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS722-Datasheet.ashx?la=en" H 9700 8200 50  0001 C CNN
	1    9700 8200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9700 7800 9100 7800
Wire Wire Line
	9700 8600 9300 8600
Wire Wire Line
	9300 8300 9300 8600
$Comp
L Device:C C?
U 1 1 6034F083
P 9100 7650
F 0 "C?" V 8848 7650 50  0000 C CNN
F 1 "0.1µF" V 8939 7650 50  0000 C CNN
F 2 "" H 9138 7500 50  0001 C CNN
F 3 "~" H 9100 7650 50  0001 C CNN
	1    9100 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 7800 8600 7800
$Comp
L Device:C C?
U 1 1 6034F08D
P 9100 8150
F 0 "C?" V 8848 8150 50  0000 C CNN
F 1 "10nF" V 8939 8150 50  0000 C CNN
F 2 "" H 9138 8000 50  0001 C CNN
F 3 "~" H 9100 8150 50  0001 C CNN
	1    9100 8150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 8300 10900 8300
Text Label 8500 8000 0    50   ~ 0
ADC_5
Text Label 11900 8300 2    50   ~ 0
12V_POMPE_5
$Comp
L power:+3.3V #PWR?
U 1 1 6037F4E7
P 3100 1850
F 0 "#PWR?" H 3100 1700 50  0001 C CNN
F 1 "+3.3V" V 3115 1978 50  0000 L CNN
F 2 "" H 3100 1850 50  0001 C CNN
F 3 "" H 3100 1850 50  0001 C CNN
	1    3100 1850
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6037F874
P 3100 4800
F 0 "#PWR?" H 3100 4650 50  0001 C CNN
F 1 "+3.3V" V 3115 4928 50  0000 L CNN
F 2 "" H 3100 4800 50  0001 C CNN
F 3 "" H 3100 4800 50  0001 C CNN
	1    3100 4800
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6037FDC4
P 8600 7800
F 0 "#PWR?" H 8600 7650 50  0001 C CNN
F 1 "+3.3V" V 8615 7928 50  0000 L CNN
F 2 "" H 8600 7800 50  0001 C CNN
F 3 "" H 8600 7800 50  0001 C CNN
	1    8600 7800
	0    -1   -1   0   
$EndComp
Connection ~ 9100 7800
$Comp
L power:GND #PWR?
U 1 1 60384E72
P 9100 7500
F 0 "#PWR?" H 9100 7250 50  0001 C CNN
F 1 "GND" H 9105 7327 50  0000 C CNN
F 2 "" H 9100 7500 50  0001 C CNN
F 3 "" H 9100 7500 50  0001 C CNN
	1    9100 7500
	-1   0    0    1   
$EndComp
Wire Wire Line
	8500 8000 9100 8000
Connection ~ 9100 8000
Wire Wire Line
	9100 8000 9300 8000
$Comp
L power:GND #PWR?
U 1 1 6038B994
P 9100 8300
F 0 "#PWR?" H 9100 8050 50  0001 C CNN
F 1 "GND" H 9105 8127 50  0000 C CNN
F 2 "" H 9100 8300 50  0001 C CNN
F 3 "" H 9100 8300 50  0001 C CNN
	1    9100 8300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6038F0FF
P 9300 8600
F 0 "#PWR?" H 9300 8350 50  0001 C CNN
F 1 "GND" H 9305 8427 50  0000 C CNN
F 2 "" H 9300 8600 50  0001 C CNN
F 3 "" H 9300 8600 50  0001 C CNN
	1    9300 8600
	1    0    0    -1  
$EndComp
Connection ~ 9300 8600
$Comp
L power:GND #PWR?
U 1 1 603927DF
P 3050 6400
F 0 "#PWR?" H 3050 6150 50  0001 C CNN
F 1 "GND" V 3055 6272 50  0000 R CNN
F 2 "" H 3050 6400 50  0001 C CNN
F 3 "" H 3050 6400 50  0001 C CNN
	1    3050 6400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60392B19
P 3100 3950
F 0 "#PWR?" H 3100 3700 50  0001 C CNN
F 1 "GND" V 3105 3822 50  0000 R CNN
F 2 "" H 3100 3950 50  0001 C CNN
F 3 "" H 3100 3950 50  0001 C CNN
	1    3100 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	11300 8300 11900 8300
Wire Wire Line
	11100 8600 11100 8750
Wire Wire Line
	11100 8750 10400 8750
Text Label 10400 8750 0    50   ~ 0
POMPE_5
$Comp
L Transistor_FET:IRLML0030 Q?
U 1 1 60315E62
P 11100 8400
F 0 "Q?" V 11442 8400 50  0000 C CNN
F 1 "IRLML0030" V 11351 8400 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11300 8325 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml0030pbf.pdf?fileId=5546d462533600a401535664773825df" H 11100 8400 50  0001 L CNN
	1    11100 8400
	0    1    -1   0   
$EndComp
$Comp
L Regulator_Switching:TSR_1-2450 U?
U 1 1 6031FE8A
P 3825 7750
F 0 "U?" H 3825 8117 50  0000 C CNN
F 1 "TSR_1-2450" H 3825 8026 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_TRACO_TSR-1_THT" H 3825 7600 50  0001 L CIN
F 3 "http://www.tracopower.com/products/tsr1.pdf" H 3825 7750 50  0001 C CNN
	1    3825 7750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3825 7950 3075 7950
$Comp
L power:GND #PWR?
U 1 1 6032193F
P 3075 7950
F 0 "#PWR?" H 3075 7700 50  0001 C CNN
F 1 "GND" V 3080 7822 50  0000 R CNN
F 2 "" H 3075 7950 50  0001 C CNN
F 3 "" H 3075 7950 50  0001 C CNN
	1    3075 7950
	0    1    1    0   
$EndComp
Wire Wire Line
	3425 7650 3000 7650
$Comp
L power:+12V #PWR?
U 1 1 60322C15
P 3000 7650
F 0 "#PWR?" H 3000 7500 50  0001 C CNN
F 1 "+12V" V 3015 7778 50  0000 L CNN
F 2 "" H 3000 7650 50  0001 C CNN
F 3 "" H 3000 7650 50  0001 C CNN
	1    3000 7650
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 60324891
P 10100 8000
F 0 "#PWR?" H 10100 7850 50  0001 C CNN
F 1 "+12V" V 10115 8128 50  0000 L CNN
F 2 "" H 10100 8000 50  0001 C CNN
F 3 "" H 10100 8000 50  0001 C CNN
	1    10100 8000
	0    1    1    0   
$EndComp
$Comp
L Sensor_Current:ACS722xLCTR-05AB U?
U 1 1 6032C3F8
P 9700 6700
F 0 "U?" H 9700 7281 50  0000 C CNN
F 1 "ACS722xLCTR-05AB" H 9700 7190 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9800 6350 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS722-Datasheet.ashx?la=en" H 9700 6700 50  0001 C CNN
	1    9700 6700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9700 6300 9100 6300
Wire Wire Line
	9700 7100 9300 7100
Wire Wire Line
	9300 6800 9300 7100
$Comp
L Device:C C?
U 1 1 6032C401
P 9100 6150
F 0 "C?" V 8848 6150 50  0000 C CNN
F 1 "0.1µF" V 8939 6150 50  0000 C CNN
F 2 "" H 9138 6000 50  0001 C CNN
F 3 "~" H 9100 6150 50  0001 C CNN
	1    9100 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 6300 8600 6300
$Comp
L Device:C C?
U 1 1 6032C408
P 9100 6650
F 0 "C?" V 8848 6650 50  0000 C CNN
F 1 "10nF" V 8939 6650 50  0000 C CNN
F 2 "" H 9138 6500 50  0001 C CNN
F 3 "~" H 9100 6650 50  0001 C CNN
	1    9100 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 6800 10900 6800
Text Label 8500 6500 0    50   ~ 0
ADC_4
Text Label 11900 6800 2    50   ~ 0
12V_POMPE_4
$Comp
L power:+3.3V #PWR?
U 1 1 6032C411
P 8600 6300
F 0 "#PWR?" H 8600 6150 50  0001 C CNN
F 1 "+3.3V" V 8615 6428 50  0000 L CNN
F 2 "" H 8600 6300 50  0001 C CNN
F 3 "" H 8600 6300 50  0001 C CNN
	1    8600 6300
	0    -1   -1   0   
$EndComp
Connection ~ 9100 6300
$Comp
L power:GND #PWR?
U 1 1 6032C418
P 9100 6000
F 0 "#PWR?" H 9100 5750 50  0001 C CNN
F 1 "GND" H 9105 5827 50  0000 C CNN
F 2 "" H 9100 6000 50  0001 C CNN
F 3 "" H 9100 6000 50  0001 C CNN
	1    9100 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	8500 6500 9100 6500
Connection ~ 9100 6500
Wire Wire Line
	9100 6500 9300 6500
$Comp
L power:GND #PWR?
U 1 1 6032C421
P 9100 6800
F 0 "#PWR?" H 9100 6550 50  0001 C CNN
F 1 "GND" H 9105 6627 50  0000 C CNN
F 2 "" H 9100 6800 50  0001 C CNN
F 3 "" H 9100 6800 50  0001 C CNN
	1    9100 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6032C427
P 9300 7100
F 0 "#PWR?" H 9300 6850 50  0001 C CNN
F 1 "GND" H 9305 6927 50  0000 C CNN
F 2 "" H 9300 7100 50  0001 C CNN
F 3 "" H 9300 7100 50  0001 C CNN
	1    9300 7100
	1    0    0    -1  
$EndComp
Connection ~ 9300 7100
Wire Wire Line
	11300 6800 11900 6800
Wire Wire Line
	11100 7100 11100 7250
Wire Wire Line
	11100 7250 10400 7250
Text Label 10400 7250 0    50   ~ 0
POMPE_4
$Comp
L Transistor_FET:IRLML0030 Q?
U 1 1 6032C432
P 11100 6900
F 0 "Q?" V 11442 6900 50  0000 C CNN
F 1 "IRLML0030" V 11351 6900 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11300 6825 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml0030pbf.pdf?fileId=5546d462533600a401535664773825df" H 11100 6900 50  0001 L CNN
	1    11100 6900
	0    1    -1   0   
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 6032C438
P 10100 6500
F 0 "#PWR?" H 10100 6350 50  0001 C CNN
F 1 "+12V" V 10115 6628 50  0000 L CNN
F 2 "" H 10100 6500 50  0001 C CNN
F 3 "" H 10100 6500 50  0001 C CNN
	1    10100 6500
	0    1    1    0   
$EndComp
$Comp
L Sensor_Current:ACS722xLCTR-05AB U?
U 1 1 6033AF15
P 9700 5200
F 0 "U?" H 9700 5781 50  0000 C CNN
F 1 "ACS722xLCTR-05AB" H 9700 5690 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9800 4850 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS722-Datasheet.ashx?la=en" H 9700 5200 50  0001 C CNN
	1    9700 5200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9700 4800 9100 4800
Wire Wire Line
	9700 5600 9300 5600
Wire Wire Line
	9300 5300 9300 5600
$Comp
L Device:C C?
U 1 1 6033AF1E
P 9100 4650
F 0 "C?" V 8848 4650 50  0000 C CNN
F 1 "0.1µF" V 8939 4650 50  0000 C CNN
F 2 "" H 9138 4500 50  0001 C CNN
F 3 "~" H 9100 4650 50  0001 C CNN
	1    9100 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 4800 8600 4800
$Comp
L Device:C C?
U 1 1 6033AF25
P 9100 5150
F 0 "C?" V 8848 5150 50  0000 C CNN
F 1 "10nF" V 8939 5150 50  0000 C CNN
F 2 "" H 9138 5000 50  0001 C CNN
F 3 "~" H 9100 5150 50  0001 C CNN
	1    9100 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 5300 10900 5300
Text Label 8500 5000 0    50   ~ 0
ADC_3
Text Label 11900 5300 2    50   ~ 0
12V_POMPE_3
$Comp
L power:+3.3V #PWR?
U 1 1 6033AF2E
P 8600 4800
F 0 "#PWR?" H 8600 4650 50  0001 C CNN
F 1 "+3.3V" V 8615 4928 50  0000 L CNN
F 2 "" H 8600 4800 50  0001 C CNN
F 3 "" H 8600 4800 50  0001 C CNN
	1    8600 4800
	0    -1   -1   0   
$EndComp
Connection ~ 9100 4800
$Comp
L power:GND #PWR?
U 1 1 6033AF35
P 9100 4500
F 0 "#PWR?" H 9100 4250 50  0001 C CNN
F 1 "GND" H 9105 4327 50  0000 C CNN
F 2 "" H 9100 4500 50  0001 C CNN
F 3 "" H 9100 4500 50  0001 C CNN
	1    9100 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	8500 5000 9100 5000
Connection ~ 9100 5000
Wire Wire Line
	9100 5000 9300 5000
$Comp
L power:GND #PWR?
U 1 1 6033AF3E
P 9100 5300
F 0 "#PWR?" H 9100 5050 50  0001 C CNN
F 1 "GND" H 9105 5127 50  0000 C CNN
F 2 "" H 9100 5300 50  0001 C CNN
F 3 "" H 9100 5300 50  0001 C CNN
	1    9100 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6033AF44
P 9300 5600
F 0 "#PWR?" H 9300 5350 50  0001 C CNN
F 1 "GND" H 9305 5427 50  0000 C CNN
F 2 "" H 9300 5600 50  0001 C CNN
F 3 "" H 9300 5600 50  0001 C CNN
	1    9300 5600
	1    0    0    -1  
$EndComp
Connection ~ 9300 5600
Wire Wire Line
	11300 5300 11900 5300
Wire Wire Line
	11100 5600 11100 5750
Wire Wire Line
	11100 5750 10400 5750
Text Label 10400 5750 0    50   ~ 0
POMPE_3
$Comp
L Transistor_FET:IRLML0030 Q?
U 1 1 6033AF4F
P 11100 5400
F 0 "Q?" V 11442 5400 50  0000 C CNN
F 1 "IRLML0030" V 11351 5400 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11300 5325 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml0030pbf.pdf?fileId=5546d462533600a401535664773825df" H 11100 5400 50  0001 L CNN
	1    11100 5400
	0    1    -1   0   
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 6033AF55
P 10100 5000
F 0 "#PWR?" H 10100 4850 50  0001 C CNN
F 1 "+12V" V 10115 5128 50  0000 L CNN
F 2 "" H 10100 5000 50  0001 C CNN
F 3 "" H 10100 5000 50  0001 C CNN
	1    10100 5000
	0    1    1    0   
$EndComp
$Comp
L Sensor_Current:ACS722xLCTR-05AB U?
U 1 1 6034EA93
P 9700 3725
F 0 "U?" H 9700 4306 50  0000 C CNN
F 1 "ACS722xLCTR-05AB" H 9700 4215 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9800 3375 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS722-Datasheet.ashx?la=en" H 9700 3725 50  0001 C CNN
	1    9700 3725
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9700 3325 9100 3325
Wire Wire Line
	9700 4125 9300 4125
Wire Wire Line
	9300 3825 9300 4125
$Comp
L Device:C C?
U 1 1 6034EA9C
P 9100 3175
F 0 "C?" V 8848 3175 50  0000 C CNN
F 1 "0.1µF" V 8939 3175 50  0000 C CNN
F 2 "" H 9138 3025 50  0001 C CNN
F 3 "~" H 9100 3175 50  0001 C CNN
	1    9100 3175
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3325 8600 3325
$Comp
L Device:C C?
U 1 1 6034EAA3
P 9100 3675
F 0 "C?" V 8848 3675 50  0000 C CNN
F 1 "10nF" V 8939 3675 50  0000 C CNN
F 2 "" H 9138 3525 50  0001 C CNN
F 3 "~" H 9100 3675 50  0001 C CNN
	1    9100 3675
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 3825 10900 3825
Text Label 8500 3525 0    50   ~ 0
ADC_2
Text Label 11900 3825 2    50   ~ 0
12V_POMPE_2
$Comp
L power:+3.3V #PWR?
U 1 1 6034EAAC
P 8600 3325
F 0 "#PWR?" H 8600 3175 50  0001 C CNN
F 1 "+3.3V" V 8615 3453 50  0000 L CNN
F 2 "" H 8600 3325 50  0001 C CNN
F 3 "" H 8600 3325 50  0001 C CNN
	1    8600 3325
	0    -1   -1   0   
$EndComp
Connection ~ 9100 3325
$Comp
L power:GND #PWR?
U 1 1 6034EAB3
P 9100 3025
F 0 "#PWR?" H 9100 2775 50  0001 C CNN
F 1 "GND" H 9105 2852 50  0000 C CNN
F 2 "" H 9100 3025 50  0001 C CNN
F 3 "" H 9100 3025 50  0001 C CNN
	1    9100 3025
	-1   0    0    1   
$EndComp
Wire Wire Line
	8500 3525 9100 3525
Connection ~ 9100 3525
Wire Wire Line
	9100 3525 9300 3525
$Comp
L power:GND #PWR?
U 1 1 6034EABC
P 9100 3825
F 0 "#PWR?" H 9100 3575 50  0001 C CNN
F 1 "GND" H 9105 3652 50  0000 C CNN
F 2 "" H 9100 3825 50  0001 C CNN
F 3 "" H 9100 3825 50  0001 C CNN
	1    9100 3825
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6034EAC2
P 9300 4125
F 0 "#PWR?" H 9300 3875 50  0001 C CNN
F 1 "GND" H 9305 3952 50  0000 C CNN
F 2 "" H 9300 4125 50  0001 C CNN
F 3 "" H 9300 4125 50  0001 C CNN
	1    9300 4125
	1    0    0    -1  
$EndComp
Connection ~ 9300 4125
Wire Wire Line
	11300 3825 11900 3825
Wire Wire Line
	11100 4125 11100 4275
Wire Wire Line
	11100 4275 10400 4275
Text Label 10400 4275 0    50   ~ 0
POMPE_2
$Comp
L Transistor_FET:IRLML0030 Q?
U 1 1 6034EACD
P 11100 3925
F 0 "Q?" V 11442 3925 50  0000 C CNN
F 1 "IRLML0030" V 11351 3925 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11300 3850 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml0030pbf.pdf?fileId=5546d462533600a401535664773825df" H 11100 3925 50  0001 L CNN
	1    11100 3925
	0    1    -1   0   
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 6034EAD3
P 10100 3525
F 0 "#PWR?" H 10100 3375 50  0001 C CNN
F 1 "+12V" V 10115 3653 50  0000 L CNN
F 2 "" H 10100 3525 50  0001 C CNN
F 3 "" H 10100 3525 50  0001 C CNN
	1    10100 3525
	0    1    1    0   
$EndComp
$Comp
L Sensor_Current:ACS722xLCTR-05AB U?
U 1 1 60355BEB
P 9700 2225
F 0 "U?" H 9700 2806 50  0000 C CNN
F 1 "ACS722xLCTR-05AB" H 9700 2715 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9800 1875 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS722-Datasheet.ashx?la=en" H 9700 2225 50  0001 C CNN
	1    9700 2225
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9700 1825 9100 1825
Wire Wire Line
	9700 2625 9300 2625
Wire Wire Line
	9300 2325 9300 2625
$Comp
L Device:C C?
U 1 1 60355BF4
P 9100 1675
F 0 "C?" V 8848 1675 50  0000 C CNN
F 1 "0.1µF" V 8939 1675 50  0000 C CNN
F 2 "" H 9138 1525 50  0001 C CNN
F 3 "~" H 9100 1675 50  0001 C CNN
	1    9100 1675
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1825 8600 1825
$Comp
L Device:C C?
U 1 1 60355BFB
P 9100 2175
F 0 "C?" V 8848 2175 50  0000 C CNN
F 1 "10nF" V 8939 2175 50  0000 C CNN
F 2 "" H 9138 2025 50  0001 C CNN
F 3 "~" H 9100 2175 50  0001 C CNN
	1    9100 2175
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 2325 10900 2325
Text Label 8500 2025 0    50   ~ 0
ADC_1
Text Label 11900 2325 2    50   ~ 0
12V_POMPE_1
$Comp
L power:+3.3V #PWR?
U 1 1 60355C04
P 8600 1825
F 0 "#PWR?" H 8600 1675 50  0001 C CNN
F 1 "+3.3V" V 8615 1953 50  0000 L CNN
F 2 "" H 8600 1825 50  0001 C CNN
F 3 "" H 8600 1825 50  0001 C CNN
	1    8600 1825
	0    -1   -1   0   
$EndComp
Connection ~ 9100 1825
$Comp
L power:GND #PWR?
U 1 1 60355C0B
P 9100 1525
F 0 "#PWR?" H 9100 1275 50  0001 C CNN
F 1 "GND" H 9105 1352 50  0000 C CNN
F 2 "" H 9100 1525 50  0001 C CNN
F 3 "" H 9100 1525 50  0001 C CNN
	1    9100 1525
	-1   0    0    1   
$EndComp
Wire Wire Line
	8500 2025 9100 2025
Connection ~ 9100 2025
Wire Wire Line
	9100 2025 9300 2025
$Comp
L power:GND #PWR?
U 1 1 60355C14
P 9100 2325
F 0 "#PWR?" H 9100 2075 50  0001 C CNN
F 1 "GND" H 9105 2152 50  0000 C CNN
F 2 "" H 9100 2325 50  0001 C CNN
F 3 "" H 9100 2325 50  0001 C CNN
	1    9100 2325
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60355C1A
P 9300 2625
F 0 "#PWR?" H 9300 2375 50  0001 C CNN
F 1 "GND" H 9305 2452 50  0000 C CNN
F 2 "" H 9300 2625 50  0001 C CNN
F 3 "" H 9300 2625 50  0001 C CNN
	1    9300 2625
	1    0    0    -1  
$EndComp
Connection ~ 9300 2625
Wire Wire Line
	11300 2325 11900 2325
Wire Wire Line
	11100 2625 11100 2775
Wire Wire Line
	11100 2775 10400 2775
Text Label 10400 2775 0    50   ~ 0
POMPE_1
$Comp
L Transistor_FET:IRLML0030 Q?
U 1 1 60355C25
P 11100 2425
F 0 "Q?" V 11442 2425 50  0000 C CNN
F 1 "IRLML0030" V 11351 2425 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11300 2350 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml0030pbf.pdf?fileId=5546d462533600a401535664773825df" H 11100 2425 50  0001 L CNN
	1    11100 2425
	0    1    -1   0   
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 60355C2B
P 10100 2025
F 0 "#PWR?" H 10100 1875 50  0001 C CNN
F 1 "+12V" V 10115 2153 50  0000 L CNN
F 2 "" H 10100 2025 50  0001 C CNN
F 3 "" H 10100 2025 50  0001 C CNN
	1    10100 2025
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60360E0E
P 4225 7650
F 0 "#PWR?" H 4225 7500 50  0001 C CNN
F 1 "+5V" V 4240 7778 50  0000 L CNN
F 2 "" H 4225 7650 50  0001 C CNN
F 3 "" H 4225 7650 50  0001 C CNN
	1    4225 7650
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female J?
U 1 1 6031A117
P 14275 1950
F 0 "J?" H 14303 1976 50  0000 L CNN
F 1 "Conn_01x03_Female" H 14303 1885 50  0000 L CNN
F 2 "" H 14275 1950 50  0001 C CNN
F 3 "~" H 14275 1950 50  0001 C CNN
	1    14275 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J?
U 1 1 6031D53E
P 14275 2475
F 0 "J?" H 14303 2501 50  0000 L CNN
F 1 "Conn_01x03_Female" H 14303 2410 50  0000 L CNN
F 2 "" H 14275 2475 50  0001 C CNN
F 3 "~" H 14275 2475 50  0001 C CNN
	1    14275 2475
	1    0    0    -1  
$EndComp
$EndSCHEMATC
