# RoboDogUMBC
 Heres a general description of the files:
 
	o Adafruit_PWMServoDriver.h		-   Contains useful functions to control the Arduino servo shield
	
	o colorTrackRoboDog.py			-   Python code that takes pixel information from a camera and outputs
						instructions serially to the Arduino (ie via USB)
									  
	o Servo_serial_control.py		-   Test file to control multiple servos using the servo shield
	
	o Continuous_servo.c			-   Test file to continually spin a motor
	
	o Dog-woof-single-sound2.h		-   Contains raw pitch/duration information of a single dog bark
	
	o playBark.c 				-   Plays the audio stored in Dog-woof-single-sound2.h 
						** Warning: Needs fixing, else this code kills Arduinos
									  
	o pitches.h				-   Defines PWM frequencies for the speaker corresponding to notes
	
	o testSpeaker.c				-   Plays a melody using the notes defined in pitches.h
    
Additional Notes:

o	All .ino files are essentially .c files used by the Arduino IDE
