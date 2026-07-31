"""
Where i have the student class related services
"""
from unittest import result

from src.domain.lab_planner import Student
from src.errors import RepositoryError
from src.testing.validations import StudentValidation
from src.command_design_pattern.student_commands import AddStudentCommand, RemoveStudentCommand, UpdateStudentCommand



class StudentService:
    def __init__(self, student_repo, grade_repo, undo_manager):
        """
        :param student_repo: repository for Student obj
        :param grade_repo: repository for Grade obj
        """
        self.student_repo = student_repo
        self.grade_repo = grade_repo
        self.undo_manager = undo_manager

    # FIRST FUNCTIONALITY
    def add_student(self, student_id, name, group):
        """
        Add a new student
        :param student_id: student id
        :param name: student name
        :param group: student group
        """
        student = Student(student_id, name, group)
        StudentValidation.validate(student)
        cmd = AddStudentCommand(self.student_repo, student)
        self.undo_manager.execute(cmd)

    def remove_student(self, student_id):
        """
        Remove a student
        :param student_id: the student id for the student to remove
        Also removes their assignments (grades)
        """
        cmd = RemoveStudentCommand(self.student_repo, self.grade_repo, student_id)
        self.undo_manager.execute(cmd)


    def update_student(self, student_id, name, group):
        """
        Update a student
        :param student_id: student id
        :param name: student name - may be modified
        :param group: student group - may be modified
        """
        old_student = self.student_repo.find_by_id(student_id)
        if old_student is None:
            raise RepositoryError("Student not found")
        new_student = Student(student_id, name, group)
        StudentValidation.validate(new_student)

        cmd = UpdateStudentCommand(self.student_repo, old_student, new_student)
        self.undo_manager.execute(cmd)

    def list_students(self):
        """
        List all students
        :return: a list of all students
        """
        return self.student_repo.list_all()

    def find_student_byID(self, student_id):
        """
        Find student by ID
        :param student_id: the student id
        :return: the student with that id
        """
        return self.student_repo.find_by_id(student_id)

    def student_with_given_assignment(self, search_assignment_id):
        """
        All students with a given assignment, sorted descending by grade
        :param search_assignment_id: the given assignment id
        :return: a list o students with that assignment, sorted descending
        """
        students_list = []
        for g in self.grade_repo.list_all():
            if g.assignment_id == search_assignment_id and g.grade_value is not None:
                student = self.student_repo.find_by_id(g.student_id)
                students_list.append((student, g.grade_value))
        sorted_students = sorted(students_list, key=lambda grade_value: grade_value[1], reverse=True)
        return sorted_students


    def best_student_situation(self):
        """
        Computes the average of the grades of all graded assignments
        and shows the students in descending order
        """
        student_grades = {}
        for g in self.grade_repo.list_all():
            if g.grade_value is not None:
                if g.student_id not in student_grades:
                    student_grades[g.student_id] = [] # pt fiecare id student din dictionar am o lista cu note
                student_grades[g.student_id].append(g.grade_value)

        results = []
        # compute averages
        for student_id, grades in student_grades.items():
            avg = sum(grades) / len(grades)
            student = self.student_repo.find_by_id(student_id)
            results.append((student, avg))

        #sort descending
        results.sort(key=lambda grade_value: grade_value[1], reverse=True)
        return results





