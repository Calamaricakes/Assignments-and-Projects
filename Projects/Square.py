from abc import ABC, abstractmethod


class Square(ABC):


    def __init__(self, horizontal, vertical):
        self.horizontal = horizontal
        self.vertical = vertical
        pass

    @abstractmethod
    def return_symbol(self):
        pass

    @abstractmethod
    def return_position(self):
        pass


class Path(Square):

    def __init__(self, horizontal, vertical):
        super().__init__(horizontal, vertical)
        self.symbol = '@'


    def return_symbol(self):
        return self.symbol

    def return_position(self):
        return self.horizontal, self.vertical


class Wall(Square):

    def __init__(self, horizontal, vertical):
        super().__init__(horizontal, vertical)
        self.symbol = '+'

    def return_symbol(self):
        return self.symbol

    def return_position(self):
        return self.horizontal, self.vertical


class Exit(Square):

    def __init__(self, horizontal, vertical):
        super().__init__(horizontal, vertical)
        self.symbol = '%'

    def return_symbol(self):
        return self.symbol

    def return_position(self):
        return self.horizontal, self.vertical


class Entry(Square):

    def __init__(self, horizontal, vertical):
        super().__init__(horizontal, vertical)
        self.symbol = '~'

    def return_symbol(self):
        return self.symbol

    def return_position(self):
        return self.horizontal, self.vertical


class Solution(Square):

    def __init__(self, horizontal, vertical):
        super().__init__(horizontal, vertical)
        self.symbol = 'o'

    def return_symbol(self):
        return self.symbol

    def return_position(self):
        return self.horizontal, self.vertical
