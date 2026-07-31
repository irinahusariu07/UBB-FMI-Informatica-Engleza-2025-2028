from src.repository.settings_reader import load_settings
from faker import Faker
from src.domain.lab_planner import Student, Assignment, Grade
from src.services.student_services import StudentService
from src.services.assignment_services import AssignmentService
from src.services.grade_services import GradeService
from src.repository.MemoryRepo import MemoryStudentRepo, MemoryAssignmentRepo, MemoryGradeRepo
from src.repository.TextFileRepo import TextFileStudentRepo, TextFileAssignmentRepo, TextFileGradeRepo
from src.repository.BinaryRepo import BinaryStudentRepo, BinaryGradeRepo, BinaryFileAssignmentRepo
from src.ui.console import Console
from src.testing.tests import run_tests
import random


# Generate defaults with Faker
def populate_defaults(student_service, assignment_service, grade_service):
    fake = Faker()
    existing_students = student_service.list_students()
    existing_assignments = assignment_service.list_assignments()

    if len(existing_students) == 0:
        for i in range(1, 21):
            student_service.add_student(i, fake.name(), fake.random_int(min=111, max=1119))
    if len(existing_assignments) == 0:
        for i in range(1, 21):
            assignment_service.add_assignment(i, f"Assignment {i}", fake.date_this_year().isoformat())

    students = student_service.list_students()
    assignments = assignment_service.list_assignments()

    for student in students:
        for assignment in assignments:
            # Randomly decide if the student gets this assignment (like 50% chance)
            if random.choice([True, False]):
                try:
                    # grade_value is None initially
                    grade_service.add_grade(None, student.student_id, assignment.assignment_id)
                except Exception:
                    # Skip if already exists
                    pass


def main():
    run_tests()

    # Load settings
    settings = load_settings()
    repo_type = settings.get("repository", "memory").lower()
    students_file = settings.get("students", "students.txt")
    assignments_file = settings.get("assignments", "assignments.txt")
    grades_file = settings.get("grades", "grades.txt")

    if repo_type == "memory":
        student_repo = MemoryStudentRepo()
        assignment_repo = MemoryAssignmentRepo()
        grade_repo = MemoryGradeRepo()
        print("Using memory repositories")

    elif repo_type == "textfile":
        student_repo = TextFileStudentRepo(students_file)
        assignment_repo = TextFileAssignmentRepo(assignments_file)
        grade_repo = TextFileGradeRepo(grades_file)
        print("Using text file repositories")

    elif repo_type == "binaryfile":
        student_repo = BinaryStudentRepo(students_file)
        assignment_repo = BinaryFileAssignmentRepo(assignments_file)
        grade_repo = BinaryGradeRepo(grades_file)
        print("Using binary file repositories")

    else:
        # Default
        print("Invalid repository in settings! Using memory repositories.")
        student_repo = MemoryStudentRepo()
        assignment_repo = MemoryAssignmentRepo()
        grade_repo = MemoryGradeRepo()

    # Initialize services
    student_service = StudentService(student_repo, grade_repo)
    assignment_service = AssignmentService(assignment_repo, grade_repo, student_repo)
    grade_service = GradeService(grade_repo, student_repo, assignment_repo)

    populate_defaults(student_service, assignment_service, grade_service)
    ui = Console(student_service, assignment_service, grade_service)
    ui.start()


if __name__ == "__main__":
    main()
