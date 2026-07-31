import random
class HangmanConsole():
    def __init__(self, service):
        self.service = service

    def run(self):
        print("Possible choices:")

        print("Add a sentence - add <s>")
        print("Start guessing game - start")
        print("Exit guessing game - exit")

        history = []
        for s in self.service.all_sentences():
            history.append(s.sentence_text.lower())

        full_hangman = "hangman"

        while True:
            try:
                command = input("Enter a command:")
                parts = command.split(maxsplit=1)
                if not parts:
                    print("Invalid command")
                    continue
                cmd = parts[0]
                if len(parts) > 1:
                    args = parts[1]
                else:
                    args = ""

                if cmd == "add":
                    s = args.strip().lower()
                    if s in history:
                        print("Duplicate sentence")
                        continue

                    try:
                        self.service.add_sentence(s)
                        history.append(s)
                        print("Sentence added")
                    except ValueError as ve:
                        print(ve)

                elif cmd == "start":
                    random_number = random.randint(0, len(history) - 1)
                    hm = []
                    count = 0
                    random_sentence = self.service.start_game(random_number)
                    guess_sentence = self.service.show_hangman(random_sentence, " ")
                    print("Your sentence is:")
                    print(guess_sentence)

                    while "".join(hm) != full_hangman and "".join(guess_sentence) != random_sentence:
                        letter = input("Enter a letter:")
                        correct_letter, guess_sentence = self.service.play_game(random_sentence, guess_sentence, letter)
                        if correct_letter == True:
                            print(f"{letter} is a good choice")
                            print(guess_sentence)
                        elif correct_letter == False:
                            print(f"{letter} is not in the sentence")
                            hm.append(full_hangman[count])
                            count += 1
                            print(hm)
                            if len(hm) == len(full_hangman):
                                print("Game over! You lose!")
                                print(f"Sentence: {random_sentence}")
                            else:
                                print(guess_sentence)

                    if "".join(guess_sentence) == random_sentence:
                        print("You won!")

                elif cmd == "exit":
                   print("Exiting game...")
                   break

                else:
                    print("Invalid command")

            except ValueError as ve:
                print(ve)










