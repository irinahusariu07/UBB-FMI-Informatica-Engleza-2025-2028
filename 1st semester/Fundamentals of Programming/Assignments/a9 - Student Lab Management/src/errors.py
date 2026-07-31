"""
Where i define Errors to be raised
"""

class ValidationError(Exception):
    """
    Raised when an error occurs during validation of input data
    """
    pass

class RepositoryError(Exception):
    """
    Raised for repo related issues - duplicates, missing ID...
    """
    pass
