"""
Console
"""
class Console:
    def __init__(self, student_service, assignment_service, grade_service, undo_manager):
        self.student_service = student_service
        self.assignment_service = assignment_service
        self.grade_service = grade_service
        self.undo_manager = undo_manager

    def show_menu(self):
        print("\n===== LAB PLANNER =====")
        print("1. Manage STUDENTS")
        print("2. Manage ASSIGNMENTS")
        print("3. Assign assignment to STUDENT")
        print("4. Assign assignment to GROUP")
        print("5. Grade a student")
        print("6. List grades")
        print("7. List all students with given assignment, sorted descending by grade")
        print("8. List all students that are late in handing in at least one assignment")
        print("9. List students with the best grades situation, descending")
        print("UNDO")
        print("REDO")
        print("0. Exit")

    def show_student_menu(self):
        print("\n --- Manage STUDENTS ---")
        print("1. Add student")
        print("2. Remove student")
        print("3. Update student")
        print("4. List students")
        print("0. Back")

    def show_assignment_menu(self):
        print("\n--- Manage ASSIGNMENTS ---")
        print("1. Add assignment")
        print("2. Remove assignment")
        print("3. Update assignment")
        print("4. List assignments")
        print("0. Back")

    def start(self):
        while True:
            self.show_menu()
            choice = input("Enter your choice: ").strip()

            if choice == "0":
                print("Goodbye")
                break

            elif choice.lower() == "undo":
                try:
                    self.undo_manager.undo()
                    print("Undo successful")
                except Exception as e:
                    print(e)

            elif choice.lower() == "redo":
                try:
                    self.undo_manager.redo()
                    print("Redo successful")
                except Exception as e:
                    print(e)

            elif choice == "1":
                while True:
                    self.show_student_menu()
                    choice = input("Enter your choice: ").strip()

                    if choice == "0":
                        break

                    if choice == "1":
                        try:
                            student_id = int(input("Student ID: "))
                        except ValueError:
                            print("Invalid student ID. Must be a number.")
                            continue
                        name = input("Student name: ")
                        try:
                            group = int(input("Student group: "))
                        except ValueError:
                            print("Invalid group. Must be a number.")
                            continue
                        try:
                            self.student_service.add_student(student_id, name, group)
                            print("Student added successfully")
                        except Exception as e:
                            print(e)

                    elif choice == "2":
                        try:
                            student_id = int(input("Student ID to remove: "))
                        except ValueError:
                            print("Invalid student ID. Must be a number.")
                            continue
                        try:
                            self.student_service.remove_student(student_id)
                            print("Student removed successfully")
                        except Exception as e:
                            print(e)

                    elif choice == "3":
                        try:
                            student_id = int(input("Student ID to update: "))
                        except ValueError:
                            print("Invalid student ID. Must be a number.")
                            continue
                        name = input("Student name: ")
                        try:
                            group = int(input("Student group: "))
                        except ValueError:
                            print("Invalid group. Must be a number.")
                            continue
                        try:
                            self.student_service.update_student(student_id, name, group)
                            print("Student updated successfully")
                        except Exception as e:
                            print(e)

                    elif choice == "4":
                        students = self.student_service.list_students()
                        if not students:
                            print("No students found")
                        else:
                            for student in students:
                                print(f"Student ID: {student.student_id}, Name: {student.name}, Group: {student.group}")

                    else:
                        print("Invalid choice")

            elif choice == "2":
                while True:
                    self.show_assignment_menu()
                    choice = input("Enter your choice: ").strip()

                    if choice == "0":
                        break

                    if choice == "1":
                        try:
                            assignment_id = int(input("Assignment ID: "))
                        except ValueError:
                            print("Invalid assignment ID. Must be a number.")
                            continue
                        description = input("Description: ")
                        deadline = input("Deadline (YYYY - MM - DD): ")
                        try:
                            self.assignment_service.add_assignment(assignment_id, description, deadline)
                            print("Assignment added successfully")
                        except Exception as e:
                            print(e)

                    elif choice == "2":
                        try:
                            assignment_id = int(input("Assignment ID to remove: "))
                        except ValueError:
                            print("Invalid assignment ID. Must be a number.")
                            continue
                        try:
                            self.assignment_service.remove_assignment(assignment_id)
                            print("Assignment removed successfully")
                        except Exception as e:
                            print(e)

                    elif choice == "3":
                        try:
                            assignment_id = int(input("Assignment ID to update: "))
                        except ValueError:
                            print("Invalid assignment ID. Must be a number.")
                            continue
                        description = input("Description: ")
                        deadline = input("Deadline (YYYY - MM - DD): ")
                        try:
                            self.assignment_service.update_assignment(assignment_id, description, deadline)
                            print("Assignment updated successfully")
                        except Exception as e:
                            print(e)

                    elif choice == "4":
                        assignments = self.assignment_service.list_assignments()
                        if not assignments:
                            print("No assignments found")
                        else:
                            for assignment in assignments:
                                print(f"Assignment ID: {assignment.assignment_id}, Description: {assignment.description}, Deadline: {assignment.deadline}")

                    else:
                        print("Invalid choice")

            elif choice == "3":
                try:
                    assignment_id = int(input("Assignment ID: "))
                    student_id = int(input("Student ID: "))
                    self.assignment_service.assign_to_student(assignment_id, student_id)
                    print("Assignment assigned to student successfully")
                except ValueError:
                    print("Invalid ID. Must be a number.")
                except Exception as e:
                    print(e)

            elif choice == "4":
                try:
                    assignment_id = int(input("Assignment ID: "))
                    group = int(input("Group number: "))
                    self.assignment_service.assign_to_group(assignment_id, group)
                    print("Assignment assigned to group successfully.")
                except ValueError:
                    print("Invalid input. Must be a number.")
                except Exception as e:
                    print(e)


            elif choice == "5":

                # Grade a student
                try:
                    student_id = int(input("Student ID: "))
                    # Get ungraded assignments for this student
                    ungraded = self.assignment_service.ungraded_assignment(student_id)
                    if not ungraded:
                        print("No ungraded assignments for this student.")
                    else:
                        print("Ungraded assignments:")
                        for i, assignment in enumerate(ungraded, 1):
                            print(
                                f"{i}. Assignment ID: {assignment.assignment_id}, Description: {assignment.description}, Deadline: {assignment.deadline}")

                        selection = int(input("Select assignment to grade by number: "))
                        if not isinstance(selection, int) or selection < 1 or selection > len(ungraded):
                            print("Invalid selection.")

                        else:
                            assignment_to_grade = ungraded[selection - 1]
                            grade_value = float(input("Grade (0-10): "))
                            self.grade_service.grade_student(student_id, assignment_to_grade.assignment_id, grade_value)
                            print("Student graded successfully.")

                except ValueError:
                    print("Invalid input, must be a number.")
                except Exception as e:
                    print(e)


            elif choice == "6":

                # List all grades
                grades = self.grade_service.list_grades()
                if not grades:
                    print("No grades found.")
                else:
                    for g in grades:
                        print(f"Student ID: {g.student_id}, Assignment ID: {g.assignment_id}, Grade: {g.grade_value}")

            elif choice == "7":
                try:
                    search_assignment_id = int(input("Assignment ID: "))
                except ValueError:
                    print("Invalid assignment ID. Must be a number.")
                    continue
                list_of_students = []
                list_of_students = self.student_service.student_with_given_assignment(search_assignment_id)
                if not list_of_students:
                    print("No graded students found for this assignment.")
                else:
                    print("Students with assignment", search_assignment_id)
                    for student, grade in list_of_students:
                        print(f"ID: {student.student_id}, Name: {student.name}, Grade: {grade}")

            elif choice == "8":
                list_of_students = []
                list_of_students = self.assignment_service.students_late_deadline()
                if not list_of_students:
                    print("All students handed their assignments on time")
                else:
                    print("Students that handed their assignment late")
                    for s in list_of_students:
                        print(s)

            elif choice == "9":
                list_of_students = []
                list_of_students = self.student_service.best_student_situation()
                if not list_of_students:
                    print("No students have grades on their assignments")
                else:
                    print("Students with the best grades situation")
                    for s, avg in list_of_students:
                        print(f"ID: {s.student_id}, Name: {s.name}, Grade average: {avg:.2f}")

            else:
                print("Invalid choice")
