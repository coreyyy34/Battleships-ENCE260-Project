Battleships

2 player game where players take turns at attempting to hit the other players battleships first player to sink all the other players ships wins

Authors
Corey Hines
Ethan Field

Building and Loading the Game
Open terminal and navigate to filder you wish to install game to
Run command: git clone git clone https://eng-git.canterbury.ac.nz/ence260-2024/group_337.git
Plug in UCFK4 into usb
Run commend: make program
Game will start on UCFK4

How to Play
Taking turns players will try to hit their opponents ship the goal is to sink all the other players ships first
Each player controls the directional button to select a target on the board
It is your turn when the blue LED is off and the opponents turn when the LED is on

Selecting Ship Layout
Move directional button left or right to select from 5 predefined boards press down to select
Note: Board 0 is a quick test layout   

Sending a Shot
Use the directional button to move the slow flashing light accross opponents board press down to fire
Previous shots will be displayed as fast flashing for hits and static for misses
If hit will be notified by feedback light and corresponding message
Same for miss but no light just message

Winning/Losing
To win have to sink you opponents ships before they sink yours
All boards have equal ships bar board 0
Upon winning victory message will appear and game will transition to victory state
Upon losing lose message will appear and game will transition to loss state