from collections import deque


class NodeQueue:

    def __init__(self):
        # deque performs better from left side of list compared to pop(0) on normal list
        self.items = deque([])

    def push(self, item):
        self.items.append(item)

    def pop(self):

        # if the stack is not empty
        if self.items:
            return self.items.popleft()

        else:
            None

    def stack_size(self):
        return len(self.items)

