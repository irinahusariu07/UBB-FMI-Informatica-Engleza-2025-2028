"""
Where i have the student class related services
"""
from src.domain.lab_planner import Student
from src.testing.validations import StudentValidation

class StudentService:
    def __init__(self, student_repo, grade_repo):
        """
        :param student_repo: repository for Student obj
        :param grade_repo: repository for Grade obj
        """
        self.student_repo = student_repo
        self.grade_repo = grade_repo

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
        self.student_repo.add(student)

    def remove_student(self, student_id):
        """
        Remove a student
        :param student_id: the student id for the student to remove
        Also removes their assignments (grades)
        """
        # Remove all the students grades
        for grade in self.grade_repo.list_all():
            if grade.student_id == student_id:
                self.grade_repo.remove(grade.student_id, grade.assignment_id)

        # Remove student
        self.student_repo.remove(student_id)

    def update_student(self, student_id, name, group):
        """
        Update a student
        :param student_id: student id
        :param name: student name - may be modified
        :param group: student group - may be modified
        """
        student = Student(student_id, name, group)
        StudentValidation.validate(student)
        self.student_repo.update(student)

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




