"""
This is where i define the domains - students, assignments, grades
"""

class Student:

    def __init__(self, student_id, name, group):
        self._student_id = student_id
        self._name = name
        self._group = group

    @property
    def student_id(self):
        return self._student_id

    @property
    def name(self):
        return self._name

    @property
    def group(self):
        return self._group

    @name.setter
    def name(self, new_name):
        self._name = new_name

    @group.setter
    def group(self, new_group):
        self._group = new_group

    def __str__(self):
        """
        The string interpretation for my student
        :return: Student id, name and group
        """
        return f"Student ID: {self._student_id}, Name: {self._name}, Group: {self._group}"

class Assignment:

    def __init__(self, assignment_id, description, deadline):
        self._assignment_id = assignment_id
        self._description = description
        self._deadline = deadline

    @property
    def assignment_id(self):
        return self._assignment_id

    @property
    def description(self):
        return self._description

    @property
    def deadline(self):
        return self._deadline

    @description.setter
    def description(self, new_description):
        self._description = new_description

    @deadline.setter
    def deadline(self, new_deadline):
        self._deadline = new_deadline

    def __str__(self):
        """
        The string interpretation for my assignment
        :return: Assignment id, description, deadline
        """
        return f"Assignment ID: {self._assignment_id}, Description: {self._description}, Deadline: {self._deadline}"


class Grade:

    def __init__(self, grade_value, student_id, assignment_id):
        self._grade_value = grade_value
        self._student_id = student_id
        self._assignment_id = assignment_id

    @property
    def assignment_id(self):
        return self._assignment_id

    @property
    def student_id(self):
        return self._student_id

    @property
    def grade_value(self):
        return self._grade_value

    @grade_value.setter
    def grade_value(self, new_grade):
        self._grade_value = new_grade

    def __str__(self):
        """
        The string interpretation for my grade
        :return: The grade, student id, and assignment id
        """
        return f"Student ID: {self._student_id}, Assignment: {self._assignment_id}, Grade Value: {self._grade_value}"












