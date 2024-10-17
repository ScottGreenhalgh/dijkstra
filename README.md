# Algorithms and Numerical Methods

### Design

When designing the application, I decided to breakdown the requirements from the brief as best I could, finding the most methodical way of completing the task while also producing the desired result. Knowing that the following was stated in the brief: “Your program does not need an interactive user interface (and certainly not a GUI)”, I quickly decided that a console-based application would result in the most productive method of completing the task while still maintaining the required criteria. I then brainstormed possible ways of displaying the destinations so that it would still be legible and easy to understand. Here I took inspiration from railway stations, where they have a list of destinations located on a board separated line by line for user’s readability. Travelers can easily distinguish destinations using this information so I thought using a similar design would be appropriate. At the planning stage I imagined the resulting destinations would display in the following way:

```
city1
    | distance
city2
    | distance
city3

Total Distance: distance
```

Using the format shown above, additional subsequent cities that are passed through can be added below with total distance as a sum of all the listed distances. With the rough output decided upon, I now needed to decide on how the user would interact with the data. I decided that if the user manually entered their desired starting and end locations, it would be much more user friendly than navigating a predetermined list. Therefore, I decided that a basic request for user inputs at the start of the application would work the best. At this stage I envisioned that the user would type their two destinations, one after the other. Here a check for spelling would be required and a re-request for the name would be needed if the input is incorrect. During this pre-application design stage, I envisioned that this would look similar to the following:

```
Enter your starting location:
<user types here>
Enter your ending location:
<user types here>

<output here>
```

Now the overall aesthetic has been decided on, the next thing that I needed to consider was whether or not any other important files needed to be loaded. At that time I couldn’t think of any necessary files, but for future projects this is an important consideration. To incorporate the previously mentioned ideas, I plan on having the provided text file (ukcities.txt) with all the locations and distances to be loaded and formatted ready for use by an algorithm. In this design phase I hadn’t quite decided which algorithm I was going to use to complete this task but I was most likely going to be the one suggested in the brief. Therefore, I could conclude that I would try implement the algorithm following the development of my text document reader/formatter.

With the design ideas summarised above I moved onto the construction phase. I believed this was the most appropriate approach to take as the interface is kept relatively simple, intuitive and easy to use, something I consider a basic requirement for an application that the masses could use.

### Algorithm

As the brief suggested, the algorithm of choice was Dijkstra’s algorithm. In the pre-production phase I envisioned that I would implement this algorithm after I created a method of reading the included ukcities.txt file and order the values in a way that I can manipulate and order the information. To do this I decided that placing the data in a 21 by 21 matrix was the most appropriate method of handling this information. By assigning each city a value up to 21, which will correspond to a specific location in the matrix when two cities are given. The value at that location of the matrix will be assigned the distance value between those two locations in the ukcities.txt file. For cities that travel to themselves, the value infinite value will be assigned. Therefore, the entire diagonal from top left to bottom right of the matrix will all be infinite and can therefore be ignored. Alongside this travel distances that don’t have a corresponding value given via the text document will also be assigned an infinite value.
The ukcities.txt file that has been attached is tab-delimited, which makes the process of separating the data apart per line much easier. Using \t in C allows the program to manipulate these tabs to acknowledge that these characters should be handled separately. This was very useful information when developing a method of reading and formatting this information. This was used in the application on line 159.

To briefly summaries how the algorithm will work for my particular implementation. The adjacency matrix will include all the cities organised into an array list where all the distances values are placed into an organised list along with infinite values filling in the gaps. These infinite values are defined as 9999 at the beginning of the application on line 7. When debugging the application, the output can be found under debug.png.

The image (debug.png) shows how each city to city distance is orientated inside a large 21 by 21 matrix. All the values that don’t correspond to the supplied 40 original values were assigned the infinite value.

The citykey is the part of the algorithm that will filter out the 21 cities from the 80 different city entries within the text document. Looping through the cities, zero to 40 using POINT_AMOUNT (defined at the beginning of my application) and cycling over twice, one for each of the cities on either side of the matrix. If Hull and York were at this location, 60 will be inserted in the previously appointed zero location and it will continue to cycle over.

#### Data Structure

A single data structure was used during the creation of the application and is very basic. This is located on lines 10-14 and temporarily holds the data for the travel distances between two locations. I didn’t see the need to include any further structures for the purposes of this application and the desired use case.

#### Computational Efficiency

