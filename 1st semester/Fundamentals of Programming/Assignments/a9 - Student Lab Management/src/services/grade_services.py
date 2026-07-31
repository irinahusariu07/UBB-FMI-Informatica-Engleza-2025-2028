"""
Where i have the grade class related services
"""
from src.domain.lab_planner import Grade, Student, Assignment
from src.errors import RepositoryError
from src.testing.validations import GradeValidation
class GradeService:
    def __init__(self, grade_repo, student_repo, assignment_repo):
        self.grade_repo = grade_repo
        self.student_repo = student_repo
        self.assignment_repo = assignment_repo

    def grade_student(self, student_id, assignment_id, grade_value):
        """
        Grade a student for a given assignment
        :param student_id: student to grade
        :param grade_value: value of the grade
        :param assignment_id: assignment to grade
        """
        # Check if student exists
        student = self.student_repo.find_by_id(student_id)
        if not student:
            raise RepositoryError(f"Student with ID {student_id} not found")

        # Check if assignment exits
        assignment = self.assignment_repo.find_by_id(assignment_id)
        if not assignment:
            raise RepositoryError(f"Assignment with ID {assignment_id} not found")

        # Check if assignment was assigned (grade == None)
        grade_obj = self.grade_repo.find_by_ids(student_id, assignment_id)
        if not grade_obj:
            raise RepositoryError(f"Assignment with ID {assignment_id} not assigned to students")
        self.grade_repo.update_grade(student_id, assignment_id, grade_value)


    def list_grades(self):
        return self.grade_repo.list_all()
