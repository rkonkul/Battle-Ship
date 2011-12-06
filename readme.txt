Ryan Konkul - rkonku2
Scott Prentice - sprent2
CS 340
Project 5: Battle Ship
12/1/2011

Development status: Fully functional
Errors: None
Known issues: None
OS: Windows 7 x64
Qt Creator 2.3.1 based on Qt 4.7.4

The design decision made regarding how the two instances talk to each other is that once they are connected, they are on equal level. Each maintains their own data and therefore sends and receives messages the same way. The other major design decision was how to allow the player to place ships. The player may enter in a row and column in boxes and the program determines whether the ship placement is correct or not. If it is, a temporary ship is displayed and remains if user clicks the set ship button or goes away if the row or column box is changed.

When the application starts, two grids of Buttons are constructed. The top row and left most column are given either a number or letter to signify which row and column the player selects. The rest are given water icons. Before the players may begin setting ships, the connection between the two must be established. One determines itself to be the server. The client then connects to the server by supplying the IP and the Port number. 

When connected, the players may begin to place ships down. The user supplies a row and column. The order the ships are placed in are Cruiser, Battle Ship, Destroyer, Submarine, Patrol Boat. When given a row, col, the program checks if the input is in bounds. If it is, it either draws the ship in the right or down direction. If the input is size_of_ship - 1 or less close to the right boundary, the ship is drawn from right to left. If close to the down direction, the ship is drawn from bottom up. 

When one player has set their ships, they set themselves as the first player to begin. When the second player finishes, they determine whether the other player is waiting and set themselves as the second player. The players then take turns taking shots at the opponent board. When the program gets a button click, and when the state is PLAYER_TURN, a message is sent of the form S row col to Send the row and col to the other player. Also, the row, col is saved for when the message of hit or miss comes back. When the player receives a message and is in the state OPPONENT_TURN, the message is checked to begin with 'S'. If it is not an error occurred. Otherwise, the button at row, col is checked if there is a ship there. If there is, a message containing 'H' is sent. Otherwise 'M' is sent. When the player receives a message and in state OPPONENT_TURN, if 'H' the ship is marked with a hit. If it is a miss the button is marked with a miss icon. The game ends when either player counts 17 hits. When 17 hits are counted, the buttons are disabled and the winner is displayed. 

