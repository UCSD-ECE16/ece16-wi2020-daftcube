# ECE 16 Lab Report 3
Prepared By: Owen Bartolf
Date: 1/30/2020

## Tutorial 1: Python
>
> **Q. Show the code - Starting with a = “Hello World!!!”, come up with a code that will give us b = “Hello” and c = “World” and d = “!!!” . Also, in code, check if “ello” is in a.**
> 
> ```python
>
> # My first* Python Program!
>
>def main():
>    
>    # A
>    a = "Hello World!!!"
>    print(a)
>    
>    # Get B, C, D
>    b = a[0:5]
>    c = a[6:11]
>    d = a[11:14]
>    
>    print(b)
>    print(c)
>    print(d)
>    
>    if "ello" in a:
>        print("ello is in a!")
>
>
>if __name__ == "__main__":
>    main()
>
> # * I did a bit of Python in the past but nothing major. I'm excited to learn !!
> ```
>
> The following code accomplishes the above task.
>
> 
> **Q. In the following code, what is the output of the print statement? Why doesn’t original_list = ['hi','how','are','you']?**
>
> The scripting command newer_list[0:2] returns a new array with the elements of newer_list from 0 to 1. Basically, on the line where we set newer_list[0:2] equal to ["how", "are"], we're not actually saving anything because the lefthand operand is a new array and not a variable or other memory location.

## Tutorial 2: Numpy and Pyserial

>
> ### Connecting Arduino to Python
>
> _Quick Note: I'm using the encoding fix that was posted in Canvas instead of the code from the lab document. Answers may vary for this reason._
>
> **Q. Try sending without the .encode. What happens?**
>
> We get the following error:
> ```
> TypeError: unicode strings are not supported, please encode to bytes: 'Hello'
> ```
> There must be something about either the implementation of the PySerial library or the Serial protocol as a transport layer that prevents the use of unicode characters. Thus, we must convert to a format that it can accept, which happens to be UTF-8.
>
> The interesting thing about UTF-8 is that it is a variable-width encoding. This means that some characters exist that are represented with more than one byte. So, if we try to send characters from other languages, especially non-latin languages, we might encounter some problems where our Arduino serial reader parses a single character as two characters instead of one.  
>
> **Q. Identify in the above code, (1) which python command prints to the python’s own console, and (2) which python command prints to the serial port to the MCU?**
>
> Prints to own console...
>```py
> print(ser.name)
>```
> Transmits over serial to print on the OLED via serial transmission to MCU...
>```py
> ser.write(S.encode('utf-8')) 
>```
> **Q. What happens if you take out the \n in the string? Why?**
>
> Nothing will print on the screen. This is  because the newline character is our message delimiter in our very simple communications protocol. 
>
> Without the newline character, our protocol does not know when a given message terminates and a new one begins. Specifically, in our Arduino code, we continue writing to a receive buffer until we reach that character. Without the character, the Arduino will continue writing to the buffer forever without actually writing a message. There could even be an ArrayOutOfBounds error somewhere in there.
>
> ---
>
> ### Receiving Data with Python
> 
> **Q. Describe the output you observe on the Python side?**
>```
> Current Time: 11
> Current Time
>```
> It's literally just the 30 characters sent from the Arduino's serial port. Depending on what part of the program execution the Python program catches the timer in, we can get all sorts of messages, from the current time to state transition debug messages.
>
> **Q. Change the code to read 10 bytes instead of 30. Now what do you get? What are the 10 bytes you received? Remove decode might help you understand**
> 
> We get the same output, but with only 10 characters. If we remove decode, we can actually see that internally, Arduino serializes our string as a series of bytes before sending the data over the wire.
> ```
> b'Current Ti'
> ```
> The b prefix indicates that these characters are bytes. These bytes match the encoding; that's why we can read the "plain english" version on the other end when we decode the output.
>
> ---
>
> ### Receiving a Byte at a Time
>
> **Q. Describe the output you observe on the Python side? Is it the same as before? What does this tell you about the print() function of python?**
>
> The output is not the same because we feed the print function an array instead of a deserialized string. However, we learned that Python's print function is a lot more flexible than C's Serial.print() equivalent. This is probably due to the dynamic typing that happens behind the scenes with Python.
> 
> ### Knowing when to Quit
> 
> Q. We purposely made a few errors above. What were they?
>
> - Syntax error: The T in try should be lowercase.
>
> ---
>
> ### Numpy
> #### Numpy Array
> **Q. Show the code - Make an Numpy Array called test_array  from a list = [0,10,4,12]. Subtract 20 from the test_array, what do you get? What is the shape of the test_array**
>
> **Q. Show the code - Make a 2D array of test_2D_array from...** 
> ```
> [0,10,4,12]
> [1,20,3,41]
> ```
>
> ---
> #### Zeros and Ones
> **Q. Make a 2D array of zeros with shape of 10x20 and then print it out**
> 
> ---
>
> #### hstack and vstack
> **Q. Show the code - Out of the test_array, create the following using hstack and vstack. **
> ```
> The format on the lab report was impossible to transpose quickly so refer to it on the lab.
> ```
> ---
> #### arange
> **Q. Show the code - Using arange, make an array called arange_array1 to equal [-3, 3,9,15] and arange_array2 to equal [ -7,  -9, -11, -13, -15, -17, -19]**
>
> ---
>
> #### linspace
> **Q. Make an array call linspace_array using linspace that goes from 0 to 100 with 49 steps.**
>
> **Q. How does linspace and arange differ? When might you use one over the other?**
>
> ---
>
> #### Indexing and Slicing
> **Q. What is an array of size 3x4 that would produce the following results. Show your work on how you deduced your answer on paper or some kind of graphics :**
>
> ```
> print(e[0])     >>> [12 3 1 2]
> print(e[1,0])  >>> 0
> print(e[:,1])   >>> [3 0 2]
> print(e[2, :2])>>> [4 2]
> print(e[2, 2:])>>> [3 1] 
> print(e[:,2])  >>> [1 1 3]
> print(e[1,3]) >>> 2
> ```
>
> ---
> #### Setting values of arrays
>
> **Q. Show your code - Now solve the above indexing and slicing problem by writing the code using array assignment. **
>
>



## Pre-Challenge Refactors
>
> I improved upon the Message library we built in the last lab. Instead of only displaying one message, I built a system that displays the new message and the previous two on the lines above. In exchange for this feature, we sacrifice the ability to print messages to a specific line.
>
> In addition, I refactored the Receive code to throw every received buffer into a struct with an ID and an integer that describes the actual size of the buffer. From there, I was able to convert the buffers into strings fairly easily.
>

## Challenge 1