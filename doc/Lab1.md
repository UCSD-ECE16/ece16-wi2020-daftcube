# ECE16 Lab 1 Report
Prepared by: Owen Bartolf

Date: 01/08/2020 (Happy Birthday to Me)

## Tutorial 1:

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
> it, including...
> 1. Delete the file on the Github website.
> 2. Delete the file on our local machine and pull the newest version to synchronize the versions, then overwrite it and commit the new changes.
> 3. Force a push. **This is the nuclear option and a really really bad idea™.**
> 4. Other methods involving branches and merging. 


When answering a Question, please include both the question and the answer, as such:

>Q. The question verbatim from the lab document

>A. Your excellent answer with whatever images and stuff.
>
>and if you need to skip a line, just keep adding > and you will have the same block. 

## Challenges:
In every lab assignment, there are 3 challenges. For each challenge, there will usually be an associated code to be submitted and a series of discussion questions. You are to answer the discussion questions here.

Including Screenshots, photos, and videos of you outputs and setup is also important as it helps contextualize what you are observing. For the most part, we only expect you to include screenshots and photos to augment your report. There will be a few challenges where we explicitly ask for videos. In those cases, please include videos. 

Divide each of challenge under a sub-sub-sub heading:

### Challenge 1: Name of Challenge
Provide a quick summary, in your own words what the challenge is about and how did you approach it. Same thing goes for this, be descriptive. And again use blocks to answer the questions in an organized fashion. 

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