The application is using a method called string token. There are arguably faster methods of creating a similar application to the one that I have using an alternative method, however I thought this would be the most simplistic method of completing the task in as minimal lines as possible. I also believe that string token is efficient enough for this particular usage that any slowdown would be negligible enough to not affect the users experience. With a sample size of one, it’s hard to comment on the overall efficiency of this application in relation to similar apps. What I can comment on is the small time delay (less than a 10th of a second, but still much slower than the remainder of the app) that is present upon launching the application where the text file is being read initially. Efficiency does increase once the data is loaded (from text file `ukcities.txt`) That preloaded information is then used to create the city key and adjacency matrix. This therefore means that checking for the text document more than once isn’t a problem as it will be loaded into memory instead, a much faster storage method. Efficiency in this context refers to the overall responsiveness of the application.

#### Memory Requirements

Memory management wasn’t a heavy concern when developing this application as there isn’t an overly large amount of information that requires storage, a few kilobytes maximum. Knowing this there is currently no memory dumping code in the application as it uses such miniscule amounts of memory to begin with that, I didn’t see a need to include this. If I had to comment on something that could potentially help with memory management, the arrays used are limited to the size they need to be, they’re not dynamic so they won’t resize themselves using unnecessary amounts of resources.

#### Testing the application

After the construction phase had been completed, I directed my attention towards testing, to see if the values that I was obtaining were the values I desired. I would also need to make sure that the locations that were selected were the using the most efficient path as possible. The best possible way I could think of doing this was to allow the application to output what locations were travelled through so I could manually tally these numbers myself and compare the values I calculate with the values the application produced. Needless to say, the numbers in all instances tallied correctly.
The next most important part of the application was checking whether or not the selected route was the most efficient out of all the possible selected locations. Checking this took much longer as I needed to make sure that each destination was taking the shortest route. Again, manually scrolling through the text document (and using ctrl F) was my method of choice. From what I can see, the algorithm is selecting the shortest values in all scenarios, however the vast number of possible combinations and my inefficient testing method I had chosen leaves the possibility that a longer route could be taken for some obscure rough that I hadn’t yet tested.

I think it’s important to note that I’ve included checks for correct spelling into the application, this will warn the user when the inputs an incorrect location name that doesn’t exist. This is however case sensitive, but this will still correctly find the location if the user puts multiple spaces before or after the input on accident. Alongside this, I’ve added functionality for the user to select another two locations after the first set of locations have been processed. This allows the program to restart itself an indefinite amount of times if multiple different selections want to be checked by the user.

A compilation of the tested locations, along with the calculated results can be found below:

```
York -> Leeds -> Manchester
Total distance: 103
York -> Doncaster -> Sheffield -> Birmingham -> Oxford -> Reading
Total distance: 352
York -> Newcastle -> Carlisle -> Moffat -> Glasgow
Total distance: 370
York -> Leeds -> Blackpool
Total distance: 155
York -> Doncaster -> Sheffield -> Birmingham -> Bristol
Total distance: 345

Oxford -> Birmingham -> Manchester -> Liverpool -> Blackpool -> Carlisle
Total distance: 507
Oxford -> Northampton -> Leicester
Total distance: 129
Oxford -> Birmingham -> Sheffield -> Doncaster -> York -> Newcastle
Total distance: 444
Oxford -> Birmingham -> Manchester -> Liverpool
Total distance: 288

Glasgow -> Moffat -> Carlisle -> Blackpool -> Leeds
Total distance: 399
Glasgow -> Moffat -> Carlisle -> Blackpool -> Leeds -> Sheffield
Total distance: 452
Glasgow -> Moffat -> Carlisle -> Blackpool -> Liverpool -> Manchester -> Birmingham -> Oxford -> Reading
Total distance: 693
```

These outputs shown above are only displayed in the console. I decided that outputting to a further text document would cause needless bloat, especially considering the user will be required to input the information less than a second prior to the result being produced. This may be considered a design oversight but I believe it maintains the overall flow of the applications while still supplying the required results to the user.

The final construction of the application had some slight differences to the planned design. One was namely how the format in which the results are displayed in the console. I did maintain the list of locations however a multi-line output appeared unnecessary, especially for outputs with 10 passing locations.

The applications compiles with the minGW C Compiler using the C90 standard. All source code can be found within the `main.c` file. No header files were needed for this application.

Line 288 of the application was used in accordance with the original script, where a small segment of the code was borrowed and reorganised to fit my particular implementation (The Crazy Programmer, 2014).

#### References

The Crazy Programmer. (2014). Dijkstra's Algorithm in C - The Crazy Programmer. [online] Available at: https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html [Accessed 28 Jan. 2019].
