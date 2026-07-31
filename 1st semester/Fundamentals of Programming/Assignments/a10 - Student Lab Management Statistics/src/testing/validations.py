from src.errors import ValidationError

class StudentValidation:
    @staticmethod
    def validate(student):
        """
        Validates student data
        :param student: the student object
        :raises ValidationError: if student data is invalid
        """
        errors = []
        if not isinstance(student.student_id, int) or student.student_id <= 0:
            errors.append('Student ID is invalid. Must be positive.')
        if student.name.strip() == "":
            errors.append('Student name is empty.')
        if not isinstance(student.group, int) or student.group <= 0:
            errors.append('Student group is invalid. Must be positive.')
        if errors:
            raise ValidationError("\n".join(errors))

class AssignmentValidation:
    @staticmethod
    def validate(assignment):
        """
        Validates assignment data
        :param assignment: the assignment object
        :raises ValidationError: if assignment data is invalid
        """
        errors = []
        if not isinstance(assignment.assignment_id, int) or assignment.assignment_id <= 0:
            errors.append('Assignment ID is invalid. Must be positive.')
        if assignment.description.strip() == "":
            errors.append('Assignment description is empty.')
        if assignment.deadline.strip() == "":
            errors.append('Assignment deadline is empty.')
        if errors:
            raise ValidationError("\n".join(errors))

class GradeValidation:
    @staticmethod
    def validate(grade):
        """
        Validates grade data
        :param grade: the grade object
        :raises ValidationError: if grade data is invalid
        """
        errors = []
        if not isinstance(grade.student_id, int) or grade.student_id <= 0:
            errors.append('Student ID is invalid. Must be positive.')
        if not isinstance(grade.assignment_id, int) or grade.assignment_id <= 0:
            errors.append('Assignment ID is invalid. Must be positive.')
        try:
            value = float(grade.grade_value)
        except ValueError:
            errors.append('Grade value is invalid. Must be a float value')

        else:
            if not (0.0 <= grade.grade_value <= 10.0):
                errors.append('Grade value is invalid. Must be between 0.0 and 10.0')
        if errors:
            raise ValidationError("\n".join(errors))