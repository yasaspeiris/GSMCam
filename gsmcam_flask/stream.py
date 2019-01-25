#!/usr/bin/env python
import cv2 #NOTE: This needs to be loaded first# Load filter2D + dilate overlay
# Load filter2D + dilate overlay
from pynq import Bitstreambs = Bitstream("/usr/local/lib/python3.6/dist-packages/pynq_cv/overlays/xv2Filter2DDilate.bit")bs.download()
import pynq_cv.overlays.xv2Filter2DDilate as xv2
# Load xlnk memory mangager
from pynq import XlnkXlnk.set_allocator_library('/usr/local/lib/python3.6/dist-packages/pynq_cv/overlays/xv2Filter2DDilate.so')mem_manager = Xlnk()

from flask import Flask, render_template, Response
import numpy


app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

def gen():
    i=1
    while i<10:
        yield (b'--frame\r\n'
            b'Content-Type: text/plain\r\n\r\n'+str(i)+b'\r\n')
        i+=1

def get_frame():

    camera = cv2.VideoCapture(0)
    width = 640
    height = 480
    camera.set(cv2.CAP_PROP_FRAME_WIDTH,width)camera.set(cv2.CAP_PROP_FRAME_HEIGHT,height)

    sobelx = np.ones((480,640),np.uint8)sobely = np.ones((480,640),np.uint8)blur_frame = np.ones((480,640),np.uint8)
    #These must be 3x3 since filter2d overlay supports a 3x3 kernel size
    kernel_sobelx = np.array([[1.0,0.0,-1.0],[2.0,0.0,-2.0],[1.0,0.0,-1.0]],np.float32)#Sobel Xkernel_sobely = np.array([[1.0,2.0,1.0],[0.0,0.0,0.0],[-1.0,-2.0,-1.0]],np.float32)#Sobel Ykernel_sharp = np.array([[-1.0,-1.0,-1.0],[-1.0,32.0,-1.0],[-1.0,-1.0,-1.0]],np.float32)#sharpkernelb = np.array([[1/16.0,1/8.0,1/16.0],[1/8.0,1/4.0,1/8.0],[1/16.0,1/8.0,1/16.0]],np.float32)#blur
    kernelVoid = np.zeros(0)

    xFin= mem_manager.cma_array((height,width),np.uint8)
    xFbuf= mem_manager.cma_array((height,width),np.uint8)
    xFout= mem_manager.cma_array((height,width),np.uint8)
    blur = mem_manager.cma_array((height,width),np.uint8)

    warpcount = 0
    weftcount = 0
    warparea = 0
    weftarea = 0
    draw_warp = 1
    draw_weft = 1
    warp_perimeter_thresh = 800
    weft_perimeter_thresh = 800

    # Flush webcam buffers (needed when rerunning notebook)
    for _ in range(5):    
        ret, frame_in = camera.read()# Read in a frame

    
    i=1
    while True:
        ret, img = camera.read()
        if ret:    
        gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY) #Convert color image from webcam to grayscale image
        xFin[:]  = gray[:] # load grayscale image to frame in buffer
        xv2.filter2D(xFin, -1, kernelb, xFout, borderType=cv2.BORDER_CONSTANT) #See how easy it is to call the overlay!
        blur_frame[:] = xFout[:]
        blur[:] = xFout[:]
        xv2.filter2D(blur, -1, kernel_sobelx, xFbuf, borderType=cv2.BORDER_CONSTANT) #convolve with sobel x filter
        xv2.filter2D(xFbuf, -1, kernelVoid, xFout, borderType=cv2.BORDER_CONSTANT)
        sobelx[:] = xFout[:]
        xv2.filter2D(blur, -1, kernel_sobely, xFbuf, borderType=cv2.BORDER_CONSTANT) #convolve with sobel y filter
        xv2.filter2D(xFbuf, -1, kernelVoid, xFout, borderType=cv2.BORDER_CONSTANT)
        sobely[:] = xFout[:]


        if draw_warp:      
            im2x, contoursx, hierarchyx = cv2.findContours(sobelx,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE) 
            for cnt in contoursx:        
                perimeter = cv2.arcLength(cnt,True) 
                    if perimeter > warp_perimeter_thresh:          
                        cv2.drawContours(img, cnt, -1, (204,50,153), 2)          
                        warpcount = warpcount+1          
                        warparea = +cv2.contourArea(cnt)
        if draw_weft:      
            im2y, contoursy, hierarchyy = cv2.findContours(sobely,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE) 
            for cnt in contoursy:        
                perimeter = cv2.arcLength(cnt,True) 
                if perimeter > weft_perimeter_thresh:          
                    cv2.drawContours(img, cnt, -1, (0,0,255), 2)          
                    weftcount = weftcount+1          
                    weftarea = +cv2.contourArea(cnt)
        mem = "Warp Yarns : "+str(warpcount)
        mem1 = "Warp Pixel Area : "+str(warparea)+ " pixels"
        mem2 = "Weft Yarns : "+str(weftcount)mem3 = "Weft Pixel Area : "+str(weftarea)+ " pixels"
        areatot = (warparea+weftarea)
        mem4 = "Totalized Pixel Area : "+str(areatot)+ " pixels"
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(img,mem,(5,370), font, 1,(0,255,0),2,cv2.LINE_AA)
        cv2.putText(img,mem1,(5,400), font, 1,(255,100,100),2,cv2.LINE_AA)
        cv2.putText(img,mem2,(5,430), font, 1,(0,255,0),2,cv2.LINE_AA)
        cv2.putText(img,mem3,(5,460), font, 1,(255,100,100),2,cv2.LINE_AA)
        cv2.putText(img,mem4,(5,30), font, 1,(255,0,0),2,cv2.LINE_AA)



        imgencode=cv2.imencode('.jpg',img)[1]
        stringData=imgencode.tostring()
        yield (b'--frame\r\n'
            b'Content-Type: text/plain\r\n\r\n'+stringData+b'\r\n')
        i+=1

    del(camera)

@app.route('/calc')
def calc():
     return Response(get_frame(),mimetype='multipart/x-mixed-replace; boundary=frame')


if __name__ == '__main__':
    app.run(host='192.168.2.1', debug=True, threaded=True)