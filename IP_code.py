import cv2
import numpy as np
import serial
import time

arduinoData= serial.Serial('com4',9600)
time.sleep(2)


x_p=0
x_pp=0
y_p=0


while True:
 cam = cv2.VideoCapture(0)
 cv2.namedWindow("thresh adjust")
 cv2.createTrackbar("--","thresh adjust",80,230, lambda x:True)
 while True:
    ret, frame = cam.read()
    cv2.imshow("test", frame)
    value= cv2.getTrackbarPos("--","thresh adjust")
    frame= cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    _,thresh=cv2.threshold(frame,value,255,cv2.THRESH_BINARY)
    cv2.imshow("live",thresh)
    if not ret:
        break
    k = cv2.waitKey(1)

    if k%256 == 27:
        # ESC pressed
        print("Escape hit, closing...")
        break

 cam.release()

 threshold= cv2.fastNlMeansDenoising(thresh, None,10,7,21)
 _,contours,hierarchy1= cv2.findContours(threshold,cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

 for cnt in contours :
  if cv2.contourArea(cnt)>550 :
   approx = cv2.approxPolyDP(cnt, 0.02* cv2.arcLength(cnt, True), True)
   cv2.drawContours(threshold, [approx],-1,(255),5)
   x= approx.ravel()[0]
   y= approx.ravel()[1]
  
   if len(approx)==3:                   #"Triangle"
    x_pp=x_p
    x_p=y_p
    y_p=2

   elif len(approx)==4:
       x1= approx.ravel()[2]
       y1= approx.ravel()[3]

       x2=approx.ravel()[4]
       y2= approx.ravel()[5]

       if ((x-x1)**2+(y-y1)**2)==((x1-x2)**2+(y1-y2)**2): # "Square"
        x_pp=x_p
        x_p=y_p
        y_p=3
        
       else:                            # "Rectangle"
        x_pp=x_p
        x_p=y_p
        y_p=4
       
   elif 4<len(approx)<10:                #"SemiCircle"
       x_pp=x_p
       x_p=y_p
       y_p=0
         
   else:                                 #"CIRCLE"
       x_pp=x_p
       x_p=y_p
       y_p=1
 
 cv2.imshow("contours",threshold)
 print("x:-"+str(x_p))
 print("y:-"+ str(y_p))
 arduinoData.write(10*x_p+y_p)
 
 cv2.waitKey(20)
 print("Enter any key for Next iteration to start")
 c= int(input())


cv2.waitKey(0)
cv2.destroyAllWindows()
