"""
Where i have the assignment class related services
"""
from src.command_design_pattern.assignment_commands import AddAssignmentCommand, RemoveAssignmentCommand, UpdateAssignmentCommand, AssignToStudentCommand, AssignToGroupCommand
from src.domain.lab_planner import Assignment, Student, Grade
from src.errors import RepositoryError
from src.testing.validations import AssignmentValidation

class AssignmentService:
    def __init__(self, assignment_repo, grade_repo, student_repo, undo_manager):
        """
        :param assignment_repo: repository for Assignment obj
        :param grade_repo: repository for Grade obj
        :param student_repo: repository for Student obj
        """
        self.assignment_repo = assignment_repo
        self.grade_repo = grade_repo
        self.student_repo = student_repo
        self.undo_manager = undo_manager

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
        cmd = AddAssignmentCommand(self.assignment_repo, assignment)
        self.undo_manager.execute(cmd)

    def remove_assignment(self, assignment_id):
        """
        Remove an assignment
        :param assignment_id: the assignment id to remove
        Also removes the grades from the assignment
        """
        cmd = RemoveAssignmentCommand(self.assignment_repo, self.grade_repo, assignment_id)
        self.undo_manager.execute(cmd)

    def update_assignment(self, assignment_id, description, deadline):
        """
        Update an assignment
        :param assignment_id: assignment id
        :param description: assignment description - may be modified
        :param deadline: deadline - may be modified
        """
        old_assignment = self.assignment_repo.find_by_id(assignment_id)
        if old_assignment is None:
            raise RepositoryError("Assignment not found")
        new_assignment = Assignment(assignment_id, description, deadline)
        AssignmentValidation.validate(new_assignment)

        cmd = UpdateAssignmentCommand(self.assignment_repo, new_assignment, old_assignment)
        self.undo_manager.execute(cmd)

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
        student = self.student_repo.find_by_id(student_id)
        if student is None:
            raise RepositoryError(f"Student with ID {student_id} not found")

        # Check if assignment exists
        assignment = self.assignment_repo.find_by_id(assignment_id)
        if assignment is None:
            raise RepositoryError(f"Assignment with ID {assignment_id} not found")

        # Check if assignment is already assigned
        if self.grade_repo.find_by_ids(student_id, assignment_id) is None:
            #if we didnt find a correlation between student and assignment we use grade = None to assign
            cmd = AssignToStudentCommand(self.grade_repo, student_id, assignment_id)
            self.undo_manager.execute(cmd)

    def assign_to_group(self, assignment_id, group_number):
        """
        Assign assignment to a group - all students in group must recieve it
        :param assignment_id: the assignment id
        :param group_number: the number of the group that recieves the assignment
        """
        cmd = AssignToGroupCommand(self.student_repo, self.grade_repo, assignment_id, group_number)
        self.undo_manager.execute(cmd)

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

    def students_late_deadline(self):
        """
        All the students that are late in handling at least 1 assignment
        = deadline has passed and student still has ungraded assigment
        """
        current_day = 18
        current_month = 12
        current_year = 2025
        late_students = []

        for g in self.grade_repo.list_all():
            if g.grade_value is None:
                a = self.assignment_repo.find_by_id(g.assignment_id)
                deadline_date = (a.deadline).split("-")
                deadline_day = int(deadline_date[2])
                deadline_month = int(deadline_date[1])
                deadline_year = int(deadline_date[0])
                overdue = ((deadline_year < current_year) or
                    (deadline_year == current_year and deadline_month < current_month)
                    or (deadline_year == current_year and deadline_month == current_month and deadline_day < current_day))

                if overdue:
                    s = self.student_repo.find_by_id(g.student_id)
                    if s not in late_students:
                        late_students.append(s)

        return late_students



