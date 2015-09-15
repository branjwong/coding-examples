# Java - "Witches, Witches, and Horcruxes"
CMPT 125
Fall 2012 Final Project
Instructor: Diana Cukierman
Completed by: Brandon Wong, Layla Trummer

## Description
	- In this project you are asked to implement an adventure game. The game is played by two wizards or witches (two players, where each player may be a program-simulated player or the user). The game unfolds on a “board” which is composed of a number of “cells” which are numbered areas where the players can land as they travel. The players start the game from cell #0 with some initial “life points”, and they travel aiming to collect seven (7) “horcruxes” that are dispersed in this different cells. (Just for you to know about this world: wizard-witches players are likely traveling with brooms or other magical means, horcruxes are common objects, but they contain parts of “Voldemort’s soul”. Voldemort is a very powerful and the most evil ever wizard2).  
	
	- The players need to collect and keep the horcruxes as they travel (we will assume that horcruxes will not harm the players as they keep them), and if any of the players gets to collect the 7 horcruxes he/she wins (and the game is over) as long as he/she remained alive during the travelling!

	- As may be expected, during their travelling players will face dangers, such as “dementors” (dark flying creatures who take away life points from the players) . Luckily, players also may find friendly “domestic elves” (magic creatures who will give life points back to players). It may be the case also that players help each other or attack each other, and/or rob each other horcruxes and/or life points, if they happen to land in the same cell! 

	- Therefore, during their travelling, players may lose and or gain life points, may be killed, may find and/or lose the horcruxes or not. Players may even encounter Voldemort himself, who will kill the poor player who lands in the cell where he is. If, on the other hand, “Dumbledore” is in that same cell at that same time, the player will be safe because Dumbledore will fight against Voldemort. (Dumbledore is a very powerful good wizard).

	- The horcruxes are placed in specific cells and stay there from the game start until they are picked up by some player (who will then carry the horcruxes with him/her). The various creatures and specific wizards (dementors, elves, Voldemort and Dumbledore) will also stay in the same cell from the start of the game till the end. However, notice that, after the player was attacked by the dementors there will be one less dementor remaining in the cell. 

	- Hence, (luckily for the players!) dementors will gradually diminish as the players visit the cells. On the other hand, unluckily for the players, players cannot know in advance where any of these creatures or specific wizards are, so, as they travel and arrive to a cell, they may be attacked or saved! 
	- The choice of where to place the 7 horcruxes , how many dementors and elves to place in the different cells and where to place Voldemort and Dumbledore will be done randomly, based in parameters (range limit values) that the user will provide before starting the game. The user will also be asked to provide initial life points for the wizard-witches-players up to a certain maximum of life points. (Fixed values may also be created for testing).

	- The way that program-simulated players move through the board is by throwing a die, which will allow to determine where the next cell is for the player based on the current position. Certain types of players however can choose to throw the die two (2) times in total, as explained in the detailed description. The “user” player on the other hand directly chooses which cell to move to, without rolling the die.

	- The game is over when one of the (or both) players die or when one of the players collected the seven horcruxes or until a certain maximum number of turns (the maximum value is defined by the user) took place. (One turn involves the travelling of one player).