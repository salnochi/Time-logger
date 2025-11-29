# Time-logger
Written in C, Time-logger is a time stamping tool for user defined events that are written out to a cvs file.  

This is a very simple tool designed to timestamp and log random events and milestones that occur in everday life.
Time-logger was written in C to be able to complie for cross platformd.

Files:
- time_log_cli = executible file for the linux command line interface
- time_log_gui = executible file for the graphical user interface using GTK3 

Source:
There are two source files in the src folder.
- time_log_cli.c = source file for use in a linux based command line interface 
- time_log_gui.c = source file for a graphical user interface in linux using GTK

Logging:
CSV logs are placed in the "logs" folder to provide a single point for references when parsing the data is needed. 
Two csv files are located in the logs folder that complement the version of the program that uses it.
- time_log.csv = used by the command line interface version
- time_log_gui.csv = used by the graphical used interface version
