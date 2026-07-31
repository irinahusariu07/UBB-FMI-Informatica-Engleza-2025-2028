class Sentence:
    def __init__(self, sentence_text):
        self.__sentence_text = sentence_text

    @property
    def sentence_text(self):
        return self.__sentence_text

    def __str__(self):
        return f"{self.__sentence_text}"