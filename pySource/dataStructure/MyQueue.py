class MyQueue:
    def __init__(self):
        self.__queue = []
    def push(self,x):
        self.__queue.append(x)
    def pop(self):
        self.__queue.pop(0)
    def front(self):
        return self.__queue[0]
    def empty(self):
        return self.__queue == []
    def size(self):
        return len(self.__queue)