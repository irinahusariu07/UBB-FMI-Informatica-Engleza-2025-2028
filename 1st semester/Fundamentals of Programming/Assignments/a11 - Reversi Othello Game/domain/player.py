"""
The player can either be human or computer
Since black starts, the human player should have black => the computer gets white
"""

class Player:
    def __init__(self, color:int, type:str):
        """
        Initialize the player
        :param color: the color of the player ---> -1 or 1
        :param type: human or computer
        """
        self.color = color
        self.type = type
