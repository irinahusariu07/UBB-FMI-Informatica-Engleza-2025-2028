"""
Where i store executed commands
"""

class UndoManager:
    def __init__(self):
        self._undo_stack = []
        self._redo_stack = []

    def execute(self, command):
        """
        Execute command and store it for undo
        """
        command.execute()
        self._undo_stack.append(command)
        self._redo_stack.clear()

    def undo(self):
        """
        Undo last command
        """
        if not self._undo_stack:
            raise Exception("Nothing to undo")

        command = self._undo_stack.pop()
        command.undo()
        self._redo_stack.append(command)

    def redo(self):
        """
        Redo last undone command
        """
        if not self._redo_stack:
            raise Exception("Nothing to redo")

        command = self._redo_stack.pop()
        command.execute()
        self._undo_stack.append(command)