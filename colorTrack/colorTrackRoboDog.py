from __future__ import print_function
import cv2
import numpy as np
import gc    # garbage collection to free memory

import serial
from time import sleep
ser = serial.Serial('COM3',9600)
sleep(1)


ser.write('a;'.encode())

cap = cv2.VideoCapture(0)

while(1):

    _, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    lower_color = np.array([160,70,60])            # RED - this is in HSV format
    upper_color = np.array([360,250,250])
    #lower_color = np.array([60,50,50])              # GREEN - HSV format
    #upper_color = np.array([90,255,255])
    #if skin - 3 < 0:
    #    lower_color = np.array([0, 50,50])
    #else:
    #    lower_color = np.array([skin-2,50,50])
    #upper_color = np.array([skin+2,230,255])

    # Threshold the HSV image to get only white colors
    mask = cv2.inRange(hsv, lower_color, upper_color)
    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame,frame, mask= mask)

    cv2.imshow('frame',frame)
    #cv2.imshow('mask',mask)
    cv2.imshow('res',res)
    maskList = mask.tolist()
    intensity = mask.item(0, 0)
    #print (maskList)

    rowavg = 0;
    colavg = 0;
    numseen = 0;
    zoomed = [[0 for x in range(100)] for y in range(100)]
    for i in range(0, len(maskList), 5):
        for j in range(0, len(maskList[i]), 5):
            if mask.item(i, j) > 0:
                rowavg = rowavg + i;
                colavg = colavg + j;
                numseen = numseen + 1;
    if numseen == 0:
        rowavg = int(round(len(maskList[0])/2))
        colavg = int(round(len(maskList)/2))
    else:
        rowavg = rowavg / numseen
        rowavgpoint = int(round(rowavg))
        colavg = colavg / numseen
        colavgpoint = int(round(colavg))
    
    directionHorizontal = len(maskList)/2 - colavg
    moveHorizontalDir = 0
    moveVerticalDir = 0


    if abs(colavg - len(maskList[0])/2) > 65:
        if abs(colavg - len(maskList[0])/2) > 210:
            moveHorizontalDir = np.sign(len(maskList[0])/2 - colavg) * 10
        else:
            moveHorizontalDir = np.sign(len(maskList[0])/2 - colavg) * 2
        #moveHorizontalDir = np.sign(len(maskList[0])/2 - colavg)
        #moveHorizontalDir = (len(maskList[0])/2 - colavg) * (45/230)
        #moveHorizontalDir = (len(maskList[0])/2 - colavg) * (45/400)
    if abs(rowavg - len(maskList)/2) > 65:
        if abs(rowavg - len(maskList)/2) > 140:
            moveVerticalDir = np.sign(len(maskList)/2 - rowavg) * 6
        else:
            moveVerticalDir = np.sign(len(maskList)/2 - rowavg) * 2
        #moveVerticalDir = np.sign(len(maskList)/2 - rowavg)
        #moveVerticalDir = (len(maskList)/2 - rowavg) * (45/160)
        #moveVerticalDir = (len(maskList)/2 - rowavg) * (45/400)
    
    
    #moveHorizontalDir = moveHorizontalDir * 15
    #moveVerticalDir = moveVerticalDir * 15
    ser.write((str(moveHorizontalDir) + ' ' + str(moveVerticalDir) + ';').encode())
    print('Center Coordinates:','%.0f' % (len(maskList[0])/2 - colavg),',', '%.0f' % (len(maskList)/2 - rowavg))#####INSERT CENTER COORDINATES HERE

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break
        
    gc.collect()
    sleep(4./120)

cv2.destroyAllWindows()