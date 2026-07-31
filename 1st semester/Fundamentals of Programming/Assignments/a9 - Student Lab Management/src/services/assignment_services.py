"""
Where i have the assignment class related services
"""
from src.domain.lab_planner import Assignment, Student, Grade
from src.errors import RepositoryError
from src.testing.validations import AssignmentValidation

class AssignmentService:
    def __init__(self, assignment_repo, grade_repo, student_repo):
        """
        :param assignment_repo: repository for Assignment obj
        :param grade_repo: repository for Grade obj
        :param student_repo: repository for Student obj
        """
        self.assignment_repo = assignment_repo
        self.grade_repo = grade_repo
        self.student_repo = student_repo

    # FIRST FUNCTIONALITY
    def add_assignment(self, assignment_id, description, deadline):
        """
        Add a new assignment
        :param assignment_id: assignment id
        :param description: assignment description
        :param deadline: deadline
        """
        assignment = Assignment(assignment_id, description, deadline)
        AssignmentValidation.validate(assignment)
        self.assignment_repo.add(assignment)

    def remove_assignment(self, assignment_id):
        """
        Remove an assignment
        :param assignment_id: the assignment id to remove
        Also removes the grades from the assignment
        """
        # Remove all the grades
        for grade in self.grade_repo.list_all():
            if grade.assignment_id == assignment_id:
                self.grade_repo.remove(grade.student_id, grade.assignment_id)

        # Remove assignment
        self.assignment_repo.remove(assignment_id)

    def update_assignment(self, assignment_id, description, deadline):
        """
        Update an assignment
        :param assignment_id: assignment id
        :param description: assignment description - may be modified
        :param deadline: deadline - may be modified
        """
        assignment = Assignment(assignment_id, description, deadline)
        AssignmentValidation.validate(assignment)
        self.assignment_repo.update(assignment)

    def list_assignments(self):
        """
        List all assignments
        :return: a list of all assignments
        """
        return self.assignment_repo.list_all()

    def find_assignment_byID(self, assignment_id):
        """
        Find assignment by ID
        :param assignment_id: the assignment id
        :return: the assignment
        """
        return self.assignment_repo.find_by_id(assignment_id)

    #SECOND FUNCTIONALITY
    def assign_to_student(self, assignment_id, student_id):
        """
        Assign an assignment to a SINGLE student if not already assigned
        """
        # Check if student exists
        student = self. student_repo.find_by_id(student_id)
        if student is None:
            raise RepositoryError(f"Student with ID {student_id} not found")

        # Check if assignment exists
        assignment = self.assignment_repo.find_by_id(assignment_id)
        if assignment is None:
            raise RepositoryError(f"Assignment with ID {assignment_id} not found")

        # Check if assignment is already assigned
        if self.grade_repo.find_by_ids(student_id, assignment_id) is None:
            #if we didnt find a corellation between student and assignment we use grade = None to assign
            grade = Grade(None, student_id, assignment_id)
            self.grade_repo.add(grade)

    def assign_to_group(self, assignment_id, group_number):
        """
        Assign assignment to a group - all students in group must recieve it
        :param assignment_id: the assignment id
        :param group_number: the number of the group that recieves the assignment
        """
        students_in_group = [
            s for s in self.student_repo.list_all()
            if s.group == group_number and self.grade_repo.find_by_ids(s.student_id, assignment_id) is None
        ]
        for student in students_in_group:
            self.assign_to_student(assignment_id, student.student_id)

    def ungraded_assignment(self, student_id):
        """
        :param student_id: the student id for which i want to show the list of ungraded assignments
        :return: list of ungraded assignments
        """
        ungraded = []
        for assignment in self.assignment_repo.list_all():
            grade_obj = self.grade_repo.find_by_ids(student_id, assignment.assignment_id)
            if grade_obj is not None and grade_obj.grade_value is None:
                ungraded.append(assignment)
        return ungraded


