"""
Where i test the logic
"""
from src.services.assignment_services import AssignmentService
from src.services.student_services import StudentService
from src.testing.validations import StudentValidation, AssignmentValidation, GradeValidation
from src.domain.lab_planner import Student, Assignment, Grade
from src.errors import ValidationError, RepositoryError
from src.repository.MemoryRepo import MemoryStudentRepo, MemoryAssignmentRepo, MemoryGradeRepo
from src.services.grade_services import GradeService
from src.services.student_services import StudentService
from src.services.assignment_services import AssignmentService

#STUDENT TESTS

def test_valid_student():
    # Test a valid student - should not raise Error
    s = Student(1, "Ana", 912)
    StudentValidation.validate(s)

def test_invalid_student():
    # Test an invalid student
    try:
        s = Student(-1, "", -5)
        StudentValidation.validate(s)
        assert False, "ValidationError wasnt raised for invalid student"
    except ValidationError:
        pass


#ASSIGNMENT TEST

def test_valid_assignment():
    #Test a valid assignment - should not raise Error
    a = Assignment(1, "Homework 1", "2025 - 12 - 19")
    AssignmentValidation.validate(a)

def test_invalid_assignment():
    #Test an invalid assignment
    try:
        a = Assignment(-1, "", "")
        AssignmentValidation.validate(a)
        assert False, "ValidationError wasnt raised for invalid assignment"
    except:
        pass


# GRADE TEST
def test_valid_grade():
    #Test a valid grade - should not raise Error
    g = Grade(9.5, 1, 1)
    GradeValidation.validate(g)

def test_invalid_grade():
    #Test an invalid grade
    try:
        g = Grade("abc", -1, -1)
        GradeValidation.validate(g)
        assert False, "ValidationError wasnt raised for invalid grade"
    except ValidationError:
        pass

def test_repo_student_add():
    repo = MemoryStudentRepo()
    # Test ADD
    s1 = Student(1, "Ana", 912)
    repo.add(s1)
    assert len(repo.list_all()) == 1
    assert repo.find_by_id(1).name == "Ana"

    #cannot add duplicate
    try:
        repo.add(s1)
        assert False, "Expected RepoError to be raised"
    except RepositoryError:
        assert True

def test_repo_student_remove():
    repo = MemoryStudentRepo()
    # Test REMOVE
    s1 = Student(1, "Ana", 912)
    repo.add(s1)
    repo.remove(1)
    assert len(repo.list_all()) == 0
    assert repo.find_by_id(1) is None

def test_repo_student_update():
    # Test UPDATE
    repo = MemoryStudentRepo()
    s1 = Student(1, "Ana", 912)
    repo.add(s1)
    updated = Student(1, "Anabell", 915)
    repo.update(updated)
    result = repo.find_by_id(1)
    assert result.name == "Anabell"
    assert result.group == 915

def test_repo_assignment_add():
    repo = MemoryAssignmentRepo()
    # Test ADD
    a1 = Assignment(1, "Homework 1", "2025 - 12 - 19")
    repo.add(a1)
    assert len(repo.list_all()) == 1
    assert repo.find_by_id(1).description == "Homework 1"

    #cannot add duplicate
    try:
        repo.add(a1)
        assert False, "Expected RepoError to be raised"
    except RepositoryError:
        assert True

def test_repo_assignment_remove():
    repo = MemoryAssignmentRepo()
    # Test REMOVE
    a1 = Assignment(1, "Homework 1", "2025 - 12 - 19")
    repo.add(a1)
    repo.remove(1)
    assert len(repo.list_all()) == 0
    assert repo.find_by_id(1) is None

def test_repo_assignment_update():
    repo = MemoryAssignmentRepo()
    # Test UPDATE
    a1 = Assignment(1, "Homework 1", "2025 - 12 - 19")
    repo.add(a1)

    updated = Assignment(1, "First Homework", "2025 - 12 - 20")
    repo.update(updated)
    result = repo.find_by_id(1)
    assert result.description == "First Homework"
    assert result.deadline == "2025 - 12 - 20"

