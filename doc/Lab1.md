# ECE16 Lab 1 Report
Prepared by: Owen Bartolf

Date: 01/08/2020 (Happy Birthday to Me)

## Tutorials
### Tutorial 1:

> #### Blink
> ![Image of Challenge](fig/Lab1_Blink.gif)
>
> Q. What is the frequency of the blink rate in this example? Note that frequency is the inverse of the time it takes for a cycle. A cycle is the time it takes to go HIGH to LOW to HIGH again. Record a video of your FireBeetle blinking.  Make a note of the answer for now, in the next GIT tutorial, you will get a copy of a sample lab report.
>
> A. With our definition of cycle, to get the time it takes for the LED to cycle from HIGH to LOW to HIGH again, we take the sum of all of our 'delay()' function
> arguments. 
> 
> It takes **1000ms + 500ms = 1500ms** to cycle from HIGH to LOW to HIGH again.
> 
> Because we're measuring the frequency of the cycle, and not the period, we will use the formula for frequency to calculate our final result.
> 
> **frequency = cycles per second = 1 / (time in seconds per single cycle)**
> **frequency = 1 / (1.5s)**
> **frequency ~= .667 Hz**
> 
> My previous note has been added to Git.

> Q. When you open the conflicted readme, what did you get? How did you fix it?
>
> A.
>![Image of Challenge](fig/Lab1_Tutorial1_GitPushIssue.png)
> What we get is this glorious error message. Essentially, we have a version conflict; the current copy of our file
> on our local repository no longer matches the file that lives in the remote repository. We have a few options to fix
> it, including but certainly not limited to...
> 1. Revert the change on the Github website.
> 2. Delete the file on our local machine and pull the newest version to synchronize the versions, then overwrite it and commit the new changes.
> 3. Force a push. **This is the nuclear option and a really really bad idea™.**
> 4. Other methods involving branches and merging.
>
> Personally, I picked option 2, but each method I talked about has its use cases.

### Tutorial 2
> #### Switch
> ![Image of Challenge](fig/Lab1_Button.gif)
>
> Q. Why do we need a pull-up resistor? Describe the behavior without it.
> 
> Todo Answer.
>
> ##### Remarks for Switch Exercise
>
> I used an LED instead of a wire to bridge my button output to my digital read pin. I made this decision because the LED just fit the breadboard better. While it doesn't light up because the 1000 ohm resistor doesn't allow enough current to create a visible amount of light light, it still completes the circuit and allows the charge to flow.
> #### External LED Blink
>
> ![Image of Challenge](fig/Lab1_BlinkLED.gif)
>
> Q. Which GPIO pin did you have to use according to the above setup?
>
> According to the diagram, we are using GPIO Pin 26.
>
> Q. What is the expected current draw?
>
> V = IR 
>
> V = [3.3 Volts Provided] - [2.2 Volt Drop over LED]; 
>
> V = 1.1 Volts
> 
> R = 220 Ω
>
> I = ?
> 
> 1.1 V = 220 Ω * (I)
>
> 1.1 V / 220 Ω = I
>
> I = .005 A
> 
>  **[[ I = 5 mA ]]**
>
> The expected current draw for this circuit is 5 milliamps.
>
> Q. What is the limit for the GPIO? You can find this on the ESP32_WROOM datasheet.
>
> According to the datasheet, its either 40 milliamps or 20 milliamps. I don't know how to read it. TODO ask in office hours.


## Challenges:

### Challenge 0: "Have a Repo with some files in it!"
> ✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅
> Oh wait, here's my required gif!
> 
> [TODO: Insert a gif.]

### Challenge 1: 

>Q. First questions

>A. Your answer and supporting image
>
>To include an image, first include your image in your images folder. 
>![Image of Challenge](fig/Lab0_SampleImage.jpg)

### Challenge 2:
>Q. Second Challenge wants you to have a video!

>A. Answer the question and describe the video.  
>![Image of Challenge](fig/Lab0_SampleVideo.gif)

### Challenge 3:
