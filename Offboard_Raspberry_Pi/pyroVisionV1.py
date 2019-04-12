##############################
## Author: Brandon Rice     ##
##                          ##
## Arizona State University ##
##                          ##
## Created on 3-24-2019 for ##
## VEX U Team PYRO Robotics ##
##                          ##
##    and the 2018-2019     ##
## VEX ROBOTICS COMPETITION:##
##                          ##
##      TURNING POINT       ##
##                          ##
## github.com/PYRORobotics  ##
##                          ##
##############################

######################################################
## Further notice:                                  ##
######################################################
## Copyright (C) Brandon Rice - All Rights Reserved ##
##                                                  ##
## Unauthorized copying of this file, via any       ##
## medium is strictly prohibited.                   ##
##                                                  ##
######################################################

from imutils.video import VideoStream
from imutils.video import WebcamVideoStream
from imutils import contours
#from imutils import perspective
import imutils
import cv2
import time
import numpy as np
import math

### Constants ###

UseWebcam = True

WIDTH = 720 # Camera's true width, px
HEIGHT = 540 # Camera's true height, px

HFOV = 64.4 # degrees
VFOV = 36.2 # degrees

hfov = VFOV # transforms because camera is rotated 90 deg
vfov = HFOV # transforms because camera is rotated 90 deg

ball_lower = np.array([18,140,135])#([12,40,150])
ball_upper = np.array([25,250,255])#([35,250,255])

blue_lower = np.array([85,50,10])
blue_upper = np.array([175,110,70])

red_lower = np.array([50,50,105])#([50,50,105])
red_upper = np.array([80,90,255])#([80,90,255])

green_lower = np.array([65,140,90])
green_upper = np.array([115,175,138])

### Quickly modify band ranges ###
blue_lower = blue_lower * 0.99
blue_upper = blue_upper * 1.01
red_lower = red_lower * 0.99
red_upper = red_upper * 1.01

blue_lower = blue_lower.astype("int")
blue_upper = blue_upper.astype("int")
red_lower = red_lower.astype("int")
red_upper = red_upper.astype("int")


if UseWebcam:
    camera = WebcamVideoStream(src=0).start()
    camera.stream.set(11, 0   ) # contrast       min: 0   , max: 255 , increment:1
    camera.stream.set(12, 70   ) # saturation     min: 0   , max: 255 , increment:1
else:
    camera = cv2.VideoCapture('shooting-locations2019-3-23.avi')

