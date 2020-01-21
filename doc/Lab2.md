# ECE16 Lab Report 2
Prepared by: Owen Bartolf

Date: 01/16/2020

## Tutorial 1: Accelerometers

> **Q. How many bits is your ADC? Try connecting your A0 pin to 3.3V. How did you calculate the bits?**
> 
> When I connect A0 to 3.3V, the output is 4095. When disconnected, the output is zero. This means there are 4096 possible values. Because our number is composed of bits, which only have two states, we can find the amount of bits needed to compose this number by throwing it in a logarithm with a base of two:
>
> ![Image](fig/Lab2/Lab2_LaTeX.png)
>
> **Q. What is the resting value of the accelerometer when it is laying face up. Why is it not 0? What is this value in terms of volts (remember that 3.3V is the maximum).**
> 
> My accelerometer rests at somewhere between 1915 and 1920 when face up.
>
> The accelerometer is not zero because it is constantly detecting the acceleration from the force of gravity.
> 
> Assuming the numerical reading is somewhat proportional to the incoming voltage, we can set up a simple proportion and solve for x:
>
> ![Image](fig/Lab2/Lab2_Proportion.png) 
>
> ![Image](fig/Lab2/Lab2_Proportion2.png)
>
> ![Image](fig/Lab2/Lab2_Proportion3.png)
>
> ![Image](fig/Lab2/Lab2_Proportion4.png)
> 
> We are receiving approximately 1.62 volts from the accelerometer.
>
> **Q. Tap the accelerometer light, medium, and hard. What is the average value of each tap? How did you calculate this? Please don’t ask us if you are tapping correctly, use your judgement :) Show a video gif of the accelerometer plotting and tapping at different strengths.**
>
> So, my first approach was to tap it once for each strength... 
>
> ![Image](fig/Lab2/Lab2_TapPlot.png)
> 
> However, I quickly realized we are more interested in the _average tap_ because knowing the average tap for each strength would allow us to create a 
>
> To get the average strength of each tap, I used the Serial Monitor to obtain the raw output. Then, I brought the data into a spreadsheeting application.
> 
> I wrote a simple query to remove all 'baseline' values that were determined to be between 1910 and 1930. This left only the extremities, or rather, the taps of various strength. I then divided the samples by the type of tap they were based on the sample's relative position in the list of samples. When recording samples, I tapped in an increasing order of relative strength. Knowing this info, I could easily take the average reading for each strength of tap.
> 
> Each tap has a downward acceleration from the initial press and an upward acceleration as it recovers to its initial position. When moving downward, the reading is less the baseline. When recovering upward, the reading is greater. With an average, these extremes cancel eachother out. Thus, I found it more valuable to take the average of the delta from the resting point rather than the average of the values.
> 
> The average deltas can be found in the below table. The table, in CSV format can be found in [Lab 2's Data Folder](data/Lab2/TapData.csv).
> 
> ![Image](fig/Lab2/Lab2_TapStatistics.png)
> 
> **Light Tap Average Deviation: 25.625**
>
> **Medium Tap Average Deviation: 53.032**
>
> **Heavy Tap Average Deviation: 248.143**
> 
> And the gif, as requested...
> 
> 

## Tutorial 2: Pulse Width Modulators

> **Q. In the above figure, assuming we are showing 2ms of data, what is the PWM frequency?**
>
> **Q. Why is 100% duty cycle 255 instead of 256?**
>
> 
> 
> **Q. We purposely made some mistakes in the above example.  What were they? It will not work directly, but by reading the compilation error, the tutorial instructions, and comments carefully, you should have no trouble getting it to work!**
> 
> 

## Tutorial 3: OLED Screens

> **Q. Again we made some intentional mistakes in the code above. What were they?**

## Tutorial 4: 

> **Q. What did the Arduino receive? How does this change if you use different line endings?**
>
> **Q. What are the Decimal values of NL (new line) and CR (Carriage Return)?**

## Challenge 1: Fading Buzzer

> **Q. Which pin does the code ask you to use for the motor?**
>
> **Q. Why can’t we achieve this speed variation using a digitalWrite and instead has to use ledcWrite?**

## Challenge 2: Gesture Detection

> **Q. What are some different logics you tried and why? What are some situations where you noticed your detection algorithm doesn’t work well?**
>
> **Q. Provide a plot showing 5 taps and the threshold used.** 
>
> **Q. Include a video of you tapping on the accelerometer and the OLED counting each time.**

## Challenge 3: Read / Write to OLED

> Q. Video of a message typed into the serial monitor and appearing on the OLED. This video should be shot WITHOUT moving the camera. 
> Q. What happens if you write a really long message? Why?

## Needless Experiment 0: Custom Plotting Application that Renders to OLED
> **Q. Is it possible?**
> 
> Yes.
> 
> **Q. But... why...?**
> 
> Weaponized Boredom.