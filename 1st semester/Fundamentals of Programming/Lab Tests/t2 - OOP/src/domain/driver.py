class Driver:
    def __init__(self, name, x, y):
        self.__name = name
        self.__x = x
        self.__y = y

    def get_name(self):
        return self.__name

    def get_x(self):
        return self.__x

    def get_y(self):
        return self.__y

    def __str__(self):
        return f"{self.__name} at ({self.__x},{self.__y})"



