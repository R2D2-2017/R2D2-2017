"""@ 
Authors: Mike Hilhorst, David de Jong, Wilco Louwerse, Robbie Valkenburg, Nicky van Steensel van der Aa, Bram van Bergeijk, Earde Bearde
Wiki: https://github.com/R2D2-2017/R2D2-2017/wiki/HC-SR04-Ultrasone-sensor
Trello: https://trello.com/c/FxRxNblW/7-6-make-the-platform-stop-when-the-sonar-sensor-detects-something-within-its-working-area
This is a test code for the sonar sensor, using a function (GetSonarDistance) to measure the distance to an object.
"""
import RPi.GPIO as GPIO                    #Import GPIO library
import time                                #Import time library
GPIO.setwarnings(False) 

triggerPin = 23                            #the pin wich we use to trigger the sonar
echoPin = 24                               #the pin on which we listen to the sonar


        def setup(outPin, inPin):
        """
        This function instantiates all pins in the correct way
        """
        GPIO.setmode(GPIO.BCM)                  #Set GPIO pin numbering 
        GPIO.setup(outPin,GPIO.OUT)             #Set pin as GPIO out
        GPIO.setup(inPin,GPIO.IN)               #Set pin as GPIO in
        GPIO.output(outPin, False)              #Set TRIG as LOW 
        time.sleep(0.001)                       #Small delay
  


        def GetSonarDistance(trigger, echo):            #Associate the triggerpins 
	"""
	A function that returns the distance to the nearest object in cm, measured by the sonar sensor.
	trigger = the trigger pin, the program sends a signal through this to the sensor.
	echo = the echo pin,  the sonar sends a signal through this to the program.
	return = the distance in cm or a 404 when no object is detected in range.
	"""
	
	GPIO.output(trigger, True)                  #Set TRIG as HIGH
	time.sleep(0.001)                  	    #Delay of 0.00001 seconds
	GPIO.output(trigger, False)                 #Set TRIG as LOW
	
	
	while GPIO.input(echo)==0:               	#Check whether the ECHO is LOW
		pulse_start = time.time()               #Saves the last known time of LOW pulse
		
	
	while GPIO.input(echo)==1:               	#Check whether the ECHO is HIGH
		pulse_end = time.time()                 #Saves the last known time of HIGH pulse
		
	
	pulse_duration = pulse_end - pulse_start 	#Get pulse duration to a variable
	
	distance = pulse_duration * 17150        	#Multiply pulse duration by 17150 to get distance

	
	if distance > 2 and distance < 400:      	#Check whether the distance is within range
		return int(distance - 0.5)  		#Print distance with 0.5 cm calibration
	else:
   		return 404                  		#display out of range




	
	
