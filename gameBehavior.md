# Games States:

### State one:

Start button is visible on the game UI. Eventually, there will be a start button at the front of the game but we've not designed this yet. For now, no goals are selected. The LEDs on the pollen are just slowly pulsing on and off.

#### Possible User Interactions:
Action: User presses start button.

Result: If the user presses start a random goal is selected and the game begins

### State two:

The game waggle dance vibrational pattern plays directing a player to a goal pollen. The hexes trigger shorter pluses on the hexes looping back to the main line. If this was music, it would be a 1/4, 1/4, 1/4, whole whole whole, 1/4, 1/4, 1/4 rhythm.

#### Possible User Interactions:

Action: User selects the right pollen

Result: A success sound plays. A side of the hex in the middle comes on. A new pattern begins and the game loop chooses a new random goal. (this will have a total of 6 possible rounds)

Action: User selects the wrong pollen.

Result: A failure sound plays. The player gets another attemp to find the goal and no led on the strip is given to the player.

Data wise, I'd like to collect win and failed attempts in a file for later.

### State three:

#### End game on win:

Win possiblity
The LED strip is fully lit. And the game is complete.

For now just turn off all the motors and and play the win sound 3 times and then take the game back to the start state.

Note: We will have to think about a reward here - it could just be vibrational and the motors could make a pleased sound then go all off and the game could begin again and go back to the start state.

#### End game on lose:

After 6 failures, the game plays the lose sound three times, all the motors go off and the game goes back to the start state.

Note: It could be interesting to make an angry bee sound here. This is something to be designed.
