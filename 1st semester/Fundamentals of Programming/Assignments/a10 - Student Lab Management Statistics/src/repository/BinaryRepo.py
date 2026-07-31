"""
The BinaryFile Repo
"""
from src.domain.lab_planner import Student, Assignment, Grade
from src.errors import RepositoryError
import pickle

class BinaryStudentRepo:
    def __init__(self, filename):
        self.filename = filename
        self.students = {}
        self.load_from_file()

    def load_from_file(self):
        """
        Reads from a binary file
        """
        try:
            with open(self.filename, "rb") as f:
                self.students = pickle.load(f)

        except FileNotFoundError:
            self.students = {}
            with open(self.filename, "wb") as f:
                pass

    def save_to_file(self):
        """
        Writes to a binary file
        """
        with open(self.filename, "wb") as f:
            pickle.dump(self.students, f)

    def add(self, student: Student):
        """
        Adds a student
        :param student: the student to add
        """
        if student.student_id in self.students:
            raise RepositoryError(f"Student with ID {student.student_id} already exists")
        self.students[student.student_id] = student
        self.save_to_file()

    def remove(self, student_id):
        """
        Removes a student
        :param student_id: the student ID to remove
        """
        if student_id not in self.students:
            raise RepositoryError(f"Student with ID {student_id} does not exist")
        del self.students[student_id]
        self.save_to_file()

    def update(self, student: Student):
        """
        Updates a student
        :param student: the student object to update
        """
        if student.student_id not in self.students:
            raise RepositoryError(f"Student with ID {student.student_id} does not exist")
        self.students[student.student_id] = student
        self.save_to_file()

    def list_all(self):
        """
        Lists all students
        :return: list of students
        """
        return list(self.students.values())

    def find_by_id(self, student_id):
        """
        Finds a student by ID
        :param student_id: the student ID to find
        :return: the student or None
        """
        return self.students.get(student_id, None)

class BinaryFileAssignmentRepo:
    def __init__(self, filename):
        self.filename = filename
        self.assignments = {}
        self.load_from_file()

    def load_from_file(self):
        """
        Reads from a binary file
        """
        try:
            with open(self.filename, "rb") as f:
                self.assignments = pickle.load(f)
        except FileNotFoundError:
            self.assignments = {}

    def save_to_file(self):
        """
        Writes to a binary file
        """
        with open(self.filename, "wb") as f:
           pickle.dump(self.assignments, f)

    def add(self, assignment: Assignment):
        """
        Adds a assignment
        :param assignment: the assignment object to add
        """
        if assignment.assignment_id in self.assignments:
            raise RepositoryError(f"Assignment with ID {assignment.assignment_id} already exists")
        self.assignments[assignment.assignment_id] = assignment
        self.save_to_file()

    def remove(self, assignment_id):
        """
        Removes a assignment
        :param assignment_id: the assignment ID to remove
        """
        if assignment_id not in self.assignments:
            raise RepositoryError(f"Assignment with ID {assignment_id} does not exist")
        del self.assignments[assignment_id]
        self.save_to_file()

    def update(self, assignment: Assignment):
        """
        Updates a assignment
        :param assignment: the assignment object to update
        """
        if assignment.assignment_id not in self.assignments:
            raise RepositoryError(f"Assignment with ID {assignment.assignment_id} does not exist")
        self.assignments[assignment.assignment_id] = assignment
        self.save_to_file()

    def list_all(self):
        """
        Lists all assignments
        :return: list of assignments
        """
        return list(self.assignments.values())

    def find_by_id(self, assignment_id):
        """
        Finds a assignment by ID
        :param assignment_id: the assignment ID to find
        :return: the assignment or None
        """
        return self.assignments.get(assignment_id, None)


class BinaryGradeRepo:
    def __init__(self, filename):
        self.filename = filename
        self.grades = {}
        self.load_from_file()

    def load_from_file(self):
        """
        Reads from a binary file
        """
        try:
            with open(self.filename, "rb") as f:
                self.grades = pickle.load(f)
        except FileNotFoundError:
            self.grades = {}

    def save_to_file(self):
        """
        Writes to a text file
        """
        with open(self.filename, "wb") as f:
            pickle.dump(self.grades, f)

    def add(self, grade: Grade):
        """
        Adds a grade
        :param grade: the grade object to add
        """
        key = (grade.student_id, grade.assignment_id)
        if key in self.grades:
            raise RepositoryError(f"Grade for student {grade.student_id} and assignment {grade.assignment_id} already exists")
        self.grades[key] = grade
        self.save_to_file()

    def remove(self, student_id, assignment_id):
        """
        Removes a grade
        :param student_id: the student ID for the grade to remove
        :param assignment_id: the assignment ID for the grade to remove
        """
        key = (student_id, assignment_id)
        if key not in self.grades:
            raise RepositoryError(f"Grade for student {student_id} and assignment {assignment_id} does not exist")
        del self.grades[key]
        self.save_to_file()

    def list_all(self):
        """
        Lists all grades
        :return: the list of grades
        """
        return list(self.grades.values())

    def find_by_ids(self, student_id, assignment_id):
        """
        Finds a grade by IDs of student and assignment
        :param student_id: the student ID for the grade to find
        :param assignment_id: the assignment ID for the grade to find
        :return: the grade or None
        """
        return self.grades.get((student_id, assignment_id), None)

    def update_grade(self, student_id, assignment_id, grade_value, from_undo = False):
        key = (student_id, assignment_id)
        grade_obj = self.grades.get(key)
        if not grade_obj:
            raise RepositoryError("Grade does not exist")
        if grade_obj.grade_value is not None and not from_undo:
            raise RepositoryError("Grade already assigned")

        grade_obj.grade_value = grade_value
        self.save_to_file()