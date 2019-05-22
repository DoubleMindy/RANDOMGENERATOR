# RANDOMGENERATOR
Course paper for "Pseudo-Random Generators Theory" subject

# What do we have?

* Mouse movements code values

* Mouse presses (left, right, ctrl) jiffies;

* Mouse scrolls;

* Keyboard jiffies;

* Parallel pool for every event class (array for mouse, for keyboard...);

* Correct arithmetic (jiffies mod 2^8 >> last 8 bits);

* Char device (/dev/lkm_example) is attached and available for reading of pool;

# How to use it?

Just type 
> sudo insmod ./lkm.ko

> dmesg

Then you see 

> [123234.3434] lkm: major number is -- N

(where N is your major number)
 
> sudo mknod /dev/lkm_example c N 0
 
> cat /dev/lkm_example

(here is your pool)

# OR 
you could create the Output.log file just typing
> ./illustrator.sh

# Don't forget to remove it!
> sudo rmmod lkm

> sudo rm /dev/lkm_example

