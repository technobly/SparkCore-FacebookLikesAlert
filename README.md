SparkCore-FacebookLikesAlert
============================

Spark Maker Kit - Facebook Likes Alert for the Spark Core.

So your Spark Core is sitting around being lazy? Give your *Core* a workout with this One-Finger Pushup Facebook Likes Alert project.

It's easy to implement a TCP Client with your Spark Core and do something useful and cool like monitor your favorite Facebook page and display the current number of Likes in an interesting way!

[Watch the short Youtube action video](https://www.youtube.com/watch?v=VVEwlagTNzU)

---

###Build It!###

Print out the two PDFs and cut out with an exacto knife.

[facebook-likes-alert-guage.pdf](https://github.com/technobly/SparkCore-FacebookLikesAlert/blob/master/artwork/facebook-likes-alert-guage.pdf?raw=true)

[one-finger-pushup-guy.pdf](https://github.com/technobly/SparkCore-FacebookLikesAlert/blob/master/artwork/one-finger-pushup-guy.pdf?raw=true)

![01](http://i.imgur.com/DQArbGL.jpg)

![02](http://i.imgur.com/VEDbP9d.jpg)

![03](http://i.imgur.com/2jCTatC.jpg)

Trace the outline of the cut out pieces on some 1/4" foam board, or Blue cor foam.  Alternatively you could probably get away with printing the artwork on some thick 80lb. cardstock.
![04](http://i.imgur.com/ss7l4MN.jpg)

![05](http://i.imgur.com/g3qDvNU.jpg)

Color the edges black with a Sharpie marker to make them less noticeable.
![06](http://i.imgur.com/gwZw50K.jpg)

Cut out the show area on the foam, but leave this area on the color paper.
![07](http://i.imgur.com/lGAG61p.jpg)

Add double-sided scotch tape to everywhere on the back of the color paper print out, except for the outlined area where the arm will pivot.

![08](http://i.imgur.com/A5hZk0G.jpg)

Align the paper print out on the foam and press it together.  One-finger pushup guy is lookin' good!
![09](http://i.imgur.com/aA0HJs1.jpg)

![10](http://i.imgur.com/EoWoccZ.jpg)

Wire up the servo! Grab a 3 pin header and plug the servo into the breadboard as shown carefully aligning the red lead with VIN and the brown lead with GND.
![11](http://i.imgur.com/odJQXbc.jpg)

![12](http://i.imgur.com/N8eJHZF.jpg)

Add a jumper from the orange lead to A7.
![13](http://i.imgur.com/ht79iVg.jpg)

Use double-sided scotch tape to attach the arm to a servo horn as shown.
![14](http://i.imgur.com/AAJcQHY.jpg)

Grab a piece of stiff wire or a pin and poke a hole through the center of the servo horn, foam and paper.  This will serve as a locating point for the next step.
![15](http://i.imgur.com/16uJzD3.jpg)

Cut out a small square with your exacto knife to all for the servo horn screw to drop through.
![16](http://i.imgur.com/6a2GHFi.jpg)

Attach and tighten down the servo horn to the servo.
![17](http://i.imgur.com/U0ubyxr.jpg)

Use some double-sided foam tape to mount your servo the side of your breadboard.
![18](http://i.imgur.com/X0XqFBb.jpg)

![19](http://i.imgur.com/tjH81vK.jpg)

Manually turn your servo fully clock-wise, it should stop in this position.  If not, unscrew the servo horn and reposition it so that it looks as close to this picture as possible.  This will ensure proper pushup action, and you'll have a fairly easy time calibrating the digit positions.
![20](http://i.imgur.com/XPAHvzh.jpg)

Check the fit of your body to arm and make any adjustments now if necessary.
![21](http://i.imgur.com/1dTfuAg.jpg)

Add more double-sided foam tape to mount the body to this side of the breadboard.
![22](http://i.imgur.com/NK7qB2f.jpg)

![23](http://i.imgur.com/HI5lZgz.jpg)

![24](http://i.imgur.com/OZkGhE0.jpg)

Find the right spot to create a fulcrum that allows your guy to do proper looking pushups.  You can try to copy this stack of three 1/4" pieces of foam stacked on top of each other placed here.
![25](http://i.imgur.com/h65adzw.jpg)

Add double-sided scotch tape to a small flap of paper which will serve as a hinge at the feet.  This will keep your guy locked in place after you calibrate your servo digit positions so you'll have repeatable readouts.
![26](http://i.imgur.com/yV0ZcJn.jpg)

Congrats! You made it :D  Go crack a cold one and celebrate.
![27](http://i.imgur.com/1Y1TbcV.jpg)

---

###Calibration!###
The first code you're going to need to run is the calibration code.  This just tries to give you a good idea of where your servo is pointing based on degrees.  By default it's mapped for you already to values that should be somewhat close.  Run the code with your serial terminal closed, after the core boots open your serial terminal and press ENTER.  Your guy should come to life and start walking from 0 to 9 every second.  If he's a little too far to the left of 0, adjust the ``SERVO_DEG_0`` value up a bit, or down a bit if too far to the right of 0.  Do the same for digit 9.  Once you are happy with these values, you can copy them into your main application.

Grab the [RAW version of calibration.cpp](https://raw.githubusercontent.com/technobly/SparkCore-FacebookLikesAlert/master/calibration.cpp) and paste into your web IDE as a new application:

![image](http://i.imgur.com/bHJjnJ0.png)

If you are building locally, place the file here:

```
..\core-firmware\src\application.cpp (renamed from calibration.cpp)
```

---

###Run the Facebook Likes Alert!###
Grab the [RAW version of application.cpp](https://raw.githubusercontent.com/technobly/SparkCore-FacebookLikesAlert/master/application.cpp) and paste into your web IDE as a new application. Copy your calibration values to ``SERVO_DEG_0`` and ``SERVO_DEG_9`` in your application.

![image](http://i.imgur.com/gR0jwML.png)

If you are building locally, place the file here:

```
..\core-firmware\src\application.cpp
```

Have fun!
-BDub