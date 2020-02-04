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
>    hiHowAreYou()
>
>def hiHowAreYou():
>    original_list = ['hi',1,2,'you']
>    new_list = original_list
>    newer_list = new_list[1:3]
>    newer_list[0:2] = ['how','are']
>    print(original_list)
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
> **Q. Try sending without the .encode. What happens?**
>
> Something
>
> **Q. Identify in the above code, (1) which python command prints to the python’s own console, and (2) which python command prints to the serial port to the MCU?**
>
> Something
>
> **Q. What happens if you take out the \n in the string? Why?**
>
> Something
>
>