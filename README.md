# Simple Shell!

We're typing this message as memory that we did the project together. We want to say that **this project was really challenging**. We'reproud of what we've done. - Ahmed & Dinamow

## The main idea

so our main idea or our big mind map was

### Take input

ofc first thing we need to do is to take input from user

### Check the input

if the user gave us path, prog name, parameter or even a file he made by himself

### Run the program

run the program depnds on user what did he gave us

### Free memorey

it was the most hated part tbh i didn't like it at all

## How to take input

we used getline to take input and ***used strtok to allocate the parameter if he gave us or not***

### How to check the input

before we allocate the parameters we check if the user gave us ***/ or . or letter*** why did we do that?
so if the user gave us `/` that means he gave us path
if user gave us `.` that means the user gave us a program he made `./`
and finally letter ofc is the program smth like `ls`

### How to run the program

we used `**strtok**` to handle the paths and
if the user gave us the path dirctly it was the ez part we just put it in execve func
if he gave us the func name or prog he made we just merge all the paths we allocated with his input and check them all if it was in one of them or not, if it was we just pass the path who gave us the true **(yes this path of the program u merged is here)** is no path gave us true we just type the error massage
