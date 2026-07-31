class Address:
    def __init__(self, addr_id, name, x, y):
        self.__id = addr_id
        self.__name = name
        self.__x = x
        self.__y = y

    def get_id(self):
        return self.__id

    def get_name(self):
        return self.__name

    def get_x(self):
        return self.__x

    def get_y(self):
        return self.__y

    def __str__(self):
        return f"Address {self.__id} {self.__name} at ({self.__x},{self.__y})"