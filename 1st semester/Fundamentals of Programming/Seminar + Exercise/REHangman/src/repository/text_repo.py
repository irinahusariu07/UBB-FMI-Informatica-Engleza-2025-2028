from domain.sentence import Sentence

class TextFileRepository:
    def __init__(self, filename):
        self.filename = filename
        self.sentences = []
        self._load_file()

        if len(self.sentences) == 0:
            self._default_sentences()

    def _default_sentences(self):
        defaults = [
            "I want gummies",
            "Watermelon sugar",
            "Fundamentals of Programming",
            "Valentine",
            "Slimshady"
        ]
        for d in defaults:
            self.sentences.append(Sentence(d))
        self._save_file()

    def _load_file(self):
        self.sentences = []
        try:
            with open(self.filename, "r") as file:
                for line in file:
                    line = line.strip()
                    self.sentences.append(Sentence(line))

        except FileNotFoundError:
            return("File not found")

    def _save_file(self):
        with open(self.filename, 'w') as file:
            for sentence in self.sentences:
                file.write(f"{sentence.sentence_text}\n")

    def get_sentences(self):
        return self.sentences.copy()

    def add(self, entity: Sentence):
        self.sentences.append(entity)
        self._save_file()
