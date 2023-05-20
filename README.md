# most-common-words-in-discord
Command-line tool to find the most sent words in any Discord channel!

# What it does
It finds the most common words in a Discord channel and outputs the data it gathers (rank, word, # of occurences) into a CSV.

I wrote this because I was curious about the most common words in my friend's Discord server's main general. I tried writing something in python to parse the data, but the general has like 2.6 million messages in it so it was hella slow. So I started again in C++ and it pretty much works LOL. 

Most of what you see in its output is just gonna be common words, but it's really cool to check out the randomass words/neologisms that pop up with way more prevalence than you expect.

**Note: you might see a lot of errors!** rapidcsv is great but it doesn't correctly parse cells with newlines in them, which is awkward! I tried to add this functionality but i gave up ): My working solution is that whenever the program encounters a broken parsing, it just skips over it in the calculation. It's dumb and definitely not good coding practice, but it does work!


# Usage
In order to run this, you're gonna have to download Tyrrrz's [DiscordChatExporter](https://github.com/Tyrrrz/DiscordChatExporter). All you need to do is export your desired Discord channel as a CSV.

It's included with your download, but this also uses d99kris's [rapidcsv](https://github.com/d99kris/rapidcsv) library to parse data. My fork only adds some CLI output to make waiting for the command to finish more interesting.

The function that finds the most common words is adapted from a [Leetcode solution](https://leetcode.com/problems/top-k-frequent-elements/solutions/3235889/c-simple-and-efficient-solution-heap-priority-queue-hash-table/) by [Jaividyasagar](https://leetcode.com/Jaividyasagar/).

This would not have been possible with either of these projects, so please give them your support!

When you download, make sure to use the --recursive flag to get the submodule:
```
git clone --recursive https://github.com/chayagirl/most-common-words-in-discord.git
```

## Linux
To export the channel using DiscordChatExporter CLI:
```
dotnet DiscordChatExporter.Cli.dll export -t TOKEN -c CHANNEL -f csv -o FILENAME.csv
```
Once the CSV file is downloaded, you can run the Makefile to compile `parse-csv.cpp`. Then you can use the executable like this:
```
./parse-csv input.csv output.csv NUM_LINES TOP_K
```
`NUM_LINES` is the amount of lines you want to process, starting from the oldest message (so if you input 100 here then you will get the most common words in the first 100 messages ever sent in the general). **Set it to -1 to process all lines!** The CSV reader reads all lines into memeory regardless, so you might as well.

`TOP_K` defines how deep the most common words list will travel. For instance, if you input 10 here, you'll get the 10 most common words in the channel.

The system should display some completion info and then tell you it's Done! and then you can look at the file.

## Mac
IDK man. I don't have a Mac.

## Windows
You can use the GUI version of DiscordChatExporter if you want! And you can def compile this on Windows with MSVC or MinGW GCC, tho I haven't tried it. I'm sure you can figure out the specifics!