# Get the Google trends from RSS feed with curl in C++
This program retrieve RSS feed from Google Trends.
It is written in C++ with curl library.


## Requirements:
In order to compile the code, you need libcurl installed.


## How to run:
1. Compile the code with `make`,
2. Run the program with `./trends_google`.

Note: if the RSS feed url changed, you may need to modify `config.hpp`.


## Output example:
`$ ./trends_google`
```
Daily Search Trends
Eric Black Jr
Golden Globes 2019 date
Super Bowl 2019 time
Kliff Kingsbury
Colts
NFL games today
NFL schedule
Queen Elizabeth death
Ravens
Football
Drake
Warriors vs Kings
Frank Reich
Booger McFarland
FA Cup
ESPN NFL
Kendall Jenner
Bryce Turner
NFL football
Football today
```


## How it works (very simple):
1. It fetches RSS page with curl,
2. It prints out "title" section of the XML.


## Note:
https://support.google.com/trends/answer/6248105?hl=en#trendingsearches

`Daily Search Trends highlights searches that jumped significantly in traffic among all searches over the past 24 hours and updates hourly. These search trends show the specific queries that were searched, and the absolute number of searches made.`

