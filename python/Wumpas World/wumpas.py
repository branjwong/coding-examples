# wumpas.py
# Assignment 2: The Wumpus World
# Brandon J Wong

class Node:
	def __init__(self, init_state, problem, node, action, root):
		if root == True:
			self.state = init_state
			self.parent = 0
		else:

# *******	These two statements right here are the sole reason why I wasn't able to complete this assignment. "You can't, for the same reason you can't allocate and free memory yourself and can't cast (as in "let's reinterpret this chunk of memory as if it looked like this") things: Dealing with memory on this level is deemed to error-prone, unimportant and automatable to be included in the language."

# http://stackoverflow.com/questions/5830179/how-to-assign-a-memory-address-to-a-variable-in-python

			self.state = node.state 		# first self.state gets BINDED to node.state
			self.parent = node
			
#			print self.state.getCoord()
#			print self.parent.state.getCoord()

			if action == "left":
				self.state.x = self.state.x - 1		# then any of these changes to self.state causes a change to node.state as well.
			elif action == "down":
				self.state.y = self.state.y - 1		# then any of these changes to self.state causes a change to node.state as well.
			elif action == "up":
				self.state.y = self.state.y + 1		# then any of these changes to self.state causes a change to node.state as well.
			elif action == "right":
				self.state.x = self.state.x + 1		# then any of these changes to self.state causes a change to node.state as well.

#			print self.state.getCoord()
#			print self.parent.state.getCoord()

#		# test to see if child dies
#		if problem != 0:
#			x = self.state.x
#			y = self.state.y
#			if problem.env[x][y] == "Wumpus" or problem.env[x][y] == "Pit":
#				self.state.alive_status = "dead"
 

# builds the problem from the text file
# print_env(): prints problem (the wumpus world board) to std.io
# get_env(): returns the environment matrix
class Problem:
	def __init__(self, f):
		# build the problem environment
		self.env = self.build_env(f)
		# initial state is where the player starts
		self.initial_state = State(coord(1),coord(1), "alive", "none", "in")
		self.actions = self.get_actions(self.initial_state)
		return

	# parses wumpax.txt into (elmt, (x,y)) tuples into a list called txt
	# elmt is one of [gold, wumpus, pit]
	# x,y are the x- and y-coordinates of each type
	def parse_txt(self, f):
		txt = []
		for i in range(5):
			txt.append(f.readline())
		for i in range (5):
			txt[i] = txt[i].split('=')
			txt[i][1] = txt[i][1].split(',')
		return txt

	def build_env(self, f):
		txt = self.parse_txt(f)
		# note this builds a 4x4 board with dimensions 0 -> 3, 0 -> 3
		env = [['empty' for i in range(4)] for j in range(4)]
		
		# assuming that there are 5 lines in the txt file, or 5 things on the board
		for i in range(5):
			x = coord(int(txt[i][1][0]))
			y = coord(int(txt[i][1][1]))
			elmt = txt[i][0]
			env[x][y] = elmt
		env[coord(1)][coord(1)] = "Start"
		return env

	def print_env(self):
		for i in reversed(range(4)):
			print i,
			for j in range(4):
				print '\t' + self.env[j][i],
			print '\n'
		for i in range(4):
			print "\t",
			print i,
		print '\n'
		return

#	def get_env(self):
#		return self.env

	def get_initial_state(self):
		return self.initial_state

	# determine whether the current state is at the goal
	def goal_test(self, state):
		x = state.x
		y = state.y
		if self.env[x][y] == "Gold":
			result = True
		else:
			result = False
		return result

	def get_actions(self, state):
		actions = []
		# print "DEBUG4: Actions are being got!"
		if state.gold_state != "Gold" and self.env[state.x][state.y] == "Gold":
			# print "DEBUG5: Pickup Action Recognised!"
			actions.append("pickup")
		if state.x - 1 >= coord(1):
			actions.append("left")
			# print "DEBUG6: Left Action Recognised!"
		if state.y - 1 >= coord(1):
			actions.append("down")
			# print "DEBUG6: Down Action Recognised!"
		if state.y + 1 <= coord(4):
			actions.append("up")
			# print "DEBUG6: Up Action Recognised!"
		if state.x + 1 <= coord(4):
			actions.append("right")
			# print "DEBUG6: Right Action Recognised!" 
		return actions
	
	
