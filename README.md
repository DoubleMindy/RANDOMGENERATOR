# RANDOMGENERATOR
Course paper for "Pseudo-Random Generators Theory" subject

# What do we have?

* Mouse code values

* Keyboard jiffies

* Correct arithmetic (jiffies mod 2^8 >> last 8 bits)

# What do we need?

* Parallel pool for every event class (array for mouse, for keyboard...)

* Some events from /dev/random (disk and interrupts) -- read the article of mr. Klyuev!

* Analyze of this shit (when we have t1,t2,...,tn and we should try models  t1..tn, t2-t1,...,tn-t(n-1) and a1 t1+...+an tn)

