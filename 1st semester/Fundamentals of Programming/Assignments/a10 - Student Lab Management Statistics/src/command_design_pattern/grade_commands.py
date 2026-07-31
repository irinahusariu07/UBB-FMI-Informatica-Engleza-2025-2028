"""
Commands for the grade related functionalities
"""
from src.command_design_pattern.student_commands import Command


class GradeStudentCommand(Command):
    def __init__(self, grade_repo, student_id, assignment_id, new_grade):
        self.grade_repo = grade_repo
        self.student_id = student_id
        self.assignment_id = assignment_id
        self.new_grade = new_grade
        self.old_grade = None

    def execute(self):
        # store the previous grade to allow undo
        grade_obj = self.grade_repo.find_by_ids(self.student_id, self.assignment_id)
        if grade_obj is None:
            raise ValueError("Assignment not assigned to student")
        self.old_grade = grade_obj.grade_value

        #update to new grade
        self.grade_repo.update_grade(self.student_id, self.assignment_id, self.new_grade)


    def undo(self):
        # restore old grade
        self.grade_repo.update_grade(self.student_id, self.assignment_id, self.old_grade, from_undo=True)