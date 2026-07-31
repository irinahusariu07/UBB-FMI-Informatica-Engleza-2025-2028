"""
The Memory Repo
"""
from src.domain.lab_planner import Student, Assignment, Grade
from src.errors import RepositoryError

class MemoryStudentRepo:
    def __init__(self):
        self.students = {}
        #the key from dictionary is the ID and the values are the student objects

    def add(self, student: Student):
        """
        Add a student to the memory repo
        :param student: the student object
        """
        if student.student_id in self.students:
            raise RepositoryError(f"Student with ID {student.student_id} already exists")
        self.students[student.student_id] = student

    def remove(self, student_id):
        """
        Remove a student from the memory repo
        :param student_id: the student ID to remove
        """
        if student_id not in self.students:
            raise RepositoryError(f"Student with ID {student_id} does not exist")
        del self.students[student_id]

    def update(self, student: Student):
        """
        Update a student from the memory repo
        :param student: the student object
        """
        if student.student_id not in self.students:
            raise RepositoryError(f"Student with ID {student.student_id} does not exist")
        self.students[student.student_id] = student #in dictionar, la studentul student.student_id stores o alta chestie

    def list_all(self):
        """
        List all students in the memory repo
        :return: the list of students
        """
        return list(self.students.values()) #dict.values() = the objects inside dict

    def find_by_id(self, student_id):
        """
        Find a student from the memory repo by ID
        :param student_id: the student ID to find
        :return: the student object with the given id
        """
        return self.students.get(student_id, None) #dict.get(key, what to return if doesnt exist)


class MemoryAssignmentRepo:
    def __init__(self):
        self.assignments = {}

    def add(self, assignment: Assignment):
        """
        Add a assignment to the memory repo
        :param assignment: the assignment object
        """
        if assignment.assignment_id in self.assignments:
            raise RepositoryError(f"Assignment with ID {assignment.assignment_id} already exists")
        self.assignments[assignment.assignment_id] = assignment

    def remove(self, assignment_id):
        """
        Remove a assignment from the memory repo
        :param assignment_id: the assignment ID to remove
        """
        if assignment_id not in self.assignments:
            raise RepositoryError(f"Assignment with ID {assignment_id} does not exist")
        del self.assignments[assignment_id]

    def update(self, assignment: Assignment):
        """
        Update a assignment from the memory repo
        :param assignment: the assignment object
        """
        if assignment.assignment_id not in self.assignments:
            raise RepositoryError(f"Assignment with ID {assignment.assignment_id} does not exist")
        self.assignments[assignment.assignment_id] = assignment

    def list_all(self):
        """
        List all assignments in the memory repo
        :return: the list of assignments
        """
        return list(self.assignments.values())

    def find_by_id(self, assignment_id):
        """
        Find a assignment from the memory repo by ID
        :param assignment_id: the assignment ID to find
        :return: the assignment object with the given id
        """
        return self.assignments.get(assignment_id, None)

class MemoryGradeRepo:
    def __init__(self):
        #store grades in a dict
        self.grades = {}

    def add(self, grade: Grade):
        """
        Add a grade to the memory repo
        :param grade: the grade object
        """
        key = (grade.student_id, grade.assignment_id)
        if key in self.grades: #daca exista deja o nota la studentul respectiv la acest assignment
            raise RepositoryError(f"Grade for student {grade.student_id} and assignment {grade.assignment_id} already exists")
        self.grades[key] = grade

    def remove(self, student_id, assignment_id):
        """
        Remove a grade from the memory repo
        :param student_id: the student ID for the grade to remove
        :param assignment_id: the assignment ID for the grade to remove
        """
        key = (student_id, assignment_id)
        if key not in self.grades:
            raise RepositoryError(f"Grade for student {student_id} and assignment {assignment_id} does not exist")
        del self.grades[key]

    def update_grade(self, student_id, assignment_id, grade_value):
        key = (student_id, assignment_id)
        if key not in self.grades:
            raise RepositoryError(f"No assignment {assignment_id} assigned to student {student_id}")

        grade_obj = self.grades[key]
        if grade_obj.grade_value is not None:
            raise RepositoryError(f"Student {student_id} already graded for assignment {assignment_id}")

        grade_obj.grade_value = grade_value

    def list_all(self):
        """
        List all grades in the memory repo
        :return: the list of grades
        """
        return list(self.grades.values())

    def find_by_ids(self, student_id, assignment_id):
        """
        Find a grade from memory repo by student ID and assignment ID
        :param student_id: student ID for the grade to find
        :param assignment_id: assignment ID for the grade to find
        :return: the grade object with the given key
        """
        return self.grades.get((student_id, assignment_id), None)
