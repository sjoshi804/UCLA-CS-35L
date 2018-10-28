 #!/usr/bin/python -tt


"""
    Output lines selected randomly from a file
    
    Copyright 2018 Siddharth Joshi.
    
    $Id: shuf.py,v 1.0 2018/04/30 20:04:42 joshi Exp $
    """

import random, sys
import argparse


def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE or STREAM."""

    # Specifying description text
    parser = argparse.ArgumentParser(description="shuf")
    # Adding --head count option
    parser.add_argument("-n", "--head-count", type=int, action="store", dest="count", help="output at most count \n")
    # Adding file arg
    parser.add_argument("file", nargs="?", type=argparse.FileType("r"), default=sys.stdin)
    # Adding --echo option
    parser.add_argument("-e", "--echo", nargs="+", action="store", help="treat each ARG as an input line \n")
    # Adding --repeat option
    # Stores true or false
    parser.add_argument("-r", "--repeat", action="store_true", dest="repeat", help="output lines can be repeated \n")
    arguments = parser.parse_args()
    # Checking if echo was provided as on option
    if arguments.echo != None:
        text = arguments.echo
    # Checking if file was provided as an argument
    elif arguments.file != None:
        text = arguments.file.readlines()
    # If no input is provided, function cannot run successfully
    else:
        # Print error statement
        parser.error("No Input!")
    if isinstance(arguments.count, int):
        # Checking if repeat was on or off
        if not arguments.repeat and arguments.count > len(text):
            arguments.count = len(text)
        # This implies argument is not nulll and of integer form
        if arguments.count < 0:
            # This should be disallowed as this is an invalid case
            parser.error("negative count: {0}".format(arguments.count))

        # Actual shuffling occurs in this loop
        for i in range(0, arguments.count):
            # Checking if repeat was on or off
            if not arguments.repeat:
                # Calls the random function to do the shuffling
                current = random.choice(text)
                if arguments.echo:
                    # If echo was specified then print to screen
                    print(current)
                else:
                    # Else print to whatever the standard output is
                    sys.stdout.write(current)
                del text[(text.index(current))]
            else:
                # Sets current to a random choice from the text
                current = random.choice(text)
                if arguments.echo:
                    print(current)
                else:
                    sys.stdout.write(current)
    elif arguments.count == None:
        # Number of lines to be processed was not specified and hence go through all
        if arguments.repeat:
            # If repeat option is enabled then do not ever break out and hence run into an infinite loop
            while True:
                current = random.choice(text)
                if arguments.echo:
                    print(current)
                else:
                    sys.stdout.write(current)
        for i in range(0, len(text)):
            # If repeat is option is enabled
            if not arguments.repeat:
                # Current line is set to a random line from the text
                current = random.choice(text)
                if arguments.echo:
                    print(current)
                else:
                    sys.stdout.write(current)
                del text [(text.index(current))]
    else:
        # Count is unknown, throw error
        parser.error("invalid count: {0}".
                     format(arguments.count))


if __name__ == "__main__":
    main()

