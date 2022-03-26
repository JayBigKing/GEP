class Stack():
    def __init__(self):
        self.__stack = []
    def push(self,value):
        self.__stack.append(value)
    def pop(self):
        #反正用的list的pop，它里面有异常检测了
        self.__stack.pop()
    def top(self):
        return self.__stack[-1]
    def empty(self):
        return self.__stack == []
    def size(self):
        return len(self.__stack)
    def clear(self):
        self.__stack = []
