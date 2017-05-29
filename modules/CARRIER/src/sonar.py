                        import RPi.GPIO as GPIO                    #Import GPIO library
import time                                #Import time library
GPIO.setmode(GPIO.BCM)                     #Set GPIO pin numbering 
GPIO.setup(23,GPIO.OUT)                  	#Set pin as GPIO out
GPIO.setup(24,GPIO.IN)                   	#Set pin as GPIO in



def Sonar(trigger, echo):                            	#Associate pin 23 to trigger and 24 to ECHO
	GPIO.output(trigger, False)                 	#Set TRIG as LOW
	time.sleep(0.001)                            	#Delay of x seconds
  
	GPIO.output(trigger, True)                  	#Set TRIG as HIGH
	time.sleep(0.001)                  	   	#Delay of 0.00001 seconds
	GPIO.output(trigger, False)                 	#Set TRIG as LOW
	
	
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








while True:
	
	
	distance = Sonar(23, 24)
	if(distance<3):
		print("FORCE STOP", distance)
	elif(distance<25):
		print("STOP: ", distance)

	time.sleep(0.01)