def test_repo_grade_add():
    repo = MemoryGradeRepo()
    # Test ADD
    g1 = Grade(7.6, 1, 1)
    repo.add(g1)
    assert len(repo.list_all()) == 1
    assert repo.find_by_ids(1, 1).grade_value == 7.6

    #Cannot add grade if already existing
    try:
        repo.add(g1)
        assert False, "Expected RepoError to be raised"
    except RepositoryError:
        assert True

def test_repo_grade_remove():
    repo = MemoryGradeRepo()
    # Test REMOVE
    g1 = Grade(7.6, 1, 1)
    repo.add(g1)
    repo.remove(1,1)
    assert len(repo.list_all()) == 0
    assert repo.find_by_ids(1, 1) is None

def test_student_services():
    student_repo = MemoryStudentRepo()
    grade_repo = MemoryGradeRepo()
    student_service = StudentService(student_repo, grade_repo)

    #ADD student
    student_service.add_student(1, "Ana", 912)
    assert len(student_service.list_students()) == 1

    #UPDATE student
    student_service.update_student(1, "Annabell", 915)
    s = student_service.find_student_byID(1)
    assert s.name == "Annabell" and s.group == 915

    # Assign a grade manually for cascade testing
    grade_repo.add(Grade(None, 1, 1))

    # Remove student -> grade should also be removed
    student_service.remove_student(1)
    assert len(student_service.list_students()) == 0
    assert len(grade_repo.list_all()) == 0

def test_assignment_services():
    assignment_repo = MemoryAssignmentRepo()
    student_repo = MemoryStudentRepo()
    grade_repo = MemoryGradeRepo()
    assignment_service = AssignmentService(assignment_repo, grade_repo, student_repo)

    # ADD student + assigment
    student_repo.add(Student(1, "Ana", 912))
    student_repo.add(Student(2, "Bob", 912))
    assignment_service.add_assignment(1, "HW1", "2025-12-20")

    # ASSIGN to student
    assignment_service.assign_to_student(1, 1)
    assert grade_repo.find_by_ids(1,1) is not None

    # ASSIGN to group
    assignment_service.assign_to_group(1, 912)
    # Ana already has it, Bob should get it
    assert grade_repo.find_by_ids(2, 1) is not None

    # REMOVE assignment -> removes grades
    assignment_service.remove_assignment(1)
    assert assignment_repo.find_by_id(1) is None
    assert len(grade_repo.list_all()) == 0


def test_grade_services():
    grade_repo = MemoryGradeRepo()
    student_repo = MemoryStudentRepo()
    assignment_repo = MemoryAssignmentRepo()
    grade_service = GradeService(grade_repo, student_repo, assignment_repo)

    # ADD student and assignment
    student_repo.add(Student(1, "Ana", 912))
    assignment_repo.add(Assignment(1, "HW1", "2025-12-20"))

    # Assign assignment to student (grade_value is None
    grade_repo.add(Grade(None, 1, 1))

    # GRADE student
    grade_service.grade_student(1,1, 9.5)
    assert grade_repo.find_by_ids(1,1).grade_value == 9.5

    # Trying to grade again = error
    try:
        grade_service.grade_student(1,1, 8)
        assert False
    except:
        assert True

    # Trying to grade unassigned student
    try:
        grade_service.grade_student(2,1, 9)
        assert False
    except RepositoryError:
        assert True

def run_tests():
    test_valid_student()
    test_valid_assignment()
    test_valid_grade()
    test_invalid_student()
    test_invalid_assignment()
    test_invalid_grade()
    test_repo_student_add()
    test_repo_student_remove()
    test_repo_student_update()
    test_repo_assignment_add()
    test_repo_assignment_remove()
    test_repo_assignment_update()
    test_repo_grade_add()
    test_repo_grade_remove()
    test_student_services()
    test_assignment_services()
    test_grade_services()


    print("All tests passed")

if __name__ == '__main__':
    run_tests()

