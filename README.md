# RANDOMGENERATOR
Course paper for "Pseudo-Random Generators Theory" subject

# What do we have?

* Mouse code values

* Keyboard jiffies

* Parallel pool for every event class (array for mouse, for keyboard...)

* Correct arithmetic (jiffies mod 2^8 >> last 8 bits)

* Char device (/dev/lkm_example) is attached and available for reading of pool;

# What do we need?

* Some events from /dev/random (disk and interrupts) -- read the article of mr. Klyuev!

* Analyze of this shit (when we have t1,t2,...,tn and we should try models  t1..tn, t2-t1,...,tn-t(n-1) and a1 t1+...+an tn)

# How to use it?

Just type 
>> sudo insmod ./test.ko

>> dmesg

>> [123234.3434] lkm_example module loaded with device major number N

(where N is your major number)
 
>> sudo mknod /dev/lkm_example c N 0
 
>> cat /dev/lkm_example

(here is your pool)

# Don't forget to remove it!
>> sudo rmmod test

>> sudo rm /dev/lkm_example

