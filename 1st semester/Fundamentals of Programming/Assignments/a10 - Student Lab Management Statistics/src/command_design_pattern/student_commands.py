"""
Commands for the student related functionalities
"""

class Command:
    def execute(self):
        raise NotImplementedError()
    def undo(self):
        raise NotImplementedError()

class AddStudentCommand(Command):
    def __init__(self, student_repo, student):
        self._student_repo = student_repo
        self._student = student

    def execute(self):
        self._student_repo.add(self._student)

    def undo(self):
        self._student_repo.remove(self._student.student_id)

class RemoveStudentCommand(Command):
    def __init__(self, student_repo, grade_repo, student_id):
        self._student_repo = student_repo
        self._grade_repo = grade_repo
        self._student_id = student_id

        self._deleted_student = None
        self._deleted_grades = []

    def execute(self):
        # save student
        self._deleted_student = self._student_repo.find_by_id(self._student_id)

        # save grades
        self._deleted_grades = [
            g for g in self._grade_repo.list_all()
            if g.student_id == self._student_id
        ]

        # delete grades
        for g in self._deleted_grades:
            self._grade_repo.remove(g.student_id, g.assignment_id)

        # delete student
        self._student_repo.remove(self._student_id)

    def undo(self):
        # restore student
        self._student_repo.add(self._deleted_student)

        # restore grades
        for g in self._deleted_grades:
            self._grade_repo.add(g)

class UpdateStudentCommand(Command):
    def __init__(self, student_repo, old_student, new_student):
        self._new_student = new_student
        self._old_student = old_student
        self._student_repo = student_repo

    def execute(self):
        self._student_repo.update(self._new_student)

    def undo(self):
        self._student_repo.update(self._old_student)

