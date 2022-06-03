# pipex
# Overview
This project is the discovery in detail and by programming of a UNIX mechanism that you already know.
# Mandatory part
This part aims to copy behavior of next shell command: 
< infile cmd1 | cmd2 > outfile, where infile and outfile are files to read from and to write to, 
cmd1 and cmd2 are shell commands to execute.
# Running
To compile this part you have to run make, firstly. 
Then run ./pipex infile cmd1 cmd2 outfile to lauch the program
# Bonus part
<infile cmd1 | cmd2 | cmd3 | ... | cmdn > outfile, where infile and outfile are files to read from and to write to, 
cmd1, cmd2, ..., cmdn are shell commands to execute.
