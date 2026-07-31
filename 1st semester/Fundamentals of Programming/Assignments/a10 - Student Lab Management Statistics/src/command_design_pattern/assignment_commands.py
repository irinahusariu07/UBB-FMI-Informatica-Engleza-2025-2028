"""
Commands for the assignment related functionalities
"""
from src.command_design_pattern.student_commands import Command
from src.domain.lab_planner import Grade


class AddAssignmentCommand(Command):

    def __init__(self, assignment_repo, assignment):
        self.assignment_repo = assignment_repo
        self.assignment = assignment

    def execute(self):
        self.assignment_repo.add(self.assignment)

    def undo(self):
        self.assignment_repo.remove(self.assignment.assignment_id)


class RemoveAssignmentCommand(Command):

    def __init__(self, assignment_repo, grade_repo, assignment_id):
        self.assignment_repo = assignment_repo
        self.grade_repo = grade_repo
        self.assignment_id = assignment_id

        self._deleted_assignment = None
        self._deleted_grades = []

    def execute(self):

        # save assignment
        self._deleted_assignment = self.assignment_repo.find_by_id(self.assignment_id)

        # save grades
        self._deleted_grades = [
            g for g in self.grade_repo.list_all()
            if g.assignment_id == self.assignment_id
        ]

        # delete grades
        for g in self._deleted_grades:
            self.grade_repo.remove(g.student_id, g.assignment_id)

        # delete assignment
        self.assignment_repo.remove(self.assignment_id)

    def undo(self):
        # restore assignment
        self.assignment_repo.add(self._deleted_assignment)

        # restore grades
        for g in self._deleted_grades:
            self.grade_repo.add(g)

class UpdateAssignmentCommand(Command):

    def __init__(self, assignment_repo, new_assignment, old_assignment):
        self.assignment_repo = assignment_repo
        self.new_assignment = new_assignment
        self.old_assignment = old_assignment

    def execute(self):
        self.assignment_repo.update(self.new_assignment)

    def undo(self):
        self.assignment_repo.update(self.old_assignment)

class AssignToStudentCommand(Command):
    def __init__(self, grade_repo, student_id, assignment_id):
        self.grade_repo = grade_repo
        self.student_id = student_id
        self.assignment_id = assignment_id

    def execute(self):
        grade = Grade(None, self.student_id, self.assignment_id)
        self.grade_repo.add(grade)

    def undo(self):
        self.grade_repo.remove(self.student_id, self.assignment_id)

class AssignToGroupCommand(Command):
    def __init__(self, student_repo, grade_repo, assignment_id, group_number):
        self.student_repo = student_repo
        self.grade_repo = grade_repo
        self.assignment_id = assignment_id
        self.group_number = group_number

        self.commands = []

    def execute(self):
        students = [
            s for s in self.student_repo.list_all()
            if s.group == self.group_number
            and self.grade_repo.find_by_ids(s.student_id, self.assignment_id) is None
        ]
        for s in students:
            cmd = AssignToStudentCommand(self.grade_repo, s.student_id, self.assignment_id)
            cmd.execute()
            self.commands.append(cmd)

    def undo(self):
        for cmd in reversed(self.commands):
            cmd.undo()