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
>
>```
>
> **Q. What happens if you take out the \n in the string? Why?**
>
> Nothing will print on the screen. This is  because the newline character is our message delimiter in our very simple communications protocol. 
>
> Without the newline character, our protocol does not know when a given message terminates and a new one begins. Specifically, in our Arduino code, we continue writing to a receive buffer until we reach that character. Without the character, the Arduino will continue writing to the buffer forever without actually writing a message. There could even be an ArrayOutOfBounds error somewhere in there.
>
>

## Pre-Challenge Refactors
>
> I improved upon the Message library we built in the last lab. Instead of only displaying one message, I built a system that displays the new message and the previous two on the lines above. In exchange for this feature, we sacrifice the ability to print messages to a specific line.
>

## Challenge 1