try:
    while(True):
        
        if UseWebcam:
            frame = camera.read()
        else:
            _,frame = camera.read()
            #frame = cv2.imread('/home/pi/pyro/frames/frame86-MR.jpg') # Use picture instead
        
        frame = imutils.resize(frame, width = WIDTH)
        frame = cv2.rotate(frame, cv2.ROTATE_90_COUNTERCLOCKWISE)
        ##hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        
        height, width, _ = frame.shape
        #print(height, width)
        midheight = height/2
        midwidth = width/2
        
        bluemask = cv2.inRange(frame, blue_lower, blue_upper)
        #greenmask = cv2.inRange(frame, green_lower, green_upper)
        redmask = cv2.inRange(frame, red_lower, red_upper)

        ##bluemaskinv = cv2.bitwise_not(bluemask)
        ##blueresult = cv2.bitwise_and(frame, frame, mask = bluemask)
        
        blueflag = cv2.bitwise_or(bluemask, bluemask)#greenmask)
        redflag = cv2.bitwise_or(redmask, redmask)#greenmask)

        
        bluemaskblur = cv2.GaussianBlur(blueflag, (7,7), cv2.BORDER_DEFAULT)
        redmaskblur = cv2.GaussianBlur(redflag, (7,7), cv2.BORDER_DEFAULT)

        
        kernelB = np.ones((9,9),np.uint8)
        #erosionB = cv2.erode(bluemaskblur,kernelB,iterations = 1)
        dilationB = cv2.dilate(bluemaskblur,kernelB,iterations = 1) #FIXME Decrease to 1 if needed for FPS
        ##blur = cv2.GaussianBlur(dilation, (2,2), cv2.BORDER_DEFAULT)
        _,threshB = cv2.threshold(dilationB,100,255,cv2.THRESH_BINARY)#(dilationB,100,255,cv2.THRESH_BINARY)

        kernelR = np.ones((11,11),np.uint8)
        #erosionR = cv2.erode(redmaskblur,kernelR,iterations = 1)
        dilationR = cv2.dilate(redmaskblur,kernelR,iterations = 1) #FIXME Decrease to 1 if needed for FPS
        ##blur = cv2.GaussianBlur(dilation, (2,2), cv2.BORDER_DEFAULT)
        _,threshR = cv2.threshold(dilationR,100,255,cv2.THRESH_BINARY)#(dilationR,100,255,cv2.THRESH_BINARY)


        bluecountours, _ = cv2.findContours(threshB, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        redcountours, _ = cv2.findContours(threshR, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for c in bluecountours:
            # if the contour is not sufficiently large, ignore it
            if cv2.contourArea(c) > 250 and cv2.arcLength(c, True) > 150 and cv2.arcLength(c, True) < 800:
                #continue
                #print(cv2.arcLength(c, True))
                epsilon = 0.1*cv2.arcLength(c, True)
                approx = cv2.approxPolyDP(c, epsilon, True)
                #print(len(approx))
         
                # compute the rotated bounding box of the contour
                box = cv2.minAreaRect(c)
                box = cv2.cv.BoxPoints(box) if imutils.is_cv2() else cv2.boxPoints(box)
                box = np.array(box, dtype="int")
             
                # order the points in the contour such that they appear
                # in top-left, top-right, bottom-right, and bottom-left
                # order, then draw the outline of the rotated bounding
                # box
                #box = perspective.order_points(box)
                '''
                cv2.drawContours(frame, [box.astype("int")], -1, (255, 0, 0), 4)
                
                
                (tl, tr, br, bl) = box
                #print(tl,tr,br,bl)
                midTop = (tl+tr)/2
                midBottom = (bl+br)/2
                midPt = (midTop+midBottom)/2
                xmid, ymid = midPt
                xmid *= 0.95
                #print(midPt)'''
                '''
                if len(approx) > 3:
                    (tl, tr, br, bl) = box = cv2.boundingRect(approx)
                    if bl >= 15:

                        midTop = (tl+tr)/2
                        midBottom = (bl+br)/2
                        midPt = (midTop+midBottom)/2
                        xmid, ymid = midPt
                        xmid *= 0.95
                        #print(midPt)'''


                        #
                if len(approx) == 4:
                    

                    (tl, tr, br, bl) = approx
                    #print(tl, tr, br, bl)
                    
                    midTop = (tl+tr)/2
                    midBottom = (bl+br)/2
                    midPt = (midTop+midBottom)/2
                    midPt = [j for i in midPt for j in i]
                    #print(midPt, len(midPt))
                    xmid, ymid = midPt
                    xmid *= 0.95
                    #print(midPt)
                    
                    tlunpacked = [j for i in tl for j in i]
                    trunpacked = [j for i in tr for j in i]
                    blunpacked = [j for i in bl for j in i]
                    brunpacked = [j for i in br for j in i]
                    
                    #print(tl, bl, tlunpacked[0], tlunpacked[1], blunpacked[0], blunpacked[1])

                    #if  > 0:#abs(tlunpacked[1] - blunpacked[1]) > 0 and abs(trunpacked[1] - brunpacked[1] > 0):
                    cv2.drawContours(frame, [approx.astype("int")], -1, (255,200,0),2)
                    cv2.circle(frame, (int(xmid), int(ymid)), 5, (255, 0, 255), -1)
                    
                    thetaOffsetX = (xmid - midwidth) / width * hfov
                    thetaOffsetY = (height - ymid) / height * vfov - 9
                    hbar = 5.5 / ( (abs(tlunpacked[1]-blunpacked[1]) + abs(trunpacked[1]-brunpacked[1])) / 2 ) * height
                    if hbar > 200:
                        hbar = 5.5 / ( abs(tlunpacked[1]-blunpacked[1]) ) * height
                    if hbar > 200:
                        hbar = 5.5 / ( abs(trunpacked[1]-brunpacked[1]) ) * height
                    if hbar > 200:
                        hbar = -10000
                    dist = hbar / (2 * math.tan(math.radians(vfov/2))) * 1.2 # 1.2 from experimentation - from dilation
                    
                    cv2.putText(frame, "{0:.1f} deg. from center".format(thetaOffsetX), (trunpacked[0]-150,trunpacked[1]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255),6)
                    cv2.putText(frame, "{0:.1f} deg. from center".format(thetaOffsetX), (trunpacked[0]-150,trunpacked[1]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,0,0),2)
                    cv2.putText(frame, "{0:.1f} deg. above ground".format(thetaOffsetY), (trunpacked[0]-150,trunpacked[1]+20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255),6)
                    cv2.putText(frame, "{0:.1f} deg. above ground".format(thetaOffsetY), (trunpacked[0]-150,trunpacked[1]+20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,0,0),2)
                    if dist >= 0:
                        cv2.putText(frame, "{0:.1f} in. away".format(dist), (trunpacked[0]-150,trunpacked[1]+40), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255),6)
                        cv2.putText(frame, "{0:.1f} in. away".format(dist), (trunpacked[0]-150,trunpacked[1]+40), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,0,0),2)
                        
                    
                    #cv2.putText(frame, "({}, {})".format(midPt[0], midPt[1]), (trunpacked[0],trunpacked[1]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255),2)
                    
        for c in redcountours:
            # if the contour is not sufficiently large, ignore it
            if cv2.contourArea(c) > 250 and cv2.arcLength(c, True) > 150 and cv2.arcLength(c, True) < 800:
                #continue
                
                epsilon = 0.1*cv2.arcLength(c, True)
                approx = cv2.approxPolyDP(c, epsilon, True)

                # compute the rotated bounding box of the contour
                box = cv2.minAreaRect(c)
                box = cv2.cv.BoxPoints(box) if imutils.is_cv2() else cv2.boxPoints(box)
                box = np.array(box, dtype="int")
             
                # order the points in the contour such that they appear
                # in top-left, top-right, bottom-right, and bottom-left
                # order, then draw the outline of the rotated bounding
                # box
                #box = perspective.order_points(box)
                '''
                cv2.drawContours(frame, [box.astype("int")], -1, (0, 0, 255), 4)
                
                (tl, tr, br, bl) = box
                #print(tl,tr,br,bl)
                midTop = (tl+tr)/2
                midBottom = (bl+br)/2
                midPt = (midTop+midBottom)/2
                xmid, ymid = midPt
                xmid *= 1.05
                #print(midPt)
                cv2.circle(frame, (int(xmid), int(ymid)), 5, (255, 0, 255), -1)
                '''
                
                if len(approx) == 4:

                    (tl, tr, br, bl) = approx
                    #print(tl, tr, br, bl)
                    
                    midTop = (tl+tr)/2
                    midBottom = (bl+br)/2
                    midPt = (midTop+midBottom)/2
                    midPt = [j for i in midPt for j in i]
                    #print(midPt, len(midPt))
                    xmid, ymid = midPt
                    xmid *= 1.05
                    #print(midPt)
                    #if tl(0)-bl(0) > 1000 and tr(0)-br(0) > 50:
                    
                    tlunpacked = [j for i in tl for j in i]
                    trunpacked = [j for i in tr for j in i]
                    blunpacked = [j for i in bl for j in i]
                    brunpacked = [j for i in br for j in i]
                    
                    cv2.drawContours(frame, [approx.astype("int")], -1, (0,200,255),2)
                    cv2.circle(frame, (int(xmid), int(ymid)), 5, (255, 0, 255), -1)
                    
                    thetaOffsetX = (xmid - midwidth) / width * hfov
                    thetaOffsetY = (height - ymid) / height * vfov - 9
                    hbar = 5.5 / ( (abs(tlunpacked[1]-blunpacked[1]) + abs(trunpacked[1]-brunpacked[1])) / 2 ) * height
                    if hbar > 200:
                        hbar = 5.5 / ( abs(tlunpacked[1]-blunpacked[1]) ) * height
                    if hbar > 200:
                        hbar = 5.5 / ( abs(trunpacked[1]-brunpacked[1]) ) * height
                    if hbar > 200:
                        hbar = -10000
                    dist = hbar / (2 * math.tan(math.radians(vfov/2))) * 1.2 # 1.2 from experimentation - from dilation
                    
                    cv2.putText(frame, "{0:.1f} deg. from center".format(thetaOffsetX), (trunpacked[0]+150,trunpacked[1]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255),6)
                    cv2.putText(frame, "{0:.1f} deg. from center".format(thetaOffsetX), (trunpacked[0]+150,trunpacked[1]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,0,255),2)
                    cv2.putText(frame, "{0:.1f} deg. above ground".format(thetaOffsetY), (trunpacked[0]+150,trunpacked[1]+20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255),6)
                    cv2.putText(frame, "{0:.1f} deg. above ground".format(thetaOffsetY), (trunpacked[0]+150,trunpacked[1]+20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,0,255),2)
                    if dist >= 0:
                        cv2.putText(frame, "{0:.1f} in. away".format(dist), (trunpacked[0]+150,trunpacked[1]+40), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255),6)
                        cv2.putText(frame, "{0:.1f} in. away".format(dist), (trunpacked[0]+150,trunpacked[1]+40), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,0,255),2)
        
        cv2.imshow('frame', frame)
        ##cv2.imshow('mask', bluemask)
        #cv2.imshow('mask', redmask)
        ##cv2.imshow('errode/dilate', dilationB)
        #cv2.imshow('b', threshB)
        #cv2.imshow('r', threshR)
        #cv2.imshow('res', cv2.bitwise_or(threshB, threshR))
        
        


        
        ##cv2.imwrite("/home/pi/pyro/frames/frame%d.jpg" % count, frame)
        

        if cv2.waitKey(33*4) & 0xFF == ord('q'):
            break
except KeyboardInterrupt:
    print("Quitting due to Keyboard Interupt.")

if UseWebcam:
    camera.stream.release() # Incase camera.stop() doesn't close/release stream
    camera.stop()
cv2.destroyAllWindows()
