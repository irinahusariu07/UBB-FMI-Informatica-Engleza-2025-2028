from domain.sentence import Sentence


class HangmanService:
    def __init__(self, repo):
        self.repo = repo

    def all_sentences(self):
        return self.repo.get_sentences()

    def add_sentence(self, sentence):
        list = sentence.split()
        if len(list) == 0:
            raise ValueError("sentence must contain at least one word")
        for i in range(len(list)):
            if len(list[i]) < 3:
                raise ValueError("the words in the sentence must contain at least 3 letters")
        s = Sentence(sentence)
        self.repo.add(s)

    def start_game(self, random_sentence):
        sentence_number = 0
        for s in self.all_sentences():
            if sentence_number == random_sentence:
                chosen_sentence = s
                break
            sentence_number += 1
        result = chosen_sentence.sentence_text
        return result

    def show_hangman(self, result, character = " "):
        first_letter = result[0]
        last_letter = result[-1]
        hangman_style = []
        new_word = False
        for j in range(len(result)):
            if result[j] == first_letter: #daca e prima litera a propozitiei - pun
                hangman_style.append(first_letter)
            elif result[j] == last_letter: #daca e ultima litera a propozitiei - pun
                hangman_style.append(last_letter)
            elif result[j] == " ": #daca e spatiu pun spatiu
                hangman_style.append(" ")
                new_word = True
            elif result[j] != " " and new_word: #daca e un cuvant nou ii afisez prima litera
                hangman_style.append(result[j])
                new_word = False
            elif result[j+1] == " " and j+1 < len(result): #daca e ultima litera dintr un cuvant afisez
                hangman_style.append(result[j+1])
            elif result[j] == character:
                hangman_style.append(character)
            else:
                hangman_style.append("_")

        return hangman_style

    def play_game(self, original_sentence, current_hidden, letter):
        letter = letter.strip().lower()
        found = False
        new_aspect = []

        for i in range(len(original_sentence)):
            if original_sentence[i].lower() == letter:
                new_aspect.append(original_sentence[i])
                found = True
            else:
                new_aspect.append(current_hidden[i])

        return found, new_aspect