class State:
	def __init__(self, x, y, alive_state, gold_state, cave_state):
		self.x = x
		self.y = y
		self.alive_state = alive_state
		self.gold_state = gold_state
		self.cave_state = cave_state
		return

#	# checks to see if the player can move in that direction, then moves	
#	def move(self, direction):
#		if direction == "left":
#			if self.x > coord(1):
#				self.x = self.x - 1
#			else:
#				print "~: Error, can't move left."
#		if direction == "down":
#			if self.y > coord(1):
#				self.y = self.y - 1
#			else:
#				print "~: Error, can't move down."
#		if direction == "up":
#			if self.y < coord(4):
#				self.y = self.y + 1
#			else:
#				print "~: Error, can't move up."
#		if direction == "right":
#			if self.x < coord(4):
#				self.x = self.x + 1
#			else:
#				print "~: Error, can't move right."
#		return

	def getCoord(self):
		return (self.x, self.y)

#	def checkGold(self, env):
#		if env[self.x][self.y] == "Gold":
#			self.gold_state = "Acquired"
#			# print "~: Gold Acquired!"
#			result = True
#		else: 
#			# print "~: No gold here, let's keep looking!"
#			result = False
#		return result

#	def leaveCave(self):
#		if self.x == coord(1) and self.y == (1):
#			self.cave_state = "Out"
#		else:
#			print "~: Error, can't leave cave."
#		return
		
def coord(x):
	return x - 1

# returns a solution or failure
def breadth_first_search(problem):
	# node <- a node with STATE = problem.INITIAL-STATE, PATH-COST = 0
	# node: __init__(self, state, problem, node, action)
	node = Node(problem.get_initial_state(), 0, 0, 0, True)

	print_current_path(node)

	# if problem.GOAL-TEST(node.STATE) then return SOLUTION(node)
	if problem.goal_test(node.state): return node
	# frontier <_ a FIFO queue with node as the only element
	frontier = []
	frontier.append(node)
	# explored <- an empty set
	explored = []

	# loop do
	while True:
		print "~:~"
		# print "DEBUG1: ",
		# print_current_frontier(frontier)

		# if EMPTY?(frontier) then return failure
		if frontier == []: return "failure"
		# node <- POP(frontier), chooses shallowest node in frontier
		node = frontier.pop()
		# add node.STATE to explored
		explored.append(node.state)

		actions = problem.get_actions(node.state)
		# print "DEBUG3: ",
		# print actions

		# for each action in problem.ACTIONS(node.STATE) do
		for action in actions:
			raw_input()
			# child <- CHILD-NODE(problem, node, action)
			child = Node(0, problem, node, action, False)

			print_current_path(child)
			print_current_frontier(frontier)
			
			# print "DEBUG2: ",
			# print child.state not in explored

			# if child.STATE is not in explored or frontier then
			if child.state not in explored: # or child.state not in frontier:	
				
				# if problem.GOAL-TEST(child.STATE) then return SOLUTION(child)
				if problem.goal_test(child.state): return child
				# frontier <- INSERT(child, frontier)
				frontier.append(child)


def print_solution(solution):
	if solution == "failure":
		print "Search failed."	
	else:
		print node.state
		while node.parent != 0:
			node = node.parent
			print node.state
	return

def print_current_path(node):
	print "CURRENT PATH:"
	print_path(node)
	return

def print_path(node):
	path = []
	path.append(node.state.getCoord())
	while node.parent != 0:
		node = node.parent
		path.append(node.state.getCoord())
	print path.pop(),
	for n in path:
		print " -> ",
		print path.pop(),
	print
	return

def print_current_frontier(frontier):
	print "FRONTIER INFORMATION:"
	for node in frontier:
		print '\t' + "Name:",
		print node.state.getCoord(),
		print '\t',
		print_path(node)

f = open('possible.txt','r')
problem = Problem(f)

print "~: Welcome to the Wumpus World!"
print "~: Generating Wumpus World...\n"

problem.print_env();


print "~: Searching for Optimal Route..."

solution = breadth_first_search(problem)

print_solution(solution)

