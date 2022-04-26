# Project Grade: 100.0/100.0
Completed fall of 2021 as a part of Lehigh University's CSE 109: System Software.

# Note:
All programs were written and optimized for X86-64 machines with gcc module 7.10.

# Given: exmaple output.

Example call:

chkLinks merle 'notMyPassword' sunlab.cse.lehigh.edu /home/merle/WWW-data/cse109.fall2021/index.html 

You will need to use your own userid and password. 

But, you will need to pass the same 3rd and 4th arguments.

Some notes:
1. Search only for "http" and "https" protocols.
2. Ensure href has "://" after the protocol and before the server name.
3. Place uniquely-named downloaded files into /tmp.
4. Ensure downloaded files have the PID in their name so your files 
   do not interfere with other students running their code.
5. Remove any files created in /tmp when done (use unlink).
6. Do not use global variables.
7. Write modular code.
8. Bonus (5): prompt user for password and display '*' for each character entered.
